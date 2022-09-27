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

//void DrawCircle(const QPoint& o,int r,QPainter* painter,const QPixmap& pix,QImage img,QColor (*function)(QColor c));

void DrawCircle(const QPoint& o, int r, QPixmap& pix,const QPixmap& texture);
void DrawSolidCircle(const QPoint &o,int r, QPixmap &pix,const QPixmap &texture);

#endif // MYALGORITHM_H
