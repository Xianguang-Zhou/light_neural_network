/*
 * Copyright (c) 2019, Xianguang Zhou <xianguang.zhou@outlook.com>. All rights
 * reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
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
