#include "backgroundlayer.h"
#include"Layer/layer.h"

BackgroundLayer::BackgroundLayer()
{
    type=LT_BACKGROUND;
}

BackgroundLayer::~BackgroundLayer()
{
    
}

void BackgroundLayer::Draw(QPaintDevice *qpd)
{
    QPainter painter(qpd);
    painter.drawImage(QRect(x,y,width,height),object);
    painter.end();
}