/*
 * Copyright (c) 2019, Xianguang Zhou <xianguang.zhou@outlook.com>. All rights
 * reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "opencl/cl_exception.h"

namespace Lnn {

CLException::CLException() {}

CLException::CLException(const std::string &message) : Exception(message) {}

CLException::CLException(const cl::Error &cause)
	: Exception(cause), _errorCode(cause.err()) {}

CLException::CLException(const std::exception &cause) : Exception(cause) {}

CLException::CLException(const std::string &message, const cl::Error &cause)
	: Exception(message, cause), _errorCode(cause.err()) {}

CLException::CLException(const std::string &message,
						 const std::exception &cause)
	: Exception(message, cause) {}

cl_int CLException::errorCode() const { return _errorCode; }

}; // namespace Lnn

