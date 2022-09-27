#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);
    
    //其它浮动窗口
    this->DWColor=new QDockWidget("颜色",this);
    this->addDockWidget(Qt::RightDockWidgetArea,DWColor);
    DWColor->setAllowedAreas(Qt::AllDockWidgetAreas);
    clmanager=new ColorManager(this);
    DWColor->setWidget(clmanager);
    
    this->DWLyat=new QDockWidget("图层属性",this);
    this->addDockWidget(Qt::RightDockWidgetArea,DWLyat);
    DWLyat->setAllowedAreas(Qt::AllDockWidgetAreas);
    lyatmanager=new LayerAttrManager(this);
    DWLyat->setWidget(lyatmanager);
    
    this->DWLayer=new QDockWidget("图层",this);
    this->addDockWidget(Qt::RightDockWidgetArea,DWLayer);
    DWLayer->setAllowedAreas(Qt::AllDockWidgetAreas);
    lymanager=new LayerManager(this);
    DWLayer->setWidget(lymanager);
    
    this->DWChannels=new QDockWidget("通道",this);
    this->addDockWidget(Qt::RightDockWidgetArea,DWChannels);
    DWChannels->setAllowedAreas(Qt::AllDockWidgetAreas);
    tabifyDockWidget(DWLayer,DWChannels);
    
    this->DWPath=new QDockWidget("路径",this);
    this->addDockWidget(Qt::RightDockWidgetArea,DWPath);
    DWPath->setAllowedAreas(Qt::AllDockWidgetAreas);
    tabifyDockWidget(DWLayer,DWPath);//合并
    
    //工具
    this->DWSetBrush=new QDockWidget("画笔设置",this);
    this->addDockWidget(Qt::LeftDockWidgetArea,DWSetBrush);
    DWSetBrush->close();
    DWSetBrush->setFloating(1);
    DWSetBrush->setAllowedAreas(Qt::AllDockWidgetAreas);
    setbrush=new SetBrushWidget(this);
    DWSetBrush->setWidget(setbrush);
    
    this->DWSetSeal=new QDockWidget("印章设置",this);
    this->addDockWidget(Qt::LeftDockWidgetArea,DWSetSeal);
    DWSetSeal->close();
    DWSetSeal->setFloating(1);
    DWSetBrush->setAllowedAreas(Qt::AllDockWidgetAreas);
    setseal=new SetSealWidget(this);
    DWSetSeal->setWidget(setseal);
    
    //准备工作区
    wkspace=new WorkSpace(this);
    wkspace->lymanager=this->lymanager;
    wkspace->clmanager=this->clmanager;
    wkspace->setbrush=this->setbrush;
    wkspace->setseal=this->setseal;
    
    //工具锁定
    connect(wkspace,&WorkSpace::LockTools,[=](bool isUnlock){
        
        ui->ActionNew->setEnabled(isUnlock);
        ui->ActionOpen->setEnabled(isUnlock);
        ui->ActionSave->setEnabled(isUnlock);
        ui->ActionExport->setEnabled(isUnlock);
        ui->ActionExit->setEnabled(isUnlock);
        
        ui->ActionShrink->setEnabled(isUnlock);
        ui->ActionExpand->setEnabled(isUnlock);
        ui->ActionFitOnScreen->setEnabled(isUnlock);
        ui->Action100Per->setEnabled(isUnlock);
        ui->ActionMoveTo0->setEnabled(isUnlock);
        
        ui->ActionToolMoveAll->setEnabled(isUnlock);
        ui->ActionToolMoveLayer->setEnabled(isUnlock);
        ui->ActionToolBrush->setEnabled(isUnlock);
        ui->ActionToolEraser->setEnabled(isUnlock);
        ui->ActionToolTextEditor->setEnabled(isUnlock);
        ui->ActionToolSeal->setEnabled(isUnlock);
    });
    
    //工具鼠标图标切换
    connect(setbrush,&SetBrushWidget::WidthChanged,[=](){
        if(wkspace->ttype==Brush||wkspace->ttype==Eraser)
        {
            wkspace->setCursor(QCursor(QPixmap(":/CursorIcon/Brush.png").scaled(setbrush->width_M*lymanager->k*2,setbrush->width_M*lymanager->k*2)));
        }
    });
    connect(setseal,&SetSealWidget::WidthChanged,[=](){
        if(wkspace->ttype==Seal)
        {
            wkspace->setCursor(QCursor(QPixmap(":/CursorIcon/Brush.png").scaled(setseal->width_M*lymanager->k*2,setseal->width_M*lymanager->k*2)));
        }
    });
    connect(ui->ActionShrink,&QAction::triggered,[=](){
        if(wkspace->ttype==Brush||wkspace->ttype==Eraser)
        {
            wkspace->setCursor(QCursor(QPixmap(":/CursorIcon/Brush.png").scaled(setbrush->width_M*lymanager->k*2,setbrush->width_M*lymanager->k*2)));
        }
        else if(wkspace->ttype==Seal)
        {
            wkspace->setCursor(QCursor(QPixmap(":/CursorIcon/Brush.png").scaled(setseal->width_M*lymanager->k*2,setseal->width_M*lymanager->k*2)));
        }
    });
    connect(ui->ActionExpand,&QAction::triggered,[=](){
        if(wkspace->ttype==Brush||wkspace->ttype==Eraser)
        {
            wkspace->setCursor(QCursor(QPixmap(":/CursorIcon/Brush.png").scaled(setbrush->width_M*lymanager->k*2,setbrush->width_M*lymanager->k*2)));
        }
        else if(wkspace->ttype==Seal)
        {
            wkspace->setCursor(QCursor(QPixmap(":/CursorIcon/Brush.png").scaled(setseal->width_M*lymanager->k*2,setseal->width_M*lymanager->k*2)));
        }        
    });
    
    this->setCentralWidget(wkspace);
    connect(lymanager,&LayerManager::wkspace_update,[=](){
        wkspace->update();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ChangeToolIcon(ToolType tt)
{
    switch (tt) {
    case MoveAll:{
        ui->ActionToolMoveAll->setIcon(QIcon(":/ToolIcon/MoveAll.png"));
    }break;
    case MoveLayer:{
        ui->ActionToolMoveLayer->setIcon(QIcon(":/ToolIcon/MoveLayer.png"));
    }break;
    case Brush:{
        ui->ActionToolBrush->setIcon(QIcon(":/ToolIcon/Brush.png"));
    }break;
    case Eraser:{
        ui->ActionToolEraser->setIcon(QIcon(":/ToolIcon/Eraser.png"));
    }break;
    case TextEditor:{
        ui->ActionToolTextEditor->setIcon(QIcon(":/ToolIcon/TextEditor.png"));
    }break;
    case Seal:{
        ui->ActionToolSeal->setIcon(QIcon(":/ToolIcon/Seal.png"));
    }
    }
}

//——————————————————————————菜单栏处理————————————————————

//文件
//新建
void MainWindow::on_ActionNew_triggered()
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
            
            lymanager->UpDateUI();
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
            
            mainwindow->lymanager->UpDateUI();
        }
    }
}

