#include "workspace.h"
#include<QDebug>

WorkSpace::WorkSpace(QWidget *parent) : QOpenGLWidget(parent)
{
    this->setAcceptDrops(1);
    setCursor(Qt::OpenHandCursor);
}

void WorkSpace::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(QColor(53,53,53));
    QBrush b(QColor(53,53,53));
    painter.setBrush(b);
    painter.drawRect(QRect(QPoint(0,0),this->size()));
    if(lymanager==nullptr)
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
    painter.drawPixmap(lymanager->x,lymanager->y,
                       lymanager->width*lymanager->k,lymanager->height*lymanager->k,
                       pix);
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
    QPixmap* img=new QPixmap;
    img->fill(Qt::transparent);
    QString filename=qm->urls()[0].toLocalFile();
    bool f=img->load(filename);
    if(f)
    {
        if(this->lymanager->v_layers.empty())
        {
            lymanager->k=this->width()/(double)img->width();
            BackgroundLayer* bgl=new BackgroundLayer;
            bgl->object=*img;
            lymanager->v_layers.push_back(bgl);
            
            lymanager->width=bgl->width=bgl->object.width();
            lymanager->height=bgl->height=bgl->object.height();
        }
        else
        {
            PictureLayer* ptl=new PictureLayer;
            ptl->object=*img;
            lymanager->v_layers.push_back(ptl);
            
            ptl->width=ptl->object.width();
            ptl->height=ptl->object.height();
        }
    }
    
    lymanager->UpDateUI();
}

void WorkSpace::mousePressEvent(QMouseEvent *qme)
{
    if(lymanager->v_layers.empty())
    {
        return;
    }
    emit LockTools(0);
    switch (ttype) {
    case MoveAll:{
        StartX=qme->x();
        StartY=qme->y();
        setCursor(Qt::ClosedHandCursor);
    }break;
    case MoveLayer:{
        if(lymanager->selectedItems().size()==0)break;
        StartX=qme->x();
        StartY=qme->y();
        LPos=lymanager->v_layers.size()-lymanager->row(lymanager->selectedItems().at(0))-1;
        //setCursor(Qt::ClosedHandCursor);
    }break;
    case Brush:{
        Painter=nullptr;
        if(lymanager->selectedItems().size()==0)break;
        LPos=lymanager->v_layers.size()-lymanager->row(lymanager->selectedItems().at(0))-1;
        if(lymanager->v_layers[LPos]->type!=2)break;
        Painter=new QPainter(&((PictureLayer*)lymanager->v_layers[LPos])->object);
        Color1=QColor(clmanager->r_M,clmanager->g_M,clmanager->b_M,setbrush->transparency_M/3);
        Color2=QColor(clmanager->r_M,clmanager->g_M,clmanager->b_M,setbrush->transparency_M);
        Count=0;
        
        Painter->setPen(Color1);
        QBrush br;
        br.setColor(Color1);
        br.setStyle(Qt::SolidPattern);
        Painter->setBrush(br);
        Painter->drawEllipse(QPoint((qme->x()-lymanager->x)/lymanager->k-lymanager->v_layers[LPos]->x,
                                       (qme->y()-lymanager->y)/lymanager->k-lymanager->v_layers[LPos]->y),
                                setbrush->width_M,setbrush->width_M);
        
        Painter->setPen(Color2);
        br.setColor(Color2);
        br.setStyle(Qt::SolidPattern);
        Painter->setBrush(br);
        Painter->drawEllipse(QPoint((qme->x()-lymanager->x)/lymanager->k-lymanager->v_layers[LPos]->x,
                                       (qme->y()-lymanager->y)/lymanager->k-lymanager->v_layers[LPos]->y),
                                setbrush->width_M*setbrush->hardness_M/100,
                                setbrush->width_M*setbrush->hardness_M/100);
        StartX=qme->x();
        StartY=qme->y();
    }break;
    case Eraser:{
        Painter=nullptr;
        if(lymanager->selectedItems().size()==0)break;
        LPos=lymanager->v_layers.size()-lymanager->row(lymanager->selectedItems().at(0))-1;
        if(lymanager->v_layers[LPos]->type!=2)break;
        Painter=new QPainter(&((PictureLayer*)lymanager->v_layers[LPos])->object);
        Count=0;
        Painter->setCompositionMode(QPainter::CompositionMode_Source);
        Painter->setPen(Qt::transparent);
        Painter->setBrush(QBrush(Qt::transparent));
        Painter->drawEllipse(QPoint((qme->x()-lymanager->x)/lymanager->k-lymanager->v_layers[LPos]->x,
                                       (qme->y()-lymanager->y)/lymanager->k-lymanager->v_layers[LPos]->y),
                                setbrush->width_M,setbrush->width_M);
        StartX=qme->x();
        StartY=qme->y();
    }break;
    case TextEditor:{
        
    }break;
    case Seal:{
        if(!setseal->mode_M)
        {
            Painter=nullptr;
            if(lymanager->selectedItems().size()==0)break;
            LPos=lymanager->v_layers.size()-lymanager->row(lymanager->selectedItems().at(0))-1;
            if(lymanager->v_layers[LPos]->type!=2)break;
            
            DrawSolidCircle(qme->pos(),1,((PictureLayer*)lymanager->v_layers[LPos])->object,((BackgroundLayer*)lymanager->v_layers[0])->object);
        }
    }break;
    }
    lymanager->UpDateUI();
}

