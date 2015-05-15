#pragma once
#include<vector>
class BoolArray
{
private:
	std::vector<unsigned int> m_Value;
public:
	BoolArray(void);
	~BoolArray(void);
	void Set(unsigned int index, bool in);
	bool Get(unsigned int index);
	void Clear(void);
};

