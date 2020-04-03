/*
 * Copyright (c) 2019, 2020, Xianguang Zhou <xianguang.zhou@outlook.com>. All
 * rights reserved.
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
#ifndef LNN_CALLING_H_
#define LNN_CALLING_H_

#include "arg.h"
#include "buffer_arg.h"
#include "buffer_array.h"
#include "cache_arg.h"
#include "opencl.h"
#include "program.h"
#include "range.h"
#include "scalar_arg.h"
#include <list>
#include <memory>
#include <string>

namespace Lnn {

class Calling {
  public:
	explicit Calling(const Program &program,
					 const std::string &function = "run");
	virtual ~Calling() = default;

	Calling &arg(std::shared_ptr<Arg> arg);

	template <typename T> Calling &arg(std::shared_ptr<ScalarArg<T>> arg) {
		this->args.push_back(arg);
		return *this;
	}
	Calling &arg(cl_float number);
	Calling &arg(cl_double number);
	Calling &arg(cl_short number);
	Calling &arg(cl_int number);
	Calling &arg(cl_long number);

	Calling &arg(std::shared_ptr<BufferArg> bufferArg);
	template <typename T>
	Calling &arg(std::shared_ptr<BufferArray<T>> bufferArray,
				 BufferArg::Type type) {
		return arg(std::make_shared<BufferArg>(bufferArray, type));
	}
	template <typename T>
	Calling &in(std::shared_ptr<BufferArray<T>> bufferArray) {
		return arg(
			std::make_shared<BufferArg>(bufferArray, BufferArg::Type::IN));
	}
	template <typename T>
	Calling &out(std::shared_ptr<BufferArray<T>> bufferArray) {
		return arg(
			std::make_shared<BufferArg>(bufferArray, BufferArg::Type::OUT));
	}
	template <typename T>
	Calling &inOut(std::shared_ptr<BufferArray<T>> bufferArray) {
		return arg(
			std::make_shared<BufferArg>(bufferArray, BufferArg::Type::IN_OUT));
	}

	Calling &cache(size_t size);
	Calling &cache(CacheArg::Type type, size_t number);
	Calling &cache(size_t typeSize, size_t number);

	Calling &pass(std::shared_ptr<Range> range);

	Calling &at(std::shared_ptr<cl::Device> device);

	void execute();

  private:
	std::shared_ptr<cl::Context> context;
	std::shared_ptr<cl::Program> program;
	std::string function;
	std::list<std::shared_ptr<Arg>> args;
	std::list<std::shared_ptr<Range>> ranges;
	std::shared_ptr<cl::Device> device;
};
}; // namespace Lnn

#endif
