/*
 * Copyright (c) 2019, Xianguang Zhou <xianguang.zhou@outlook.com>. All rights
 * reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "opencl/program.h"
#include "io_exception.h"
#include "opencl/cl_exception.h"
#include <fstream>

namespace Lnn {

using cl::Context;
using std::ifstream;
using std::istream;
using std::istreambuf_iterator;
using std::shared_ptr;
using std::string;

Program::Program() {}

Program::Program(const Context &ctx, const string &path) { init(ctx, path); }

Program::Program(const Context &ctx, istream &is) { init(ctx, is); }

Program::~Program() {}

void Program::init(const Context &ctx, const string &path) {
	ifstream fs(path);
	if (fs) {
		init(ctx, fs);
	} else {
		throw IOException("OpenCL file is not found.");
	}
}

void Program::init(const Context &ctx, istream &is) {
	try {
		istreambuf_iterator<char> begin(is);
		istreambuf_iterator<char> end;
		string source(begin, end);
		program = shared_ptr<cl::Program>(new cl::Program(ctx, source));
		program->build();
	} catch (const cl::Error &error) {
		throw CLException(error);
	} catch (const std::exception &ex) {
		throw IOException(ex);
	}
}

}; // namespace Lnn

