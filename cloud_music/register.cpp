#include "register.h"
#include "ui_register.h"
#include <QDialog>
#include <QtWidgets/QMessageBox>

Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{

    ui->setupUi(this);
    setWindowTitle(QStringLiteral("注册"));
    ui->pass->setEchoMode(QLineEdit::Password); //设置密码编辑框为隐藏模式
    ui->pass_->setEchoMode(QLineEdit::Password); //设置密码编辑框为隐藏模式
    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);    // 禁止最大化按钮
//    setFixedSize(441,507);                     // 禁止拖动窗口大小
    icon = "00";
    icoDia = new QDialog(this);
    layout_fri = new QVBoxLayout(icoDia);
    layout_fri->setMargin(20);
    layout_fri->setAlignment(Qt::AlignBaseline);
    //添加头像
    for(int i=0;i<7;i++)
    {
        QString path = QString(":/image/image/headicon/0%1.jpg").arg(i);            //注意文件夹的路径名称（与diamante中的资源保持一致）
        QPushButton *bu_temp = new QPushButton(icoDia);
        bu_temp->setIcon(QPixmap(path));
        qDebug()<<"path is "<<path;
        icolist.append(bu_temp);
        layout_fri->addWidget(bu_temp);
        connect(bu_temp,&QPushButton::clicked,
                [=]() mutable
                {
                    this->icoDia->hide();
                    ui->headimage->setIcon(QPixmap(path));
                    //ui->messEdit->append("\n");
                    icon[0] = path[7];
                    icon[1] = path[8];
                }
                );

    }
}

Register::~Register()
{
    delete ui;
}

void Register::on_pushButton_clicked()
{
    if(ui->name->text()!=""&&ui->gender->text()!=""&&ui->email->text()!=""&&ui->pass->text()!=""&&ui->pass_->text()!=""&&ui->userID->text()!=""&&ui->phone->text()!=""&&ui->pass->text()==ui->pass_->text())
    {
        //信息完整且正确
        QString temp = QString("register %1 %2 %3 %4 %5 %6")
                .arg(ui->userID->text()).arg(ui->name->text()).arg(ui->gender->text())
                .arg(ui->phone->text()).arg(ui->email->text())
                .arg(ui->pass->text());
        qDebug()<<"icon "<<icon;
        qDebug()<<"发给服务器的是： "<<temp;

        tcpSocket->write(temp.toUtf8().data());
        QMessageBox::information(this, QStringLiteral("注册"), QStringLiteral("注册成功"));//显示注册成功信息的弹窗
    }else QMessageBox::information(this, QStringLiteral("注册"), QStringLiteral("注册失败"));

}
void Register::regiSucce(QString info)
{
    //
    int i;
    QString id;
    for(i=0;i<info.size();i++)
    {
        if(info[i]==' ')
        {
            i++;
            break;
        }
    }
    for(int j=0;i<info.size();i++,j++)
    {
        id[j] = info[i];
    }
    qDebug()<<"服务器发来的id是 "<<id;
    QString temp = QString("系统给您分配的id是\n[%1]\n<请牢记您的id>").arg(id);
    QMessageBox::warning(this,QStringLiteral("id分配"),temp);
    this->hide();
}
void Register::on_headimage_clicked()
{
    icoDia->show();
}
