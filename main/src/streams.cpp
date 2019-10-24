#include "streams.hpp"
#include <math.h>

void MemoryStream::Write(gsl::not_null<void*> data, size_t length)
{
	/*
	std::cout << "len " << length << std::endl;

	std::byte b = (std::byte)length;

	m_buffer.insert(std::end(m_buffer),
		sizeof(b), //size
		b); // value
	*/
    m_buffer.insert(std::end(m_buffer), 
                reinterpret_cast<std::byte*>(data.get()), 
                reinterpret_cast<std::byte*>(data.get()) + length);
}

void MemoryStream::WriteStr(const std::string& data)
{
    assert(data.length() < 0xffff);

    uint8_t strSize = static_cast<uint8_t>(data.size());
    Write<uint8_t>(strSize);

    m_buffer.insert(std::end(m_buffer), 
                reinterpret_cast<const std::byte*>(data.data()), 
                reinterpret_cast<const std::byte*>(data.data()) + data.length());
}

std::string MemoryStream::ReadStr()
{
    uint8_t strSize = Read<uint8_t>();
    gsl::span<std::byte> str = Read(strSize);

	std::string output = "";


	for(auto iter = str.begin(); iter != str.end(); ++iter)
	{
		output += (char)*iter;
	}


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

	float fx = (data.x + 1) * 1000;
	float fy = (data.y + 1) * 1000;
	float fz = (data.z + 1) * 1000;

	uint16_t tempx = static_cast<uint16_t>(fx);
	uint16_t tempy = static_cast<uint16_t>(fy);
	uint16_t tempz = static_cast<uint16_t>(fz);

	Write(tempx);
	Write(tempy);
	Write(tempz);
}



Quaternion MemoryStream::ReadQuat()
{
	Quaternion q;

	auto tempx = Read<uint16_t>();
	auto tempy = Read<uint16_t>();
	auto tempz = Read<uint16_t>();

	q.x = static_cast<float>(tempx * 0.001 - 1);
	q.y = static_cast<float>(tempy * 0.001 - 1);
	q.z = static_cast<float>(tempz * 0.001 - 1);
	q.w = sqrt(1.f - (q.x * q.x + q.y * q.y + q.z * q.z));

	return q;
}

Vector3 MemoryStream::ReadVector3() {

	Vector3 v;

	v.x = Read<float>();
	v.y = Read<float>();
	v.z = Read<float>();

	return v;
}


