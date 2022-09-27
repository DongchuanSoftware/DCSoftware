#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <QWidget>
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
#include"myalgorithm.h"
#include"SetToolsWidgets/SetSealWidget/setsealwidget.h"
#include<QOpenGLWidget>

enum ToolType{MoveAll,
              MoveLayer,
              Brush,
              Eraser,
              TextEditor,
              Seal
             };

class WorkSpace : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit WorkSpace(QWidget *parent = nullptr);
    LayerManager* lymanager=nullptr;
    ColorManager* clmanager=nullptr;
    
    void paintEvent(QPaintEvent*);
    
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent* event);
    void dropEvent(QDropEvent *de);
    
    ToolType ttype=MoveAll;
    void mousePressEvent(QMouseEvent* qme);
    void mouseMoveEvent(QMouseEvent* qme);
    void mouseReleaseEvent(QMouseEvent* qme);
    
    int StartX;
    int StartY;
    int LPos;
    QPainter* Painter;
    QColor Color1;
    QColor Color2;
    int Count;
    
    SetBrushWidget* setbrush;
    SetSealWidget* setseal;
signals:
    
    void LockTools(bool isUnlock);
    
public slots:
};

#endif // WORKSPACE_H
