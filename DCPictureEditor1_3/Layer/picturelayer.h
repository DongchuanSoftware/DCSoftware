#ifndef PICTURELAYER_H
#define PICTURELAYER_H

#include"Layer/layer.h"
#include<QPaintDevice>
#include<QPainter>
#include<QPixmap>
#include<QImage>

class PictureLayer:public Layer
{
public:
    PictureLayer();
    ~PictureLayer();
    void Draw(QPaintDevice* qpd);
    
    QImage object;
};

#endif // PICTURELAYER_H
