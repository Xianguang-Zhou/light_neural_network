/*
 * Copyright (c) 2019, Xianguang Zhou <xianguang.zhou@outlook.com>. All rights
 * reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef LNN_RANGE_3D_H_
#define LNN_RANGE_3D_H_

#include "range.h"

namespace Lnn {

class Range3D : public Range {
  public:
	explicit Range3D(size_t globalWidth, size_t globalHeight,
					 size_t globalDepth);
	explicit Range3D(size_t globalWidth, size_t globalHeight,
					 size_t globalDepth, size_t localWidth, size_t localHeight,
					 size_t localDepth);
	void putToQueue(const cl::CommandQueue &queue,
					const cl::Kernel &kernel) const override;

  private:
	size_t globalWidth;
	size_t globalHeight;
	size_t globalDepth;
	size_t localWidth;
	size_t localHeight;
	size_t localDepth;
};
}; // namespace Lnn

#endif

