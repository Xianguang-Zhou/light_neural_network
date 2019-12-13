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
#ifndef LNN_ARG_H_
#define LNN_ARG_H_

#include "opencl.h"
#include <memory>

namespace Lnn {

class ArgInputContext {
  public:
	explicit ArgInputContext(std::shared_ptr<cl::Context> context,
							 std::shared_ptr<cl::Device> device,
							 cl::Kernel &kernel, const cl::CommandQueue &queue)
		: context(context), device(device), kernel(kernel), queue(queue) {}
	std::shared_ptr<cl::Context> getContext() const { return context; }
	std::shared_ptr<cl::Device> getDevice() const { return device; }
	cl::Kernel &getKernel() const { return kernel; }
	const cl::CommandQueue &getQueue() const { return queue; }
	cl_uint getIndexAndIncrement() { return index++; }

  private:
	std::shared_ptr<cl::Context> context;
	std::shared_ptr<cl::Device> device;
	cl::Kernel &kernel;
	const cl::CommandQueue &queue;
	cl_uint index = 0;
};

class Arg {
  public:
	virtual void input(ArgInputContext &ctx) = 0;
	virtual void output(const cl::CommandQueue &queue){};
	virtual ~Arg() = default;
};
}; // namespace Lnn

#endif
