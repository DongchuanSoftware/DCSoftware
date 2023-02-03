#include "layermanager.h"

LayerManager::LayerManager(QWidget *parent) : QTableWidget(parent)
{
    this->setColumnCount(3);
    this->horizontalHeader()->setVisible(0);
    this->verticalHeader()->setVisible(0);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);//行选择
    this->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);//可编辑
    
    x=0;
    y=0;
    k=1;
    
    this->setColumnWidth(0,50);
    this->setColumnWidth(1,150);
    this->resizeColumnToContents(2);
    this->horizontalHeader()->setStretchLastSection(true);
    
    //------------------------右键菜单------------------------------------
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    
    //单选普通
    QMenu* menuPictureLayer=new QMenu(this);
    QMenu* menuBackgroundLayer=new QMenu(this);
    QMenu* menuTextLayer=new QMenu(this);
    QMenu* menuMultiLayer=new QMenu(this);
    
    QAction* actionInsertAbove=new QAction("上方插入图层",this);
    connect(actionInsertAbove,&QAction::triggered,this,[=](){
        int x=this->row(this->selectedItems().first());
        PictureLayer* ply=new PictureLayer;
        ply->width=v_layers[0]->width;
        ply->height=v_layers[0]->height;
        QImage pix(ply->width,ply->height,QImage::Format_ARGB32);
        pix.fill(Qt::transparent);
        ply->object=pix;
        this->v_layers.insert(v_layers.begin()+(v_layers.size()-x),ply);
        this->upDateUI();
        this->selectRow(x);
    });
    
    QAction* actionInsertBelow=new QAction("下方插入图层",this);
    connect(actionInsertBelow,&QAction::triggered,this,[=](){
        int x=this->row(this->selectedItems().first());
        PictureLayer* ply=new PictureLayer;
        ply->width=v_layers[0]->width;
        ply->height=v_layers[0]->height;
        QImage pix(ply->width,ply->height,QImage::Format_ARGB32);
        pix.fill(Qt::transparent);
        ply->object=pix;
        this->v_layers.insert(v_layers.begin()+(v_layers.size()-x-1),ply);
        this->upDateUI();
        this->selectRow(x+1);
    });
    
    QAction* actionDelete=new QAction("删除图层",this);
    connect(actionDelete,&QAction::triggered,this,[=](){
        int x=this->row(this->selectedItems().first());
        delete v_layers[v_layers.size()-x-1];
        v_layers.erase(v_layers.begin()+(v_layers.size()-x-1));
        this->upDateUI();
        this->selectRow(x);
    });
    
    QAction* actionMoveUp=new QAction("向上移动图层",this);
    connect(actionMoveUp,&QAction::triggered,this,[=](){
        int x=(int)v_layers.size()-this->row(this->selectedItems().first())-1;
        QDialog dlg(this);
        QLineEdit led(&dlg);
        led.setValidator(new QIntValidator(0,500,this));
        led.resize(400,50);
        dlg.setFixedSize(400,50);
        dlg.setWindowTitle("向上移动");
        led.setText("1");
        connect(&led,&QLineEdit::editingFinished,&dlg,&QDialog::close);
        dlg.exec();
        int y=led.text().toInt();
        y=(x+y<(int)v_layers.size())?y:((int)v_layers.size()-x-1);
        if(y!=0)
        {
            v_layers.insert(v_layers.begin()+(x+y+1),v_layers[x]);
            v_layers.erase(v_layers.begin()+x);
            this->upDateUI();
            this->selectRow((int)v_layers.size()-x-y-1);
        }
    });
    
    QAction* actionMoveDown=new QAction("向下移动图层",this);
    connect(actionMoveDown,&QAction::triggered,this,[=](){
        int x=(int)v_layers.size()-this->row(this->selectedItems().first())-1;
        QDialog dlg(this);
        QLineEdit led(&dlg);
        led.setValidator(new QIntValidator(0,500,this));
        led.resize(400,50);
        dlg.setFixedSize(400,50);
        dlg.setWindowTitle("向上移动");
        led.setText("1");
        connect(&led,&QLineEdit::editingFinished,&dlg,&QDialog::close);
        dlg.exec();
        int y=led.text().toInt();
        y=(x-y>0)?y:(x-1);
        if(y!=0)
        {
            v_layers.insert(v_layers.begin()+(x-y),v_layers[x]);
            v_layers.erase(v_layers.begin()+(x+1));
            this->upDateUI();
            this->selectRow((int)v_layers.size()-x+y-1);
        }
    });
    
    QAction* actionMergeDown=new QAction("向下合并图层",this);
    connect(actionMergeDown,&QAction::triggered,this,[=](){
        int x=this->row(this->selectedItems().first());
        QImage pix(this->width,this->height,QImage::Format_ARGB32);
        pix.fill(Qt::transparent);
        v_layers[v_layers.size()-x-2]->Draw(&pix);
        v_layers[v_layers.size()-x-1]->Draw(&pix);
        Layer* ly;
        if(v_layers[v_layers.size()-x-2]->type==LT_BACKGROUND)
        {
            BackgroundLayer* bgl=new BackgroundLayer;
            bgl->object=pix;
            ly=bgl;
        }
        else
        {
            PictureLayer* pcl=new PictureLayer;
            pcl->object=pix;
            ly=pcl;
        }
        ly->width=this->width;
        ly->height=this->height;
        int y=v_layers.size()-x-2;
        delete v_layers[y];
        delete v_layers[y+1];
        v_layers.erase(v_layers.begin()+y,
                       v_layers.begin()+(y+2));
        v_layers.insert(v_layers.begin()+y,ly);
        this->upDateUI();
        this->selectRow(x-1);
    });
    
    QAction* actionToPictureLayer=new QAction("转图片图层",this);
    connect(actionToPictureLayer,&QAction::triggered,this,[=](){
        PictureLayer* ply=new PictureLayer;
        ply->width=v_layers[0]->width;
        ply->height=v_layers[0]->height;
        QImage pix(ply->width,ply->height,QImage::Format_ARGB32);
        pix.fill(Qt::transparent);
        v_layers[v_layers.size()-this->row(this->selectedItems().first())-1]->Draw(&pix);
        ply->object=pix;
        std::vector<Layer*>::iterator it=v_layers.begin();
        it+=v_layers.size()-this->row(this->selectedItems().first());
        this->v_layers.insert(it,ply);
        delete *(it-1);
        v_layers.erase(it-1);
        this->upDateUI();
    });
    
    QAction* actionDeleteMulti=new QAction("删除图层",this);
    connect(actionDeleteMulti,&QAction::triggered,this,[=](){
        int x=v_layers.size()-this->row(this->selectedItems().last())-1;
        x=((x!=0)?x:1);
        int y=v_layers.size()-this->row(this->selectedItems().first());
        for(int i=x;i<y;i++)
        {
            delete v_layers[i];
        }
        v_layers.erase(v_layers.begin()+x,
                       v_layers.begin()+y);
        this->upDateUI();
    });
    
    menuBackgroundLayer->addAction(actionInsertAbove);
    
    menuPictureLayer->addAction(actionInsertAbove);
    menuPictureLayer->addAction(actionInsertBelow);
    menuPictureLayer->addAction(actionDelete);
    menuPictureLayer->addAction(actionMoveUp);
    menuPictureLayer->addAction(actionMoveDown);
    menuPictureLayer->addAction(actionMergeDown);
    
    menuTextLayer->addAction(actionInsertAbove);
    menuTextLayer->addAction(actionInsertBelow);
    menuTextLayer->addAction(actionDelete);
    menuTextLayer->addAction(actionMoveUp);
    menuTextLayer->addAction(actionMoveDown);
    menuTextLayer->addAction(actionMergeDown);
    menuTextLayer->addAction(actionToPictureLayer);
    
    menuMultiLayer->addAction(actionDeleteMulti);
    
    connect(this,&QTableWidget::customContextMenuRequested,this,[=](QPoint){
        QList<QTableWidgetItem*> items=this->selectedItems();
        if(items.count()==1)//单选
        {
            switch(v_layers[v_layers.size()-this->row(this->selectedItems().first())-1]->type){
            case LT_BACKGROUND:{
                menuBackgroundLayer->exec(QCursor::pos());
            }break;
            case LT_PICTURE:{
                menuPictureLayer->exec(QCursor::pos());
            }break;
            case LT_TEXT:{
                menuTextLayer->exec(QCursor::pos());
            }break;
            }
        }
        else if(items.count()>1)//多选
        {
            menuMultiLayer->exec(QCursor::pos());
        }
    });
    
}

