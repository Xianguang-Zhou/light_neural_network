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
