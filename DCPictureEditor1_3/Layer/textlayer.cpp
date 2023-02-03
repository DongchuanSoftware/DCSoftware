#include "textlayer.h"

TextLayer::TextLayer()
{
    type=LT_TEXT;
}

TextLayer::~TextLayer()
{
    
}

void TextLayer::Draw(QPaintDevice *qpd)
{
    QPainter painter(qpd);
    painter.translate(x,y);
    object.drawContents(&painter);
    painter.end();
}