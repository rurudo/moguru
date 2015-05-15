#pragma once
#include "../System/DxLibMath.h"
#include "../System/DataManager.h"

class ItemEquip
{
	public:
		ItemEquip(void);
		~ItemEquip(void);

		//èâä˙âª
		void Init(void);
		//âï˙
		void Release(void);
		//çXêV
		void Update(void);
		//ï`âÊ
		void Draw(void);

		//
		void SetEnable(bool flag);

		void SetTarget(float targetX,float targetY);
		void SetReverse(bool flag);

		bool GetReverseFlag(void);
		bool GetMoveFlag(void);
		bool GetStayFlag(void);
		int GetSlotSize(void);
		void GetDefPos(int* x,int* y);
		int GetDefPosX(void);
		int GetDefPosY(void);
		int GetWidth(void);
		int GetHeight(void);
		DXLibMath::Vector2 GetPosition(void);

		void Reset(void);
	private:
		DXLibMath::Vector2		m_Pos;
		DXLibMath::Vector2		m_SlotPos;
		DXLibMath::Vector2		m_TargetPos;

		bool					m_Enable;
		bool					m_MoveFlag;
		bool					m_StayFlag;
		bool					m_ReverseFlag;

		int						m_Alpha;
		int						m_Frame;
		int						m_MoveStep;
		int						m_ReverseStep;

		int						m_BackOffset;

		static const int DefaultPosX;
		static const int DefaultPosY;
		static const int DefaultWidth;
		static const int DefaultHeight;

		static const int DefaultFontPosX;
		static const int DefaultFontPosY;
		static const int DefaultFontSize;

		static const int TargetOffset;

		enum Step{
			Step1,
			Step2
		};

		enum Frame{
			Frame1 = 10,
			Frame2 = 5
		};
};

