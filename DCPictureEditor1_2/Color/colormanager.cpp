#include "colormanager.h"
#include "ui_colormanager.h"
#include<iostream>

ColorManager::ColorManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorManager)
{
    ui->setupUi(this);
//    ui->VerticalSliderH->setMaximum(255*6-1);
//    ui->VerticalSliderH->setMinimum(0);
//    ui->VerticalSliderH->setInvertedAppearance(1);
    
//    ui->VerticalSlider->setMaximum(100);
//    ui->VerticalSlider->setMinimum(0);
    
//    ui->HorizontalSlider->setMaximum(100);
//    ui->HorizontalSlider->setMinimum(0);
    
    
//    connect(ui->VerticalSliderH,&QSlider::sliderMoved,[=](){
//        this->update(); 
//    });
//    connect(ui->VerticalSlider,&QSlider::sliderMoved,[=](){
//        this->v_M=ui->VerticalSlider->value()/100.0;
//        this->update();
//    });
//    connect(ui->HorizontalSlider,&QSlider::sliderMoved,[=](){
//        this->s_M=ui->HorizontalSlider->value()/100.0;
//        this->update();
//    });
    ui->hwidget->h_M=&h_M;
    ui->svwidget->h_M=&h_M;
    ui->svwidget->s_M=&s_M;
    ui->svwidget->v_M=&v_M;
    
    connect(ui->svwidget,&SVWidget::parent_update,[=](){
        update();
    });
    connect(ui->cpushbutton,&QPushButton::clicked,[=](){
        QColor cl=QColorDialog::getColor(QColor(r_M,g_M,b_M),this,"选择颜色");
        if(cl==QColor())return;
        r_M=cl.red();
        g_M=cl.green();
        b_M=cl.blue();
        RGB_HSV(r_M,g_M,b_M,h_M,s_M,v_M);
        
        update();
    });
}

ColorManager::~ColorManager()
{
    delete ui;
}



void ColorManager::paintEvent(QPaintEvent *)
{
    //HSV_RGB(h_M,s_M,v_M,r_M,g_M,b_M);
    HSV_RGB(h_M,s_M,v_M,r_M,g_M,b_M);
    ui->cpushbutton->setStyleSheet(QString("background-color:rgb(%1,%2,%3)").arg(r_M).arg(g_M).arg(b_M));
    ui->hwidget->mslider->setValue(h_M);
//    ui->VerticalSliderH->move(width()-60-ui->VerticalSliderH->width(),0);
//    ui->VerticalSliderH->resize(ui->VerticalSliderH->width(),this->height());
//    ui->VerticalSlider->move(width()-120,0);
//    ui->VerticalSlider->resize(ui->VerticalSlider->width(),this->height()-50);
//    ui->HorizontalSlider->move(0,height()-30);
//    ui->HorizontalSlider->resize(this->width()-140,ui->HorizontalSlider->height());
    
//    //painter.setPen(i_colors[ui->VerticalSliderH->value()]);
//    //painter.drawRect(0,0,30,30);
//    int h;
//    double s,v;
//    RGB_HSV(i_colors[ui->VerticalSliderH->value()].red(),
//            i_colors[ui->VerticalSliderH->value()].green(),
//            i_colors[ui->VerticalSliderH->value()].blue(),
//            h,s,v);
//    QBrush br=QBrush(Qt::SolidPattern);
    
//    for(s=1;s>=0;s-=0.01)
//    {
//        for(v=1;v>=0;v-=0.01)
//        {
//            int r,g,b;
//            HSV_RGB(h,s,v,r,g,b);
//            painter.setPen(QColor(r,g,b));
//            br.setColor(QColor(r,g,b));
//            painter.setBrush(br);
////            painter.drawPoint(10+s*(width()-150),10+(1-v)*(height()-50));
////            painter.drawPoint(10+s*(width()-151),10+(1-v)*(height()-51));
////            painter.drawPoint(10+s*(width()-150),10+(1-v)*(height()-51));
////            painter.drawPoint(10+s*(width()-151),10+(1-v)*(height()-50));
//            painter.drawRect(s*(width()-150),(1-v)*(height()-50),(width()-150)/100,(height()-50)/100);
//            //painter.drawLine(10+(width()-150),10,10+s*(width()-150),10+(1-v)*(height()-50));
//        }
//    }
//    int r,g,b;
//    HSV_RGB(h,s_M,v_M,r,g,b);
//    now_color=QColor(r,g,b);
//    painter.setPen(now_color);
//    br.setColor(now_color);
//    painter.setBrush(br);
//    painter.drawRect(width()-30,0,60,height());
    
//    painter.setPen(Qt::black);
//    br.setColor(Qt::transparent);
//    painter.setBrush(br);
//    //painter.drawEllipse(10+s_M*(width()-150),10+(1-v_M)*(height()-50),(width()-150)/100,(height()-59)/100);
//    //painter.drawEllipse(QPoint(10+s_M*(width()-150),v_M),10,10);
//    painter.drawRect(s_M*(width()-150),(1-v_M)*(height()-50),10,10);
//    painter.drawRect(s_M*(width()-150)-1,(1-v_M)*(height()-50)-1,12,12);
//    painter.drawRect(s_M*(width()-150)-2,(1-v_M)*(height()-50)-2,14,14);
}

void ColorManager::mousePressEvent(QMouseEvent *qme)
{
//    if(qme->x()>width()-30)
//    {
//        now_color=QColorDialog::getColor(now_color);
//    }
}