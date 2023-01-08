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

void drawMyArc(QPainter* p,QPoint o,int r,QPoint s,QPoint e);

#endif // MYALGORITHM_H
