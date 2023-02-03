#include "setbrushwidget.h"
#include "ui_setbrushwidget.h"
#include<iostream>

SetBrushWidget::SetBrushWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetBrushWidget)
{
    ui->setupUi(this);
    
    ui->sliderTransparency->setMaximum(255);
    ui->sliderTransparency->setMinimum(0);
    ui->spinBoxTransparency->setMaximum(255);
    ui->spinBoxTransparency->setMinimum(0);
    connect(ui->sliderTransparency,&QSlider::valueChanged,this,[=](int v){
        ui->spinBoxTransparency->setValue(v);
    });
    ui->sliderTransparency->setValue(255);
    
    ui->sliderWidth->setMaximum(100);
    ui->sliderWidth->setMinimum(1);
    ui->spinBoxWidth->setMaximum(100);
    ui->spinBoxWidth->setMinimum(1);
    connect(ui->sliderWidth,&QSlider::valueChanged,this,[=](int v){
        ui->spinBoxWidth->setValue(v);
    });
    ui->sliderWidth->setValue(7);
    
    ui->sliderHardness->setMaximum(100);
    ui->sliderHardness->setMinimum(1);
    ui->spinBoxHardness->setMaximum(100);
    ui->spinBoxHardness->setMinimum(1);
    connect(ui->sliderHardness,&QSlider::valueChanged,this,[=](int v){
        ui->spinBoxHardness->setValue(v);
    });
    ui->sliderHardness->setValue(70);
    
    ui->spinBoxRadius->setValue(100);
    
    connect(this,&SetBrushWidget::setWidth,ui->spinBoxWidth,&QSpinBox::setValue);
    connect(this,&SetBrushWidget::setRadius,ui->spinBoxRadius,&QSpinBox::setValue);
}

SetBrushWidget::~SetBrushWidget()
{
    delete ui;
}

void SetBrushWidget::on_spinBoxTransparency_valueChanged(int v)
{
    ui->sliderTransparency->setValue(v);
    transparency_M=v;
}

void SetBrushWidget::on_spinBoxWidth_valueChanged(int v)
{
    ui->sliderWidth->setValue(v);
    width_M=v;
    emit widthChanged();
}

void SetBrushWidget::on_spinBoxHardness_valueChanged(int v)
{
    ui->sliderHardness->setValue(v);
    hardness_M=v;
}

void SetBrushWidget::on_spinBoxRadius_valueChanged(int v)
{
    radius_M=v;
}


void SetBrushWidget::on_radioButtonCircle_clicked()
{
    isCircle_M=1;
}


void SetBrushWidget::on_radioButtonArc_clicked()
{
    isCircle_M=0;
    lockedR_M=0;
}


void SetBrushWidget::on_radioButtonArcLR_clicked()
{
    isCircle_M=0;
    lockedR_M=1;
}

