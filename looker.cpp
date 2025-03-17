#include "looker.h"
HHOOK mouseHook;
int cur_x, cur_y;
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
        MSLLHOOKSTRUCT* pMouseStruct = (MSLLHOOKSTRUCT*)lParam;
        cur_x = pMouseStruct->pt.x;
        cur_y = pMouseStruct->pt.y;
        looker_overlay->updatePosition(cur_x, cur_y);
        // qDebug()<<QString::asprintf("Windows x: %d, y: %d", cur_x, cur_y);
    }
    return CallNextHookEx(mouseHook, nCode, wParam, lParam);
}

void startMouseTracking() {
    // 设置鼠标钩子，SetWindowsHookEx函数用于安装钩子
    // WH_MOUSE_LL表示鼠标钩子, MouseProc是回调函数, GetModuleHandle(NULL)获取当前模块句柄, 0表示全局钩子
    // MouseProc 可以自定义名称吗？当然可以，这个名称是自己起的，只要符合C++的命名规范即可
    // GetModuleHandle(NULL)获取当前模块句柄，这个函数是获取当前模块的句柄，这个函数的参数是模块的名称，如果传入NULL，表示获取当前模块的句柄
    // 0表示全局钩子，这个参数是一个线程ID，如果是0，表示全局钩子，这个钩子对所有的线程都有效
    mouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, GetModuleHandle(NULL), 0);
    if (!mouseHook) {
        // 错误处理
        qDebug()<<"Failed to install mouse hook!";
    }
}

void stopMouseTracking() {
    UnhookWindowsHookEx(mouseHook);
}
