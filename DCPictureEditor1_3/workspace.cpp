#include "workspace.h"
#include<QDebug>

WorkSpace::WorkSpace(QWidget *parent,
                     LayerManager *_lymanager,
                     LayerAttrManager *_lyatmanager,
                     ColorManager *_clmanager,
                     SetBrushWidget *_setbrush) : QOpenGLWidget(parent)
{
    lymanager=_lymanager;
    lyatmanager=_lyatmanager;
    clmanager=_clmanager;
    setbrush=_setbrush;
    
    this->setMinimumSize(300,300);
    
    this->setAcceptDrops(1);
    setCursor(Qt::OpenHandCursor);
}

void WorkSpace::initializeGL()
{
    initializeOpenGLFunctions();
    glDisable(GL_DEPTH_TEST);
}

void WorkSpace::paintGL()
{
    glClearColor(0.20784313725490197f, 0.20784313725490197f, 0.20784313725490197f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    if(lymanager==nullptr)
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
    
    
    QPainter pt;
    if(!pt.begin(this))
    {
        QMessageBox::warning(this,"错误","WorkSpace::paintGL::painter异常");
    }
    pt.drawImage(QRect(lymanager->x,lymanager->y,
                        lymanager->width*lymanager->k,lymanager->height*lymanager->k),
                        img);
    pt.end();
}

void WorkSpace::resizeGL(int, int)
{
    
}

void WorkSpace::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}

void WorkSpace::dragMoveEvent(QDragMoveEvent* event)
{
    event->setDropAction(Qt::MoveAction);
    event->accept();
}

void WorkSpace::dropEvent(QDropEvent *de)
{
    const QMimeData* qm=de->mimeData();
    QImage img;
    QString filename=qm->urls().at(0).toLocalFile();
    bool f=img.load(filename);
    if(f)
    {
        if(this->lymanager->v_layers.empty())
        {
            lymanager->k=this->width()/(double)img.width();
            BackgroundLayer* bgl=new BackgroundLayer;
            bgl->object=img;
            lymanager->v_layers.push_back(bgl);
            
            lymanager->width=bgl->width=bgl->object.width();
            lymanager->height=bgl->height=bgl->object.height();
        }
        else
        {
            PictureLayer* ptl=new PictureLayer;
            ptl->object=img;
            lymanager->v_layers.push_back(ptl);
            
            ptl->width=ptl->object.width();
            ptl->height=ptl->object.height();
        }
    }
    
    lymanager->upDateUI();
}

void WorkSpace::wheelEvent(QWheelEvent *qwe)
{
    if(lymanager->v_layers.empty()||(lymanager->selectedItems().size()==0))
    {
        return;
    }
    lymanager->x+=qwe->angleDelta().x();
    lymanager->y+=qwe->angleDelta().y();
    this->update();
}

