#include "backgroundlayer.h"
#include"Layer/layer.h"

BackgroundLayer::BackgroundLayer()
{
    type=LT_BACKGROUND;
}

BackgroundLayer::~BackgroundLayer()
{
    
}

void BackgroundLayer::Draw(QPixmap *qpd)
{
    QPainter painter(qpd);
    painter.drawPixmap(x,y,width,height,object);
    painter.end();
}