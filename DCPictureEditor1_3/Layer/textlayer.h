#ifndef TEXTLAYER_H
#define TEXTLAYER_H

#include"Layer/layer.h"
#include<QPaintDevice>
#include<QPainter>
#include<QPixmap>
#include<QString>
#include<QFont>
#include<QTextDocument>

class TextLayer:public Layer
{
public:
    TextLayer();
    ~TextLayer();
    void Draw(QPaintDevice* qpd);
    
    QTextDocument object;
};

#endif // TEXTLAYER_H
