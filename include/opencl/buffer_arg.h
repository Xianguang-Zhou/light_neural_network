/*
 * Copyright (c) 2019, Xianguang Zhou <xianguang.zhou@outlook.com>. All rights
 * reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
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
