/*
 * Copyright (c) 2019, Xianguang Zhou <xianguang.zhou@outlook.com>. All rights reserved.
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
#include "io_exception.h"

namespace Lnn {

IOException::IOException() {}

IOException::IOException(const std::string &message) : Exception(message) {}

IOException::IOException(const std::exception &cause) : Exception(cause) {}

IOException::IOException(const std::string &message,
						 const std::exception &cause)
	: Exception(message, cause) {}

}; // namespace Lnn
