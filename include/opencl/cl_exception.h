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
#ifndef LNN_CL_EXCEPTION_H_
#define LNN_CL_EXCEPTION_H_

#include "lnn_exception.h"
#include "opencl.h"

namespace Lnn {

class CLException : public Exception {
  public:
	explicit CLException(const std::string &message);
	explicit CLException(const cl::Error &cause);
	explicit CLException(const std::exception &cause);
	explicit CLException(const std::string &message, const cl::Error &cause);
	explicit CLException(const std::string &message,
						 const std::exception &cause);
	cl_int errorCode() const;

  protected:
	explicit CLException() = default;

  private:
	cl_int _errorCode;
};

}; // namespace Lnn

#endif
