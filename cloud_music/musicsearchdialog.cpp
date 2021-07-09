#include "MusicSearchDialog.h"
#include "ui_MusicSearchDialog.h"
#include <QtWidgets/QMessageBox>
#include <QVBoxLayout>

MusicSearchDialog::MusicSearchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MusicSearchDialog)
{
    ui->setupUi(this);
    ui->SearchlineEdit->clear();
    //m_pSearchLineEdit = new QLineEdit();
    //QPushButton *pSearchButton = new QPushButton(this);
    ui->SearchButton->setCursor(Qt::PointingHandCursor);
    ui->SearchButton->setFixedSize(22, 22);
    ui->SearchButton->setToolTip(QStringLiteral("搜索"));
    ui->SearchButton->setStyleSheet("QPushButton{border-image:url(:/images/icon_search_normal); background:transparent;} \
                                         QPushButton:hover{border-image:url(:/images/icon_search_hover)} \
                                         QPushButton:pressed{border-image:url(:/images/icon_search_press)}");

    //防止文本框输入内容位于按钮之下
    QMargins margins = ui->SearchlineEdit->textMargins();
    ui->SearchlineEdit->setTextMargins(margins.left(), margins.top(), ui->SearchButton->width(), margins.bottom());
    ui->SearchlineEdit->setPlaceholderText(QStringLiteral("请输入搜索内容"));

    QHBoxLayout *pSearchLayout = new QHBoxLayout();
    pSearchLayout->addStretch();
    pSearchLayout->addWidget(ui->SearchButton);
    pSearchLayout->setSpacing(0);
    pSearchLayout->setContentsMargins(0, 0, 0, 0);
    ui->SearchlineEdit->setLayout(pSearchLayout);

    connect(ui->SearchButton, SIGNAL(clicked(bool)), this, SLOT(search()));
}

MusicSearchDialog::~MusicSearchDialog()
{ 
    ui->SearchlineEdit->clear();
    delete ui;
}

void MusicSearchDialog::search(){
    QString strText = ui->SearchlineEdit->text();
    //若在数据库中搜寻到某个歌曲 则显将结果显示在搜索弹框中
    if (!strText.isEmpty())             //此处应该修改为当搜索不到歌曲时  则显示“无当前搜索歌曲”（这得结合数据库去实现）
    {
        QMessageBox::information(this, QStringLiteral("搜索"), QStringLiteral("搜索内容为%1").arg(strText));
    }
}
