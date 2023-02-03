#ifndef SETBRUSHWIDGET_H
#define SETBRUSHWIDGET_H

#include <QWidget>

namespace Ui {
class SetBrushWidget;
}

class SetBrushWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit SetBrushWidget(QWidget *parent = nullptr);
    ~SetBrushWidget();
    
    bool flag_trans=1;
    
    int transparency_M=255;
    int width_M=7;
    int hardness_M=1;
    int radius_M=100;
    bool isCircle_M=1;
    bool lockedR_M;
    

signals:
    void widthChanged();
    void setWidth(int w);
    void setRadius(int r);
    
private slots:
    void on_spinBoxTransparency_valueChanged(int v);
    
    void on_spinBoxWidth_valueChanged(int v);
    
    void on_spinBoxHardness_valueChanged(int v);
    
    void on_spinBoxRadius_valueChanged(int v);
    
    void on_radioButtonCircle_clicked();
    
    void on_radioButtonArc_clicked();
    
    void on_radioButtonArcLR_clicked();
    
private:
    Ui::SetBrushWidget *ui;
};

#endif // SETBRUSHWIDGET_H