void WorkSpace::mousePressEvent(QMouseEvent *qme)
{
    if(lymanager->v_layers.empty()||(lymanager->selectedItems().size()==0))
    {
        inited=0;
        return;
    }
    inited=1;
    emit lockTools(0);
    
    layerIndex=lymanager->v_layers.size()-lymanager->row(lymanager->selectedItems().first())-1;
    layerType=lymanager->v_layers[layerIndex]->type;
    if(layerType==LT_PICTURE)
    {
        if(!painter.begin(&((PictureLayer*)(lymanager->v_layers[layerIndex]))->object))
        {
            QMessageBox::warning(this,"错误","WorkSpace::mousePressEvent::painter异常");
        }
        painter.setRenderHint(QPainter::Antialiasing);
    }
    
    switch (ttype) {
    case MoveAll:{
        startPos=qme->pos();
        setCursor(Qt::ClosedHandCursor);
    }break;
    case MoveLayer:{
        startPos=QPoint((qme->pos().x()-lymanager->x)/lymanager->k,
                        (qme->pos().y()-lymanager->y)/lymanager->k);
    }break;
    case Brush:{
        if(layerType!=LT_PICTURE)return;
        startPos=QPoint((qme->pos().x()-lymanager->x)/lymanager->k-lymanager->v_layers[layerIndex]->x,
                        (qme->pos().y()-lymanager->y)/lymanager->k-lymanager->v_layers[layerIndex]->y);
        pen1.setColor(QColor(clmanager->r_M,clmanager->g_M,clmanager->b_M,setbrush->transparency_M/3));
        pen1.setWidth(setbrush->width_M);
        pen2.setColor(QColor(clmanager->r_M,clmanager->g_M,clmanager->b_M,setbrush->transparency_M));
        pen2.setWidth(setbrush->width_M*setbrush->hardness_M/100);
        painter.setPen(pen1);
        painter.drawPoint(startPos);
        painter.setPen(pen2);
        painter.drawPoint(startPos);
    }break;
    case DrawLine:{
        if(layerType!=LT_PICTURE)return;
        setCursor(Qt::SizeAllCursor);
        startPos=QPoint((qme->pos().x()-lymanager->x)/lymanager->k-lymanager->v_layers[layerIndex]->x,
                        (qme->pos().y()-lymanager->y)/lymanager->k-lymanager->v_layers[layerIndex]->y);
        pen1.setColor(QColor(clmanager->r_M,clmanager->g_M,clmanager->b_M,setbrush->transparency_M));
        pen1.setWidth(setbrush->width_M);
        painter.setPen(pen1);
        painter.setCompositionMode(QPainter::CompositionMode_Source);
        img=((PictureLayer*)(lymanager->v_layers[layerIndex]))->object;
    }break;
    case DrawCircle:{
        if(layerType!=LT_PICTURE)return;
        startPos=QPoint((qme->pos().x()-lymanager->x)/lymanager->k-lymanager->v_layers[layerIndex]->x,
                        (qme->pos().y()-lymanager->y)/lymanager->k-lymanager->v_layers[layerIndex]->y);
        pen1.setColor(QColor(clmanager->r_M,clmanager->g_M,clmanager->b_M,setbrush->transparency_M));
        pen1.setWidth(setbrush->width_M);
        painter.setPen(pen1);
        painter.setCompositionMode(QPainter::CompositionMode_Source);
        if(setbrush->isCircle_M)
        {
            img=((PictureLayer*)(lymanager->v_layers[layerIndex]))->object;
        }
        else
        {
            if(qme->button()==Qt::RightButton)
            {
                oPos=startPos;
            }
            else
            {
                if(!setbrush->lockedR_M)
                {
                    emit setbrush->setRadius(std::sqrt(std::abs(oPos.x()-startPos.x())*std::abs(oPos.x()-startPos.x())
                                                       +std::abs(oPos.y()-startPos.y())*std::abs(oPos.y()-startPos.y())));
                }
            }
        }
    }break;
    case Eraser:{
        if(layerType!=LT_PICTURE)return;
        startPos=QPoint((qme->pos().x()-lymanager->x)/lymanager->k-lymanager->v_layers[layerIndex]->x,
                        (qme->pos().y()-lymanager->y)/lymanager->k-lymanager->v_layers[layerIndex]->y);
        pen1.setColor(QColor(0,0,0,0));
        pen1.setWidth(setbrush->width_M);
        painter.setPen(pen1);
        painter.setCompositionMode(QPainter::CompositionMode_Source);
        painter.drawPoint(startPos);
    }break;
    case TextEditor:{
        
    }break;
    case Seal:{
        if(qme->button()==Qt::RightButton)
        {
            switch(layerType) {
            case LT_PICTURE:{
                oPos=QPoint((qme->pos().x()-lymanager->x)/lymanager->k-lymanager->v_layers[layerIndex]->x,
                            (qme->pos().y()-lymanager->y)/lymanager->k-lymanager->v_layers[layerIndex]->y);
                texture=&((PictureLayer*)(lymanager->v_layers[layerIndex]))->object;
            }break;
            case LT_BACKGROUND:{
                oPos=QPoint((qme->pos().x()-lymanager->x)/lymanager->k-lymanager->v_layers[layerIndex]->x,
                            (qme->pos().y()-lymanager->y)/lymanager->k-lymanager->v_layers[layerIndex]->y);
                texture=&((BackgroundLayer*)(lymanager->v_layers[layerIndex]))->object;
            }break;
            default:break;
            }
        }
        else
        {
            if(layerType!=LT_PICTURE)return;
            startPos=QPoint((qme->pos().x()-lymanager->x)/lymanager->k-lymanager->v_layers[layerIndex]->x,
                            (qme->pos().y()-lymanager->y)/lymanager->k-lymanager->v_layers[layerIndex]->y);
            painter.setSealTool(&((PictureLayer*)(lymanager->v_layers[layerIndex]))->object,startPos,
                                texture,oPos);
            pen1.setWidth(setbrush->width_M);
            painter.setPen(pen1);
        }
    }break;
    }
    lymanager->upDateUI();
}

