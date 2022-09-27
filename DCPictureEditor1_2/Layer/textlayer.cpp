#include "textlayer.h"

TextLayer::TextLayer()
{
    type=3;
}

void TextLayer::Draw(QPixmap *qpd)
{
    QPainter painter(qpd);
//    painter.setPen(color);
//    painter.setFont(font);
    //painter.drawText(QRect(x,y,width,height),Qt::TextWordWrap,object);
    //painter.drawText(x,y,object);
    painter.translate(x,y);
    object.drawContents(&painter);
}