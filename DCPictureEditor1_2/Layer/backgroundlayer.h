#ifndef BACKGROUNDLAYER_H
#define BACKGROUNDLAYER_H

#include"Layer/layer.h"
#include<QPaintDevice>
#include<QPainter>
#include<QPixmap>

class BackgroundLayer:public Layer
{
public:
    BackgroundLayer();
    void Draw(QPixmap* qpd);
    
    QPixmap object;
};

#endif // BACKGROUNDLAYER_H
