#include "actionnewwidget.h"
#include "ui_actionnewwidget.h"

ActionNewWidget::ActionNewWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ActionNewWidget)
{
    ui->setupUi(this);
    
    ui->SpinBoxW->setValue(1920);
    ui->SpinBoxH->setValue(1080);
    
    color=QColor(0,0,0);
    ui->cpushbutton->setStyleSheet(QString("background-color:rgb(%1,%2,%3)").arg(color.red()).arg(color.green()).arg(color.blue()));
    connect(ui->cpushbutton,&QPushButton::clicked,[=](){
        HSVColorDialog hsvcd(this);
        color=hsvcd.GetColor(color);
        
        ui->cpushbutton->setStyleSheet(QString("background-color:rgb(%1,%2,%3)").arg(color.red()).arg(color.green()).arg(color.blue()));
    });
}

ActionNewWidget::~ActionNewWidget()
{
    delete ui;
}

void ActionNewWidget::on_PushButtonSure_clicked()
{
    pix=new QPixmap(ui->SpinBoxW->value(),ui->SpinBoxH->value());
    pix->fill(color);
    if(p_dlg!=nullptr)
    {
        p_dlg->close();
    }
}

void ActionNewWidget::on_PushButtonCancel_clicked()
{
    if(p_dlg!=nullptr)
    {
        p_dlg->close();
    }
}

void ActionNewWidget::on_ButtonChange_clicked()
{
    filename=QFileDialog::getSaveFileName(this,"新建","C:/无标题.dcpe","项目(*.dcpe)");
    ui->LineEditPath->setText(filename);
}
