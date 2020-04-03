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
	explicit Exception() = default;

  private:
	std::string message;
};

}; // namespace Lnn

#endif
