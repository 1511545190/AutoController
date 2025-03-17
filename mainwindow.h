#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "overlaywidget.h"
#include <QCloseEvent>
#include <QStringList>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_acSave_triggered();

    void on_check_main_ontop_stateChanged(int arg1);

    void on_btn_auto_time_run_clicked();

protected:
    void closeEvent(QCloseEvent *event) override;
private:
    Ui::MainWindow *ui;
    int cur_task_line;
    int total_task_line;
    QStringList task_list;
};
#endif // MAINWINDOW_H
