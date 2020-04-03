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
#include "opencl/kernel.h"

namespace Lnn {

using std::istream;
using std::make_shared;
using std::make_unique;
using std::shared_ptr;

shared_ptr<Calling> Kernel::call() const {
	shared_ptr<Calling> calling = make_shared<Calling>(*program, "run");
	calling->at(device);
	return calling;
}

void Kernel::init(shared_ptr<cl::Context> context,
				  shared_ptr<cl::Device> device, istream &is) {
	this->device = device;
	this->program = make_unique<Program>(context, is);
}

} // namespace Lnn
