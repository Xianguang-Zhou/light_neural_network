/*
 * Copyright (c) 2020, Xianguang Zhou <xianguang.zhou@outlook.com>. All rights
 * reserved.
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
#include "opencl/file_kernel_provider.h"
#include <fstream>

namespace Lnn {

using std::ifstream;
using std::istream;
using std::make_shared;
using std::shared_ptr;
using std::string;

FileKernelProvider::FileKernelProvider(const string &rootDirPath)
	: rootDirPath(rootDirPath) {}

shared_ptr<istream> FileKernelProvider::get(const string &path) const {
	return make_shared<ifstream>(rootDirPath / path);
}

} // namespace Lnn
