/*
 * Copyright (c) 2019, Xianguang Zhou <xianguang.zhou@outlook.com>. All rights
 * reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "opencl/range_3d.h"

namespace Lnn {

using cl::NDRange;

Range3D::Range3D(size_t globalWidth, size_t globalHeight, size_t globalDepth)
	: Range3D(globalWidth, globalHeight, globalDepth, 1, 1, 1) {}

Range3D::Range3D(size_t globalWidth, size_t globalHeight, size_t globalDepth,
				 size_t localWidth, size_t localHeight, size_t localDepth)
	: globalWidth(globalWidth), globalHeight(globalHeight),
	  globalDepth(globalDepth), localWidth(localWidth),
	  localHeight(localHeight), localDepth(localDepth) {}

void Range3D::putToQueue(const cl::CommandQueue &queue,
						 const cl::Kernel &kernel) const {
	NDRange offset(0, 0, 0);
	NDRange global(globalWidth, globalHeight, globalDepth);
	NDRange local(localWidth, localHeight, localDepth);
	queue.enqueueNDRangeKernel(kernel, offset, global, local);
}

}; // namespace Lnn

