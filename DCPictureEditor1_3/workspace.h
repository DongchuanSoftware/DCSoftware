#ifndef WORKSPACE_H
#define WORKSPACE_H

#include<Layer/layermanager.h>
#include<QPaintDevice>
#include<QDragEnterEvent>
#include<QDragMoveEvent>
#include<QDropEvent>
#include<QMimeData>
#include<QMouseEvent>
#include"Color/colormanager.h"
#include"SetToolsWidgets/SetBrushWidget/setbrushwidget.h"
#include"SetToolsWidgets/SetTextEditorWidget/fontsetting.h"
#include<QTextEdit>
#include"SetToolsWidgets/SetTextEditorWidget/textlayereditor.h"
#include"SetToolsWidgets/SetSealWidget/setsealwidget.h"
#include"Layer/layerattrmanager.h"
#include<cmath>
#include<QtOpenGLWidgets/QtOpenGLWidgets>
#include<QtOpenGL/QOpenGLFunctions_4_5_Core>
#include<QtOpenGL>
#include"myalgorithm.h"

enum ToolType{
    MoveAll,
    MoveLayer,
    Brush,
    DrawLine,
    DrawCircle,
    Eraser,
    TextEditor,
    Seal
};

class WorkSpace : public QOpenGLWidget,public QOpenGLFunctions_4_5_Core
{
    Q_OBJECT
public:
    explicit WorkSpace(QWidget *parent,LayerManager* _lymanager,LayerAttrManager* _lyatmanager,ColorManager* _clmanager,SetBrushWidget* _setbrush,SetSealWidget* _setseal);
    LayerManager* lymanager=nullptr;
    LayerAttrManager* lyatmanager=nullptr;
    ColorManager* clmanager=nullptr;
    
    void initializeGL();
    void paintGL();
    void resizeGL(int, int);
    
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent* event);
    void dropEvent(QDropEvent *de);
    
    ToolType ttype=MoveAll;
    void mousePressEvent(QMouseEvent* qme);
    void mouseMoveEvent(QMouseEvent* qme);
    void mouseReleaseEvent(QMouseEvent* qme);
    
    SetBrushWidget* setbrush;
    SetSealWidget* setseal;
private:
    bool inited;
    QPoint startPos;
    int layerIndex;
    int layerType;
    QPainter painter;
    QPen pen1;
    QPen pen2;
    QPixmap pix;
    QPoint oPos;
    
signals:
    
    void lockTools(bool isUnlock);
    
public slots:
};

#endif // WORKSPACE_H
