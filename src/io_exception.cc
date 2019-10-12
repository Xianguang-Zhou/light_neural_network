/*
 * Copyright (c) 2019, Xianguang Zhou <xianguang.zhou@outlook.com>. All rights
 * reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include "io_exception.h"

namespace Lnn {

IOException::IOException() {}

IOException::IOException(const std::string &message) : Exception(message) {}

IOException::IOException(const std::exception &cause) : Exception(cause) {}

IOException::IOException(const std::string &message,
						 const std::exception &cause)
	: Exception(message, cause) {}

}; // namespace Lnn
