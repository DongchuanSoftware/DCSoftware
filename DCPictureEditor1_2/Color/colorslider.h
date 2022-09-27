#ifndef COLORSLIDER_H
#define COLORSLIDER_H

#include <QWidget>
#include<QSlider>
#include<QMouseEvent>

class ColorSlider : public QSlider
{
    Q_OBJECT
public:
    explicit ColorSlider(QWidget *parent = nullptr);
    
    void mousePressEvent(QMouseEvent* qme);
    void mouseMoveEvent(QMouseEvent* qme);
    
signals:
    
public slots:
};

#endif // COLORSLIDER_H
