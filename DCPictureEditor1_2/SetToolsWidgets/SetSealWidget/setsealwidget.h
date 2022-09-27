#ifndef SETSEALWIDGET_H
#define SETSEALWIDGET_H

#include <QWidget>
#include<QPixmap>

namespace Ui {
class SetSealWidget;
}

class SetSealWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit SetSealWidget(QWidget *parent = nullptr);
    ~SetSealWidget();
    
    int width_M=7;
    bool mode_M=0;
    QPoint sppoint_M;
    int layerpos_M=0;

signals:
    void WidthChanged();
    
private slots:
    void on_SpinBoxWidth_valueChanged(int v);
    
    void on_BtnChangeSPPoint_clicked();
    
private:
    Ui::SetSealWidget *ui;
};

#endif // SETSEALWIDGET_H
