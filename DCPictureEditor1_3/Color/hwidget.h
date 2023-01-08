#ifndef HWIDGET_H
#define HWIDGET_H

#include <QWidget>
#include<QPainter>
#include<QSlider>
#include<QHBoxLayout>
#include"colorslider.h"

class HWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HWidget(QWidget *parent = nullptr);
    ~HWidget();
    
    QColor* i_colors;
    
    void paintEvent(QPaintEvent*);
    
    //QSlider* mslider;
    ColorSlider* mslider;
    
    int* h_M;
    
signals:
    
public slots:
};

#endif // HWIDGET_H
