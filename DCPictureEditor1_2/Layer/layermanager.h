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
using namespace std; 

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
    //vector<Layer*> v_layers;
    deque<Layer*> v_layers;
    
    void UpDateUI();
    
signals:
    void wkspace_update();
    
public slots:
};

#endif // LAYERMANAGER_H
