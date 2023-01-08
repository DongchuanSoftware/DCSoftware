#include "setsealwidget.h"
#include "ui_setsealwidget.h"

SetSealWidget::SetSealWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetSealWidget)
{
    ui->setupUi(this);
    
}

SetSealWidget::~SetSealWidget()
{
    delete ui;
}
