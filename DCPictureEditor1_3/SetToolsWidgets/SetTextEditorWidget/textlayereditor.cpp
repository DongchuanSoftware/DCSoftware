#include "textlayereditor.h"
#include "ui_textlayereditor.h"

TextLayerEditor::TextLayerEditor(int tlayer_pos, LayerManager* lym, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TextLayerEditor)
{
    ui->setupUi(this);
    
    ui->wkwidget->lymanager=this->lymanager=lym;
    ui->scrollAreaWidgetContents->setFixedSize(lymanager->width,lymanager->height);
    
    ui->wkwidget->tlayer_pos=this->tlayer_pos=tlayer_pos;
    ui->wkwidget->w=ui->mainEdit;
    
    ui->mainEdit->setTextColor(ui->fsWidget->color_M);
    ui->mainEdit->setFont(ui->fsWidget->font_M);
    
    connect(ui->mainEdit,&QTextEdit::selectionChanged,[=](){
        ui->fsWidget->color_M=ui->mainEdit->textColor();
        ui->fsWidget->font_M=ui->mainEdit->currentFont();
        ui->fsWidget->upDateUI();
    });
    
    connect(ui->mainEdit,&QTextEdit::cursorPositionChanged,[=](){
        ui->fsWidget->color_M=ui->mainEdit->textColor();
        ui->fsWidget->font_M=ui->mainEdit->currentFont();
        ui->fsWidget->upDateUI();
    });
    
    connect(ui->fsWidget,&FontSetting::colorChanged,[=](){
        ui->mainEdit->setTextColor(ui->fsWidget->color_M);
    });
    
    connect(ui->fsWidget,&FontSetting::fontChanged,[=](){
        ui->mainEdit->setCurrentFont(ui->fsWidget->font_M);
    });
    
    connect(ui->mainEdit,&QTextEdit::textChanged,[=](){
        ui->mainEdit->resize(ui->mainEdit->document()->size().width(),ui->mainEdit->document()->size().height());
    });
}

QTextEdit* TextLayerEditor::mainEdit()
{
    return ui->mainEdit;
}

TextLayerEditor::~TextLayerEditor()
{
    delete ui;
}
