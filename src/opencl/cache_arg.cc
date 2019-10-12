/*
 * Copyright (c) 2019, Xianguang Zhou <xianguang.zhou@outlook.com>. All rights
 * reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include "opencl/cache_arg.h"

namespace Lnn {

CacheArg::CacheArg(Type type, size_t number)
	: CacheArg(static_cast<size_t>(type), number) {}

CacheArg::CacheArg(size_t typeSize, size_t number) : size(typeSize * number) {}

CacheArg::CacheArg(size_t size) : size(size) {}

void CacheArg::input(ArgInputContext &ctx) {
	if (!clBuffer) {
		clBuffer = std::make_unique<cl::Buffer>(*ctx.getContext(),
												CL_MEM_READ_WRITE, size);
	}
	ctx.getKernel().setArg(ctx.getIndexAndIncrement(), *clBuffer);
}

}; // namespace Lnn
