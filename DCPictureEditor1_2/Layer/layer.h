#ifndef LAYER_H
#define LAYER_H
#include<QPaintDevice>
#include<QPainter>
#include<QString>
#include<QLabel>

class Layer
{
public:
    Layer(){
        x=0;
        y=0;
        vis=1;
        name="未命名图层";
    }
    int x;
    int y;
    int width;
    int height;
    bool vis;
    QString name;
    virtual void Draw(QPixmap* qpd)=0;
    int type;
};

#endif // LAYER_H
