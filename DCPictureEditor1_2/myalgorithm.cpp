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

void DrawCircle(const QPoint &o,int r, QPixmap &pix,const QPixmap &texture)
{
    int tmpx,tmpy;
    tmpx=o.x();
    tmpy=o.y()+r;
    
    QImage img=pix.toImage();
    QImage itext=texture.toImage();
    
    img.setPixelColor(o.x(),o.y()+r,itext.pixelColor(o.x(),o.y()+r));
    img.setPixelColor(o.x(),o.y()-r,itext.pixelColor(o.x(),o.y()-r));
    img.setPixelColor(o.x()+r,o.y(),itext.pixelColor(o.x()+r,o.y()));
    img.setPixelColor(o.x()-r,o.y(),itext.pixelColor(o.x()-r,o.y()));
    
    while(tmpx<=tmpy)
    {
        if((tmpx+1-o.x())*(tmpx+1-o.x())+(tmpy-0.5-o.y())*(tmpy-0.5-o.y())>r*r)
        {
            tmpx++;
            tmpy--;
        }
        else
        {
            tmpx++;
        }
        
        img.setPixelColor(tmpx,tmpy,itext.pixelColor(tmpx,tmpy));
        img.setPixelColor(2*o.x()-tmpx,tmpy,itext.pixelColor(2*o.x()-tmpx,tmpy));
        img.setPixelColor(tmpx,2*o.y()-tmpy,itext.pixelColor(tmpx,2*o.y()-tmpy));
        img.setPixelColor(2*o.x()-tmpx,2*o.y()-tmpy,itext.pixelColor(2*o.x()-tmpx,2*o.y()-tmpy));        
        
        img.setPixelColor(tmpy,tmpx,itext.pixelColor(tmpy,tmpx));
        img.setPixelColor(tmpy,2*o.x()-tmpx,itext.pixelColor(tmpy,2*o.x()-tmpx));
        img.setPixelColor(2*o.y()-tmpy,tmpx,itext.pixelColor(2*o.y()-tmpy,tmpx));
        img.setPixelColor(2*o.y()-tmpy,2*o.x()-tmpx,itext.pixelColor(2*o.y()-tmpy,2*o.x()-tmpx));        
    }
    
    pix=QPixmap::fromImage(img);
}

