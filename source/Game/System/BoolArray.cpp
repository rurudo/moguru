#include "BoolArray.h"

BoolArray::BoolArray(void)
{
}

BoolArray::~BoolArray(void)
{
}

void BoolArray::Set(unsigned int index, bool in)
{
	unsigned int num = index / sizeof(unsigned int);
	if(num + 1 > m_Value.size())
	{
		m_Value.resize(num + 1);
	}
	unsigned int mask = 1 << (index % sizeof(unsigned int));
	m_Value[num] = (in ? m_Value[num]|mask : m_Value[num]&~mask);
}

bool BoolArray::Get(unsigned int index)
{
	unsigned int num = index / sizeof(unsigned int);
	if(num + 1 > m_Value.size())
	{
		return false;
	}
	unsigned int mask = 1 << (index % sizeof(unsigned int));
	return ((m_Value[num] & mask) == mask);
}

void BoolArray::Clear(void)
{
	m_Value.clear();
}