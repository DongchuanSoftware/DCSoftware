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
    void on_pushButtonSure_clicked();
    
    void on_pushButtonCancel_clicked();
    
    void on_buttonChange_clicked();
    
private:
    Ui::ActionNewWidget *ui;
};

#endif // ACTIONNEWWIDGET_H
