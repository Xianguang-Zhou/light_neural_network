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
