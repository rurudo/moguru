#pragma once
class StageDig
{
private:
	int m_DigPoint;
	int	m_SEWaterCnt;	//�������̃J�E���^
public:
	StageDig(void);
	~StageDig(void);
	void Update(void);
	void OPUpdate(float);
};

