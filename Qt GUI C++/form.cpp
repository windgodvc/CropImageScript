#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    setWindowFlags(  Qt::WindowStaysOnTopHint);
    //  主窗口关闭时 副窗口一起关闭
    setAttribute(Qt::WA_QuitOnClose,false);
    setWindowFlags(  Qt::WindowStaysOnTopHint);
}

Form::~Form()
{
    delete ui;
}

QLabel *Form::getLabel()
{
    return ui->label;
}

void Form::on_Form_destroyed(QObject *arg1)
{
    this->hide();
    return ;
}
