#include "layerattrmanager.h"
#include "ui_layerattrmanager.h"

LayerAttrManager::LayerAttrManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerAttrManager)
{
    ui->setupUi(this);
}

LayerAttrManager::~LayerAttrManager()
{
    delete ui;
}