//导出
void MainWindow::on_ActionExport_triggered()
{
    QString filename=QFileDialog::getSaveFileName(this,"导出","C:/无标题.jpg","图片(*.jpg *.jpeg *.png *.bmp *.ppm *.xbm *.xpm)");
    //qDebug()<<filename;
    if(lymanager==nullptr||filename==""||lymanager->v_layers.empty())
    {
        return;
    }
    QPixmap pix(lymanager->width,lymanager->height);
    pix.fill(Qt::transparent);
    for(int i=0;i<lymanager->v_layers.size();i++)
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
void MainWindow::on_ActionExit_triggered()
{
    this->close();
}

//视图
//缩小
void MainWindow::on_ActionShrink_triggered()
{
    if(lymanager->k*lymanager->width*0.9>=1&&lymanager->k*lymanager->height*0.9>=1)
    {
        lymanager->k*=0.9;
        wkspace->update();
    }
}

//放大
void MainWindow::on_ActionExpand_triggered()
{
    if(lymanager->k*1.1<=20)
    {
        lymanager->k*=1.1;
        wkspace->update();
    }
}

//适应屏幕
void MainWindow::on_ActionFitOnScreen_triggered()
{
    lymanager->k=wkspace->width()/(double)lymanager->v_layers[0]->width;
    wkspace->update();
}

//100%
void MainWindow::on_Action100Per_triggered()
{
    lymanager->k=1;
    wkspace->update();
}

//回原点
void MainWindow::on_ActionMoveTo0_triggered()
{
    lymanager->x=0;
    lymanager->y=0;
    wkspace->update();
}


//工具

void MainWindow::on_ActionToolMoveAll_triggered()
{
    ChangeToolIcon(wkspace->ttype);
    ui->ActionToolMoveAll->setIcon(QIcon(":/ToolIcon/MoveAll1.png"));
    wkspace->setCursor(Qt::OpenHandCursor);
    wkspace->ttype=MoveAll;
}

void MainWindow::on_ActionToolMoveLayer_triggered()
{
    ChangeToolIcon(wkspace->ttype);
    ui->ActionToolMoveLayer->setIcon(QIcon(":/ToolIcon/MoveLayer1.png"));
    wkspace->setCursor(Qt::SizeAllCursor);
    wkspace->ttype=MoveLayer;
}

void MainWindow::on_ActionToolBrush_triggered()
{
    ChangeToolIcon(wkspace->ttype);
    ui->ActionToolBrush->setIcon(QIcon(":/ToolIcon/Brush1.png"));
    wkspace->setCursor(QCursor(QPixmap(":/CursorIcon/Brush.png").scaled(setbrush->width_M*lymanager->k*2,setbrush->width_M*lymanager->k*2)));
    wkspace->ttype=Brush;
}

void MainWindow::on_ActionToolEraser_triggered()
{
    ChangeToolIcon(wkspace->ttype);
    ui->ActionToolEraser->setIcon(QIcon(":/ToolIcon/Eraser1.png"));
    wkspace->setCursor(QCursor(QPixmap(":/CursorIcon/Brush.png").scaled(setbrush->width_M*lymanager->k*2,setbrush->width_M*lymanager->k*2)));
    wkspace->ttype=Eraser;
}

void MainWindow::on_ActionToolTextEditor_triggered()
{
    ChangeToolIcon(wkspace->ttype);
    ui->ActionToolTextEditor->setIcon(QIcon(":/ToolIcon/TextEditor1.png"));
    wkspace->setCursor(QCursor(QPixmap(":/CursorIcon/TextEditor.png").scaled(100,80)));
    wkspace->ttype=TextEditor;
}

void MainWindow::on_ActionToolSeal_triggered()
{
    ChangeToolIcon(wkspace->ttype);
    ui->ActionToolSeal->setIcon(QIcon(":/ToolIcon/Seal1.png"));
    wkspace->setCursor(QCursor(QPixmap(":/CursorIcon/Brush.png").scaled(setbrush->width_M*lymanager->k*2,setbrush->width_M*lymanager->k*2)));
    wkspace->ttype=Seal;
}
