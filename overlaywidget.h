#ifndef OVERLAYWIDGET_H
#define OVERLAYWIDGET_H
#include <QApplication>
#include <Windows.h>
#include <QObject>
#include <QWidget>
#include <QPainter>

class OverlayWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OverlayWidget(QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent*) override;
public:
    void updatePosition(int x,int y);
private:
    QPoint m_pos;
signals:
};

#endif // OVERLAYWIDGET_H
