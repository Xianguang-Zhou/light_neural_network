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
#include "opencl/device.h"
#include "opencl/file_kernel_provider.h"
#include <CL/cl.hpp>
#include <memory>

namespace Lnn {

using std::make_shared;
using std::shared_ptr;

shared_ptr<Device> Device::defaultDevice() {
	static cl::Device clDevice = cl::Device::getDefault();
	static cl::Context clContext = cl::Context::getDefault();
	static shared_ptr<FileKernelProvider> fileKernelProvider =
		make_shared<FileKernelProvider>();
	static shared_ptr<Device> device = make_shared<Device>(
		shared_ptr<cl::Context>(&clContext), shared_ptr<cl::Device>(&clDevice),
		fileKernelProvider);
	return device;
}

Device::Device(shared_ptr<cl::Context> context, shared_ptr<cl::Device> device,
			   shared_ptr<KernelProvider> kernelProvider)
	: clContext(context), clDevice(device), kernelProvider(kernelProvider) {}

} // namespace Lnn
