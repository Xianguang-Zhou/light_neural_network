/*
 * Copyright (c) 2019, Xianguang Zhou <xianguang.zhou@outlook.com>. All rights
 * reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#ifndef LNN_BUFFER_ARRAY_H_
#define LNN_BUFFER_ARRAY_H_

#include "opencl.h"
#include <iostream>
#include <memory>
#include <vector>

namespace Lnn {

class ArgBuffer {
  protected:
	virtual ~ArgBuffer() = default;

  private:
	virtual const cl::Buffer &
	createClBuffer(std::shared_ptr<cl::Context> context,
				   std::shared_ptr<cl::Device> device) = 0;

	virtual void updateClBuffer(const cl::CommandQueue &queue) = 0;

	virtual void updateBuffer(bool clBufferModified,
							  const cl::CommandQueue &queue) = 0;

	virtual void deleteClBuffer() = 0;

	friend class BufferArg;
};

template <typename T> class BufferArray : private ArgBuffer {
  private:
	enum class State { SYNCHRONIZED, BUFFER_MODIFIED, CL_BUFFER_MODIFIED };

  public:
	static void copy(const BufferArray<T> &src, size_t srcPos,
					 BufferArray<T> &dest, size_t destPos, size_t length) {
		if (src.buffer != dest.buffer) {
			src.updateBuffer();
			std::memcpy(dest.buffer + destPos, src.buffer + srcPos,
						length * sizeof(T));
			dest.state = State::BUFFER_MODIFIED;
		}
	}

	explicit BufferArray(size_t length)
		: length(length), buffer(new T[length]), state(State::BUFFER_MODIFIED) {
	}

	explicit BufferArray(const T *elements, size_t length)
		: BufferArray(length) {
		std::memcpy(buffer, elements, length * sizeof(T));
		this->state = State::BUFFER_MODIFIED;
	}

	explicit BufferArray(const std::vector<T> &elements)
		: BufferArray(elements.data(), elements.size()) {}

	explicit BufferArray(const BufferArray<T> &other, size_t from, size_t to)
		: BufferArray(to - from) {
		other.updateBuffer();
		std::memcpy(buffer, other.buffer + from, length * sizeof(T));
		this->retainClBuffer = other.retainClBuffer;
		this->context = other.context;
		this->device = other.device;
		this->state = State::BUFFER_MODIFIED;
	}

	explicit BufferArray(const BufferArray<T> &other)
		: BufferArray(other, 0, other.length) {}

	virtual ~BufferArray() { delete[] buffer; }

	virtual BufferArray<T> &operator=(const BufferArray<T> &other) {
		if (this->buffer != other.buffer) {
			if (this->length != other.length) {
				delete[] this->buffer;
				this->length = other.length;
				this->buffer = new T[other.length];
				clBuffer.reset();
			}
			this->retainClBuffer = other.retainClBuffer;
			if (!retainClBuffer && clBuffer) {
				clBuffer.reset();
			}
			if (this->device != other.device) {
				clBuffer.reset();
				this->context = other.context;
				this->device = other.device;
			}
			other.updateBuffer();
			std::memcpy(this->buffer, other.buffer, other.length * sizeof(T));
			this->state = State::BUFFER_MODIFIED;
		}
		return *this;
	}

	virtual bool operator==(const BufferArray<T> &other) const {
		if (this->buffer == other.buffer) {
			return true;
		}
		if (this->length != other.length) {
			return false;
		}
		if (this->retainClBuffer != other.retainClBuffer) {
			return false;
		}
		if (this->context != other.context) {
			return false;
		}
		if (this->device != other.device) {
			return false;
		}
		this->updateBuffer();
		other.updateBuffer();
		return std::strncmp((char *)const_cast<T *>(this->buffer),
							(char *)const_cast<T *>(other.buffer),
							this->length * sizeof(T)) == 0;
	}

	virtual bool operator!=(const BufferArray<T> &other) const {
		return !((*this) == other);
	}

	virtual operator std::string() const {
		updateBuffer();
		std::string str("[");
		if (length > 0) {
			size_t index = 0;
			for (size_t limit = length - 1; index < limit; index++) {
				str += std::to_string(buffer[index]);
				str += ", ";
			}
			str += std::to_string(buffer[index]);
		}
		str += "]";
		return str;
	}

	void print() const { std::cout << std::string(*this) << std::endl; }

	void setRetainClBuffer(bool retain) {
		this->retainClBuffer = retain;
		if (!retain && clBuffer) {
			updateBuffer();
			clBuffer.reset();
		}
	}

	bool isRetainClBuffer() const { return this->retainClBuffer; }

	size_t getLength() const { return this->length; }

	T get(size_t index) const {
		updateBuffer();
		return buffer[index];
	}

	void set(size_t index, T value) {
		updateBuffer();
		buffer[index] = value;
		state = State::BUFFER_MODIFIED;
	}

	const T &operator[](size_t index) const {
		updateBuffer();
		return buffer[index];
	}

	T &operator[](size_t index) {
		updateBuffer();
		state = State::BUFFER_MODIFIED;
		return buffer[index];
	}

	void get(size_t begin, T *elements, size_t offset, size_t length) const {
		updateBuffer();
		std::memcpy(elements + offset, buffer + begin, length * sizeof(T));
	}

	std::vector<T> get(size_t begin, size_t end) const {
		std::vector<T> elements(end - begin);
		get(begin, elements.data(), 0, elements.size());
		return elements;
	}

	std::vector<T> get() const { return get(0, length); }

	void set(size_t begin, const T *elements, size_t offset, size_t length) {
		updateBuffer();
		std::memcpy(buffer + begin, elements + offset, length * sizeof(T));
		state = State::BUFFER_MODIFIED;
	}

	void set(size_t begin, const std::vector<T> &elements, size_t offset) {
		set(begin, elements.data(), offset, elements.size() - offset);
	}

	void set(const T *elements, size_t offset, size_t length) {
		set(0, elements, offset, length);
	}

	void set(const std::vector<T> &elements, size_t offset) {
		set(elements.data(), offset, elements.size() - offset);
	}

	void set(size_t begin, const std::vector<T> &elements) {
		set(begin, elements.data(), 0, elements.size());
	}

	void set(const std::vector<T> &elements) { set(0, elements); }

  private:
	void updateBuffer() const {
		if (clBuffer && State::CL_BUFFER_MODIFIED == this->state) {
			cl::CommandQueue queue(*context, *device);
			queue.enqueueReadBuffer(*clBuffer, true, 0, length * sizeof(T),
									buffer);
			const_cast<BufferArray<T> *>(this)->state = State::SYNCHRONIZED;
		}
	}

	const cl::Buffer &
	createClBuffer(std::shared_ptr<cl::Context> context,
				   std::shared_ptr<cl::Device> device) override {
		if (!clBuffer) {
			clBuffer = std::make_unique<cl::Buffer>(*context, CL_MEM_READ_WRITE,
													length * sizeof(T));
			this->context = context;
			this->device = device;
			this->state = State::BUFFER_MODIFIED;
		}
		return *clBuffer;
	}

	void updateClBuffer(const cl::CommandQueue &queue) override {
		if (State::BUFFER_MODIFIED == this->state) {
			queue.enqueueWriteBuffer(*clBuffer, false, 0, length * sizeof(T),
									 buffer);
			this->state = State::SYNCHRONIZED;
		}
	}

	void updateBuffer(bool clBufferModified,
					  const cl::CommandQueue &queue) override {
		if (clBufferModified) {
			this->state = State::CL_BUFFER_MODIFIED;
		}
		if (!retainClBuffer) {
			if (State::CL_BUFFER_MODIFIED == this->state) {
				queue.enqueueReadBuffer(*clBuffer, false, 0, length * sizeof(T),
										buffer);
				this->state = State::SYNCHRONIZED;
			}
		}
	}

	void deleteClBuffer() override {
		if (!retainClBuffer) {
			clBuffer.reset();
		}
	}

	size_t length;
	T *buffer;
	std::unique_ptr<cl::Buffer> clBuffer;
	bool retainClBuffer = false;
	State state;
	std::shared_ptr<cl::Context> context;
	std::shared_ptr<cl::Device> device;
};

typedef BufferArray<cl_char> CharArray;
typedef BufferArray<cl_uchar> UcharArray;
typedef BufferArray<cl_short> ShortArray;
typedef BufferArray<cl_ushort> UshortArray;
typedef BufferArray<cl_int> IntArray;
typedef BufferArray<cl_uint> UintArray;
typedef BufferArray<cl_long> LongArray;
typedef BufferArray<cl_ulong> UlongArray;
typedef BufferArray<cl_half> HalfArray;
typedef BufferArray<cl_float> FloatArray;
typedef BufferArray<cl_double> DoubleArray;

}; // namespace Lnn

#endif
