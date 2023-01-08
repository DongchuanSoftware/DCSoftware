#ifndef LAYER_H
#define LAYER_H
#include<QPaintDevice>
#include<QPainter>
#include<QString>
#include<QLabel>
#include<QMessageBox>

enum LayerType{
    LT_BACKGROUND=1,
    LT_PICTURE,
    LT_TEXT
};

class Layer
{
public:
    Layer();
    virtual ~Layer();
    int x;
    int y;
    int width;
    int height;
    bool vis;
    QString name;
    virtual void Draw(QPixmap* qpd)=0;
    LayerType type;
};

#endif // LAYER_H
