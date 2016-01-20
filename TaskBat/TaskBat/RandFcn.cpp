#include "RandFcn.h"
#include "stdafx.h"
#include <cmath>
VOID RandValue(int min, int max, int &n)
{
    int range;
	double j;
	range=max-min; 

//    srand((unsigned)time(NULL)); //初始化随机种子   

    n=rand();  
	j=((double)n/(double)RAND_MAX); 
	if(range<10000)
	{
        n=(int)(j*10000.0)%range;
	}
	else
	{
	    n=(int)(j*(double)range); /*把校正值乘以所需要的范围值(即500-50)从而产生一个在0到43之间的值*/ 
    }
	n+=min;
}

VOID RandValueFloat(float min, float max, float &n)
{
    float range;
	double j;
	range=max-min; 

//    srand((unsigned)time(NULL)); //初始化随机种子   

    n=rand();  
	j=((double)n/(double)RAND_MAX); 
    n=(float)(j*(double)range); /*把校正值乘以所需要的范围值(即500-50)从而产生一个在0到43之间的值*/ 
	n+=min;
}

VOID RandArray(int num, int range, int *dst)
{
    int i;
    
//    srand((unsigned)time(NULL)); //初始化随机种子   
    
    for(i=0; i<num; i++)   
    {   
        //生成一个0~(100-i)中的随机下标(第一次是0~99,   第二次就是0~98...)   
        dst[i] = rand() % range;   
	}   
}

int* Sort(int count, int *arr)
{
    int i,j,tmp;
    for(i=0;i<count; i++)
	{
        for(j=count-1;j>i;j--)
		{
            if(arr[j]<arr[j-1])
			{
                tmp=arr[j-1];
                arr[j-1]=arr[j];
                arr[j]=tmp;
            }
         }
    }
    return arr;
}

int Distance(int c,int a)
{
	return (int)sqrt(double((c+a)*(c-a)));
}

VOID RandPath(int num, int *dst)
{
    int i, turn, *src;
	src = new int[num];   
    for(i=0; i<num; i++)  
	{
        src[i] = i; //初始化源数组   
		dst[i] = 0; //初始化源数组 
	}

	turn = num/2;   

//    srand((unsigned)time(NULL)); //初始化随机种子   
    
    for(i=0; i<turn; i++)   
    {   
        int temp;   
     
        //生成一个0~(100-i)中的随机下标(第一次是0~99,   第二次就是0~98...)   
        int j = rand()%(num-i);   
    
        //从源数组中取这个标号所对应的值   
        dst[src[j]] = 1;   
    
        //将这个数组元素放到最后(第一次是src[99]上,   第二次就是src[98]上...)   
        temp = src[j];   
        src[j] = src[num-1-i];   
        src[num-1-i] = temp;   
	}   
	delete src;
}

VOID RandPausePoint(int t, int m, int *dsts, int *dste)
{
	int i;
	double j;
	double rangex,rangey;
//    srand((unsigned)time(NULL)); //初始化随机种子   
	rangex = (double)t/(double)(m*2);
	rangey = 2.0;
    for(i=0;i<m;i++)
	{
		dsts[i] = rand();  
		j=((double)dsts[i]/(double)RAND_MAX); 
		dsts[i] = (double)t/(double)m * (double)i + (int)((double)j*rangex);
	}
    for(i=0;i<m;i++)
	{
		dste[i] = rand();  
		j=((double)dste[i]/(double)RAND_MAX); 
		dste[i] = dsts[i] + 2 + (int)((double)j*rangey); /*把校正值乘以所需要的范围值(即500-50)从而产生一个在0到43之间的值*/ 
    } 
}

VOID RandEventOrder(int t, int m, int *dst)
{
	int i;
	double j;
	int rangex;
//    srand((unsigned)time(NULL)); //初始化随机种子   
	if (m > 1)
		rangex = (t-2)/(m-1) - 2;
	else
		rangex = t;
	dst[0] = 2 + (1.0*rand()/(double)RAND_MAX)*rangex;
    for(i=1;i<m;i++)
	{
		/*dst[i] = rand();  
		j=((double)dst[i]/(double)RAND_MAX); 
		dst[i] = i*((float)t/(float)m) + (int)(j*(double)rangex) + 2;*/

		dst[i] = dst[i-1] + (1.0*rand()/(double)RAND_MAX)*rangex + 2;
	}
}

