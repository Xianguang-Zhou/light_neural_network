/*
 * Copyright (c) 2019, Xianguang Zhou <xianguang.zhou@outlook.com>. All rights
 * reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
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