void WorkSpace::mouseMoveEvent(QMouseEvent *qme)
{
    if(lymanager->v_layers.empty())
    {
        return;
    }
    switch (ttype) {
    case MoveAll:{
        lymanager->x+=qme->x()-StartX;
        lymanager->y+=qme->y()-StartY;
        StartX=qme->x();
        StartY=qme->y();
    }break;
    case MoveLayer:{
        if(LPos==0)
        {
            return;
        }
        if(lymanager->selectedItems().size()==0)break;
        lymanager->v_layers[LPos]->x+=
                (qme->x()-StartX)/lymanager->k;
        lymanager->v_layers[LPos]->y+=
                (qme->y()-StartY)/lymanager->k;
        StartX=qme->x();
        StartY=qme->y();
    }break;
    case Brush:{
        if(lymanager->selectedItems().size()==0)
        {
            return;
        }
        if(lymanager->v_layers[LPos]->type!=2)break;
        if(setbrush->spacing_M==0||Count%setbrush->spacing_M==0)
        {
            Painter->setPen(Color1);
            QBrush br;
            br.setColor(Color1);
            br.setStyle(Qt::SolidPattern);
            Painter->setBrush(br);
            Painter->drawEllipse(QPoint((qme->x()-lymanager->x)/lymanager->k-lymanager->v_layers[LPos]->x,
                                           (qme->y()-lymanager->y)/lymanager->k-lymanager->v_layers[LPos]->y),
                                    setbrush->width_M,setbrush->width_M);
            
            Painter->setPen(Color2);
            br.setColor(Color2);
            br.setStyle(Qt::SolidPattern);
            Painter->setBrush(br);
            Painter->drawEllipse(QPoint((qme->x()-lymanager->x)/lymanager->k-lymanager->v_layers[LPos]->x,
                                           (qme->y()-lymanager->y)/lymanager->k-lymanager->v_layers[LPos]->y),
                                    setbrush->width_M*setbrush->hardness_M/100,
                                    setbrush->width_M*setbrush->hardness_M/100);
            if(setbrush->spacing_M==0)
            {
                for(double i=0.1;i<=setbrush->fluency_M;i+=0.2)
                {
                    Painter->drawEllipse(QPoint((((qme->x()-lymanager->x)/lymanager->k-lymanager->v_layers[LPos]->x)+i*((StartX-lymanager->x)/lymanager->k-lymanager->v_layers[LPos]->x))/(1+i),
                                                   (((qme->y()-lymanager->y)/lymanager->k-lymanager->v_layers[LPos]->y)+i*((StartY-lymanager->y)/lymanager->k-lymanager->v_layers[LPos]->y))/(1+i)),
                                            setbrush->width_M*setbrush->hardness_M/100,
                                            setbrush->width_M*setbrush->hardness_M/100);
                }
            }
        }
        Count++;
        StartX=qme->x();
        StartY=qme->y();
    }break;
    case Eraser:{
        if(lymanager->selectedItems().size()==0)
        {
            return;
        }
        if(lymanager->v_layers[LPos]->type!=2)break;
        if(setbrush->spacing_M==0||Count%setbrush->spacing_M==0)
        {
            Painter->drawEllipse(QPoint((qme->x()-lymanager->x)/lymanager->k-lymanager->v_layers[LPos]->x,
                                           (qme->y()-lymanager->y)/lymanager->k-lymanager->v_layers[LPos]->y),
                                    setbrush->width_M,setbrush->width_M);
            if(setbrush->spacing_M==0)
            {
                for(double i=0.1;i<=setbrush->fluency_M;i+=0.2)
                {
                    Painter->drawEllipse(QPoint((((qme->x()-lymanager->x)/lymanager->k-lymanager->v_layers[LPos]->x)+i*((StartX-lymanager->x)/lymanager->k-lymanager->v_layers[LPos]->x))/(1+i),
                                                   (((qme->y()-lymanager->y)/lymanager->k-lymanager->v_layers[LPos]->y)+i*((StartY-lymanager->y)/lymanager->k-lymanager->v_layers[LPos]->y))/(1+i)),
                                            setbrush->width_M*setbrush->hardness_M/100,
                                            setbrush->width_M*setbrush->hardness_M/100);
                }
            }
        }
        Count++;
        StartX=qme->x();
        StartY=qme->y();
    }break;
    case TextEditor:{
        
    }break;
    case Seal:{

        
    }break;
    }
    this->update();
}

