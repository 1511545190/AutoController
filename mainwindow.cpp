#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "controller.h"
#include "looker.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //look
    startMouseTracking();
    // 鼠标移动
    connect(ui->btn_mouse_move, &QPushButton::clicked, [this](){
        QPoint pos;
        QString x_y = ui->position->text();
        QStringList x_y_list = x_y.split(",");
        pos.setX(x_y_list[0].toInt());
        pos.setY(x_y_list[1].toInt());
        controller::simulateMouseMove(pos.x(), pos.y());
    });
    // 鼠标点击
    connect(ui->btn_mouse_click, &QPushButton::clicked, [](){
        controller::simulateMouseClick();
    });

    connect(ui->btn_insert, &QPushButton::clicked, [=](){
        // 键盘输入
        QString Message = ui->insertContext->toPlainText();
        for(int i = 0; i < Message.length(); i++)
        {
            controller::simulateKeyPress(Message[i].toLatin1());
        }
    });

    //先移动到指定位置，再点击，再输入
    connect(ui->btn_task_run, &QPushButton::clicked, [=](){
        QPoint pos;
        QString x_y = ui->position->text();
        QStringList x_y_list = x_y.split(",");
        pos.setX(x_y_list[0].toInt());
        pos.setY(x_y_list[1].toInt());
        controller::simulateMouseMove(pos.x(), pos.y());
        controller::simulateMouseClick();
        // 键盘输入
        QString Message = ui->insertContext->toPlainText();
        for(int i = 0; i < Message.length(); i++)
        {
            controller::simulateKeyPress(Message[i].toLatin1());
        }
    });


}

MainWindow::~MainWindow()
{
    stopMouseTracking();
    delete ui;
}
