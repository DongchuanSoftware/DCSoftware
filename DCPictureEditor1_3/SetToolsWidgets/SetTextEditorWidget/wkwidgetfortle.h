#ifndef WKWIDGETFORTLE_H
#define WKWIDGETFORTLE_H

#include <QWidget>
#include<QPainter>
#include"Layer/layermanager.h"
#include<QMouseEvent>

class WKWidgetForTLE : public QWidget
{
    Q_OBJECT
public:
    explicit WKWidgetForTLE(QWidget *parent = nullptr);
    
    LayerManager* lymanager;
    int tlayer_pos;
    void paintEvent(QPaintEvent*);
    QWidget* w;
    
    void mousePressEvent(QMouseEvent* qme);
    void mouseMoveEvent(QMouseEvent* qme);
    int StartX;
    int StartY;
    
signals:
    
public slots:
};

#endif // WKWIDGETFORTLE_H
