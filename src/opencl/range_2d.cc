/*
 * Copyright (c) 2019, Xianguang Zhou <xianguang.zhou@outlook.com>. All rights
 * reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include "opencl/range_2d.h"

namespace Lnn {

using cl::NDRange;

Range2D::Range2D(size_t globalWidth, size_t globalHeight)
	: Range2D(globalWidth, globalHeight, 1, 1) {}

Range2D::Range2D(size_t globalWidth, size_t globalHeight, size_t localWidth,
				 size_t localHeight)
	: globalWidth(globalWidth), globalHeight(globalHeight),
	  localWidth(localWidth), localHeight(localHeight) {}

void Range2D::putToQueue(const cl::CommandQueue &queue,
						 const cl::Kernel &kernel) const {
	NDRange offset(0, 0);
	NDRange global(globalWidth, globalHeight);
	NDRange local(localWidth, localHeight);
	queue.enqueueNDRangeKernel(kernel, offset, global, local);
}

}; // namespace Lnn
