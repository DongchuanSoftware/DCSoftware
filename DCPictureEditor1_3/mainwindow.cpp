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
    
    //准备工作区
    wkspace=new WorkSpace(this,
                          lymanager,
                          lyatmanager,
                          clmanager,
                          setbrush);
    
    //工具锁定
    connect(wkspace,&WorkSpace::lockTools,this,[=](bool isUnlock){
        QList<QAction*> listMenus=ui->menuTools->actions();
        listMenus+=ui->menuEdit->actions();
        listMenus+=ui->menuFile->actions();
        listMenus+=ui->menuView->actions();
        listMenus+=ui->menuHide->actions();
        for(QList<QAction*>::iterator i=listMenus.begin();i!=listMenus.end();i++)
        {
            (*i)->setEnabled(isUnlock);
        }
    });
    
    //工具鼠标图标切换
    connect(setbrush,&SetBrushWidget::widthChanged,this,&MainWindow::upDateCursorIcon);
    
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

void MainWindow::upDateCursorIcon()
{
    switch(wkspace->ttype)
    {
    case Brush:
    case Eraser:
    case Seal:
    {
        if(((setbrush->width_M*lymanager->k)<=1000)&&((setbrush->width_M*lymanager->k)>=8))
        {
            QPixmap pix(setbrush->width_M*lymanager->k,setbrush->width_M*lymanager->k);
            pix.fill(Qt::transparent);
            QPoint o(setbrush->width_M*lymanager->k/2,setbrush->width_M*lymanager->k/2);
            QPainter qpt;
            qpt.begin(&pix);
            qpt.setPen(Qt::black);
            qpt.drawEllipse(o,pix.width()/2,pix.height()/2);
            qpt.setPen(Qt::white);
            qpt.drawEllipse(o,pix.width()/2-1,pix.height()/2-1);
            qpt.end();
            wkspace->setCursor(QCursor(pix));
        }
        else
        {
            wkspace->setCursor(Qt::ArrowCursor);
        }
    }break;
    default:break;
    }
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
    
    if(anw.img!=nullptr)
    {
        if(this->lymanager->v_layers.empty())
        {
            lymanager->k=wkspace->width()/(double)anw.img->width();
            BackgroundLayer* bgl=new BackgroundLayer;
            bgl->object=*anw.img;
            lymanager->v_layers.push_back(bgl);
            
            lymanager->width=bgl->width=bgl->object.width();
            lymanager->height=bgl->height=bgl->object.height();
            
            lymanager->upDateUI();
        }
        else
        {
            MainWindow* mainwindow=new MainWindow;
            mainwindow->show();
            
            mainwindow->lymanager->k=mainwindow->wkspace->width()/(double)anw.img->width();
            BackgroundLayer* bgl=new BackgroundLayer;
            bgl->object=*anw.img;
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
    QImage img(lymanager->width,lymanager->height,QImage::Format_ARGB32);
    img.fill(Qt::transparent);
    for(int i=0;i<(int)lymanager->v_layers.size();i++)
    {
        if(lymanager->v_layers[i]->vis)
        {
            lymanager->v_layers[i]->Draw(&img);
        }
        
    }
    img.save(filename);
}

//打印
void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;
    QPrintPreviewDialog ppd(&printer,this);
    ppd.setStyleSheet("color:rgb(0,0,0);");
    connect(&ppd,&QPrintPreviewDialog::paintRequested,this,[=](QPrinter* prt){
        if(lymanager==nullptr||lymanager->v_layers.empty())
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
        QPainter p;
        p.begin(prt);
        double k=p.viewport().width()/(double)pix.width();
        k=pix.height()*k<p.viewport().height()?k:(p.viewport().height()/(double)pix.height());
        p.drawPixmap(QRect((p.viewport().width()-pix.width()*k)/2,
                           (p.viewport().height()-pix.height()*k)/2,
                           pix.width()*k,pix.height()*k),pix);
        p.end();
    });
    ppd.exec();
}

//退出
void MainWindow::on_actionExit_triggered()
{
    this->close();
}

//--------------------------------------------编辑--------------------------------------------

//水平翻折
void MainWindow::on_actionHorizontalFold_triggered()
{
    if(lymanager->selectedItems().size()==0)return;
    int pos=lymanager->v_layers.size()-lymanager->row(lymanager->selectedItems().at(0))-1;
    if(lymanager->v_layers[pos]->type!=2)return;
    ((PictureLayer*)lymanager->v_layers[pos])->object.mirror(1,0);
    lymanager->upDateUI();
}

//垂直翻折
void MainWindow::on_actionVerticalFold_triggered()
{
    if(lymanager->selectedItems().size()==0)return;
    int pos=lymanager->v_layers.size()-lymanager->row(lymanager->selectedItems().at(0))-1;
    if(lymanager->v_layers[pos]->type!=2)return;
    ((PictureLayer*)lymanager->v_layers[pos])->object.mirror(0,1);
    lymanager->upDateUI();
}

//顺时针90°
void MainWindow::on_actionClockwiseRotation90Dgr_triggered()
{
    if(lymanager->selectedItems().size()==0)return;
    int pos=lymanager->v_layers.size()-lymanager->row(lymanager->selectedItems().at(0))-1;
    if(lymanager->v_layers[pos]->type!=2)return;
    QTransform mat;
    mat.rotate(90);
    ((PictureLayer*)lymanager->v_layers[pos])->object=((PictureLayer*)lymanager->v_layers[pos])->object.transformed(mat);
    lymanager->v_layers[pos]->width=((PictureLayer*)lymanager->v_layers[pos])->object.width();
    lymanager->v_layers[pos]->height=((PictureLayer*)lymanager->v_layers[pos])->object.height();
    lymanager->upDateUI();
}

//逆时针90°
void MainWindow::on_actionCounterClockwiseRotation90Dgr_triggered()
{
    if(lymanager->selectedItems().size()==0)return;
    int pos=lymanager->v_layers.size()-lymanager->row(lymanager->selectedItems().at(0))-1;
    if(lymanager->v_layers[pos]->type!=2)return;
    QTransform mat;
    mat.rotate(270);
    ((PictureLayer*)lymanager->v_layers[pos])->object=((PictureLayer*)lymanager->v_layers[pos])->object.transformed(mat);
    lymanager->v_layers[pos]->width=((PictureLayer*)lymanager->v_layers[pos])->object.width();
    lymanager->v_layers[pos]->height=((PictureLayer*)lymanager->v_layers[pos])->object.height();
    lymanager->upDateUI();
}

//180°
void MainWindow::on_actionClockwiseRotation180Dgr_triggered()
{
    if(lymanager->selectedItems().size()==0)return;
    int pos=lymanager->v_layers.size()-lymanager->row(lymanager->selectedItems().at(0))-1;
    if(lymanager->v_layers[pos]->type!=2)return;
    QTransform mat;
    mat.rotate(180);
    ((PictureLayer*)lymanager->v_layers[pos])->object=((PictureLayer*)lymanager->v_layers[pos])->object.transformed(mat);
    lymanager->v_layers[pos]->width=((PictureLayer*)lymanager->v_layers[pos])->object.width();
    lymanager->v_layers[pos]->height=((PictureLayer*)lymanager->v_layers[pos])->object.height();
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
        upDateCursorIcon();
    }
}

