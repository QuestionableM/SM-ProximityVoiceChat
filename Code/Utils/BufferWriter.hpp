#pragma once

#include <cstdint>
#include <cstddef>
#include <memory>

class BufferWriter
{
public:
	BufferWriter(char* dest_buffer, std::size_t buff_sz)
		: m_buffer(dest_buffer), m_bufferSz(buff_sz), m_offset(0) {}

	template<typename T>
	bool Write(const T& data)
	{
		if (m_bufferSz < (m_offset + sizeof(T)))
			return false;

		std::memcpy(m_buffer + m_offset, &data, sizeof(T));
		m_offset += sizeof(T);

		return true;
	}

	bool WriteBuffer(char* buff, std::size_t buff_sz)
	{
		if (m_bufferSz < (m_offset + buff_sz))
			return false;

		std::memcpy(m_buffer + m_offset, buff, buff_sz);
		m_offset += buff_sz;

		return true;
	}

	std::size_t GetOffset() const
	{
		return m_offset;
	}

private:
	char* m_buffer;
	std::size_t m_bufferSz;
	std::size_t m_offset;
};