void DrawSolidCircle(const QPoint &o,int r, QPixmap &pix,const QPixmap &texture)
{
    int tmpx=o.x();
    int tmpy=o.y()+r;
    QImage img=pix.toImage();
    QImage itext=texture.toImage();
    bool** vis=new bool*[pix.width()];
    for(int i=0;i<pix.width();i++)
    {
        vis[i]=new bool[pix.height()]{0};
        for(int j=0;j<pix.height();j++)
        {
            vis[i][j]=0;
        }
    }
    
    img.setPixelColor(o,itext.pixelColor(o));
    
    img.setPixelColor(o.x(),o.y()+r,itext.pixelColor(o.x(),o.y()+r));
    img.setPixelColor(o.x(),o.y()-r,itext.pixelColor(o.x(),o.y()-r));
    img.setPixelColor(o.x()+r,o.y(),itext.pixelColor(o.x()+r,o.y()));
    img.setPixelColor(o.x()-r,o.y(),itext.pixelColor(o.x()-r,o.y()));
    
    if(o.x()>=0&&o.x()<img.width()&&o.y()+r>=0&&o.y()+r<img.height())vis[o.x()][o.y()+r]=1;
    if(o.x()>=0&&o.x()<img.width()&&o.y()-r>=0&&o.y()-r<img.height())vis[o.x()][o.y()-r]=1;
    if(o.x()+r>=0&&o.x()+r<img.width()&&o.y()>=0&&o.y()<img.height())vis[o.x()+r][o.y()]=1;
    if(o.x()-r>=0&&o.x()-r<img.width()&&o.y()>=0&&o.y()<img.height())vis[o.x()-r][o.y()]=1;
    
    while(tmpx<=tmpy)
    {
        if((tmpx+1-o.x())*(tmpx+1-o.x())+(tmpy-0.5-o.y())*(tmpy-0.5-o.y())>r*r)
        {
            tmpx++;
            tmpy--;
        }
        else
        {
            tmpx++;
        }
        
        img.setPixelColor(tmpx,tmpy,itext.pixelColor(tmpx,tmpy));
        img.setPixelColor(2*o.x()-tmpx,tmpy,itext.pixelColor(2*o.x()-tmpx,tmpy));
        img.setPixelColor(tmpx,2*o.y()-tmpy,itext.pixelColor(tmpx,2*o.y()-tmpy));
        img.setPixelColor(2*o.x()-tmpx,2*o.y()-tmpy,itext.pixelColor(2*o.x()-tmpx,2*o.y()-tmpy));
        
        if(tmpx>=0&&tmpx<pix.width()&&tmpy>=0&&tmpy<pix.height())vis[tmpx][tmpy]=1;
        if(2*o.x()-tmpx>=0&&2*o.x()-tmpx<pix.width()&&tmpy>=0&&tmpy<pix.height())vis[2*o.x()-tmpx][tmpy]=1;
        if(tmpx>=0&&tmpx<pix.width()&&2*o.y()-tmpy>=0&&2*o.y()-tmpy<pix.height())vis[tmpx][2*o.y()-tmpy]=1;
        if(2*o.x()-tmpx>=0&&2*o.x()-tmpx<pix.width()&&2*o.y()-tmpy>=0&&2*o.y()-tmpy<pix.height())vis[2*o.x()-tmpx][2*o.y()-tmpy]=1;
        
        img.setPixelColor(tmpy,tmpx,itext.pixelColor(tmpy,tmpx));
        img.setPixelColor(tmpy,2*o.x()-tmpx,itext.pixelColor(tmpy,2*o.x()-tmpx));
        img.setPixelColor(2*o.y()-tmpy,tmpx,itext.pixelColor(2*o.y()-tmpy,tmpx));
        img.setPixelColor(2*o.y()-tmpy,2*o.x()-tmpx,itext.pixelColor(2*o.y()-tmpy,2*o.x()-tmpx));
        
        if(tmpy>=0&&tmpy<pix.width()&&tmpx>=0&&tmpx<pix.height())vis[tmpy][tmpx]=1;
        if(tmpy>=0&&tmpy<pix.width()&&2*o.x()-tmpx>=0&&2*o.x()-tmpx<pix.height())vis[tmpy][2*o.x()-tmpx]=1;
        if(2*o.y()-tmpy>=0&&2*o.y()-tmpy<pix.width()&&tmpx>=0&&tmpx<pix.height())vis[2*o.y()-tmpy][tmpx]=1;
        if(2*o.y()-tmpy>=0&&2*o.y()-tmpy<pix.width()&&2*o.x()-tmpx>=0&&2*o.x()-tmpx<pix.height())vis[2*o.y()-tmpy][2*o.x()-tmpx]=1;
    }
    
    std::queue<QPoint> q;
    q.push(o);
    vis[o.x()][o.y()]=1;
    while(!q.empty())
    {
        QPoint tp=q.front();
        q.pop();
        
        vis[tp.x()][tp.y()]=1;
        img.setPixelColor(tp,itext.pixelColor(tp));
        
        if((tp.x()>=0)&&(tp.x()<pix.width())&&(tp.y()+1>=0)&&(tp.y()+1<pix.height())&&(!vis[tp.x()][tp.y()+1]))
        {
            q.push(QPoint(tp.x(),tp.y()+1));
            vis[tp.x()][tp.y()+1]=1;
        }
        if((tp.x()>=0)&&(tp.x()<pix.width())&&(tp.y()-1>=0)&&(tp.y()-1<pix.height())&&(!vis[tp.x()][tp.y()-1]))
        {
            q.push(QPoint(tp.x(),tp.y()-1));
            vis[tp.x()][tp.y()-1]=1;
        }
        if((tp.x()+1>=0)&&(tp.x()+1<pix.width())&&(tp.y()>=0)&&(tp.y()<pix.height())&&(!vis[tp.x()+1][tp.y()]))
        {
            q.push(QPoint(tp.x()+1,tp.y()));
            vis[tp.x()+1][tp.y()]=1;
        }
        if((tp.x()-1>=0)&&(tp.x()-1<pix.width())&&(tp.y()>=0)&&(tp.y()<pix.height())&&(tp.x()-1<pix.width())&&(!vis[tp.x()-1][tp.y()]))
        {
            q.push(QPoint(tp.x()-1,tp.y()));
            vis[tp.x()-1][tp.y()]=1;
        }
    }
    
    
    pix=QPixmap::fromImage(img);
    
    for(int i=0;i<pix.width();i++)
    {
        delete [] vis[i];
    }
    delete [] vis;
}


