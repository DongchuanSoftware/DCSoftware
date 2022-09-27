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
    int spacing_M=0;
    int fluency_M=10;

signals:
    void WidthChanged();
    
private slots:
    void on_SpinBoxTransparency_valueChanged(int v);
    
    void on_SpinBoxWidth_valueChanged(int v);
    
    void on_SpinBoxHardness_valueChanged(int v);
    
    void on_SpinBoxSpacing_valueChanged(int v);
    
    void on_SpinBoxFluency_valueChanged(int v);
    
private:
    Ui::SetBrushWidget *ui;
};

#endif // SETBRUSHWIDGET_H
