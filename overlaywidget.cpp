#include "overlaywidget.h"
#include<QScreen>
OverlayWidget::OverlayWidget(QWidget *parent)
    : QWidget{parent}
{
    // 设置窗口属性：无边框、透明背景、置顶
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_TransparentForMouseEvents); // 允许鼠标穿透
    // 构造函数中设置窗口标志
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowTransparentForInput);


    QScreen *screen = QGuiApplication::primaryScreen();
    qreal scale = screen->devicePixelRatio(); // 设备物理缩放因子
    qDebug() << "设备物理缩放因子: " << scale;
    // 设置窗口实际物理尺寸（如3840x2160 for 200%缩放）
    // 实际物理尺寸 = 逻辑尺寸 * 缩放因子
    // 逻辑尺寸指的是在不考虑缩放的情况下的尺寸，比如在屏幕分辨率为1920x1080的情况下，逻辑尺寸就是1920x108
    // 实际物理尺寸指的是在考虑缩放的情况下的尺寸，比如在屏幕分辨率为1920x1080的情况下，缩放因子为200%，实际物理尺寸就是3840x2160
    // 那么画坐标的时候，就需要把逻辑坐标转换为物理坐标，比如逻辑坐标(100, 100)对应的物理坐标就是(200, 200)
    setGeometry(QRect(0, 0,screen->geometry().width() * scale,screen->geometry().height() * scale));
    // setGeometry函数的作用是设置窗口的位置和大小，这里设置窗口大小为屏幕大小，即全屏
}

void OverlayWidget::paintEvent(QPaintEvent*)
{
    // 绘制窗口背景 这个会因屏幕缩放导致误差
    // QPainter painter(this);
    // painter.setRenderHint(QPainter::Antialiasing);
    // painter.setPen(Qt::NoPen);
    // painter.setBrush(QColor(255, 0, 0, 200)); // 半透明红色
    // painter.drawEllipse(m_pos, 5, 5); // 绘制半径为5的红点

    QPainter painter(this);
    // 逻辑坐标转换为物理像素坐标
    QPoint cursorPos = QCursor::pos();
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(255, 0, 0, 200)); // 半透明红色
    painter.setBrush(Qt::red);
    // painter都是使用物理坐标绘制的，所以需要把逻辑坐标转换为物理坐标
    painter.drawEllipse(cursorPos, 8, 8); // 使用物理坐标绘制

}

void OverlayWidget::updatePosition(int cur_x, int cur_y)
{
    m_pos = QPoint(cur_x, cur_y);
    // qDebug()<< "Read Point Position: " << m_pos;
    update();// 重绘
}

