#include "ItemEquip.h"
#include "MixTreeData.h"

const int ItemEquip :: DefaultFontPosX		= 11;
const int ItemEquip :: DefaultFontPosY		= 10;
const int ItemEquip :: DefaultFontSize		= 45;

const int ItemEquip :: DefaultPosX			= 616;
const int ItemEquip :: DefaultPosY			= 440;
const int ItemEquip :: DefaultWidth			= 170;
const int ItemEquip :: DefaultHeight		= 135;

const int ItemEquip :: TargetOffset			= 45;

ItemEquip::ItemEquip(void){
	Init();
}


ItemEquip::~ItemEquip(void){
}


void ItemEquip :: Init(void){
	m_Enable = false;
	Reset();
}

void ItemEquip :: Update(void){
	if(m_MoveFlag){
		switch(m_MoveStep){
		case Step1:
			m_Pos.x -= (DefaultPosX - m_TargetPos.x) / Frame1;
			if(m_Pos.x < m_TargetPos.x){
				m_Pos.x = m_TargetPos.x;
			}
			m_Pos.y -= (DefaultPosY - m_TargetPos.y) / Frame1;
			if(m_Pos.y < m_TargetPos.y){
				m_Pos.y = m_TargetPos.y;
			}

			m_SlotPos.x -= (DefaultPosX - m_TargetPos.x) / Frame1;
			if(m_SlotPos.x < m_TargetPos.x){
				m_SlotPos.x = m_TargetPos.x;
			}
			m_SlotPos.y -= (DefaultPosY - m_TargetPos.y) / Frame1;
			if(m_SlotPos.y < m_TargetPos.y){
				m_SlotPos.y = m_TargetPos.y;
			}

			if(m_Frame > Frame1){
				m_Frame = 0;
				m_MoveStep++;
			}
			m_Frame++;
			break;
		case Step2:
			m_Pos.x += TargetOffset / Frame2;
			m_BackOffset += TargetOffset / Frame2;

			if(m_Frame > Frame2){
				m_Frame = 0;
				m_Pos.x = m_TargetPos.x+TargetOffset;
				m_BackOffset = (int)(TargetOffset);
				m_MoveFlag = false;
				m_StayFlag = true;
				m_MoveStep = Step1;
				m_ReverseStep = Step1;
			}
			m_Frame++;
			break;
		}
	}
	if(m_ReverseFlag){
		switch(m_ReverseStep){
		case Step1:
			m_Pos.x -= TargetOffset / Frame2;
			m_BackOffset -= TargetOffset / Frame2;

			if(m_Frame > Frame2){
				m_Frame = 0;
				m_Pos.x = m_TargetPos.x+TargetOffset;
				m_BackOffset = (int)(TargetOffset);
				m_MoveFlag = false;
				m_ReverseStep++;
			}
			m_Frame++;
			break;
		case Step2:
			m_Pos.x += (DefaultPosX - m_TargetPos.x) / Frame1;
			if(m_Pos.x > DefaultPosX){
				m_Pos.x = DefaultPosX;
			}
			m_Pos.y += (DefaultPosY - m_TargetPos.y) / Frame1;
			if(m_Pos.y > DefaultPosY){
				m_Pos.y = DefaultPosY;
			}

			m_SlotPos.x += (DefaultPosX - m_TargetPos.x) / Frame1;
			if(m_SlotPos.x > DefaultPosX){
				m_SlotPos.x = DefaultPosX;
			}
			m_SlotPos.y += (DefaultPosY - m_TargetPos.y) / Frame1;
			if(m_SlotPos.y > DefaultPosY){
				m_SlotPos.y = DefaultPosY;
			}

			if(m_Frame > Frame1){
				m_Frame = 0;
				m_Pos.x = DefaultPosX;
				m_Pos.y = DefaultPosY;
				m_ReverseFlag = false;
				m_MoveStep = Step1;
				m_ReverseStep = Step1;
			}
			m_Frame++;
			break;
		}
	}
}

