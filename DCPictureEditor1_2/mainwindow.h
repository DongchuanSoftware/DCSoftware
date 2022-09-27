#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"Layer/layermanager.h"
#include<QDockWidget>
#include"workspace.h"
#include<QStatusBar>
#include"Color/colormanager.h"
#include"Layer/backgroundlayer.h"
#include"SetToolsWidgets/SetBrushWidget/setbrushwidget.h"
#include<QFileDialog>
#include<QImage>
#include"Color/svwidget.h"
#include<QDebug>
#include"ActionsWidgets/ActionNewWidget/actionnewwidget.h"
#include<QHBoxLayout>
#include"SetToolsWidgets/SetTextEditorWidget/fontsetting.h"
#include"SetToolsWidgets/SetTextEditorWidget/textlayereditor.h"
#include"SetToolsWidgets/SetSealWidget/setsealwidget.h"
#include"Layer/layerattrmanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
    ColorManager* clmanager;
    QDockWidget* DWColor;
    
    LayerManager* lymanager;
    QDockWidget* DWLayer;
    
    LayerAttrManager* lyatmanager;
    QDockWidget* DWLyat;
    
    QDockWidget* DWChannels;
    
    QDockWidget* DWPath;
    
    
    WorkSpace* wkspace;
    
    SetBrushWidget* setbrush;
    QDockWidget* DWSetBrush;
    SetSealWidget* setseal;
    QDockWidget* DWSetSeal;
    
    void ChangeToolIcon(ToolType tt);
    
    
private slots:
    void on_ActionExit_triggered();
    
    void on_ActionShrink_triggered();
    
    void on_ActionExpand_triggered();
    
    void on_ActionToolMoveAll_triggered();
    
    void on_ActionToolMoveLayer_triggered();
    
    void on_ActionToolBrush_triggered();
    
    void on_ActionToolEraser_triggered();
    
    void on_ActionNew_triggered();
    
    void on_ActionExport_triggered();
    
    void on_ActionToolTextEditor_triggered();
    
    void on_ActionToolSeal_triggered();
    
    void on_ActionFitOnScreen_triggered();
    
    void on_Action100Per_triggered();
    
    void on_ActionMoveTo0_triggered();
    
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
