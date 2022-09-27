#ifndef ACTIONNEWWIDGET_H
#define ACTIONNEWWIDGET_H

#include <QWidget>
#include<QFileDialog>
#include<QDialog>
#include"Color/colormanager.h"
#include<QPixmap>
#include<QHBoxLayout>
#include"Color/hsvcolordialog.h"

namespace Ui {
class ActionNewWidget;
}

class ActionNewWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit ActionNewWidget(QWidget *parent = nullptr);
    ~ActionNewWidget();
    
    QString filename;
    QColor color;
    QPixmap* pix=nullptr;
    
    QDialog* p_dlg=nullptr;
    
private slots:
    void on_PushButtonSure_clicked();
    
    void on_PushButtonCancel_clicked();
    
    void on_ButtonChange_clicked();
    
private:
    Ui::ActionNewWidget *ui;
};

#endif // ACTIONNEWWIDGET_H
