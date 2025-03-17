#ifndef LOOKER_H
#define LOOKER_H

#include <Windows.h>
#include <QDebug>
#include <QString>
#include "overlaywidget.h"
extern HHOOK mouseHook; // 声明
extern int cur_x, cur_y;
extern OverlayWidget *looker_overlay;// 光点
// 鼠标钩子回调函数, 用于捕获鼠标事件
// 在什么时候调用这个函数呢？当鼠标事件发生时，系统会调用这个函数
// 只需要在这个函数里面处理鼠标事件即可
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam);

// 安装钩子，开始捕获鼠标事件
// 这个函数需要在程序启动时调用
void startMouseTracking();

// 卸载钩子, 停止捕获鼠标事件,需要在程序结束时调用
void stopMouseTracking();

#endif // LOOKER_H