void ItemEquip :: Draw(void){
	DataManager &data = DataManager::GetInstance();

	if(m_Enable){
		//スロットのフレームのバックに半透明の白背景:装備仕様としている時(アイコンの上にあるとき)
		if(m_SlotPos.x != DefaultPosX){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);									//透過率のセット
			DrawBox( (int)m_SlotPos.x-5, (int)m_SlotPos.y-5, (int)m_SlotPos.x + DefaultWidth+5+m_BackOffset, (int)m_SlotPos.y + DefaultHeight+5, GetColor(255,255,255), TRUE );
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);									//透過率のセット
		}
		//アイコンの描画
		DrawGraph( (int)m_SlotPos.x, (int)m_SlotPos.y, data.Get( DataManager::Equipment_Icon_Frame ), TRUE );
		if(m_StayFlag){
			for( int i = 0; i < 3; i++ )
			{
				int id = data.m_MogllStatus.equip[i];
				if( id != -1 )
				{
					DrawExtendGraph((int)m_SlotPos.x, (int)m_SlotPos.y+(45*i),
									(int)m_SlotPos.x+45, (int)m_SlotPos.y+(45*i)+45, 
									data.GetGraphicGroupData( id + DataManager::GG_ITEM0 ), TRUE );
				}
			}
		}
		//スロットのフレームのバックに黒背景
		DrawBox( (int)m_Pos.x, (int)m_Pos.y, (int)m_Pos.x + DefaultWidth, (int)m_Pos.y + DefaultHeight, GetColor(0,0,0), TRUE );
		//スロットのフレーム描画
		DrawGraph( (int)m_Pos.x, (int)m_Pos.y, data.Get( DataManager::Equipment_Font_Frame ), TRUE );
		//装備の効果イメージテキスト
		for( int i = 0; i < 3; i++ )
		{
			int id = data.m_MogllStatus.equip[i];
			if( id != -1 )
			{
				id = (id/10)*30 + id%10;
				DrawGraph( (int)m_Pos.x+DefaultFontPosX, (int)m_Pos.y+DefaultFontPosY + i*DefaultFontSize, data.GetGraphicGroupData(DataManager::GG_STRING01_BLUE + id ), TRUE);
			}
		}
	}
}

void ItemEquip :: SetEnable(bool flag){
	m_Enable = flag;
}

void ItemEquip :: SetTarget(float targetX,float targetY){
	if(!m_MoveFlag && !m_ReverseFlag){
		m_TargetPos.x = targetX*800.0f+20;
		m_TargetPos.y = targetY*600.0f+20;
		m_BackOffset = 0;
		//m_ReverseFlag = false;
		m_MoveFlag = true;

		//m_Pos.x = (float)DefaultPosX;
		//m_Pos.y = (float)DefaultPosY;

		//m_SlotPos.x = m_Pos.x;
		//m_SlotPos.y = m_Pos.y;

		//m_BackOffset = 0;

		//m_Frame = 0;
	}
}

void ItemEquip :: SetReverse(bool flag){
	if(flag && m_StayFlag && !m_MoveFlag){
		m_ReverseFlag = flag;
		m_StayFlag = false;
	}
	else if(!flag){
		m_ReverseFlag = flag;
		m_MoveStep = Step1;
		m_ReverseStep = Step1;

		m_BackOffset = 0;

		m_Frame = 0;
	}
}

bool ItemEquip :: GetReverseFlag(void){
	return m_ReverseFlag;
}
bool ItemEquip :: GetMoveFlag(void){
	return m_MoveFlag;
}
bool ItemEquip :: GetStayFlag(void){
	return m_StayFlag;
}
int ItemEquip :: GetSlotSize(void){
	return TargetOffset;
}
void ItemEquip :: GetDefPos(int* x,int* y){
	*x = DefaultPosX;
	*y = DefaultPosY;
}
int ItemEquip :: GetDefPosX(void){
	return DefaultPosX;
}
int ItemEquip :: GetDefPosY(void){
	return DefaultPosY;
}
int ItemEquip :: GetWidth(void){
	return DefaultWidth;
}
int ItemEquip :: GetHeight(void){
	return DefaultHeight;
}
DXLibMath::Vector2 ItemEquip :: GetPosition(void){
	return m_SlotPos;
}

void ItemEquip :: Reset(void){
	m_MoveFlag = false;
	m_StayFlag = false;
	m_ReverseFlag = false;

	m_MoveStep = Step1;
	m_ReverseStep = Step1;

	m_Pos.x = (float)DefaultPosX;
	m_Pos.y = (float)DefaultPosY;

	m_SlotPos.x = m_Pos.x;
	m_SlotPos.y = m_Pos.y;

	m_TargetPos.x = m_Pos.x;
	m_TargetPos.y = m_Pos.y;

	m_Alpha;

	m_BackOffset = 0;

	m_Frame = 0;
}