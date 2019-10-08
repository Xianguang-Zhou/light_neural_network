/*
 * Copyright (c) 2019, Xianguang Zhou <xianguang.zhou@outlook.com>. All rights
 * reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
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
