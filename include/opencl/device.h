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
#ifndef LNN_DEVICE_H_
#define LNN_DEVICE_H_

#include "kernel.h"
#include "kernel_provider.h"
#include <mutex>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>

namespace Lnn {

class Device {
  public:
	static std::shared_ptr<Device> defaultDevice();

	explicit Device(std::shared_ptr<cl::Context> context,
					std::shared_ptr<cl::Device> device,
					std::shared_ptr<KernelProvider> kernelProvider);
	virtual ~Device() = default;

	template <class T> std::shared_ptr<T> kernel() const {
		std::type_index typeIndex(typeid(T));
		try {
			return std::static_pointer_cast<T>(kernels.at(typeIndex));
		} catch (const std::out_of_range &ex) {
			std::lock_guard lock(kernelsMutex);
			if (kernels.count(typeIndex)) {
				return std::static_pointer_cast<T>(kernels.at(typeIndex));
			} else {
				std::shared_ptr<T> kernel(new T());
				std::shared_ptr<std::string> kernelPath = kernel->path();
				std::shared_ptr<std::istream> streamPtr =
					kernelProvider->get(*kernelPath + ".cl");
				kernel->init(clContext, clDevice, *streamPtr);
				kernels.insert(std::make_pair(typeIndex, kernel));
				return kernel;
			}
		}
	}

  private:
	std::shared_ptr<cl::Context> clContext;
	std::shared_ptr<cl::Device> clDevice;
	std::unordered_map<std::type_index, std::shared_ptr<Kernel>> kernels;
	std::mutex kernelsMutex;
	std::shared_ptr<KernelProvider> kernelProvider;
};

} // namespace Lnn

#endif
