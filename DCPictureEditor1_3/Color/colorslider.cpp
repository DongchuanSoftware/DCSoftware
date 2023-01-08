#include "colorslider.h"

ColorSlider::ColorSlider(QWidget *parent) : QSlider (parent)
{
    
}

void ColorSlider::mousePressEvent(QMouseEvent *qme)
{
    this->setValue(qme->pos().y()/(double)this->height()*this->maximum());
}

void ColorSlider::mouseMoveEvent(QMouseEvent *qme)
{
    this->setValue(qme->pos().y()/(double)this->height()*this->maximum());
}