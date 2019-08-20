/*
 * Copyright (c) 2019, Xianguang Zhou <xianguang.zhou@outlook.com>. All rights
 * reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef LNN_CALLING_H_
#define LNN_CALLING_H_

#include "opencl.h"
#include "program.h"
#include <memory>
#include <string>

namespace Lnn {

class Calling {
  public:
	explicit Calling(const Program &program,
					 const std::string &function = "run");
	virtual ~Calling();

  private:
	std::shared_ptr<cl::Program> program;
	std::string function;
};
}; // namespace Lnn

#endif

