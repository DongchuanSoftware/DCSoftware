#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    //工具单选
    groupTools=new QActionGroup(this);
    QList<QAction*> listTools=ui->menuTools->actions();
    for(QList<QAction*>::iterator i=listTools.begin();i!=listTools.end();i++)
    {
        groupTools->addAction(*i);
    }
    
    //准备浮动窗口
    clmanager=new ColorManager(this);
    lymanager=new LayerManager(this);
    lyatmanager=new LayerAttrManager(this,lymanager);
    setbrush=new SetBrushWidget(this);
    setseal=new SetSealWidget(this);
    
    //准备工作区
    wkspace=new WorkSpace(this,
                          lymanager,
                          lyatmanager,
                          clmanager,
                          setbrush,
                          setseal);
    
    //工具锁定
    connect(wkspace,&WorkSpace::lockTools,this,[=](bool isUnlock){
        QList<QAction*> listMenus=ui->menuTools->actions();
        listMenus+=ui->menuEdit->actions();
        listMenus+=ui->menuFile->actions();
        listMenus+=ui->menuView->actions();
        for(QList<QAction*>::iterator i=listMenus.begin();i!=listMenus.end();i++)
        {
            (*i)->setEnabled(isUnlock);
        }
    });
    
    //工具鼠标图标切换
    connect(setbrush,&SetBrushWidget::widthChanged,this,[=](){
        if(wkspace->ttype==Brush||wkspace->ttype==Eraser)
        {
            wkspace->setCursor(QCursor(QPixmap(":/CursorIcon/Brush.png").scaled(setbrush->width_M*lymanager->k*2,setbrush->width_M*lymanager->k*2)));
        }
    });
    connect(setseal,&SetSealWidget::widthChanged,this,[=](){
        if(wkspace->ttype==Seal)
        {
            wkspace->setCursor(QCursor(QPixmap(":/CursorIcon/Brush.png").scaled(setseal->width_M*lymanager->k*2,setseal->width_M*lymanager->k*2)));
        }
    });
    
    connect(lymanager,&LayerManager::wkspaceUpdate,this,[=](){
        wkspace->update();
    });
    
    //界面布局
    //第一行
    this->dwColor=new QDockWidget("颜色",this);
    this->addDockWidget(Qt::RightDockWidgetArea,dwColor);
    dwColor->setAllowedAreas(Qt::AllDockWidgetAreas);
    dwColor->setWidget(clmanager);
    
    //第二行
    this->dwLyat=new QDockWidget("图层属性",this);
    this->addDockWidget(Qt::RightDockWidgetArea,dwLyat);
    dwLyat->setAllowedAreas(Qt::AllDockWidgetAreas);
    dwLyat->setWidget(lyatmanager);
    
    //工具
    this->dwSetBrush=new QDockWidget("画笔设置",this);
    this->addDockWidget(Qt::RightDockWidgetArea,dwSetBrush);
    dwSetBrush->setAllowedAreas(Qt::AllDockWidgetAreas);
    dwSetBrush->setWidget(setbrush);
    
    this->dwSetSeal=new QDockWidget("印章设置",this);
    this->addDockWidget(Qt::RightDockWidgetArea,dwSetSeal);
    dwSetBrush->setAllowedAreas(Qt::AllDockWidgetAreas);
    dwSetSeal->setWidget(setseal);
    
    //第三行
    this->dwLayer=new QDockWidget("图层",this);
    this->addDockWidget(Qt::RightDockWidgetArea,dwLayer);
    dwLayer->setAllowedAreas(Qt::AllDockWidgetAreas);
    dwLayer->setWidget(lymanager);
    
    this->dwChannels=new QDockWidget("通道",this);
    this->addDockWidget(Qt::RightDockWidgetArea,dwChannels);
    dwChannels->setAllowedAreas(Qt::AllDockWidgetAreas);
    
    this->dwPath=new QDockWidget("路径",this);
    this->addDockWidget(Qt::RightDockWidgetArea,dwPath);
    dwPath->setAllowedAreas(Qt::AllDockWidgetAreas);
    
    dwSetBrush->setFloating(1);
    dwSetBrush->hide();
    dwSetSeal->setFloating(1);
    dwSetSeal->hide();
    
    tabifyDockWidget(dwLayer,dwChannels);
    tabifyDockWidget(dwLayer,dwPath);//合并
    dwLayer->raise();
    
    dwLayer->setMinimumHeight(230);
    this->resizeDocks(QList<QDockWidget*>()<<dwColor<<dwLyat<<dwLayer,
                      QList<int>()<<width()/10<<width()/10<<width()/10,
                      Qt::Horizontal);
    
    this->setCentralWidget(wkspace);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//——————————————————————————菜单栏处理————————————————————

