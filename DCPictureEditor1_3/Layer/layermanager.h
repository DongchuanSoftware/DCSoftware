#ifndef LAYERMANAGER_H
#define LAYERMANAGER_H

#include <QWidget>
#include"Layer/layer.h"
#include"Layer/textlayer.h"
#include"Layer/backgroundlayer.h"
#include"Layer/picturelayer.h"
#include<QTableWidget>
#include<vector>
#include<QHeaderView>
#include<QCheckBox>
#include<QLabel>
#include<QMenu>
#include<QAction>
#include<deque>
#include<QDialog>
#include<QLineEdit>

class LayerManager : public QTableWidget
{
    Q_OBJECT
public:
    explicit LayerManager(QWidget *parent = nullptr);
    ~LayerManager();
    
    int x;
    int y;
    int width;
    int height;
    double k;
    std::vector<Layer*> v_layers;
    
    void upDateUI();
    
signals:
    void wkspaceUpdate();
    void layerNameChanged();
    
public slots:
};

#endif // LAYERMANAGER_H
