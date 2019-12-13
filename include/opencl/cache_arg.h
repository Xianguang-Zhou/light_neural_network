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
#ifndef LNN_CACHE_ARG_H_
#define LNN_CACHE_ARG_H_

#include "arg.h"

namespace Lnn {

class CacheArg : public Arg {
  public:
	enum class Type { SHORT = 2, INT = 4, LONG = 8, FLOAT = 4, DOUBLE = 8 };

	explicit CacheArg(Type type, size_t number);
	explicit CacheArg(size_t typeSize, size_t number);
	explicit CacheArg(size_t size);
	void input(ArgInputContext &ctx) override;

	const size_t size;

  private:
	std::unique_ptr<cl::Buffer> clBuffer;
};

}; // namespace Lnn

#endif