//--------------------------------------------文件--------------------------------------------
//新建
void MainWindow::on_actionNew_triggered()
{
    QDialog dlg(this);
    ActionNewWidget anw(&dlg);
    anw.p_dlg=&dlg;
    QHBoxLayout hbl;
    hbl.addWidget(&anw);
    dlg.setLayout(&hbl);
    dlg.exec();
    
    if(anw.pix!=nullptr)
    {
        if(this->lymanager->v_layers.empty())
        {
            lymanager->k=wkspace->width()/(double)anw.pix->width();
            BackgroundLayer* bgl=new BackgroundLayer;
            bgl->object=*anw.pix;
            lymanager->v_layers.push_back(bgl);
            
            lymanager->width=bgl->width=bgl->object.width();
            lymanager->height=bgl->height=bgl->object.height();
            
            lymanager->upDateUI();
        }
        else
        {
            MainWindow* mainwindow=new MainWindow;
            mainwindow->show();
            
            mainwindow->lymanager->k=mainwindow->wkspace->width()/(double)anw.pix->width();
            BackgroundLayer* bgl=new BackgroundLayer;
            bgl->object=*anw.pix;
            mainwindow->lymanager->v_layers.push_back(bgl);
            
            mainwindow->lymanager->width=bgl->width=bgl->object.width();
            mainwindow->lymanager->height=bgl->height=bgl->object.height();
            
            mainwindow->lymanager->upDateUI();
        }
    }
}

//导出
void MainWindow::on_actionExport_triggered()
{
    QString filename=QFileDialog::getSaveFileName(this,"导出","C:/无标题.jpg","图片(*.jpg *.jpeg *.png *.bmp *.ppm *.xbm *.xpm)");
    if(lymanager==nullptr||filename==""||lymanager->v_layers.empty())
    {
        return;
    }
    QPixmap pix(lymanager->width,lymanager->height);
    pix.fill(Qt::transparent);
    for(int i=0;i<(int)lymanager->v_layers.size();i++)
    {
        if(lymanager->v_layers[i]->vis)
        {
            lymanager->v_layers[i]->Draw(&pix);
        }
        
    }
    QImage img=pix.toImage();
    img.save(filename);
}

//退出
void MainWindow::on_actionExit_triggered()
{
    this->close();
}

//--------------------------------------------编辑--------------------------------------------

void MainWindow::on_actionHorizontalFold_triggered()
{
    if(lymanager->selectedItems().size()==0)return;
    int pos=lymanager->v_layers.size()-lymanager->row(lymanager->selectedItems().at(0))-1;
    if(lymanager->v_layers[pos]->type!=2)return;
    ((PictureLayer*)lymanager->v_layers[pos])->object=QPixmap::fromImage(((PictureLayer*)lymanager->v_layers[pos])->object.toImage().mirrored(1,0));
    lymanager->upDateUI();
}

void MainWindow::on_actionVerticalFold_triggered()
{
    if(lymanager->selectedItems().size()==0)return;
    int pos=lymanager->v_layers.size()-lymanager->row(lymanager->selectedItems().at(0))-1;
    if(lymanager->v_layers[pos]->type!=2)return;
    ((PictureLayer*)lymanager->v_layers[pos])->object=QPixmap::fromImage(((PictureLayer*)lymanager->v_layers[pos])->object.toImage().mirrored(0,1));
    lymanager->upDateUI();
}

