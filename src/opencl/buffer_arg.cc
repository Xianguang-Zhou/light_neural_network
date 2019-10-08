/*
 * Copyright (c) 2019, Xianguang Zhou <xianguang.zhou@outlook.com>. All rights
 * reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
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
