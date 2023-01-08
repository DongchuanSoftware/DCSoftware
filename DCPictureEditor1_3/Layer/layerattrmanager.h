#ifndef LAYERATTRMANAGER_H
#define LAYERATTRMANAGER_H

#include <QWidget>
#include"Layer/layer.h"
#include<QString>
#include"Layer/layermanager.h"

namespace Ui {
class LayerAttrManager;
}

class LayerAttrManager : public QWidget
{
    Q_OBJECT
    
public:
    explicit LayerAttrManager(QWidget *parent,LayerManager* _lymanager);
    ~LayerAttrManager();
    
    void upDateUI();
    
    LayerManager* lymanager;
    double k;
    
private slots:
    void on_editName_textChanged(const QString &str);
    
    void on_spinWidth_valueChanged(int width);
    
    void on_spinHeight_valueChanged(int height);
    
    void on_spinX_valueChanged(int x);
    
    void on_spinY_valueChanged(int y);
    
private:
    Ui::LayerAttrManager *ui;
};

#endif // LAYERATTRMANAGER_H
