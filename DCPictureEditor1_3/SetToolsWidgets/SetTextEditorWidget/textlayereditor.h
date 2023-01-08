#ifndef TEXTLAYEREDITOR_H
#define TEXTLAYEREDITOR_H

#include <QWidget>
#include"Layer/layermanager.h"
#include<QPainter>
#include<QToolButton>
#include<QTextEdit>

namespace Ui {
class TextLayerEditor;
}

class TextLayerEditor : public QWidget
{
    Q_OBJECT
    
public:
    explicit TextLayerEditor(int tlayer_pos,LayerManager* lym,QWidget *parent = nullptr);
    ~TextLayerEditor();
    
    //void paintEvent(QPaintEvent*);
    
    LayerManager* lymanager;
    QFont realFont;
    int realWidth;
    int realHeight;
    double k=1;
    int tlayer_pos;
    
    QTextEdit* mainEdit();
    
private:
    Ui::TextLayerEditor *ui;
};

#endif // TEXTLAYEREDITOR_H