VOID RandPoint(int x, int y, int m, POINT *dst)
{
	int i;
    int rangex,rangey;
	double j;
	
//    srand((unsigned)time(NULL)); //初始化随机种子   

	rangex=x; 
    rangey=y;

	for(i=0;i<m;i++)
	{
		dst[i].x=rand();  
		j=((double)dst[i].x/(double)RAND_MAX); 
		dst[i].x=(int)(j*(double)rangex);
		dst[i].y=rand();  
		j=((double)dst[i].y/(double)RAND_MAX); 
		dst[i].y=(int)(j*(double)rangey); /*把校正值乘以所需要的范围值(即500-50)从而产生一个在0到43之间的值*/ 
    } 
}

VOID RandPoint1(int num, int r, int resx, int resy, int *dstx, int *dsty)
{
    short *Sig;
	short *Laby, *Labx;
	int minx, maxx, miny, maxy;
	int b,my,mx,n;
	int lB,uB;
	int i,j,k,sd;

	minx = r*3+1;
	maxx = resx-r*3;
	miny = minx;
	maxy = resy-r*3;
	Sig = new short[maxy-miny+1];
	Laby = new short[maxy-miny+1];
	Labx = new short[maxx-minx+1];
	mx = maxx-minx+1;
    for(k=0;k<maxx-minx+1;k++)
	{
        Labx[k] = k;
	}
//	srand((unsigned)time(NULL)); //初始化随机种子   
	dstx[0]=(int)((double)rand()/(double)RAND_MAX*(double)(maxx-minx)); 
//	RandValue(time(NULL), 0, maxx-minx, dstx[0]);
//	RandValue(time(NULL), 0, maxy-miny, dsty[0]);
	dsty[0]=(int)((double)rand()/(double)RAND_MAX*(double)(maxy-miny)); 
//	sd = dsty[0];
	for(i=1;i<num;i++)
	{
		my = 0;
		while(my<1)
		{
            n = (int)((double)rand()/(double)RAND_MAX*(double)(mx-1));
			//RandValue(time(NULL), 0, mx-1, n);
			dstx[i] = Labx[n];
 //           dstx[i] += sd;
			if(dstx[i]>maxx-minx)
			{
                dstx[i] = dstx[i] - (maxx-minx);
			}
			sd = dstx[i];
			for(k=0;k<maxy-miny+1;k++)
			{
                Sig[k] = 0;
			}
			for(j=i;j>0;j--)
			{
				if((abs(dstx[i]-dstx[j-1]))<(4*r))
				{
					b = Distance(4*r,abs(dstx[i]-dstx[j-1]));
					lB = dsty[j-1]-b;
					uB = dsty[j-1]+b;
					if(lB<0)
					{
						lB = 0;
					}
					if(uB>maxy-miny)
					{
						uB = maxy-miny;
					}
					for(k=lB;k<uB+1;k++)
					{
						Sig[k] = 1;
					}
				}
			}
			my = 0;
			for(k=0;k<maxy-miny+1;k++)
			{
                if(Sig[k] == 0)
				{
				    Laby[my] = k;
				    my++;
				}
			}
			if(my<1)
			{
				mx--;
				for(k=0;k<mx;k++)
				{
					if(Labx[k]>=dstx[i])
					{
					    Labx[k] += 1;
					}
				} 
			}
		}
        n=(int)((double)rand()/(double)RAND_MAX*(double)(my-1));
//      RandValue(time(NULL), 0, my-1, n);
        dsty[i] = Laby[n];
	}
	for(i=0;i<num;i++)
	{
		dstx[i] += r*3+1;
        dsty[i] += r*3+1;
	}
    delete Sig;
	delete Laby;
	delete Labx;
}

