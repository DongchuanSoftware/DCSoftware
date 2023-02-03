#include "picturelayer.h"

PictureLayer::PictureLayer()
{
    type=LT_PICTURE;
}

PictureLayer::~PictureLayer()
{
    
}

void PictureLayer::Draw(QPaintDevice *qpd)
{
    QPainter painter;
    painter.begin(qpd);
    painter.drawImage(QRect(x,y,width,height),object);
    painter.end();
}