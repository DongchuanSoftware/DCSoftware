#ifndef SVWIDGET_H
#define SVWIDGET_H

#include <QWidget>
#include<myalgorithm.h>
#include<QPainter>
#include<QMouseEvent>

class SVWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SVWidget(QWidget *parent = nullptr);
    
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent* qme);
    void mouseMoveEvent(QMouseEvent* qme);
    
    QColor* i_colors;
    
    int* h_M;
    double* s_M;
    double* v_M;
    
signals:
    void parent_update();
public slots:
};

#endif // SVWIDGET_H
