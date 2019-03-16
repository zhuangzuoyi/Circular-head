#include "widget.h"
#include "ui_widget.h"
#include "QFileDialog"
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_openfile_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open file"), ".", tr("IMG Files(*.png *.jepg *.jpg)"));
    this->ui->sourcefile->setText(path);
    this->ui->editarea->setSourcefile(path);

}

void Widget::on_pushButton_clicked()
{
    this->ui->editarea->saveImg();
}
