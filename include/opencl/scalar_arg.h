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

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-attributes"
#endif

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

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif

}; // namespace Lnn

#endif
