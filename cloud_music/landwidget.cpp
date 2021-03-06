#include "landwidget.h"
#include "ui_landwidget.h"
#include <QMessageBox>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>
#include <QFile>

LandWidget::LandWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LandWidget)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags()&~Qt::WindowMaximizeButtonHint);    // 禁止最大化按钮
//    setFixedSize(445,508);                     // 禁止拖动窗口大小
    setWindowTitle(QStringLiteral("登录"));    //设置窗口标题

    ui->password->setEchoMode(QLineEdit::Password); //设置密码编辑框为隐藏模式
    //判断是否已记住账号密码，如果是填充输入框
    QFile file(":/data.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray temp = file.readAll();

    if(temp!=""){
        QString data = temp;
        int index_i = data.indexOf('_');
        int index_p = data.indexOf(';');
        QString id_re = data.mid(0,index_i);
        QString p_re = data.mid(index_i+1,index_p-index_i-1);
        qDebug()<<id_re<<" "<<p_re;
        ui->id->setText(id_re);
        ui->password->setText(p_re);

    }
    file.close();

    //注册按键
    connect(ui->forgetpassword,SIGNAL(clicked()), this,SLOT(findPasswod_clicked()));
}

void LandWidget::setTcpSocket(QTcpSocket *tcp)
{
    //设置通信套接字
    tcpSocket = tcp;
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(slotDataRecv()));   //将收到服务器消息信号与槽函数建立连接
}


LandWidget::~LandWidget()
{
    delete ui;
}

bool LandWidget::judgement(QByteArray array)
{
    //判断服务器返回的消息是否是信息匹配，如果是返回true否则返回false
    //服务器返回消息格式
    /*
     * {
    "PacketType": "land_success"
    }
     */
    //解包
    /*
     * 测试用例
     * */
    QString temp = array;
    QString type = NULL;
    QString user = NULL;
    int i=0;
    for(i=0;i<temp.size();i++)
    {
        if(temp[i] == ' ')
        {
            i++;
            break;
        }
        type[i] = temp[i];
    }

    if(type == "success")
    {
        for(int j=0;i<temp.size();i++,j++)
        {
            if(temp[i]==' ')
            {
                break;
            }
            user[j] = temp[i];
        }
        user_active = user.toInt();
        return true;
    }else if(type == "register_su"){

        regi->regiSucce(temp);
    }
    else{
        QMessageBox::warning(this,QStringLiteral("错误"),QStringLiteral("账号或密码错误"));
    }
    return false;
}

void LandWidget::slotDataRecv()
{
    //收到服务器消息时
    if(judgement(tcpSocket->readAll()))//读取服务器消息并判断
    {
        //服务器返回登陆信息正确
        emit landSuccess(); //给主窗口发送登陆成功信号
    }
    else{

    }

}
void LandWidget::on_login_clicked()
{
    //点击登陆按钮时    此处注释的等连接数据库后再进行处理
//    if(ui->id->text()=="")
//    {
//        //当id未填写时
//        QMessageBox::warning(this,QStringLiteral("错误"),QStringLiteral("请填写id"));
//    }else {
//        if(ui->password->text()=="")
//        {
//            //当密码未填写时
//            QMessageBox::warning(this,QStringLiteral("错误"),QStringLiteral("请填写密码"));
//        }else {
//            //账号密码都填写时
//            if(ui->remember->isChecked())
//            {
//                //当记住密码被选中时

//                QString data = QString("%1_%2;").arg(ui->id->text()).arg(ui->password->text());
//               // QByteArray temp = data.t;
//                QFile file("D:\code\WangWangChat\clientCode\202003\demo3\data.txt");
//                file.open(QIODevice::ReadWrite|QIODevice::Text);
//                QByteArray temp = file.readAll();
//                qDebug()<<"line 138"<<temp;
//                file.write(data.toStdString().c_str());
//                file.close();
//            }else{


//            }
//            tcpSocket->write(landPack(ui->id->text().toInt(),ui->password->text()).toUtf8().data());//将登陆信息打包发给服务器
//        }
//    }
    extern int quit_login;
    quit_login=0;           //退出状态重置
    this->hide();           //登录界面隐藏起来
    mainwidget = new MainWidget;
//    mainwidget->show();     //进程并未终止   因此无法跳回到登录界面
//    mainwidget->setAttribute(Qt::WA_ShowModal, true);
    mainwidget->show();

    if(mainwidget->doExec() == MainWidget::Rejected){           //代表主界面的退出  因此result的状态会设置为rejected
        this->show();
        qDebug()<<"quit1"<<endl;

    }

//    mainwidget->closeEvent();
//    if(quit_login==1){   //尝试使用while循环？？
//        qDebug()<<"quit1"<<endl;
//        this->show();       //代表用户退出当前登录 回到了登录界面
//    }

}
QString LandWidget::landPack(int id, QString password)
{
    QString temp = QString("%1 %2 %3 ").arg("login").arg(id).arg(password);
    return temp;
}

void LandWidget::on_registeButton_clicked()
{
    //点击注册按钮
    regi = new Register;
    regi->show();
    regi->setSocket(this->tcpSocket);
}

void LandWidget::findPasswod_clicked()        //找回密码的按钮
{
    forget1.show();
    forget1.exec();
}

