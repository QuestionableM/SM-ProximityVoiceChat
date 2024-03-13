#pragma once

#include <cstdint>
#include <cstddef>
#include <memory>

class BufferReader
{
public:
	BufferReader(const char* buff)
		: buffer(buff), offset(0) {}

	inline void skip(std::size_t bytes)
	{
		this->offset += bytes;
	}

	template<typename T>
	inline void ReadRef(T* object)
	{
		std::memcpy(object, buffer + offset, sizeof(T));
		offset += sizeof(T);
	}

	template<typename T>
	inline static void reverse_object(T* obj)
	{
		char* v_obj_start = reinterpret_cast<char*>(obj);
		char* v_obj_end = v_obj_start + sizeof(T);

		std::reverse(v_obj_start, v_obj_end);
	}

	template<typename T>
	inline void ReadRefBE(T* object)
	{
		this->ReadRef(object);
		this->reverse_object<T>(object);
	}

	template<typename T, bool t_big_endian = false>
	inline T Read()
	{
		T obj;
		this->ReadRef<T>(&obj);
		return obj;
	}

	template<typename T>
	inline T ReadBE()
	{
		T obj;
		this->ReadRef<T>(&obj);
		this->reverse_object<T>(&obj);
	}

	std::size_t	Offset() const { return this->offset; }

private:
	const char* buffer;
	std::size_t offset;
};