//放大
void MainWindow::on_actionExpand_triggered()
{
    if(lymanager->k*1.1<=20)
    {
        lymanager->k*=1.1;
        wkspace->update();
        upDateCursorIcon();
    }
}

//适应屏幕
void MainWindow::on_actionFitOnScreen_triggered()
{
    lymanager->k=wkspace->width()/(double)lymanager->v_layers[0]->width;
    wkspace->update();
    upDateCursorIcon();
}

//100%
void MainWindow::on_action100Per_triggered()
{
    lymanager->k=1;
    wkspace->update();
    upDateCursorIcon();
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
        wkspace->ttype=Brush;
        upDateCursorIcon();
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
        wkspace->ttype=Eraser;
        upDateCursorIcon();
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
        wkspace->ttype=Seal;
        upDateCursorIcon();
    }
}

//--------------------------------------------隐藏菜单--------------------------------------------
void MainWindow::on_actionToolShrink_triggered()
{
    switch(wkspace->ttype)
    {
    case Brush:
    case Eraser:
    case DrawLine:
    case DrawCircle:
    case Seal:
    {
        if(setbrush->width_M-1>=1)
        {
            emit setbrush->setWidth(setbrush->width_M-1);
        }
    }break;
    default:break;
    }
    upDateCursorIcon();
}

void MainWindow::on_actionToolExpand_triggered()
{
    switch(wkspace->ttype)
    {
    case Brush:
    case Eraser:
    case DrawLine:
    case DrawCircle:
    case Seal:
    {
        if(setbrush->width_M+1<=100)
        {
            emit setbrush->setWidth(setbrush->width_M+1);
        }
    }break;
    default:break;
    }
    upDateCursorIcon();
}
