#include "layerattrmanager.h"
#include "ui_layerattrmanager.h"

LayerAttrManager::LayerAttrManager(QWidget *parent, LayerManager *_lymanager) :
    QWidget(parent),
    ui(new Ui::LayerAttrManager)
{
    ui->setupUi(this);
    ui->spinX->setMinimum(-100000000);
    ui->spinX->setMaximum(100000000);
    ui->spinY->setMinimum(-100000000);
    ui->spinY->setMaximum(100000000);
    
    ui->editName->setReadOnly(1);
    ui->spinX->setReadOnly(1);
    ui->spinY->setReadOnly(1);
    ui->spinWidth->setReadOnly(1);
    ui->spinHeight->setReadOnly(1);
    ui->checkClockK->setCheckable(0);
    
    this->lymanager=_lymanager;
    
    connect(lymanager,&LayerManager::layerNameChanged,this,[=](){
        this->upDateUI();
    });
    connect(lymanager,&LayerManager::itemSelectionChanged,this,[=](){
        this->upDateUI();
    });
}

LayerAttrManager::~LayerAttrManager()
{
    delete ui;
}

void LayerAttrManager::upDateUI()
{
    if(lymanager->selectedItems().size()==0)return;
    int n=lymanager->v_layers.size()-lymanager->selectedItems().first()->row()-1;
    const Layer& ly=*lymanager->v_layers[n];
    
    QString lyName("第%1图层");
    if(lymanager->selectedItems().size()>1)
    {
        ui->editName->setReadOnly(1);
        ui->spinX->setReadOnly(1);
        ui->spinY->setReadOnly(1);
        ui->spinWidth->setReadOnly(1);
        ui->spinHeight->setReadOnly(1);
        ui->checkClockK->setCheckable(0);
    }
    else
    {
        switch (ly.type) {
        case LT_BACKGROUND:{
            ui->editName->setReadOnly(0);
            ui->spinX->setReadOnly(1);
            ui->spinY->setReadOnly(1);
            ui->spinWidth->setReadOnly(1);
            ui->spinHeight->setReadOnly(1);
            ui->checkClockK->setCheckable(0);
            lyName+="——背景图层";
        }break;
        case LT_PICTURE:{
            ui->editName->setReadOnly(0);
            ui->spinX->setReadOnly(0);
            ui->spinY->setReadOnly(0);
            ui->spinWidth->setReadOnly(0);
            ui->spinHeight->setReadOnly(0);
            ui->checkClockK->setCheckable(1);
            lyName+="——图片图层";
        }break;
        case LT_TEXT:{
            ui->editName->setReadOnly(0);
            ui->spinX->setReadOnly(0);
            ui->spinY->setReadOnly(0);
            ui->spinWidth->setReadOnly(1);
            ui->spinHeight->setReadOnly(1);
            ui->checkClockK->setCheckable(0);
            lyName+="——文本图层";
        }break;
        }
    }
    ui->editSelectedLayer->setText(lyName.arg(n));
    ui->editName->setText(ly.name);
    ui->spinX->setValue(ly.x);
    ui->spinY->setValue(ly.y);
    ui->spinHeight->setValue(ly.height);
    ui->spinWidth->setValue(ly.width);
}

void LayerAttrManager::on_editName_textChanged(const QString &str)
{
    if(lymanager->selectedItems().size()==0)return;
    int n=lymanager->v_layers.size()-lymanager->selectedItems().first()->row()-1;
    Layer& ly=*lymanager->v_layers[lymanager->v_layers.size()-lymanager->selectedItems().first()->row()-1];
    ly.name=str;
    lymanager->upDateUI();
}

void LayerAttrManager::on_spinWidth_valueChanged(int width)
{
    if(lymanager->selectedItems().size()==0)return;
    int n=lymanager->v_layers.size()-lymanager->selectedItems().first()->row()-1;
    Layer& ly=*lymanager->v_layers[lymanager->v_layers.size()-lymanager->selectedItems().first()->row()-1];
    if(ui->checkClockK->isChecked())
    {
        ly.height=ly.height*width/ly.width;
    }
    ly.width=width;
    ly.width=ly.width<1?1:ly.width;
    ly.height=ly.height<1?1:ly.height;
    lymanager->upDateUI();
}

void LayerAttrManager::on_spinHeight_valueChanged(int height)
{
    if(lymanager->selectedItems().size()==0)return;
    int n=lymanager->v_layers.size()-lymanager->selectedItems().first()->row()-1;
    Layer& ly=*lymanager->v_layers[lymanager->v_layers.size()-lymanager->selectedItems().first()->row()-1];
    if(ui->checkClockK->isChecked())
    {
        ly.width=ly.width*height/ly.height;
    }
    ly.height=height;
    ly.width=ly.width<1?1:ly.width;
    ly.height=ly.height<1?1:ly.height;    
    lymanager->upDateUI();
}

void LayerAttrManager::on_spinX_valueChanged(int x)
{
    if(lymanager->selectedItems().size()==0)return;
    int n=lymanager->v_layers.size()-lymanager->selectedItems().first()->row()-1;
    Layer& ly=*lymanager->v_layers[lymanager->v_layers.size()-lymanager->selectedItems().first()->row()-1];
    ly.x=x;
    lymanager->upDateUI();
}

void LayerAttrManager::on_spinY_valueChanged(int y)
{
    if(lymanager->selectedItems().size()==0)return;
    int n=lymanager->v_layers.size()-lymanager->selectedItems().first()->row()-1;
    Layer& ly=*lymanager->v_layers[lymanager->v_layers.size()-lymanager->selectedItems().first()->row()-1];
    ly.y=y;
    lymanager->upDateUI();
}
