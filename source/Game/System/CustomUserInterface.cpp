#include "CustomUserInterface.h"

CustomUserInterface::CustomUserInterface(void)
{
	m_Size.x = 1.0;
	m_Size.y = 1.0;
	m_Handle = 0;
	m_InSpaceX = 0;
	m_InSpaceY = 0;
	m_OutSpaceX = 0;
	m_OutSpaceY = 0;
}

CustomUserInterface::~CustomUserInterface(void)
{
}

void CustomUserInterface::SetVisible(bool isVisible)
{
	m_Flags.Set(InterfaceFlag_Visible, isVisible);
}

void CustomUserInterface::Update(void)
{
}

void CustomUserInterface::Draw(int widthNum, int heightNum, int *handle)
{
	if(m_Flags.Get(InterfaceFlag_Visible))
	{
		if(m_Handle)
		{
			DXLibMath::DrawExtendGraphResize(m_Position.x, m_Position.y, m_Size.x, m_Size.y, m_Handle, 1);
		}
		// éqóvëfÇPÇ¬Ç†ÇΩÇËÇÃÉTÉCÉYÇéZèo
		double width = (m_Size.x - m_OutSpace.left - m_OutSpace.right - widthNum * (m_InSpace.left + m_InSpace.right)) / widthNum;
		double height = (m_Size.y - m_OutSpace.up - m_OutSpace.down - heightNum * (m_InSpace.up + m_InSpace.down)) / heightNum;
		int w, h;
		DXLibMath::ConvertPixcel(width, height, &w, &h);
		for(int i = 0; i < heightNum; i++)
		{
			for(int j = 0; j < widthNum; j++)
			{
				double posX = m_Position.x + m_OutSpace.left + m_InSpace.left;
				double posY = m_Position.y + m_OutSpace.up + m_InSpace.up;
				int x, y;
				DXLibMath::ConvertPixcel(posX, posY, &x, &y);
				x += j * (w + m_InSpaceX + m_OutSpaceX);
				y += i * (h + m_InSpaceY + m_OutSpaceY);
				DrawExtendGraph(x, y, x + w, y + h, handle[i * widthNum + j], TRUE);
			}
		}
	}
}

void CustomUserInterface::Draw(int widthNum, int heightNum, int *handle,char judgeList[],int sortList[],int judgeVal[],int judgeNum,int silhouetteVal[],int silhouetteNum)
{
	bool l_flag = false;

	if(m_Flags.Get(InterfaceFlag_Visible))
	{
		if(m_Handle)
		{
			DXLibMath::DrawExtendGraphResize(m_Position.x, m_Position.y, m_Size.x, m_Size.y, m_Handle, 1);
		}
		// éqóvëfÇPÇ¬Ç†ÇΩÇËÇÃÉTÉCÉYÇéZèo
		double width = (m_Size.x - m_OutSpace.left - m_OutSpace.right - widthNum * (m_InSpace.left + m_InSpace.right)) / widthNum;
		double height = (m_Size.y - m_OutSpace.up - m_OutSpace.down - heightNum * (m_InSpace.up + m_InSpace.down)) / heightNum;
		int w, h;
		DXLibMath::ConvertPixcel(width, height, &w, &h);
		for(int i = 0; i < heightNum; i++)
		{
			for(int j = 0; j < widthNum; j++)
			{
				double posX = m_Position.x + m_OutSpace.left + m_InSpace.left;
				double posY = m_Position.y + m_OutSpace.up + m_InSpace.up;
				int x, y;
				DXLibMath::ConvertPixcel(posX, posY, &x, &y);
				x += j * (w + m_InSpaceX + m_OutSpaceX);
				y += i * (h + m_InSpaceY + m_OutSpaceY);

				for(int k=0;k<judgeNum;k++){
					if(judgeList[sortList[i * widthNum + j]] == judgeVal[k]){
						SetDrawBright( 100 , 100 , 100 );
						l_flag = true;
						break;
					}
				}

				if(!l_flag){
					for(int k=0;k<silhouetteNum;k++){
						if(judgeList[sortList[i * widthNum + j]] == silhouetteVal[k]){
							SetDrawBright( 0 , 0 , 0 );
							break;
						}
					}
				}

				DrawExtendGraph(x, y, x + w, y + h, handle[i * widthNum + j], TRUE);
				SetDrawBright( 255 , 255 , 255 );

				l_flag = false;
			}
		}
	}
}

void CustomUserInterface::GetPosition(int width, int height, int *x, int *y)
{

}

void CustomUserInterface::SetRect(double x, double y, double width, double height)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Size.x = width;
	m_Size.y = height;
}

void CustomUserInterface::SetRect(float x, float y, float width, float height)
{
	m_Position.x = static_cast<double>(x);
	m_Position.y = static_cast<double>(y);
	m_Size.x = static_cast<double>(width);
	m_Size.y = static_cast<double>(height);
}

void CustomUserInterface::SetPosition(double x, double y)
{
	m_Position.x = x;
	m_Position.y = y;
}

void CustomUserInterface::SetGraphicHandle(int handle)
{
	m_Handle = handle;
}

void CustomUserInterface::SetOutSpace(double up, double down, double left, double right)
{
	m_OutSpace.up = up;
	m_OutSpace.down = down;
	m_OutSpace.left = left;
	m_OutSpace.right = right;
	DXLibMath::ConvertPixcel(up + down, left + right, &m_OutSpaceX, &m_OutSpaceY);
}

void CustomUserInterface::SetInSpace(double up, double down, double left, double right)
{
	m_InSpace.up = up;
	m_InSpace.down = down;
	m_InSpace.left = left;
	m_InSpace.right = right;
	DXLibMath::ConvertPixcel(up + down, left + right, &m_InSpaceX, &m_InSpaceY);
}