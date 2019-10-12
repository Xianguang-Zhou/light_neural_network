/*
 * Copyright (c) 2019, Xianguang Zhou <xianguang.zhou@outlook.com>. All rights
 * reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
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
