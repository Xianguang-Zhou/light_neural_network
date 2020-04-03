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
#ifndef LNN_BUFFER_ARG_H_
#define LNN_BUFFER_ARG_H_

#include "arg.h"
#include "buffer_array.h"

namespace Lnn {

class BufferArg : public Arg {
  public:
	enum class Type { IN, OUT, IN_OUT };

	explicit BufferArg(std::shared_ptr<ArgBuffer> buffer, Type type);
	virtual ~BufferArg();

	bool isIn() const;
	bool isOut() const;

	void input(ArgInputContext &ctx) override;
	void output(const cl::CommandQueue &queue) override;

	const Type type;

  private:
	std::shared_ptr<ArgBuffer> buffer;
};

}; // namespace Lnn

#endif
