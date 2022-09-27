#ifndef LAYERATTRMANAGER_H
#define LAYERATTRMANAGER_H

#include <QWidget>

namespace Ui {
class LayerAttrManager;
}

class LayerAttrManager : public QWidget
{
    Q_OBJECT
    
public:
    explicit LayerAttrManager(QWidget *parent = nullptr);
    ~LayerAttrManager();
    
private:
    Ui::LayerAttrManager *ui;
};

#endif // LAYERATTRMANAGER_H