LayerManager::~LayerManager()
{
    for(int i=0;i<(int)v_layers.size();i++)
    {
        delete v_layers[i];
    }
    this->clear();
}

void LayerManager::upDateUI()
{
    this->setRowCount(this->v_layers.size());
    
    for(int i=0;i<(int)this->v_layers.size();i++)
    {
        this->setRowHeight(v_layers.size()-i-1,100);
        //图层名
        QTableWidgetItem* twi=new QTableWidgetItem(this->v_layers[i]->name);
        this->setItem(v_layers.size()-i-1,2,twi);
        
        connect(this,&QTableWidget::cellChanged,this,[=](int row,int col){
            if((row==((int)v_layers.size()-i-1))&&(col==2))
            this->v_layers[i]->name=this->item(row,col)->text();
            emit layerNameChanged();
        });
        
        //图层图标
        QLabel* lb=new QLabel(this);
        QPixmap pix(this->width,this->height);
        pix.fill(Qt::transparent);
        this->v_layers[i]->Draw(&pix);
        lb->setPixmap(pix.scaled(150,100));
        this->setCellWidget(v_layers.size()-i-1,1,lb);
        //是否可见
        QCheckBox* ckb=new QCheckBox(this);
        ckb->setStyleSheet("QCheckBox::indicator"
                           "{"
                           "width:50px;"
                           "height:50px;"
                           "}"
                           "QCheckBox::indicator:checked"
                           "{"
                           "image:url(:/OtherIcon/Visit1.png);"
                           "}"
                           "QCheckBox::indicator:unchecked"
                           "{"
                           "image:url(:/OtherIcon/Visit0.png);"
                           "}");
        ckb->setChecked(v_layers[i]->vis);
        this->setCellWidget(v_layers.size()-i-1,0,ckb);
        connect(ckb,&QCheckBox::clicked,this,[=](int x){
            this->v_layers[i]->vis=(bool)x;
            emit wkspaceUpdate();
        });
    }
    emit wkspaceUpdate();
}