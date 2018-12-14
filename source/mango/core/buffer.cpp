/*
    MANGO Multimedia Development Platform
    Copyright (C) 2012-2017 Twilight Finland 3D Oy Ltd. All rights reserved.
*/
#include <mango/core/buffer.hpp>
#include <mango/core/exception.hpp>

#define ID "Buffer: "

namespace mango {

    Buffer::Buffer()
        : m_offset(0)
    {
    }

    Buffer::Buffer(size_t size)
        : m_buffer(size)
        , m_offset(0)
    {
    }

    Buffer::Buffer(const uint8* address, size_t size)
        : m_buffer(address, address + size)
        , m_offset(0)
    {
    }

    Buffer::Buffer(Memory memory)
        : m_buffer(memory.address, memory.address + memory.size)
        , m_offset(0)
    {
    }

    Buffer::~Buffer()
    {
    }

    void Buffer::reserve(size_t size)
    {
        m_buffer.reserve(size);
    }

    void Buffer::resize(size_t size)
    {
        m_buffer.resize(size);
        m_offset = size;
    }

    uint8* Buffer::data()
    {
		return &m_buffer[0];
    }

    Buffer::operator Memory () const
    {
        uint8 *address = const_cast<uint8 *>(m_buffer.data());
        return Memory(address, m_buffer.size());
    }

	Buffer::operator uint8* ()
	{
		return &m_buffer[0];
	}

    uint64 Buffer::size() const
    {
        return m_buffer.size();
    }

    uint64 Buffer::offset() const
    {
        return m_offset;
    }

    void Buffer::seek(uint64 distance, SeekMode mode)
    {
        switch (mode)
        {
            case BEGIN:
                m_offset = size_t(distance);
                break;

            case CURRENT:
                m_offset += size_t(distance);
                break;

            case END:
                m_offset = size_t(m_buffer.size() - distance);
                break;
        }
    }

    void Buffer::read(void* dest, size_t size)
    {
        const size_t left = m_buffer.size() - m_offset;
        if (left < size) {
            size = left;
            MANGO_EXCEPTION(ID"Reading past end of buffer.");
        }
        std::memcpy(dest, &m_buffer[m_offset], size);
        m_offset += size;
    }

    void Buffer::write(const void* data, size_t size)
    {
        const uint8 *source = reinterpret_cast<const uint8 *>(data);
        const int64 left = m_buffer.size() - m_offset;
        const int64 right = size - left;

        if (left > 0) {
            // write into existing array
            size = std::min(size, size_t(left));
            std::memcpy(&m_buffer[m_offset], source, size);
            source += size;
            m_offset += size;
        }

        if (right > 0) {
            // append at end of existing array
            m_buffer.insert(m_buffer.end(), source, source + right);
            m_offset += size_t(right);
        }
    }

} // namespace mango