void WorkSpace::mouseMoveEvent(QMouseEvent *qme)
{
    if(lymanager->v_layers.empty()||!inited)
    {
        return;
    }
    switch (ttype) {
    case MoveAll:{
        lymanager->x+=qme->pos().x()-startPos.x();
        lymanager->y+=qme->pos().y()-startPos.y();
        startPos=qme->pos();
    }break;
    case MoveLayer:{
        if(lymanager->v_layers[layerIndex]->type==LT_BACKGROUND)
        {
            return;
        }
        QPoint p=QPoint((qme->pos().x()-lymanager->x)/lymanager->k,
                        (qme->pos().y()-lymanager->y)/lymanager->k);
        lymanager->v_layers[layerIndex]->x+=p.x()-startPos.x();
        lymanager->v_layers[layerIndex]->y+=p.y()-startPos.y();
        startPos=p;
    }break;
    case Brush:{
        if(layerType!=LT_PICTURE)return;
        QPoint p=QPoint((qme->pos().x()-lymanager->x)/lymanager->k-lymanager->v_layers[layerIndex]->x,
                        (qme->pos().y()-lymanager->y)/lymanager->k-lymanager->v_layers[layerIndex]->y);
        painter.setPen(pen1);
        painter.drawLine(startPos,p);
        painter.setPen(pen2);
        painter.drawLine(startPos,p);
        startPos=p;
    }break;
    case DrawLine:{
        if(layerType!=LT_PICTURE)return;
        QPoint p=QPoint((qme->pos().x()-lymanager->x)/lymanager->k-lymanager->v_layers[layerIndex]->x,
                        (qme->pos().y()-lymanager->y)/lymanager->k-lymanager->v_layers[layerIndex]->y);
        painter.drawImage(QRect(QPoint(0,0),img.size()),img);
        painter.drawLine(startPos,p);
    }break;
    case DrawCircle:{
        if(layerType!=LT_PICTURE)return;
        QPoint p=QPoint((qme->pos().x()-lymanager->x)/lymanager->k-lymanager->v_layers[layerIndex]->x,
                        (qme->pos().y()-lymanager->y)/lymanager->k-lymanager->v_layers[layerIndex]->y);
        if(setbrush->isCircle_M)
        {
            painter.drawImage(QRect(QPoint(0,0),img.size()),img);
            int r=(int)std::sqrt(std::abs(p.x()-startPos.x())*std::abs(p.x()-startPos.x())
                                 +std::abs(p.y()-startPos.y())*std::abs(p.y()-startPos.y()));            
            painter.drawEllipse(startPos,r,r);
            emit setbrush->setRadius(r);
        }
        else
        {
            painter.drawMyArc(oPos,setbrush->radius_M,startPos,p);
            startPos=p;
        }
        
    }break;
    case Eraser:{
        if(layerType!=LT_PICTURE)return;
        QPoint p=QPoint((qme->pos().x()-lymanager->x)/lymanager->k-lymanager->v_layers[layerIndex]->x,
                        (qme->pos().y()-lymanager->y)/lymanager->k-lymanager->v_layers[layerIndex]->y);
        painter.drawLine(startPos,p);
        startPos=p;
    }break;
    case TextEditor:{
        
    }break;
    case Seal:{
        if(layerType!=LT_PICTURE)return;
        QPoint p=QPoint((qme->pos().x()-lymanager->x)/lymanager->k-lymanager->v_layers[layerIndex]->x,
                        (qme->pos().y()-lymanager->y)/lymanager->k-lymanager->v_layers[layerIndex]->y);
        painter.drawMyLine(startPos,p);
        startPos=p;
    }break;
    }
    this->update();
}

