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

	int MaxStarNum; //���Ǹ���
	int R; //�Ӱ뾶
	int V; //����ÿ֡�ƶ����ظ���
	int zBufferFront; //ǰ��������ʼ����
	int zBufferBack; //�󻺳�����ʼ����

	void Seed(int Num, int zMin, int zMax)
	{
		int i, c=Num;
		for (i=0; i<c; i++)
		{
			Stars.insert(Stars.end(), new CStar(R, zMin, zMax));
		}
	}

	//��ͼ�Ż�
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
		//�ƶ�����
		if (V >= 0)
		{
			for (i = Stars.begin(); i != Stars.end(); ++i)
			{
				star = *i;
				star->z -= V;
				if (star->z < -R) //�Ƴ��ӽ�
				{
					i = Stars.erase(i);
					delete star;
				}
			}

			//�ƶ�������
			zBufferFront -= V;

			if (zBufferFront <= R)
			{
				zBufferFront = R*2;
			}
			
			//��������
			Seed(c-(int)Stars.size(), zBufferFront, zBufferFront+R);
		}
		else
		{
			for (i = Stars.begin(); i != Stars.end(); ++i)
			{
				star = *i;
				star->z -= V;
				if (star->z > R*2) //�Ƴ��ӽ�
				{
					i = Stars.erase(i);
					delete star;
				}
			}

			//�ƶ�������
			zBufferBack -= V;

			if (zBufferBack >= -R)
			{
				zBufferBack = -R*2;
			}
			
			//��������
			Seed(c-(int)Stars.size(), zBufferBack, zBufferBack+R);
		}
	}

	void Show(LPDIRECT3DDEVICE9 &g_pd3dDevice)
	{
		//׼��GDI��Դ
//		CDC* pDC = pWnd->GetDC();
//		CBitmap bmp, *pBmpOld;
//		CDC memdc;
		
//		bmp.CreateCompatibleBitmap(pDC, rect.right, rect.bottom);
//		memdc.CreateCompatibleDC(pDC);
//		pBmpOld = memdc.SelectObject(&bmp);

		//���ڴ��ﻭ����
		CStar* star;

		for (i = Stars.begin(); i != Stars.end(); ++i)
		{
			star = *i;
			star->Show(g_pd3dDevice, R);
		}

		//��ʾ����Ļ��
//		RECT r;
//		pWnd->GetClientRect(&r);
//		pDC->BitBlt(0, 0, r.right, r.bottom, &memdc, (rect.right-r.right)/2, (rect.bottom-r.bottom)/2, SRCCOPY);

		//�ͷ�GDI��Դ
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