VOID RandPoint2(int num, int r, float cwidth, float cheight, int resx, int resy, int *dstx, int *dsty)
{
    short *Sig;
	short *Laby, *Labx;
	int minx, maxx, miny, maxy;
	int b,my,mx,n;
	int lB,uB;
	int i,j,k;

	minx = r*3+1;
	maxx = resx-r*3;
	miny = minx;
	maxy = resy-r*3;
	Sig = new short[maxy-miny+1];
	Laby = new short[maxy-miny+1];
	Labx = new short[maxx-minx+1];
	mx = maxx-minx+1;
    for(k=0;k<maxx-minx+1;k++)
	{
        Labx[k] = k;
	}
//	srand((unsigned)time(NULL)); //初始化随机种子   
//	dstx[0]=(int)((double)rand()/(double)RAND_MAX*(double)(maxx-minx)); 
//	dsty[0]=(int)((double)rand()/(double)RAND_MAX*(double)(maxy-miny)); 
	for(i=0;i<num;i++)
	{
		my = 0;
		while(my<1)
		{
            n = (int)((double)rand()/(double)RAND_MAX*(double)(mx-1));
			dstx[i] = Labx[n];
			for(k=0;k<maxy-miny+1;k++)
			{
                Sig[k] = 0;
			}
			for(j=i;j>0;j--)
			{
				if((abs(dstx[i]-dstx[j-1]))<(4*r))
				{
					b = Distance(4*r,abs(dstx[i]-dstx[j-1]));
					lB = dsty[j-1]-b;
					uB = dsty[j-1]+b;
					if(lB<0)
					{
						lB = 0;
					}
					if(uB>maxy-miny)
					{
						uB = maxy-miny;
					}
					for(k=lB;k<uB+1;k++)
					{
						Sig[k] = 1;
					}
				}
			}
			if((abs(dstx[i]-((maxx-minx+1)/2)))<(r+cwidth/2))
			{
				lB = (maxy-miny+1)/2-(r+cheight/2);
				uB = (maxy-miny+1)/2+r+cheight/2;
				if(lB<0)
				{
					lB = 0;
				}
				if(uB>maxy-miny)
				{
					uB = maxy-miny;
				}
				for(k=lB;k<uB+1;k++)
				{
					Sig[k] = 1;
				}
			}            
			my = 0;
			for(k=0;k<maxy-miny+1;k++)
			{
                if(Sig[k] == 0)
				{
				    Laby[my] = k;
				    my++;
				}
			}
			if(my<1)
			{
				mx--;
				for(k=0;k<mx;k++)
				{
					if(Labx[k]>=dstx[i])
					{
					    Labx[k] += 1;
					}
				} 
			}
		}
        n=(int)((double)rand()/(double)RAND_MAX*(double)(my-1));
        dsty[i] = Laby[n];
	}
	for(i=0;i<num;i++)
	{
		dstx[i] += r*3+1;
        dsty[i] += r*3+1;
	}
    delete Sig;
	delete Laby;
	delete Labx;
}

