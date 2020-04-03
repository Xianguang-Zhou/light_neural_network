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
#include "opencl/cl_exception.h"

namespace Lnn {

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