void WorkSpace::mouseReleaseEvent(QMouseEvent *qme)
{
    if(lymanager->v_layers.empty())
    {
        return;
    }
    switch (ttype) {
    case MoveAll:{
        setCursor(Qt::OpenHandCursor);
    }break;
    case MoveLayer:{
        
    }break;
    case Brush:{
        if(Painter!=nullptr)
        {
            delete Painter;
        }
    }break;
    case Eraser:{
        if(Painter!=nullptr)
        {
            delete Painter;
        }
    }break;
    case TextEditor:{
        if(lymanager->selectedItems().size()==0)
        {
            return;
        }
        LPos=lymanager->v_layers.size()-lymanager->row(lymanager->selectedItems().at(0))-1;
        if(lymanager->v_layers[LPos]->type!=3)
        {
            QDialog d(this);
            d.setWindowFlags(Qt::Dialog|Qt::WindowMinMaxButtonsHint|Qt::WindowCloseButtonHint);
            d.setWindowState(Qt::WindowMaximized);
            TextLayerEditor fs(-1,lymanager,&d);
            fs.MainEdit()->move(qme->x(),qme->y());
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
                tl->object.setHtml(fs.MainEdit()->document()->toHtml());
                tl->x=fs.MainEdit()->x();
                tl->y=fs.MainEdit()->y();
                tl->width=fs.MainEdit()->document()->size().width();
                tl->height=fs.MainEdit()->document()->size().height();
                lymanager->v_layers.push_back(tl);
            }
        }
        else
        {
            QDialog d(this);
            d.setWindowFlags(Qt::Dialog|Qt::WindowMinMaxButtonsHint|Qt::WindowCloseButtonHint);
            d.setWindowState(Qt::WindowMaximized);
            TextLayerEditor fs(LPos,lymanager,&d);
            fs.MainEdit()->move(lymanager->v_layers[LPos]->x,lymanager->v_layers[LPos]->y);
            fs.MainEdit()->setHtml(((TextLayer*)lymanager->v_layers[LPos])->object.toHtml());
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
                TextLayer* tl=(TextLayer*)lymanager->v_layers[LPos];
                tl->object.setHtml(fs.MainEdit()->document()->toHtml());
                tl->x=fs.MainEdit()->x();
                tl->y=fs.MainEdit()->y();
                tl->width=fs.MainEdit()->document()->size().width();
                tl->height=fs.MainEdit()->document()->size().height();
            }
        }
    }break;
    case Seal:{
        
    }break;
    }
    emit LockTools(1);
    lymanager->UpDateUI();
}