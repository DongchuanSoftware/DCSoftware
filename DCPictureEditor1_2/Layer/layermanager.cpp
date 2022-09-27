#include "layermanager.h"
//#include<iostream>
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
    
    this->setColumnWidth(0,100);
    this->setColumnWidth(1,150);
    this->resizeColumnToContents(2);
    this->horizontalHeader()->setStretchLastSection(true);
    
    //------------------------右键菜单------------------------------------
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    //单选普通
    QMenu* menu1=new QMenu(this);
    QAction* action_InsertAbove=new QAction("上方插入图层",menu1);
    connect(action_InsertAbove,&QAction::triggered,[=](){
        PictureLayer* ply=new PictureLayer;
        ply->width=v_layers[0]->width;
        ply->height=v_layers[0]->height;
        QPixmap pix(ply->width,ply->height);
        pix.fill(Qt::transparent);
        ply->object=pix;
        std::deque<Layer*>::iterator it=v_layers.begin();
        it+=v_layers.size()-this->row(this->selectedItems().at(0));
        this->v_layers.insert(it,ply);
        
        this->UpDateUI();
    });
    menu1->addAction(action_InsertAbove);
    
    QAction* action_InsertBelow=new QAction("下方插入图层",menu1);
    connect(action_InsertBelow,&QAction::triggered,[=](){
        PictureLayer* ply=new PictureLayer;
        ply->width=v_layers[0]->width;
        ply->height=v_layers[0]->height;
        QPixmap pix(ply->width,ply->height);
        pix.fill(Qt::transparent);
        //pix.fill(Qt::red);
        ply->object=pix;
        std::deque<Layer*>::iterator it=v_layers.begin();
        it+=v_layers.size()-this->row(this->selectedItems().at(0))-1;
        this->v_layers.insert(it,ply);
        
        this->UpDateUI();
    });
    menu1->addAction(action_InsertBelow);
    
    QAction* action_Delete=new QAction("删除图层",menu1);
    connect(action_Delete,&QAction::triggered,[=](){
        std::deque<Layer*>::iterator it=v_layers.begin();
        it+=v_layers.size()-this->row(this->selectedItems().at(0))-1;
        this->v_layers.erase(it);
        this->UpDateUI();
    });
    menu1->addAction(action_Delete);
    
    QAction* action_MoveUp=new QAction("向上移动图层",menu1);
    QDialog* dlg1=new QDialog(this);
    QLineEdit* led1=new QLineEdit(dlg1);
    led1->setValidator(new QIntValidator(0,500,this));
    led1->resize(400,50);
    dlg1->setFixedSize(400,50);
    dlg1->setWindowTitle("向上移动");
    connect(action_MoveUp,&QAction::triggered,[=](){
        led1->setText("1");
        dlg1->exec();
        int x=led1->text().toInt();
        if(x!=0)
        {
            if(x-this->row(this->selectedItems().at(0))-1<0)
            {
                x++;
                std::deque<Layer*>::iterator it=v_layers.begin();
                it+=v_layers.size()-this->row(this->selectedItems().at(0))-1+x;
                this->v_layers.insert(it,v_layers[v_layers.size()-this->row(this->selectedItems().at(0))-1]);
                it-=x;
                this->v_layers.erase(it);
                this->UpDateUI();
            }
            else
            {
                x=v_layers.size()-(v_layers.size()-this->row(this->selectedItems().at(0))-1);
                std::deque<Layer*>::iterator it=v_layers.begin();
                it+=v_layers.size()-this->row(this->selectedItems().at(0))-1+x;
                this->v_layers.insert(it,v_layers[v_layers.size()-this->row(this->selectedItems().at(0))-1]);
                it-=x;
                this->v_layers.erase(it);
                this->UpDateUI();
            }
        }
    });
    menu1->addAction(action_MoveUp);
    
    QAction* action_MoveDown=new QAction("向下移动图层",menu1);
    QDialog* dlg2=new QDialog(this);
    QLineEdit* led2=new QLineEdit(dlg2);
    led2->setValidator(new QIntValidator(0,500,this));
    led2->resize(400,50);
    dlg2->setFixedSize(400,50);
    dlg2->setWindowTitle("向下移动");
    connect(action_MoveDown,&QAction::triggered,[=](){
        led2->setText("1");
        dlg2->exec();
        int x=led2->text().toInt();
        if(x!=0)
        {
            if((v_layers.size()-this->row(this->selectedItems().at(0))-1)>x)
            {
                std::deque<Layer*>::iterator it=v_layers.begin();
                it+=v_layers.size()-this->row(this->selectedItems().at(0))-1-x;
                this->v_layers.insert(it,v_layers[v_layers.size()-this->row(this->selectedItems().at(0))-1]);
                it=v_layers.begin()+v_layers.size()-this->row(this->selectedItems().at(0))-1;
                this->v_layers.erase(it);
                this->UpDateUI();
            }
            else
            {
                //x=v_layers.size()-this->row(this->selectedItems().at(0))-2;
                std::deque<Layer*>::iterator it=v_layers.begin();
                this->v_layers.insert(it+1,v_layers[v_layers.size()-this->row(this->selectedItems().at(0))-1]);
                it=v_layers.begin()+v_layers.size()-this->row(this->selectedItems().at(0))-1;
                this->v_layers.erase(it);
                this->UpDateUI();
            }
        }
    });
    menu1->addAction(action_MoveDown);
    
    QAction* action_MergeDown=new QAction("向下合并图层",menu1);
    connect(action_MergeDown,&QAction::triggered,[=](){
       
        if(v_layers[v_layers.size()-this->row(this->selectedItems().at(0))-2]->type==1){
            
            BackgroundLayer* pcl=new BackgroundLayer;
            pcl->width=this->width;
            pcl->height=this->height;
            QPixmap pix(pcl->width,pcl->height);
            pix.fill(Qt::transparent);
            v_layers[v_layers.size()-this->row(this->selectedItems().at(0))-2]->Draw(&pix);
            v_layers[v_layers.size()-this->row(this->selectedItems().at(0))-1]->Draw(&pix);
            std::deque<Layer*>::iterator it=v_layers.begin();
            it+=v_layers.size()-this->row(this->selectedItems().at(0))-1;
            this->v_layers.erase(it);
            this->v_layers.erase(it-1);
            pcl->object=pix;
            this->v_layers.insert(it-1,pcl);
            this->UpDateUI();
        }
        else
        {
            PictureLayer* pcl=new PictureLayer;
            pcl->width=this->width;
            pcl->height=this->height;
            QPixmap pix(pcl->width,pcl->height);
            pix.fill(Qt::transparent);
            v_layers[v_layers.size()-this->row(this->selectedItems().at(0))-2]->Draw(&pix);
            v_layers[v_layers.size()-this->row(this->selectedItems().at(0))-1]->Draw(&pix);
            std::deque<Layer*>::iterator it=v_layers.begin();
            it+=v_layers.size()-this->row(this->selectedItems().at(0))-1;
            this->v_layers.erase(it);
            this->v_layers.erase(it-1);
            pcl->object=pix;
            this->v_layers.insert(it-1,pcl);
            this->UpDateUI();
        }
    });
    menu1->addAction(action_MergeDown);
    
    //单选背景
    QMenu* menu2=new QMenu(this);
    QAction* action_InsertAbove_b=new QAction("上方插入图层",menu2);
    connect(action_InsertAbove_b,&QAction::triggered,[=](){
        PictureLayer* ply=new PictureLayer;
        ply->width=v_layers[0]->width;
        ply->height=v_layers[0]->height;
        QPixmap pix(ply->width,ply->height);
        pix.fill(Qt::transparent);
        ply->object=pix;
        
        this->v_layers.insert(v_layers.begin()+1,ply);
        
        this->UpDateUI();
    });
    menu2->addAction(action_InsertAbove_b);
    
    //单选其它
    QMenu* menu4=new QMenu(this);
    menu4->addAction(action_InsertAbove);
    menu4->addAction(action_InsertBelow);
    menu4->addAction(action_Delete);
    menu4->addAction(action_MoveUp);
    menu4->addAction(action_MoveDown);
    menu4->addAction(action_MergeDown);
    
    QAction* action_ToPictureLayer=new QAction("转图片图层");
    connect(action_ToPictureLayer,&QAction::triggered,[=](){
        PictureLayer* ply=new PictureLayer;
        ply->width=v_layers[0]->width;
        ply->height=v_layers[0]->height;
        QPixmap pix(ply->width,ply->height);
        pix.fill(Qt::transparent);
        v_layers[v_layers.size()-this->row(this->selectedItems().at(0))-1]->Draw(&pix);
        ply->object=pix;
        std::deque<Layer*>::iterator it=v_layers.begin();
        it+=v_layers.size()-this->row(this->selectedItems().at(0));
        this->v_layers.insert(it,ply);
        
        v_layers.erase(it-1);
        this->UpDateUI();
    });
    menu4->addAction(action_ToPictureLayer);
    
    //多选
    QMenu* menu3=new QMenu(this);
    QAction* action_DeleteAll=new QAction("删除图层",menu3);
    connect(action_DeleteAll,&QAction::triggered,[=](){
        int x=this->selectedItems().size();
        for(int i=0;i<x;i++)
        {
            if(v_layers.size()-this->row(this->selectedItems().at(0))-1!=0)
            {
                std::deque<Layer*>::iterator it=v_layers.begin();
                it+=v_layers.size()-this->row(this->selectedItems().at(0))-1;
                this->v_layers.erase(it);
                this->UpDateUI();
            }
        }
    });
    menu3->addAction(action_DeleteAll);
    
    connect(this,&QTableWidget::customContextMenuRequested,[=](QPoint){
        QList<QTableWidgetItem*> items=this->selectedItems();
        if(items.count()==1)//单选
        {
            if(v_layers[v_layers.size()-this->row(this->selectedItems().at(0))-1]->type==2)//不是背景
            {
                menu1->exec(QCursor::pos());
            }
            else if(v_layers[v_layers.size()-this->row(this->selectedItems().at(0))-1]->type==1)//背景
            {
                menu2->exec(QCursor::pos());
            }
            else if(v_layers[v_layers.size()-this->row(this->selectedItems().at(0))-1]->type==3)
            {
                menu4->exec(QCursor::pos());
            }
        }
        else if(items.count()>1)//多选
        {
            menu3->exec(QCursor::pos());
        }
    });
}

