#pragma once

#include <cstdint>
#include <cstddef>
#include <memory>

class BufferReader
{
public:
	inline BufferReader(const std::uint8_t* buff) noexcept
		: buffer(buff)
		, offset(0)
	{}

	template<typename T>
	inline void ReadRef(T* object)
	{
		std::memcpy(object, buffer + offset, sizeof(T));
		offset += sizeof(T);
	}

	template<typename T>
	inline static void ReverseObject(T* obj)
	{
		char* v_obj_start = reinterpret_cast<char*>(obj);
		char* v_obj_end = v_obj_start + sizeof(T);

		std::reverse(v_obj_start, v_obj_end);
	}

	template<typename T>
	inline void ReadRefBE(T* object)
	{
		this->ReadRef(object);
		this->ReverseObject<T>(object);
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
		this->ReverseObject<T>(&obj);
	}

	inline void Skip(const std::size_t bytes) noexcept
	{
		this->offset += bytes;
	}

	inline std::size_t Offset() const noexcept
	{
		return this->offset;
	}

private:
	const std::uint8_t* buffer;
	std::size_t offset;
};