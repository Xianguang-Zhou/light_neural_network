/*
 * Copyright (c) 2019, Xianguang Zhou <xianguang.zhou@outlook.com>. All rights
 * reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "opencl/calling.h"

namespace Lnn {

using std::string;

Calling::Calling(const Program &program, const string &function)
	: program(program.program), function(function) {}

Calling::~Calling() {}
}; // namespace Lnn

