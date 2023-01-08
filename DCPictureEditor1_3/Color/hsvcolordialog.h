#ifndef HSVCOLORDIALOG_H
#define HSVCOLORDIALOG_H

#include <QObject>
#include<QDialog>
#include"colormanager.h"
#include<QDialogButtonBox>
#include<QVBoxLayout>

class HSVColorDialog : public QObject
{
    Q_OBJECT
public:
    explicit HSVColorDialog(QObject *parent = nullptr);
    
    QColor getColor(QColor color_M);
    
signals:
    
public slots:
};

#endif // HSVCOLORDIALOG_H
