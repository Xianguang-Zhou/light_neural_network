/*
 * Copyright (c) 2019, Xianguang Zhou <xianguang.zhou@outlook.com>. All rights
 * reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include "opencl/range_1d.h"

namespace Lnn {

using cl::NDRange;

Range1D::Range1D(size_t globalWidth, size_t localWidth)
	: globalWidth(globalWidth), localWidth(localWidth) {}

void Range1D::putToQueue(const cl::CommandQueue &queue,
						 const cl::Kernel &kernel) const {
	NDRange offset(0);
	NDRange global(globalWidth);
	NDRange local(localWidth);
	queue.enqueueNDRangeKernel(kernel, offset, global, local);
}

}; // namespace Lnn
