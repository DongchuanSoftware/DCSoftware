#include "picturelayer.h"

PictureLayer::PictureLayer()
{
    type=LT_PICTURE;
}

PictureLayer::~PictureLayer()
{
    
}

void PictureLayer::Draw(QPixmap *qpd)
{
    QPainter painter;
    painter.begin(qpd);
    painter.drawPixmap(x,y,width,height,object);
    painter.end();
}