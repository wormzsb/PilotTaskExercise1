#ifndef __CSTAR__H__
#define __CSTAR__H__

#include "math.h"
#include <d3d9.h>
#include <d3dx9.h>

int Random(int max);

extern struct CUSTOMVERTEX
{
	FLOAT x, y, z, rhw;
	DWORD color;
};
class CStar
{
private:
	int GetRandomXY(int R)
	{
		int r = (int)(R)-6;
		return (rand()%2 == 0) ? Random(r) : -Random(r);
	}

public:
	int x, y, z; //ÈýÎ¬×ø±ê
	int r; //Çò°ë¾¶
//	CBrush* pBrush;
	CUSTOMVERTEX vertices[4];
	
	CStar(int R, int zMin, int zMax)
	{
		x = GetRandomXY(R);
		y = GetRandomXY(R);
		z = zMin + Random(zMax - zMin);
		r = 4;
		
//		pBrush = Brushes[Random(4)];
	}

	void Show(LPDIRECT3DDEVICE9 &g_pd3dDevice, int R)
	{
		if (this->z<0 || this->z>R) return;

		int l = (int)pow((double)(x*x+y*y+z*z), 0.5);
		if (l <= R)
		{
			double f = (double)(R-this->z)/(double)R;
			int r = 1 + (int)((double)(R-l)/(double)R*this->r);
			int x = R + (int)((double)(this->x)/(double)(10+this->z)*R);
			int y = R + (int)((double)(this->y)/(double)(10+this->z)*R);

			vertices[0].x = x;
			vertices[0].y = y;
			vertices[0].z = 0.0f;
			vertices[0].rhw = 0.5f;
			vertices[0].color = 0x00ffffff;
			vertices[1].x = x+r;
			vertices[1].y = y;
			vertices[1].z = 0.0f;
			vertices[1].rhw = 0.5f;
            vertices[1].color = 0x00ffffff;
			vertices[2].x = x+r;
			vertices[2].y = y+r;
			vertices[2].z = 0.0f;
			vertices[2].rhw = 0.5f;
			vertices[2].color = 0x00ffffff;
			vertices[3].x = x;
			vertices[3].y = y+r;
			vertices[3].z = 0.0f;
			vertices[3].rhw = 0.5f;
			vertices[3].color = 0x00ffffff;
			g_pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN,2,vertices,sizeof(CUSTOMVERTEX)); //»­Í¼ÐÎ
//			dc.FillRect(&CRect(x, y, x+r, y+r), pBrush);//&brWhite);
		}
	}


};

#endif //__CSTAR__H__