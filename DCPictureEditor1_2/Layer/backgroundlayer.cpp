#include "backgroundlayer.h"
#include"Layer/layer.h"

BackgroundLayer::BackgroundLayer()
{
    type=1;
}

void BackgroundLayer::Draw(QPixmap *qpd)
{
    QPainter painter(qpd);
    painter.drawPixmap(x,y,width,height,object);
}