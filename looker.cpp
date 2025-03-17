#include "looker.h"

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
        MSLLHOOKSTRUCT* pMouseStruct = (MSLLHOOKSTRUCT*)lParam;
        int x = pMouseStruct->pt.x;
        int y = pMouseStruct->pt.y;
        qDebug()<<QString::asprintf("x: %d, y: %d", x, y);
    }
    return CallNextHookEx(mouseHook, nCode, wParam, lParam);
}

void startMouseTracking() {
    mouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, GetModuleHandle(NULL), 0);
    if (!mouseHook) {
        // 错误处理
        qDebug()<<"Failed to install mouse hook!";
    }
}

void stopMouseTracking() {
    UnhookWindowsHookEx(mouseHook);
}
