#ifndef PICTURELAYER_H
#define PICTURELAYER_H

#include"Layer/layer.h"
#include<QPaintDevice>
#include<QPainter>
#include<QPixmap>

class PictureLayer:public Layer
{
public:
    PictureLayer();
    void Draw(QPixmap* qpd);
    
    QPixmap object;
};

#endif // PICTURELAYER_H
