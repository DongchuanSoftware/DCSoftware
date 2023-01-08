#ifndef SETTEXTEDITORWIDGET_H
#define SETTEXTEDITORWIDGET_H

#include <QWidget>
#include<QFontDialog>
#include"Color/colormanager.h"
#include<QDialogButtonBox>
#include"Color/hsvcolordialog.h"
#include<QColor>

namespace Ui {
class FontSetting;
}

class FontSetting : public QWidget
{
    Q_OBJECT
    
public:
    explicit FontSetting(QWidget *parent = nullptr);
    ~FontSetting();
    
    QFont font_M;
    QColor color_M;
    
    void upDateUI();
    
private:
    Ui::FontSetting *ui;
signals:
    void colorChanged();
    void fontChanged();
};

#endif // SETTEXTEDITORWIDGET_H
