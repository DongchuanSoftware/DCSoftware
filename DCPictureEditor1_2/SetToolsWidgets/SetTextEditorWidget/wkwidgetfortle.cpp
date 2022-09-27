#include "wkwidgetfortle.h"

WKWidgetForTLE::WKWidgetForTLE(QWidget *parent) : QWidget(parent)
{
    this->setCursor(QCursor(Qt::SizeAllCursor));
}

void WKWidgetForTLE::paintEvent(QPaintEvent *)
{

    if(lymanager==nullptr)
    {
        return;
    }
    QPainter painter(this);
    QPixmap pix(lymanager->width,lymanager->height);
    pix.fill(Qt::transparent);
    for(int i=0;i<lymanager->v_layers.size();i++)
    {
        if(lymanager->v_layers[i]->vis&&i!=tlayer_pos)
        {
            lymanager->v_layers[i]->Draw(&pix);
        }
        
    }
    painter.drawPixmap(0,0,
                       lymanager->width,lymanager->height,
                       pix);
}

void WKWidgetForTLE::mousePressEvent(QMouseEvent *qme)
{
    StartX=qme->x();
    StartY=qme->y();
}

void WKWidgetForTLE::mouseMoveEvent(QMouseEvent *qme)
{
    if(w!=nullptr)
    {
        w->move(w->x()+qme->x()-StartX,w->y()+qme->y()-StartY);
        StartX=qme->x();
        StartY=qme->y();
    }
}