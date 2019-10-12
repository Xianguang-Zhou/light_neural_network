/*
 * Copyright (c) 2019, Xianguang Zhou <xianguang.zhou@outlook.com>. All rights
 * reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
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
