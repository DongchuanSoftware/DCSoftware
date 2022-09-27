#include "fontsetting.h"
#include "ui_fontsetting.h"

FontSetting::FontSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FontSetting)
{
    ui->setupUi(this);
    
    font_M.family();
    font_M.pixelSize();
    
    connect(ui->ButtonFont,&QPushButton::clicked,[=](){
        bool b;
        font_M=QFontDialog::getFont(&b,font_M,this,"修改字体");
        UpDateUI();
        emit FontChanged();
    });
    
    connect(ui->ButtonColor,&QPushButton::clicked,[=](){
        HSVColorDialog hsvcd(this);
        color_M=hsvcd.GetColor(color_M);
        UpDateUI();
        emit ColorChanged();
    });
    
    connect(ui->BoxUnderLine,&QCheckBox::clicked,[=](int b){
        font_M.setUnderline(b);
        UpDateUI();
        emit FontChanged();
    });
    
    connect(ui->BoxStrikeOut,&QCheckBox::clicked,[=](int b){
        font_M.setStrikeOut(b);
        UpDateUI();
        emit FontChanged();
    });
    
    connect(ui->BoxBold,&QCheckBox::clicked,[=](int b){
        font_M.setBold(b);
        UpDateUI();
        emit FontChanged();
    });
    
    connect(ui->BoxItalic,&QCheckBox::clicked,[=](int b){
        font_M.setItalic(b);
        UpDateUI();
        emit FontChanged();
    });
    
    UpDateUI();
}

void FontSetting::UpDateUI()
{
    ui->LineFamily->setText(font_M.family());
    ui->LineSize->setText(QString("%1").arg(font_M.pointSize()));
    ui->ButtonColor->setStyleSheet(QString("background-color:rgb(%1,%2,%3)").arg(color_M.red()).arg(color_M.green()).arg(color_M.blue()));    
    ui->BoxUnderLine->setChecked(font_M.underline());
    ui->BoxStrikeOut->setChecked(font_M.strikeOut());
    ui->BoxBold->setChecked(font_M.bold());
    ui->BoxItalic->setChecked(font_M.italic());
}

FontSetting::~FontSetting()
{
    delete ui;
}
