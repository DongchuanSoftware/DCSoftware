#include "colormanager.h"
#include "ui_colormanager.h"

ColorManager::ColorManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorManager)
{
    ui->setupUi(this);
    
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
    HSV_RGB(h_M,s_M,v_M,r_M,g_M,b_M);
    ui->cpushbutton->setStyleSheet(QString("background-color:rgb(%1,%2,%3)").arg(r_M).arg(g_M).arg(b_M));
    ui->hwidget->mslider->setValue(h_M);
}