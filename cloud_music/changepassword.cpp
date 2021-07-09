#include "changepassword.h"
#include "ui_changepassword.h"

changePassword::changePassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changePassword)
{
    ui->setupUi(this);
     connect(ui->cancel,SIGNAL(clicked()), this,SLOT(on_exit_clicked()));
     connect(ui->confirm,SIGNAL(clicked()), this,SLOT(confirm_clicked()));
}

changePassword::~changePassword()
{
    delete ui;
}

void changePassword::on_exit_clicked(){ //不做任何操作  直接出退出当前界面
    close();
    exec();     //进程结束
}

void changePassword::confirm_clicked(){     //确认修改密码
    //修改密码  同时需要修改储存信息的数据库
    close();    //修改完成后 退出当前界面
    exec();     //进程结束
}
