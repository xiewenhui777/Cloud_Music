#include "information.h"
#include "ui_information.h"

information::information(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::information)
{
    ui->setupUi(this);
    ui->userID->setFocusPolicy(Qt::NoFocus);    //代表文本框失去焦点 不可编辑了
    ui->phone->setFocusPolicy(Qt::NoFocus);
    ui->pass->setFocusPolicy(Qt::NoFocus);
    ui->pass_confirm->setFocusPolicy(Qt::NoFocus);
    ui->gender->setFocusPolicy(Qt::NoFocus);
    ui->name->setFocusPolicy(Qt::NoFocus);
    ui->email->setFocusPolicy(Qt::NoFocus);

    connect(ui->edit,SIGNAL(clicked()), this,SLOT(edit_clicked()));
    connect(ui->save,SIGNAL(clicked()), this,SLOT(save_clicked()));
}

information::~information()
{
    delete ui;
}


void information::edit_clicked(){
    ui->userID->setFocus();    //代表文本框重新获得焦点
    ui->phone->setFocus();
    ui->pass->setFocus();
    ui->pass_confirm->setFocus();
    ui->gender->setFocus();
    ui->name->setFocus();
    ui->email->setFocus();

   // ui->gender->setFocusPolicy(Policy);

//    close();
//    exec();     //进程结束
}
void information::save_clicked(){
    close();
    exec();     //进程结束
}
