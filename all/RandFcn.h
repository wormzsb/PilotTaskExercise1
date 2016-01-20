
VOID RandValue(int min, int max, int &n);

VOID RandValueFloat(float min, float max, float &n);

VOID RandArray(int num, int range, int *dst);

int* Sort(int count, int *arr);

int Distance(int c,int a);

VOID RandPath(int num, int *dst);

VOID RandPausePoint(int t, int m, int *dsts, int *dste);

VOID RandEventOrder(int t, int m, int *dst);

VOID RandPoint(int x, int y, int m, POINT *dst);

VOID RandPoint1(int num, int r, int resx, int resy, int *dstx, int *dsty);

VOID RandPoint2(int num, int r, float cwidth, float cheight, int resx, int resy, int *dstx, int *dsty);

VOID RandPoint3(int num, int r, POINT p1, POINT p2, float cwidth, float cheight, int resx, int resy, int *dstx, int *dsty);

VOID RandOrder(int num, int *dst);

VOID RandOrder1(int num, int getnum, int *dst);