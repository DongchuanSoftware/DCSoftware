#include "hsvcolordialog.h"

HSVColorDialog::HSVColorDialog(QObject *parent) : QObject(parent)
{
    
}

QColor HSVColorDialog::getColor(QColor color_M)
{
    QDialog dialog((QWidget*)parent());
    ColorManager clm(&dialog);
    
    clm.r_M=color_M.red();
    clm.g_M=color_M.green();
    clm.b_M=color_M.blue();
    RGB_HSV(clm.r_M,clm.g_M,clm.b_M,clm.h_M,clm.s_M,clm.v_M);
    clm.update();
    
    QDialogButtonBox button(&dialog);
    button.addButton("确定",QDialogButtonBox::YesRole);
    button.addButton("取消",QDialogButtonBox::NoRole);
    connect(&button,&QDialogButtonBox::accepted,&dialog,&QDialog::accept);
    connect(&button,&QDialogButtonBox::rejected,&dialog,&QDialog::reject);
    
    QVBoxLayout vbl;
    vbl.addWidget(&clm);
    vbl.addWidget(&button);
    
    dialog.setMinimumSize(clm.size());
    dialog.setLayout(&vbl);
    if(dialog.exec()==QDialog::Accepted)
    {
        
        color_M=QColor(clm.r_M,clm.g_M,clm.b_M);
    }
    return color_M;
}