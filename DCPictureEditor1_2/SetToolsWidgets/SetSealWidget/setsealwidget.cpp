#include "setsealwidget.h"
#include "ui_setsealwidget.h"

SetSealWidget::SetSealWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetSealWidget)
{
    ui->setupUi(this);
    
    sppoint_M=QPoint(0,0);
    
    ui->SliderWidth->setMaximum(100);
    ui->SliderWidth->setMinimum(1);
    ui->SpinBoxWidth->setMaximum(100);
    ui->SpinBoxWidth->setMinimum(1);
    connect(ui->SliderWidth,&QSlider::valueChanged,[=](int v){
        ui->SpinBoxWidth->setValue(v);
    });
    ui->SliderWidth->setValue(7);
}

SetSealWidget::~SetSealWidget()
{
    delete ui;
}

void SetSealWidget::on_SpinBoxWidth_valueChanged(int v)
{
    ui->SliderWidth->setValue(v);
    width_M=v;
    emit WidthChanged();
}

void SetSealWidget::on_BtnChangeSPPoint_clicked()
{
    mode_M=1;
}
