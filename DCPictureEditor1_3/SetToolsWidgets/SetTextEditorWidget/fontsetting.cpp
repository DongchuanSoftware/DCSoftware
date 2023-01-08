#include "fontsetting.h"
#include "ui_fontsetting.h"

FontSetting::FontSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FontSetting)
{
    ui->setupUi(this);
    
    font_M.family();
    font_M.pixelSize();
    
    connect(ui->buttonFont,&QPushButton::clicked,[=](){
        bool b;
        font_M=QFontDialog::getFont(&b,font_M,this,"修改字体");
        upDateUI();
        emit fontChanged();
    });
    
    connect(ui->buttonColor,&QPushButton::clicked,[=](){
        HSVColorDialog hsvcd(this);
        color_M=hsvcd.getColor(color_M);
        upDateUI();
        emit colorChanged();
    });
    
    connect(ui->boxUnderLine,&QCheckBox::clicked,[=](int b){
        font_M.setUnderline(b);
        upDateUI();
        emit fontChanged();
    });
    
    connect(ui->boxStrikeOut,&QCheckBox::clicked,[=](int b){
        font_M.setStrikeOut(b);
        upDateUI();
        emit fontChanged();
    });
    
    connect(ui->boxBold,&QCheckBox::clicked,[=](int b){
        font_M.setBold(b);
        upDateUI();
        emit fontChanged();
    });
    
    connect(ui->boxItalic,&QCheckBox::clicked,[=](int b){
        font_M.setItalic(b);
        upDateUI();
        emit fontChanged();
    });
    
    upDateUI();
}

void FontSetting::upDateUI()
{
    ui->lineFamily->setText(font_M.family());
    ui->lineSize->setText(QString("%1").arg(font_M.pointSize()));
    ui->buttonColor->setStyleSheet(QString("background-color:rgb(%1,%2,%3)").arg(color_M.red()).arg(color_M.green()).arg(color_M.blue()));    
    ui->boxUnderLine->setChecked(font_M.underline());
    ui->boxStrikeOut->setChecked(font_M.strikeOut());
    ui->boxBold->setChecked(font_M.bold());
    ui->boxItalic->setChecked(font_M.italic());
}

FontSetting::~FontSetting()
{
    delete ui;
}
