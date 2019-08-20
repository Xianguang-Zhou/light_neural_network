/*
 * Copyright (c) 2019, Xianguang Zhou <xianguang.zhou@outlook.com>. All rights
 * reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "lnn_exception.h"

namespace Lnn {

Exception::Exception() {}

Exception::Exception(const std::string &message) : message(message) {}

Exception::Exception(const std::exception &cause) : message(cause.what()) {}

Exception::Exception(const std::string &message, const std::exception &cause)
	: message(message + "\nCaused by:\n" + cause.what()) {}

const char *Exception::what() const noexcept { return message.c_str(); }

}; // namespace Lnn