//--------------------------------------------视图--------------------------------------------
//缩小
void MainWindow::on_actionShrink_triggered()
{
    if(lymanager->k*lymanager->width*0.9>=1&&lymanager->k*lymanager->height*0.9>=1)
    {
        lymanager->k*=0.9;
        wkspace->update();
        if(wkspace->ttype==Brush||wkspace->ttype==Eraser)
        {
            wkspace->setCursor(QCursor(QPixmap(":/CursorIcon/Brush.png").scaled(setbrush->width_M*lymanager->k*2,setbrush->width_M*lymanager->k*2)));
        }
        else if(wkspace->ttype==Seal)
        {
            wkspace->setCursor(QCursor(QPixmap(":/CursorIcon/Brush.png").scaled(setseal->width_M*lymanager->k*2,setseal->width_M*lymanager->k*2)));
        }
    }
}

//放大
void MainWindow::on_actionExpand_triggered()
{
    if(lymanager->k*1.1<=20)
    {
        lymanager->k*=1.1;
        wkspace->update();
        if(wkspace->ttype==Brush||wkspace->ttype==Eraser)
        {
            wkspace->setCursor(QCursor(QPixmap(":/CursorIcon/Brush.png").scaled(setbrush->width_M*lymanager->k*2,setbrush->width_M*lymanager->k*2)));
        }
        else if(wkspace->ttype==Seal)
        {
            wkspace->setCursor(QCursor(QPixmap(":/CursorIcon/Brush.png").scaled(setseal->width_M*lymanager->k*2,setseal->width_M*lymanager->k*2)));
        }
    }
}

//适应屏幕
void MainWindow::on_actionFitOnScreen_triggered()
{
    lymanager->k=wkspace->width()/(double)lymanager->v_layers[0]->width;
    wkspace->update();
}

//100%
void MainWindow::on_action100Per_triggered()
{
    lymanager->k=1;
    wkspace->update();
}

//回原点
void MainWindow::on_actionMoveTo0_triggered()
{
    lymanager->x=0;
    lymanager->y=0;
    wkspace->update();
}


//--------------------------------------------工具--------------------------------------------

void MainWindow::on_actionToolMoveAll_toggled(bool checked)
{
    if(checked)
    {
        wkspace->setCursor(Qt::OpenHandCursor);
        wkspace->ttype=MoveAll;
    }
}


void MainWindow::on_actionToolMoveLayer_toggled(bool checked)
{
    if(checked)
    {
        wkspace->setCursor(Qt::SizeAllCursor);
        wkspace->ttype=MoveLayer;
    }
}


void MainWindow::on_actionToolBrush_toggled(bool checked)
{
    if(checked)
    {
        wkspace->setCursor(QCursor(QPixmap(":/CursorIcon/Brush.png").scaled(setbrush->width_M*lymanager->k*2,setbrush->width_M*lymanager->k*2)));
        wkspace->ttype=Brush;
    }
}

void MainWindow::on_actionToolDrawLine_toggled(bool checked)
{
    if(checked)
    {
        wkspace->setCursor(Qt::ArrowCursor);
        wkspace->ttype=DrawLine;
    }
}

void MainWindow::on_actionDrawCircle_toggled(bool checked)
{
    if(checked)
    {
        wkspace->setCursor(Qt::ArrowCursor);
        wkspace->ttype=DrawCircle;
    }
}


void MainWindow::on_actionToolEraser_toggled(bool checked)
{
    if(checked)
    {
        wkspace->setCursor(QCursor(QPixmap(":/CursorIcon/Brush.png").scaled(setbrush->width_M*lymanager->k*2,setbrush->width_M*lymanager->k*2)));
        wkspace->ttype=Eraser;
    }
}


void MainWindow::on_actionToolTextEditor_toggled(bool checked)
{
    if(checked)
    {
        wkspace->setCursor(QCursor(QPixmap(":/CursorIcon/TextEditor.png").scaled(100,80)));
        wkspace->ttype=TextEditor;
    }
}



void MainWindow::on_actionToolSeal_toggled(bool checked)
{
    if(checked)
    {
        wkspace->setCursor(QCursor(QPixmap(":/CursorIcon/Brush.png").scaled(setbrush->width_M*lymanager->k*2,setbrush->width_M*lymanager->k*2)));
        wkspace->ttype=Seal;
    }
}


