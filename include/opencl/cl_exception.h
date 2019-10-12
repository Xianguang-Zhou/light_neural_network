/*
 * Copyright (c) 2019, Xianguang Zhou <xianguang.zhou@outlook.com>. All rights
 * reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#ifndef LNN_CL_EXCEPTION_H_
#define LNN_CL_EXCEPTION_H_

#include "lnn_exception.h"
#include "opencl.h"
#include <string>

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
	explicit CLException();

  private:
	cl_int _errorCode;
};

}; // namespace Lnn

#endif
