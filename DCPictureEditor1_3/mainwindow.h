#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"Layer/layermanager.h"
#include<QDockWidget>
#include"workspace.h"
#include<QStatusBar>
#include"Color/colormanager.h"
#include"SetToolsWidgets/SetBrushWidget/setbrushwidget.h"
#include<QFileDialog>
#include<QImage>
#include<QDebug>
#include"ActionsWidgets/ActionNewWidget/actionnewwidget.h"
#include<QHBoxLayout>
#include"SetToolsWidgets/SetTextEditorWidget/fontsetting.h"
#include"SetToolsWidgets/SetTextEditorWidget/textlayereditor.h"
#include"Layer/layerattrmanager.h"
#include<QTime>
#include<QActionGroup>
#include<QPrinter>
#include<QPrintPreviewDialog>
#include<QTransform>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QActionGroup* groupTools;
    
    ColorManager* clmanager;
    QDockWidget* dwColor;
    
    LayerManager* lymanager;
    QDockWidget* dwLayer;
    
    LayerAttrManager* lyatmanager;
    QDockWidget* dwLyat;
    
    QDockWidget* dwChannels;
    
    QDockWidget* dwPath;
    
    
    WorkSpace* wkspace;
    
    SetBrushWidget* setbrush;
    QDockWidget* dwSetBrush;

public slots:
    void upDateCursorIcon();
    
private slots:
    void on_actionExit_triggered();
    
    void on_actionShrink_triggered();
    
    void on_actionExpand_triggered();
    
    void on_actionNew_triggered();
    
    void on_actionExport_triggered();
    
    void on_actionFitOnScreen_triggered();
    
    void on_action100Per_triggered();
    
    void on_actionMoveTo0_triggered();
    
    void on_actionHorizontalFold_triggered();
    
    void on_actionVerticalFold_triggered();
    
    void on_actionToolBrush_toggled(bool checked);
    
    void on_actionToolEraser_toggled(bool checked);
    
    void on_actionToolTextEditor_toggled(bool checked);
    
    void on_actionToolSeal_toggled(bool checked);
    
    void on_actionToolMoveAll_toggled(bool checked);
    
    void on_actionToolMoveLayer_toggled(bool checked);
    
    void on_actionToolDrawLine_toggled(bool checked);
    
    void on_actionDrawCircle_toggled(bool checked);
    
    void on_actionPrint_triggered();
    
    void on_actionClockwiseRotation90Dgr_triggered();
    
    void on_actionCounterClockwiseRotation90Dgr_triggered();
    
    void on_actionClockwiseRotation180Dgr_triggered();
    
    void on_actionToolShrink_triggered();
    
    void on_actionToolExpand_triggered();
    
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
