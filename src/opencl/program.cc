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
#include "opencl/program.h"
#include "io_exception.h"
#include "opencl/cl_exception.h"
#include <fstream>
#include <memory>

namespace Lnn {

using cl::Context;
using std::ifstream;
using std::istream;
using std::istreambuf_iterator;
using std::make_shared;
using std::shared_ptr;
using std::string;

Program::Program() {}

Program::Program(shared_ptr<Context> ctx, const string &path) {
	init(ctx, path);
}

Program::Program(shared_ptr<Context> ctx, istream &is) { init(ctx, is); }

Program::~Program() {}

void Program::init(shared_ptr<Context> ctx, const string &path) {
	ifstream fs(path);
	if (fs) {
		init(ctx, fs);
	} else {
		throw IOException("OpenCL file is not found.");
	}
}

void Program::init(shared_ptr<Context> ctx, istream &is) {
	try {
		this->context = ctx;
		istreambuf_iterator<char> begin(is);
		istreambuf_iterator<char> end;
		string source(begin, end);
		program = make_shared<cl::Program>(*ctx, source);
		program->build();
	} catch (const cl::Error &error) {
		throw CLException(error);
	} catch (const std::exception &ex) {
		throw IOException(ex);
	}
}

}; // namespace Lnn