void WorkSpace::mouseReleaseEvent(QMouseEvent *qme)
{
    if(lymanager->v_layers.empty()||!inited)
    {
        return;
    }
    
    if(painter.paintEngine())
    {
        painter.end();
    }
    
    switch (ttype) {
    case MoveAll:{
        setCursor(Qt::OpenHandCursor);
    }break;
    case MoveLayer:{}break;
    case Brush:{}break;
    case DrawLine:{
        setCursor(Qt::ArrowCursor);
    }break;
    case DrawCircle:{}break;
    case Eraser:{}break;
    case TextEditor:{
        if(lymanager->v_layers[layerIndex]->type!=LT_TEXT)
        {
            QDialog d(this);
            d.setWindowFlags(Qt::Dialog|Qt::WindowMinMaxButtonsHint|Qt::WindowCloseButtonHint);
            d.setWindowState(Qt::WindowMaximized);
            TextLayerEditor fs(-1,lymanager,&d);
            fs.mainEdit()->move(qme->pos().x(),qme->pos().y());
            QVBoxLayout vbl(this);
            
            QDialogButtonBox button(&d);
            button.addButton("确定",QDialogButtonBox::YesRole);
            button.addButton("取消",QDialogButtonBox::NoRole);
            connect(&button,&QDialogButtonBox::accepted,&d,&QDialog::accept);
            connect(&button,&QDialogButtonBox::rejected,&d,&QDialog::reject);
            
            vbl.addWidget(&fs);
            vbl.addWidget(&button);
            d.setLayout(&vbl);
            if(d.exec()==QDialog::Accepted)
            {
                TextLayer* tl=new TextLayer;
                tl->object.setHtml(fs.mainEdit()->document()->toHtml());
                tl->x=fs.mainEdit()->x();
                tl->y=fs.mainEdit()->y();
                tl->width=fs.mainEdit()->document()->size().width();
                tl->height=fs.mainEdit()->document()->size().height();
                lymanager->v_layers.push_back(tl);
            }
        }
        else
        {
            QDialog d(this);
            d.setWindowFlags(Qt::Dialog|Qt::WindowMinMaxButtonsHint|Qt::WindowCloseButtonHint);
            d.setWindowState(Qt::WindowMaximized);
            TextLayerEditor fs(layerIndex,lymanager,&d);
            fs.mainEdit()->move(lymanager->v_layers[layerIndex]->x,lymanager->v_layers[layerIndex]->y);
            fs.mainEdit()->setHtml(((TextLayer*)lymanager->v_layers[layerIndex])->object.toHtml());
            QVBoxLayout vbl(this);
            
            QDialogButtonBox button(&d);
            button.addButton("确定",QDialogButtonBox::YesRole);
            button.addButton("取消",QDialogButtonBox::NoRole);
            connect(&button,&QDialogButtonBox::accepted,&d,&QDialog::accept);
            connect(&button,&QDialogButtonBox::rejected,&d,&QDialog::reject);
            
            vbl.addWidget(&fs);
            vbl.addWidget(&button);
            d.setLayout(&vbl);
            if(d.exec()==QDialog::Accepted)
            {
                TextLayer* tl=(TextLayer*)lymanager->v_layers[layerIndex];
                tl->object.setHtml(fs.mainEdit()->document()->toHtml());
                tl->x=fs.mainEdit()->x();
                tl->y=fs.mainEdit()->y();
                tl->width=fs.mainEdit()->document()->size().width();
                tl->height=fs.mainEdit()->document()->size().height();
            }
        }
    }break;
    case Seal:{
    }break;
    }
    emit lockTools(1);
    lymanager->upDateUI();
    lyatmanager->upDateUI();
}