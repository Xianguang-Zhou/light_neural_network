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
#ifndef LNN_PROGRAM_H_
#define LNN_PROGRAM_H_

#include "opencl.h"
#include <istream>
#include <memory>
#include <string>

namespace Lnn {

class Program {
  public:
	explicit Program(std::shared_ptr<cl::Context> ctx, const std::string &path);
	explicit Program(std::shared_ptr<cl::Context> ctx, std::istream &is);
	virtual ~Program();

  protected:
	explicit Program();
	void init(std::shared_ptr<cl::Context> ctx, const std::string &path);
	void init(std::shared_ptr<cl::Context> ctx, std::istream &is);

  private:
	std::shared_ptr<cl::Program> program;
	std::shared_ptr<cl::Context> context;

	friend class Calling;
};

}; // namespace Lnn

#endif
