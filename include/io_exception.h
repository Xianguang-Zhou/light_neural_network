/*
 * Copyright (c) 2019, Xianguang Zhou <xianguang.zhou@outlook.com>. All rights
 * reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef LNN_IO_EXCEPTION_H_
#define LNN_IO_EXCEPTION_H_

#include "lnn_exception.h"
#include <string>

namespace Lnn {

class IOException : public Exception {
  public:
	explicit IOException(const std::string &message);
	explicit IOException(const std::exception &cause);
	explicit IOException(const std::string &message,
						 const std::exception &cause);

  protected:
	explicit IOException();
};

}; // namespace Lnn

#endif

