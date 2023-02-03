#ifndef BACKGROUNDLAYER_H
#define BACKGROUNDLAYER_H

#include"Layer/layer.h"
#include<QPaintDevice>
#include<QPainter>
#include<QPixmap>
#include<QImage>

class BackgroundLayer:public Layer
{
public:
    BackgroundLayer();
    ~BackgroundLayer();
    void Draw(QPaintDevice* qpd);
    
    QImage object;
};

#endif // BACKGROUNDLAYER_H