LayerManager::~LayerManager()
{
    this->clear();
}

void LayerManager::UpDateUI()
{
    //this->clear();
    
    this->setRowCount(this->v_layers.size());
    
    for(int i=0;i<this->v_layers.size();i++)
    //for(int i=v_layers.size()-1;i>=0;i--)
    {
        this->setRowHeight(v_layers.size()-i-1,100);
        //图层名
        QTableWidgetItem* twi=new QTableWidgetItem(this->v_layers[i]->name);
        this->setItem(v_layers.size()-i-1,2,twi);
        connect(this,&QTableWidget::itemChanged,[=](QTableWidgetItem* qtwi){
            if(qtwi==twi)
            {
                this->v_layers[i]->name=this->item(v_layers.size()-i-1,2)->text();
            }
        });
        //图层图标
        QLabel* lb=new QLabel;
        QPixmap pix(this->width,this->height);
        pix.fill(Qt::transparent);
        this->v_layers[i]->Draw(&pix);
        lb->setPixmap(pix.scaled(150,100));
        this->setCellWidget(v_layers.size()-i-1,1,lb);
        //是否可见
        QCheckBox* ckb=new QCheckBox(this);
        ckb->setChecked(v_layers[i]->vis);
        this->setCellWidget(v_layers.size()-i-1,0,ckb);
        connect(ckb,&QCheckBox::clicked,[=](int x){
            this->v_layers[i]->vis=(bool)x;
            emit wkspace_update();
        });
    }
    emit wkspace_update();
}