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

signals:
    void widthChanged();
    
private slots:
    
private:
    Ui::SetSealWidget *ui;
};

#endif // SETSEALWIDGET_H
