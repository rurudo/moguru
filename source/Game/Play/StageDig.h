#pragma once
class StageDig
{
private:
	int m_DigPoint;
	int	m_SEWaterCnt;	//水中音のカウンタ
public:
	StageDig(void);
	~StageDig(void);
	void Update(void);
	void OPUpdate(float);
};

