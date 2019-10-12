/*
 * Copyright (c) 2019, Xianguang Zhou <xianguang.zhou@outlook.com>. All rights
 * reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#ifndef LNN_RANGE_H_
#define LNN_RANGE_H_

#include "opencl.h"

namespace Lnn {

class Range {
  public:
	virtual void putToQueue(const cl::CommandQueue &queue,
							const cl::Kernel &kernel) const = 0;
	virtual ~Range() = default;
};
}; // namespace Lnn

#endif
