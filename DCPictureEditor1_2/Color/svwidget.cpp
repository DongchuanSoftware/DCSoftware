#include "svwidget.h"

SVWidget::SVWidget(QWidget *parent) : QWidget(parent)
{
    //setCursor(Qt::CrossCursor);
    setCursor(QCursor(QPixmap(":/CursorIcon/Circle.png").scaled(33,33)));
}

void SVWidget::paintEvent(QPaintEvent *)
{
    //---------背景---------------
    double s,v;
    QBrush br=QBrush(Qt::SolidPattern);
    QPainter painter(this);
    //for(s=1;s>=0;s-=0.01)
    for(s=0;s<=1;s+=0.01)
    {
        for(v=1;v>=0;v-=0.01)
        {
            int r,g,b;
            HSV_RGB(*h_M,s,v,r,g,b);
            painter.setPen(QColor(r,g,b));
            br.setColor(QColor(r,g,b));
            painter.setBrush(br);
            //painter.drawRect(s*width(),(1-v)*height(),width()/100,height()/100);
            painter.drawRect(s*width(),(1-v)*height(),width()/100,height()/100);
        }
    }
    //--------点--------
    painter.setPen(QColor(0,0,0));
    br.setColor(Qt::transparent);
    painter.setBrush(br);
    painter.drawEllipse(QPoint(*s_M*width(),(1-*v_M)*height()),5,5);
    painter.drawEllipse(QPoint(*s_M*width(),(1-*v_M)*height()),7,7);
    painter.drawEllipse(QPoint(*s_M*width(),(1-*v_M)*height()),9,9);
    painter.setPen(QColor(255,255,255));
    painter.drawEllipse(QPoint(*s_M*width(),(1-*v_M)*height()),6,6);
    painter.drawEllipse(QPoint(*s_M*width(),(1-*v_M)*height()),8,8);
}

void SVWidget::mousePressEvent(QMouseEvent *qme)
{
    *s_M=qme->x()/(double)width();
    *v_M=1-qme->y()/(double)height();
    emit parent_update();
}

void SVWidget::mouseMoveEvent(QMouseEvent *qme)
{
    if(qme->x()/(double)width()<0)
    {
        *s_M=0;
    }
    else if(qme->x()/(double)width()>1)
    {
        *s_M=1;
    }
    else
    {
        *s_M=qme->x()/(double)width();
    }
    if(1-qme->y()/(double)height()<0)
    {
        *v_M=0;
    }
    else if(1-qme->y()/(double)height()>1)
    {
        *v_M=1;
    }
    else
    {
        *v_M=1-qme->y()/(double)height();
    }
    emit parent_update();
}