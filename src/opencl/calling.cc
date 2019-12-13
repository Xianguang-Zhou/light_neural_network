/*
 * Copyright (c) 2019, Xianguang Zhou <xianguang.zhou@outlook.com>. All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "opencl/calling.h"
#include "opencl/cl_exception.h"

namespace Lnn {

using cl::CommandQueue;
using cl::Kernel;
using std::make_shared;
using std::shared_ptr;
using std::string;

Calling::Calling(const Program &program, const string &function)
	: context(program.context), program(program.program), function(function) {}

Calling::~Calling() {}

Calling &Calling::arg(shared_ptr<Arg> arg) {
	args.push_back(arg);
	return *this;
}

Calling &Calling::arg(cl_float number) {
	return arg(make_shared<FloatArg>(number));
}

Calling &Calling::arg(cl_double number) {
	return arg(make_shared<DoubleArg>(number));
}

Calling &Calling::arg(cl_short number) {
	return arg(make_shared<ShortArg>(number));
}

Calling &Calling::arg(cl_int number) {
	return arg(make_shared<IntArg>(number));
}

Calling &Calling::arg(cl_long number) {
	return arg(make_shared<LongArg>(number));
}

Calling &Calling::arg(shared_ptr<BufferArg> bufferArg) {
	this->args.push_back(bufferArg);
	return *this;
}

Calling &Calling::cache(size_t size) {
	this->args.push_back(make_shared<CacheArg>(size));
	return *this;
}

Calling &Calling::cache(CacheArg::Type type, size_t number) {
	this->args.push_back(make_shared<CacheArg>(type, number));
	return *this;
}

Calling &Calling::cache(size_t typeSize, size_t number) {
	this->args.push_back(make_shared<CacheArg>(typeSize, number));
	return *this;
}

Calling &Calling::pass(shared_ptr<Range> range) {
	this->ranges.push_back(range);
	return *this;
}

Calling &Calling::at(shared_ptr<cl::Device> device) {
	this->device = device;
	return *this;
}

void Calling::execute() {
	if (ranges.empty()) {
		throw CLException("Ranges is empty.");
	}
	if (!device) {
		throw CLException("Device is not specified.");
	}
	try {
		CommandQueue queue(*context, *device);
		Kernel kernel(*program, function.c_str());
		ArgInputContext argInputContext(context, device, kernel, queue);
		for (shared_ptr<Arg> arg : args) {
			arg->input(argInputContext);
		}
		if (ranges.size() > 1) {
			cl_uint passIdArgIndex = static_cast<cl_uint>(args.size());
			cl_int passId = 0;
			for (shared_ptr<Range> range : ranges) {
				kernel.setArg(passIdArgIndex, passId);
				range->putToQueue(queue, kernel);
				++passId;
			}
		} else {
			ranges.front()->putToQueue(queue, kernel);
		}
		for (shared_ptr<Arg> arg : args) {
			arg->output(queue);
		}
		queue.finish();
		args.clear();
	} catch (const cl::Error &error) {
		throw CLException(error);
	}
}

}; // namespace Lnn
