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
    explicit WorkSpace(QWidget *parent,
                       LayerManager* _lymanager,
                       LayerAttrManager* _lyatmanager,
                       ColorManager* _clmanager,
                       SetBrushWidget* _setbrush);
    
    LayerManager* lymanager=nullptr;
    LayerAttrManager* lyatmanager=nullptr;
    ColorManager* clmanager=nullptr;
    
    ToolType ttype=MoveAll;
    SetBrushWidget* setbrush;

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int, int);
    
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent* event);
    void dropEvent(QDropEvent *de);
    
    void wheelEvent(QWheelEvent* qwe);
    
    void mousePressEvent(QMouseEvent* qme);
    void mouseMoveEvent(QMouseEvent* qme);
    void mouseReleaseEvent(QMouseEvent* qme);
private:
    bool inited;
    QPoint startPos;
    QPoint oPos;
    int layerIndex;
    LayerType layerType;
    MyPainter painter;
    QPen pen1;
    QPen pen2;
    QImage img;
    QImage* texture;
    
signals:
    
    void lockTools(bool isUnlock);
    
public slots:
};

#endif // WORKSPACE_H
