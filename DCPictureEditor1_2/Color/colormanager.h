#ifndef COLORMANAGER_H
#define COLORMANAGER_H

#include <QWidget>
#include<QPaintEvent>
#include<QPainter>
#include<QColor>
#include<algorithm>
#include<QColorDialog>
#include"myalgorithm.h"

namespace Ui {
class ColorManager;
}

class ColorManager : public QWidget
{
    Q_OBJECT
public:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent* qme);
    
    int h_M=0;
    double s_M=0;
    double v_M=0;
    int r_M=0;
    int g_M=0;
    int b_M=0;
    
    QColor now_color;
    
public:
    explicit ColorManager(QWidget *parent = nullptr);
    ~ColorManager();
    
private:
    Ui::ColorManager *ui;
};

#endif // COLORMANAGER_H
