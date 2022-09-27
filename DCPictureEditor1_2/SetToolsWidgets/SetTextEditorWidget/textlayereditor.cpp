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
    ui->wkwidget->w=ui->MainEdit;
    
    /*
    if(lymanager==nullptr)
    {
        return;
    }
    //QPainter painter(ui->scrollAreaWidgetContents);
    QPixmap pix(lymanager->width,lymanager->height);
    pix.fill(Qt::transparent);
    for(int i=0;i<lymanager->v_layers.size();i++)
    {
        if(lymanager->v_layers[i]->vis&&i!=tlayer_pos)
        {
            lymanager->v_layers[i]->Draw(&pix);
        }
        
    }
    pix.save("C:/Users/l'z'y/Desktop/1.png");
    QPalette plt=ui->scrollAreaWidgetContents->palette();
    plt.setBrush(QPalette::Window,QBrush(pix));
    ui->scrollAreaWidgetContents->setStyleSheet("");
    ui->scrollAreaWidgetContents->setAutoFillBackground(1);
    ui->scrollAreaWidgetContents->setPalette(plt);
//    QWidget* w=new QWidget(this);
//    w->setAutoFillBackground(1);
//    w->setPalette(plt);
//    QDialog d;
//    w->setParent(&d);
//    w->show();
//    d.exec();*/
    
    ui->MainEdit->setTextColor(ui->FSWidget->color_M);
    ui->MainEdit->setFont(ui->FSWidget->font_M);
    
    connect(ui->MainEdit,&QTextEdit::selectionChanged,[=](){
        //QTextCursor qtc=ui->MainEdit->textCursor();
        //ui->MainEdit->te
//        QDialog dlg(this);
//        dlg.exec();
        ui->FSWidget->color_M=ui->MainEdit->textColor();
        ui->FSWidget->font_M=ui->MainEdit->currentFont();
        ui->FSWidget->UpDateUI();
    });
    
    connect(ui->MainEdit,&QTextEdit::cursorPositionChanged,[=](){
        ui->FSWidget->color_M=ui->MainEdit->textColor();
        ui->FSWidget->font_M=ui->MainEdit->currentFont();
        ui->FSWidget->UpDateUI();
    });
    
    connect(ui->FSWidget,&FontSetting::ColorChanged,[=](){
        ui->MainEdit->setTextColor(ui->FSWidget->color_M);
    });
    
    connect(ui->FSWidget,&FontSetting::FontChanged,[=](){
        //ui->MainEdit->setFont(ui->FSWidget->font_M);
        ui->MainEdit->setCurrentFont(ui->FSWidget->font_M);
    });
    
    connect(ui->MainEdit,&QTextEdit::textChanged,[=](){
        ui->MainEdit->resize(ui->MainEdit->document()->size().width(),ui->MainEdit->document()->size().height());
    });
}

//void TextLayerEditor::paintEvent(QPaintEvent *)
//{
//    if(lymanager==nullptr)
//    {
//        return;
//    }
//    QPainter painter(ui->scrollAreaWidgetContents);
//    QPixmap pix(lymanager->width,lymanager->height);
//    pix.fill(Qt::transparent);
//    for(int i=0;i<lymanager->v_layers.size();i++)
//    {
//        if(lymanager->v_layers[i]->vis&&i!=tlayer_pos)
//        {
//            lymanager->v_layers[i]->Draw(&pix);
//        }
        
//    }
//    painter.drawPixmap(lymanager->x,lymanager->y,
//                       lymanager->width*lymanager->k,lymanager->height*lymanager->k,
//                       pix);
//}



QTextEdit* TextLayerEditor::MainEdit()
{
    return ui->MainEdit;
}

TextLayerEditor::~TextLayerEditor()
{
    delete ui;
}
