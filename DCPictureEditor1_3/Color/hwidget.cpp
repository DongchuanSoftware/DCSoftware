#include "hwidget.h"

HWidget::HWidget(QWidget *parent) : QWidget(parent)
{
    i_colors=new QColor[255*6];
    for(int i=0;i<=0xff;i++)
    {
        i_colors[i]=QColor(255,i,0);
    }
    for(int i=0xff-1;i>=0;i--)
    {
        i_colors[255*2-i]=QColor(i,255,0);
    }
    for(int i=0;i<=0xff;i++)
    {
        i_colors[255*2+i]=QColor(0,255,i);
    }
    for(int i=0xff-1;i>=0;i--)
    {
        i_colors[255*4-i]=QColor(0,i,255);
    }
    for(int i=0;i<=0xff;i++)
    {
        i_colors[255*4+i]=QColor(i,0,255);
    }
    for(int i=0xff-1;i>0;i--)
    {
        i_colors[255*6-i]=QColor(255,0,i);
    }
    
    mslider=new ColorSlider(this);
    mslider->setMaximum(359);
    mslider->setMinimum(0);
    mslider->move(0,0);
    mslider->setStyleSheet("QSlider::groove:vertical {width: 30px; \
                           background-color: transparent;} \
                           QSlider::handle:vertical { \
                           background: transparent; \
                           height: 8px; \
                           border: 4px solid white; \
                           border-radius: 2px;} \
                           QSlider::add-page:vertical {background: transparent;} \
                           QSlider::sub-page:vertical {background: transparent;}"
    );
    mslider->setInvertedAppearance(1);
    connect(mslider,&QSlider::valueChanged,[=](int val){
        *h_M=val;
        parent->update();
    });
}

HWidget::~HWidget()
{
    delete [] i_colors;
}
void HWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    for(int i=0;i<255*6;i++)
    {
        painter.setPen(QColor(53,53,53));
        painter.drawLine(0,i/(255*6/(double)height()),width(),i/(255*6/(double)height()));
        
        painter.setPen(i_colors[i]);
        painter.drawLine(3,i/(255*6/(double)height()),width()-3,i/(255*6/(double)height()));
    }
    mslider->resize(this->width(),this->height());
    painter.end();
}