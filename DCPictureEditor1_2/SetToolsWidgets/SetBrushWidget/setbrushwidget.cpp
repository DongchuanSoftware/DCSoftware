#include "setbrushwidget.h"
#include "ui_setbrushwidget.h"
#include<iostream>

SetBrushWidget::SetBrushWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetBrushWidget)
{
    ui->setupUi(this);
    
    ui->SliderTransparency->setMaximum(255);
    ui->SliderTransparency->setMinimum(0);
    ui->SpinBoxTransparency->setMaximum(255);
    ui->SpinBoxTransparency->setMinimum(0);
    connect(ui->SliderTransparency,&QSlider::valueChanged,[=](int v){
        ui->SpinBoxTransparency->setValue(v);
    });
    ui->SliderTransparency->setValue(255);
    
    ui->SliderWidth->setMaximum(100);
    ui->SliderWidth->setMinimum(1);
    ui->SpinBoxWidth->setMaximum(100);
    ui->SpinBoxWidth->setMinimum(1);
    connect(ui->SliderWidth,&QSlider::valueChanged,[=](int v){
        ui->SpinBoxWidth->setValue(v);
    });
    ui->SliderWidth->setValue(7);
    
    ui->SliderHardness->setMaximum(100);
    ui->SliderHardness->setMinimum(1);
    ui->SpinBoxHardness->setMaximum(100);
    ui->SpinBoxHardness->setMinimum(1);
    connect(ui->SliderHardness,&QSlider::valueChanged,[=](int v){
        ui->SpinBoxHardness->setValue(v);
    });
    ui->SliderHardness->setValue(70);
    
    ui->SliderSpacing->setMaximum(100);
    ui->SliderSpacing->setMinimum(0);
    ui->SpinBoxSpacing->setMaximum(100);
    ui->SpinBoxSpacing->setMinimum(0);
    connect(ui->SliderSpacing,&QSlider::valueChanged,[=](int v){
        ui->SpinBoxSpacing->setValue(v);
    });
    ui->SliderSpacing->setValue(0);
    
    ui->SliderFluency->setMaximum(20);
    ui->SliderFluency->setMinimum(1);
    ui->SpinBoxFluency->setMaximum(20);
    ui->SpinBoxFluency->setMinimum(1);
    connect(ui->SliderFluency,&QSlider::valueChanged,[=](int v){
        ui->SpinBoxFluency->setValue(v);
    });
    ui->SliderFluency->setValue(10);
}

SetBrushWidget::~SetBrushWidget()
{
    delete ui;
}

void SetBrushWidget::on_SpinBoxTransparency_valueChanged(int v)
{
    ui->SliderTransparency->setValue(v);
    transparency_M=v;
}

void SetBrushWidget::on_SpinBoxWidth_valueChanged(int v)
{
    ui->SliderWidth->setValue(v);
    width_M=v;
    emit WidthChanged();
}

void SetBrushWidget::on_SpinBoxHardness_valueChanged(int v)
{
    ui->SliderHardness->setValue(v);
    hardness_M=v;
}

void SetBrushWidget::on_SpinBoxSpacing_valueChanged(int v)
{
    ui->SliderSpacing->setValue(v);
    spacing_M=v;
}

void SetBrushWidget::on_SpinBoxFluency_valueChanged(int v)
{
    ui->SliderFluency->setValue(v);
    fluency_M=v;
}
