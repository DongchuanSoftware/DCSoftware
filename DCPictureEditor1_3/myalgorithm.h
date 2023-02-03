#ifndef MYALGORITHM_H
#define MYALGORITHM_H

#include<algorithm>
#include<cmath>
#include<QPoint>
#include<queue>
#include<QPainter>
#include<QPixmap>
#include<QImage>

void HSV_RGB(double h,double s,double v,int& r,int& g,int& b);
void RGB_HSV(int r,int g,int b,int& h,double& s,double& v);

double pointToDegree(QPoint o,QPoint a);

class MyPainter:public QPainter
{
private:
    QImage* imgDevice;
    QImage* texture;
    int xOffset;
    int yOffset;
    QPoint ap;
public:
    MyPainter();
    
    void setSealTool(QImage* _imgDevice,QPoint a,QImage* _texture,QPoint aPrime);
    
    void drawMyArc(QPoint o,int r,QPoint s,QPoint e);
    void drawMyLine(QPoint a,QPoint b);
};

#endif // MYALGORITHM_H
