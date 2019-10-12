/*
 * Copyright (c) 2019, Xianguang Zhou <xianguang.zhou@outlook.com>. All rights
 * reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#ifndef LNN_EXCEPTION_H_
#define LNN_EXCEPTION_H_

#include <exception>
#include <string>

namespace Lnn {

class Exception : public std::exception {
  public:
	explicit Exception(const std::string &message);
	explicit Exception(const std::exception &cause);
	explicit Exception(const std::string &message, const std::exception &cause);
	const char *what() const noexcept override;

  protected:
	explicit Exception();

  private:
	std::string message;
};

}; // namespace Lnn

#endif