//void DrawCircle(const QPoint &o,int r, QPainter* painter, const QPixmap& pix, QImage img,QColor (*function)(QColor))
//{
//    unsigned int tmpx,tmpy;
//    tmpx=o.x();
//    tmpy=o.y()+r;
    
//    bool** vis;
//    vis=new bool*[pix.width()];
//    for(int i=0;i<pix.width();i++)
//    {
//        vis[i]=new bool[pix.height()];
//        for(int j=0;j<pix.height();j++)
//        {
//            vis[i][j]=0;
//        }
//    }
    
////    qDebug()<<tmpx<<' '<<tmpy;
////    QDialog d;
////    d.exec();
    
//    if(tmpx<pix.width()&&tmpy<pix.height())
//    {
//        vis[tmpx][tmpy]=1;
//        painter->setPen((*function)(img.pixel(tmpx,tmpy)));
//        painter->drawPoint(tmpx,tmpy);
//    }
//    if(2*o.x()-tmpx<pix.width()&&2*o.y()-tmpy<pix.height())
//    {
//        vis[2*o.x()-tmpx][2*o.y()-tmpy]=1;
//        painter->setPen((*function)(img.pixel(2*o.x()-tmpx,2*o.y()-tmpy)));
//        painter->drawPoint(2*o.x()-tmpx,2*o.y()-tmpy);
//    }
//    if(tmpy<pix.width()&&tmpx<pix.height())
//    {
//        vis[tmpy][tmpx]=1;
//        painter->setPen((*function)(img.pixel(tmpy,tmpx)));
//        painter->drawPoint(tmpy,tmpx);
//    }
//    if(2*o.y()-tmpy<pix.width()&&2*o.x()-tmpx<pix.height())
//    {
//        vis[2*o.y()-tmpy][2*o.x()-tmpx]=1;
//        painter->setPen((*function)(img.pixel(2*o.y()-tmpy,2*o.y()-tmpx)));
//        painter->drawPoint(2*o.y()-tmpy,2*o.y()-tmpx);
//    }
    
//    while(tmpx<=tmpy)
//    {
//        if((tmpx+1-o.x())*(tmpx+1-o.x())+(tmpy-0.5-o.y())*(tmpy-0.5-o.y())>r*r)
//        {
//            tmpx++;
//            tmpy--;
//        }
//        else
//        {
//            tmpx++;
//        }
        
