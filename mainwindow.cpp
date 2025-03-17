#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "controller.h"
#include "looker.h"
#include "overlaywidget.h"
#include <QTimer>
#include <QPropertyAnimation>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),cur_task_line(0)
{


    ui->setupUi(this);
    ui->check_main_ontop->setCheckState(Qt::Unchecked);
    ui->curLineSpin->setMaximum(0);
    ui->btn_insert_down->setEnabled(false);

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

    // 当palinTextEdit中的内容发生变化时，更新statusLabel的内容
    connect(ui->insertContext, &QPlainTextEdit::textChanged, [this](){
        cur_task_line = 0;
        QString content = ui->insertContext->toPlainText().toUtf8();
        QString numberOfLines = QString::number(content.count("\n") + 1);
        ui->statusbar->showMessage("行数：" + numberOfLines);
        total_task_line = content.count("\n") + 1;
        ui->curLineSpin->setMinimum(0);
        ui->curLineSpin->setMaximum(total_task_line);
        //将每一行加入到task_list
        task_list.clear();
        task_list = content.split("\n");
        qDebug() << "task_list: " << task_list;
        ui->btn_insert_down->setEnabled(true);
    });


    connect(ui->btn_insert_down,&QPushButton::clicked,[=](){
        int posx = ui->position->text().split(",")[0].toInt();
        int posy = ui->position->text().split(",")[1].toInt();
        controller::simulateMouseMove(posx,posy);
        controller::simulateMouseClick();
        QString sendMessage = task_list[cur_task_line];
        for(int i = 0; i < sendMessage.length(); i++)
        {
            //QChar to char，unicode
            char c;
            c = sendMessage[i].toLatin1();
            Sleep(200);
            qDebug()<<sendMessage[i]<<","<<c;

            controller::simulateKeyPress(c);
        }
        controller::simulateKeyPress('\n');
        cur_task_line++;
        ui->statusbar->showMessage("当前执行行号：" + QString::number(cur_task_line)+"总行数"+QString::number(total_task_line));
    });

    connect(ui->curLineSpin,&QSpinBox::valueChanged,[=](int value){
        cur_task_line = value;
    });



}

MainWindow::~MainWindow()
{
    stopMouseTracking();
    delete ui;
}
// 保存当前鼠标的位置的到ui->position
void MainWindow::on_acSave_triggered()
{
    ui->position->setText(QString::asprintf("%d,%d", cur_x, cur_y));
    qDebug() << "Saved";
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    // 关闭悬浮窗
    if (looker_overlay) {
        looker_overlay->close();  // 关闭悬浮窗

    }
    event->accept();// 关闭主窗口

}






void MainWindow::on_check_main_ontop_stateChanged(int arg1)
{
    // 获取窗口句柄
    // reinterpret_cast<HWND>(this->winId())将窗口转换为HWND类型

    HWND hwnd = reinterpret_cast<HWND>(this->winId());

    if(arg1 == Qt::Checked)
    {
        // this->setWindowFlags(Qt::WindowStaysOnTopHint);//设置窗口置顶，用QT自带的会闪烁

        //setWindowPos函数设置窗口的位置,HWND_TOPMOST表示置顶,0,0表示窗口的左上角坐标,0,0表示窗口的宽高,SWP_NOSIZE | SWP_NOMOVE表示不改变窗口的大小和位置
        ::SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);

        qDebug()<<"Checked";

    }
    else
    {
        // this->setWindowFlags(Qt::Window);//取消窗口置顶
        ::SetWindowPos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);

    }

    this->show();

}

