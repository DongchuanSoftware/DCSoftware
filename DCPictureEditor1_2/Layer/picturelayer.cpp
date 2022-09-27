#include "picturelayer.h"

PictureLayer::PictureLayer()
{
    type=2;
}

void PictureLayer::Draw(QPixmap *qpd)
{
    QPainter painter(qpd);
    painter.drawPixmap(x,y,width,height,object);
}