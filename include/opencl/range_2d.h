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
#ifndef LNN_RANGE_2D_H_
#define LNN_RANGE_2D_H_

#include "range.h"

namespace Lnn {

class Range2D : public Range {
  public:
	explicit Range2D(size_t globalWidth, size_t globalHeight);
	explicit Range2D(size_t globalWidth, size_t globalHeight, size_t localWidth,
					 size_t localHeight);
	void putToQueue(const cl::CommandQueue &queue,
					const cl::Kernel &kernel) const override;

  private:
	size_t globalWidth;
	size_t globalHeight;
	size_t localWidth;
	size_t localHeight;
};
}; // namespace Lnn

#endif