//        if(tmpx<pix.width()&&tmpy<pix.height())
//        {
//            vis[tmpx][tmpy]=1;
//            painter->setPen((*function)(img.pixel(tmpx,tmpy)));
//            painter->drawPoint(tmpx,tmpy);
//        }
//        if(2*o.x()-tmpx<pix.width()&&tmpy<pix.height())
//        {
//            vis[2*o.x()-tmpx][tmpy]=1;
//            painter->setPen((*function)(img.pixel(2*o.x()-tmpx,tmpy)));
//            painter->drawPoint(2*o.x()-tmpx,tmpy);
//        }
//        if(tmpx<pix.width()&&2*o.y()-tmpy<pix.height())
//        {
//            vis[tmpx][2*o.y()-tmpy]=1;
//            painter->setPen((*function)(img.pixel(tmpx,2*o.y()-tmpy)));
//            painter->drawPoint(tmpx,2*o.y()-tmpy);
//        }
//        if(2*o.x()-tmpx<pix.width()&&2*o.y()-tmpy<pix.height())
//        {
//            vis[2*o.x()-tmpx][2*o.y()-tmpy]=1;
//            painter->setPen((*function)(img.pixel(2*o.x()-tmpx,2*o.y()-tmpy)));
//            painter->drawPoint(2*o.x()-tmpx,2*o.y()-tmpy);
//        }
        
        
//        if(tmpy<pix.width()&&tmpx<pix.height())
//        {
//            vis[tmpy][tmpx]=1;
//            painter->setPen((*function)(img.pixel(tmpy,tmpx)));
//            painter->drawPoint(tmpy,tmpx);
//        }
//        if(tmpy<pix.width()&&2*o.x()-tmpx<pix.height())
//        {
//            vis[tmpy][2*o.x()-tmpx]=1;
//            painter->setPen((*function)(img.pixel(tmpy,2*o.x()-tmpx)));
//            painter->drawPoint(tmpy,2*o.x()-tmpx);
//        }
//        if(2*o.y()-tmpy<pix.width()&&tmpx<pix.height())
//        {
//            vis[2*o.y()-tmpy][tmpx]=1;
//            painter->setPen((*function)(img.pixel(2*o.y()-tmpy,tmpx)));
//            painter->drawPoint(2*o.y()-tmpy,tmpx);
//        }
//        if(2*o.y()-tmpy<pix.width()&&2*o.x()-tmpx<pix.height())
//        {
//            vis[2*o.y()-tmpy][2*o.x()-tmpx]=1;
//            painter->setPen((*function)(img.pixel(2*o.y()-tmpy,2*o.y()-tmpx)));
//            painter->drawPoint(2*o.y()-tmpy,2*o.y()-tmpx);
//        }
//    }
    
////    std::queue<QPoint> q;
////    q.push(o);
//    //vis[o.x()][o.y()]=1;
////    while(!q.empty())
////    {
////        QPoint tp=q.front();
////        q.pop();
        
////        vis[tp.x()][tp.y()]=1;
////        //painter->setPen((*function)(img.pixel(tp)));
////        painter->drawPoint(tp);
        
////        if((tp.y()+1<pix.height())&&(!vis[tp.x()][tp.y()+1]))
////        {
////            q.push(QPoint(tp.x(),tp.y()+1));
////            vis[tp.x()][tp.y()+1]=1;
////        }
////        if((tp.y()-1<pix.height())&&(!vis[tp.x()][tp.y()-1]))
////        {
////            q.push(QPoint(tp.x(),tp.y()-1));
////            vis[tp.x()][tp.y()-1]=1;
////        }
////        if((tp.x()+1<pix.width())&&(!vis[tp.x()+1][tp.y()]))
////        {
////            q.push(QPoint(tp.x()+1,tp.y()));
////            vis[tp.x()+1][tp.y()]=1;
////        }
////        if((tp.x()-1<pix.width())&&(!vis[tp.x()-1][tp.y()]))
////        {
////            q.push(QPoint(tp.x()-1,tp.y()));
////            vis[tp.x()-1][tp.y()]=1;
////        }
////    }
    
////    for(int i=0;i<pix.width();i++)
////    {
////        delete [] vis[i];
////    }
////    delete [] vis;
//}