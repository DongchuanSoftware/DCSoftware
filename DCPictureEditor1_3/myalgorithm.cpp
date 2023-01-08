#include "myalgorithm.h"

#include<QDialog>
#include<QDebug>

void HSV_RGB(double h,double s,double v,int& r,int& g,int& b)
{
	int h1=(int)(h/60)%6;
	double f=h/60-h1;
	double p=v*(1-s);
	double q=v*(1-f*s);
	double t=v*(1-(1-f)*s);
	switch(h1)
	{
		case 0:{
			r=v*255;
			g=t*255;
			b=p*255;
			break;
		}
		case 1:{
			r=q*255;
			g=v*255;
			b=p*255;
			break;
		}
		case 2:{
			r=p*255;
			g=v*255;
			b=t*255;
			break;
		}
		case 3:{
			r=p*255;
			g=q*255;
			b=v*255;
			break;
		}
		case 4:{
			r=t*255;
			g=p*255;
			b=v*255;
			break;
		}
		case 5:{
			r=v*255;
			g=p*255;
			b=q*255;
			break;
		}
	}
}

void RGB_HSV(int r,int g,int b,int& h,double& s,double& v)
{
	int arr[3]={r,g,b};
	std::sort(arr,arr+3);
	//min=arr[0]
	if(arr[0]==arr[2])
	{
		h=0;
	}
	else if(arr[2]==r&&g>=b)
	{
		h=60*(g-b)/(double)(arr[2]-arr[0]);
	}
	else if(arr[2]==r&&g<b)
	{
		h=60*(g-b)/(double)(arr[2]-arr[0])+360;
	}
	else if(arr[2]==g)
	{
		h=60*(b-r)/(double)(arr[2]-arr[0])+120;
	}
	else if(arr[2]==b)
	{
		h=60*(r-g)/(double)(arr[2]-arr[0])+240;
	}
	
	if(arr[2]==0)
	{
		s=0;
	}
	else
	{
		s=1-(arr[0]/(double)arr[2]);
	}
    v=arr[2]/255.0;
}

double pointToDegree(QPoint o,QPoint a)
{
    if(a.x()>o.x())
    {
        return -std::atan((a.y()-o.y())/(float)(a.x()-o.x()))*180/3.1415926;
    }
    else if(a.x()<o.x())
    {
        return 180-std::atan((a.y()-o.y())/(float)(a.x()-o.x()))*180/3.1415926;
    }
    else
    {
        return (a.y()<o.y())?90:270;
    }
}

void drawMyArc(QPainter *p, QPoint o, int r, QPoint s, QPoint e)
{
    if(o==s||o==e)return;
    double sd=pointToDegree(o,s);
    double ed=pointToDegree(o,e);
    double x=ed-sd+360;
    x=x>360?(x-360):x;
    p->drawArc(o.x()-r,o.y()-r,r*2,r*2,
               sd*16,
               (x<=180?x:(x-360))*16);
}
