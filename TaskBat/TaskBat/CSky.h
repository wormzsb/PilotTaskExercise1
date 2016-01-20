#ifndef __CSKY__H__
#define __CSKY__H__

#include <list>
#include "CStar.h"
using namespace std ;

class CSky
{
private:
	typedef list<CStar*> CStarList;

	CStarList Stars;
	CStarList::iterator i;

	int MaxStarNum; //星星个数
	int R; //视半径
	int V; //星星每帧移动像素个数
	int zBufferFront; //前缓冲区起始坐标
	int zBufferBack; //后缓冲区起始坐标

	void Seed(int Num, int zMin, int zMax)
	{
		int i, c=Num;
		for (i=0; i<c; i++)
		{
			Stars.insert(Stars.end(), new CStar(R, zMin, zMax));
		}
	}

	//画图优化
	RECT rect;

	void Prepare(int R)
	{
		rect.left = rect.top = 0;
		rect.right = rect.bottom = R*2;
	}

public:
	CSky(int Num=4000, int R=512, int V=4)
	{
		this->MaxStarNum = Num;
		this->R = R;
		this->V = V;
		this->zBufferFront = R*2;
		this->zBufferBack = -R*2;
		
		Prepare(R);

		Seed(Num*2, -R, R*2);
	}

	void NextFrame()
	{
		CStar* star;
        int c = (int)Stars.size();
		//移动星星
		if (V >= 0)
		{
			for (i = Stars.begin(); i != Stars.end(); ++i)
			{
				star = *i;
				star->z -= V;
				if (star->z < -R) //移出视界
				{
					i = Stars.erase(i);
					delete star;
				}
			}

			//移动缓冲区
			zBufferFront -= V;

			if (zBufferFront <= R)
			{
				zBufferFront = R*2;
			}
			
			//补充星星
			Seed(c-(int)Stars.size(), zBufferFront, zBufferFront+R);
		}
		else
		{
			for (i = Stars.begin(); i != Stars.end(); ++i)
			{
				star = *i;
				star->z -= V;
				if (star->z > R*2) //移出视界
				{
					i = Stars.erase(i);
					delete star;
				}
			}

			//移动缓冲区
			zBufferBack -= V;

			if (zBufferBack >= -R)
			{
				zBufferBack = -R*2;
			}
			
			//补充星星
			Seed(c-(int)Stars.size(), zBufferBack, zBufferBack+R);
		}
	}

	void Show(LPDIRECT3DDEVICE9 &g_pd3dDevice)
	{
		//准备GDI资源
//		CDC* pDC = pWnd->GetDC();
//		CBitmap bmp, *pBmpOld;
//		CDC memdc;
		
//		bmp.CreateCompatibleBitmap(pDC, rect.right, rect.bottom);
//		memdc.CreateCompatibleDC(pDC);
//		pBmpOld = memdc.SelectObject(&bmp);

		//在内存里画星星
		CStar* star;

		for (i = Stars.begin(); i != Stars.end(); ++i)
		{
			star = *i;
			star->Show(g_pd3dDevice, R);
		}

		//显示到屏幕上
//		RECT r;
//		pWnd->GetClientRect(&r);
//		pDC->BitBlt(0, 0, r.right, r.bottom, &memdc, (rect.right-r.right)/2, (rect.bottom-r.bottom)/2, SRCCOPY);

		//释放GDI资源
//		memdc.SelectObject(pBmpOld);
//		pWnd->ReleaseDC(pDC);
	}

	void AddV(int dv)
	{
		int vSave = V;

		V += dv;
		if (vSave<0 && V>=0)
		{
			zBufferFront = R*2;
		}
		else if (vSave>=0 && V<0)
		{
			zBufferBack = -R*2;
		}
	}
};


#endif //__CSKY__H__