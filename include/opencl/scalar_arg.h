/*
 * Copyright (c) 2019, Xianguang Zhou <xianguang.zhou@outlook.com>. All rights
 * reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#ifndef LNN_SCALAR_ARG_H_
#define LNN_SCALAR_ARG_H_

#include "arg.h"

namespace Lnn {

template <typename T> class ScalarArg : public Arg {
  public:
	explicit ScalarArg(T scalar) : scalar(scalar) {}

	void input(ArgInputContext &ctx) override {
		ctx.getKernel().setArg(ctx.getIndexAndIncrement(), scalar);
	}

  private:
	T scalar;
};

typedef ScalarArg<cl_char> CharArg;
typedef ScalarArg<cl_uchar> UcharArg;
typedef ScalarArg<cl_short> ShortArg;
typedef ScalarArg<cl_ushort> UshortArg;
typedef ScalarArg<cl_int> IntArg;
typedef ScalarArg<cl_uint> UintArg;
typedef ScalarArg<cl_long> LongArg;
typedef ScalarArg<cl_ulong> UlongArg;
typedef ScalarArg<cl_half> HalfArg;
typedef ScalarArg<cl_float> FloatArg;
typedef ScalarArg<cl_double> DoubleArg;

}; // namespace Lnn

#endif