VOID RandPoint3(int num, int r, POINT p1, POINT p2, float cwidth, float cheight, int resx, int resy, int *dstx, int *dsty)
{
    short *Sig;
	short *Laby, *Labx;
	int minx, maxx, miny, maxy;
	int b,my,mx,n;
	int lB,uB;
	int i,j,k;

	minx = r*3+1;
	maxx = resx-r*3;
	miny = minx;
	maxy = resy-r*3;
	Sig = new short[maxy-miny+1];
	Laby = new short[maxy-miny+1];
	Labx = new short[maxx-minx+1];
	mx = maxx-minx+1;
    for(k=0;k<maxx-minx+1;k++)
	{
        Labx[k] = k;
	}
//	srand((unsigned)time(NULL)); //初始化随机种子   
//	dstx[0]=(int)((double)rand()/(double)RAND_MAX*(double)(maxx-minx)); 
//	dsty[0]=(int)((double)rand()/(double)RAND_MAX*(double)(maxy-miny)); 
	for(i=0;i<num;i++)
	{
		my = 0;
		while(my<1)
		{
            n = (int)((double)rand()/(double)RAND_MAX*(double)(mx-1));
			dstx[i] = Labx[n];
			for(k=0;k<maxy-miny+1;k++)
			{
                Sig[k] = 0;
			}
			for(j=i;j>0;j--)
			{
				if((abs(dstx[i]-dstx[j-1]))<(4*r))
				{
					b = Distance(4*r,abs(dstx[i]-dstx[j-1]));
					lB = dsty[j-1]-b;
					uB = dsty[j-1]+b;
					if(lB<0)
					{
						lB = 0;
					}
					if(uB>maxy-miny)
					{
						uB = maxy-miny;
					}
					for(k=lB;k<uB+1;k++)
					{
						Sig[k] = 1;
					}
				}
			}
			if(abs(dstx[i]-(p1.x-minx))<(r+cwidth+cwidth/2))
			{
				lB = p1.y-miny-(r+cheight+cheight/2);
				uB = p1.y-miny+r+cheight+cheight/2;
				if(lB<0)
				{
					lB = 0;
				}
				if(uB>maxy-miny)
				{
					uB = maxy-miny;
				}
				for(k=lB;k<uB+1;k++)
				{
					Sig[k] = 1;
				}
			}    
            if(abs(dstx[i]-(p2.x-minx))<(r+cwidth+cwidth/2))
			{
				lB = p2.y-miny-(r+cheight+cheight/2);
				uB = p2.y-miny+r+cheight+cheight/2;
				if(lB<0)
				{
					lB = 0;
				}
				if(uB>maxy-miny)
				{
					uB = maxy-miny;
				}
				for(k=lB;k<uB+1;k++)
				{
					Sig[k] = 1;
				}
			}        
			my = 0;
			for(k=0;k<maxy-miny+1;k++)
			{
                if(Sig[k] == 0)
				{
				    Laby[my] = k;
				    my++;
				}
			}
			if(my<1)
			{
				mx--;
				for(k=0;k<mx;k++)
				{
					if(Labx[k]>=dstx[i])
					{
					    Labx[k] += 1;
					}
				} 
			}
		}
        n=(int)((double)rand()/(double)RAND_MAX*(double)(my-1));
        dsty[i] = Laby[n];
	}
	for(i=0;i<num;i++)
	{
		dstx[i] += r*3+1;
        dsty[i] += r*3+1;
	}
    delete Sig;
	delete Laby;
	delete Labx;
}

VOID RandOrder(int num, int *dst)
{
    int i, *src;
	src = new int[num];   
    for(i=0; i<num; i++)  
	{
        src[i] = i; //初始化源数组   
	}
    
//    srand((unsigned)time(NULL)); //初始化随机种子   
    
    for(i=0; i<num; i++)   
    {   
        int temp;   
     
        //生成一个0~(100-i)中的随机下标(第一次是0~99,   第二次就是0~98...)   
		int j = rand()%(num-i);   
    
        //从源数组中取这个标号所对应的值   
        dst[i] = src[j];   
    
        //将这个数组元素放到最后(第一次是src[99]上,   第二次就是src[98]上...)   
        temp = src[j];   
        src[j] = src[num-1-i];   
        src[num-1-i] = temp;   
	}   
	delete src;
}

VOID RandOrder1(int num, int getnum, int *dst)
{
    int i, *src;
	src = new int[num];   
    for(i=0; i<num; i++)  
	{
        src[i] = i; //初始化源数组   
	}
    
//    srand((unsigned)time(NULL)); //初始化随机种子   
    
    for(i=0; i<getnum; i++)   
    {   
        int temp;   
     
        //生成一个0~(100-i)中的随机下标(第一次是0~99,   第二次就是0~98...)   
		int j = rand()%(num-i);   
    
        //从源数组中取这个标号所对应的值   
        dst[i] = src[j];   
    
        //将这个数组元素放到最后(第一次是src[99]上,   第二次就是src[98]上...)   
        temp = src[j];   
        src[j] = src[num-1-i];   
        src[num-1-i] = temp;   
	}   
	delete src;
}