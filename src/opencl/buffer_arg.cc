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
#include "opencl/buffer_arg.h"

namespace Lnn {

BufferArg::BufferArg(std::shared_ptr<ArgBuffer> buffer, Type type)
	: type(type), buffer(buffer) {}

BufferArg::~BufferArg() { buffer->deleteClBuffer(); }

bool BufferArg::isIn() const {
	return Type::IN == type || Type::IN_OUT == type;
}

bool BufferArg::isOut() const {
	return Type::OUT == type || Type::IN_OUT == type;
}

void BufferArg::input(ArgInputContext &ctx) {
	ctx.getKernel().setArg(
		ctx.getIndexAndIncrement(),
		buffer->createClBuffer(ctx.getContext(), ctx.getDevice()));
	if (isIn()) {
		buffer->updateClBuffer(ctx.getQueue());
	}
}

void BufferArg::output(const cl::CommandQueue &queue) {
	buffer->updateBuffer(isOut(), queue);
}

}; // namespace Lnn
