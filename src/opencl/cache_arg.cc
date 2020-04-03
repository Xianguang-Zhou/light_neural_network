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
