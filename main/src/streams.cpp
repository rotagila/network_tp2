#include "streams.hpp"

void MemoryStream::Write(gsl::not_null<void*> data, size_t length)
{

	std::cout << "len " << length << std::endl;

	std::byte b = (std::byte)length;

	m_buffer.insert(std::end(m_buffer),
		sizeof(b), //size
		b); // value

    m_buffer.insert(std::end(m_buffer), 
                reinterpret_cast<std::byte*>(data.get()), 
                reinterpret_cast<std::byte*>(data.get()) + length);
}

void MemoryStream::WriteStr(const std::string& data)
{
    assert(data.length() < 0xffff);

    uint16_t strSize = static_cast<uint16_t>(data.size());
    Write<unsigned short>(strSize);

    m_buffer.insert(std::end(m_buffer), 
                reinterpret_cast<const std::byte*>(data.data()), 
                reinterpret_cast<const std::byte*>(data.data()) + data.length());
}

std::string MemoryStream::ReadStr()
{
    uint16_t strSize = Read<uint16_t>();
    auto str = Read(strSize);

	std::string output(reinterpret_cast<char*>(str.data()), str.size());

    return output;
}

void MemoryStream::Write(gsl::span<const char> data)
{
    m_buffer.insert(std::end(m_buffer), 
                reinterpret_cast<const std::byte*>(data.data()), 
                reinterpret_cast<const std::byte*>(data.data()) + data.size_bytes());
}

void MemoryStream::Write(gsl::span<std::byte> data)
{
    m_buffer.insert(std::end(m_buffer), data.data(), data.data() + data.size_bytes());
}

// vector3 implementation
void MemoryStream::Write(Vector3& data)
{
	Write(data.x);
	Write(data.y);
	Write(data.z);
}

// quaternion implementation
void MemoryStream::Write(Quaternion& data)
{
	Write(data.x);
	Write(data.y);
	Write(data.z);
	Write(data.w);
}


Quaternion MemoryStream::ReadQuat()
{
	Quaternion q;

	q.x = Read<float>();
	q.y = Read<float>();
	q.z = Read<float>();
	q.w = Read<float>();

	return q;
}

Vector3 MemoryStream::ReadVector3() {

	Vector3 v;

	v.x = Read<float>();
	v.y = Read<float>();
	v.z = Read<float>();

	return v;
}


