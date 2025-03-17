#include "controller.h"

controller::controller() {}

void controller::simulateMouseMove(int x, int y)
{
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dx = x * (65535.0f / GetSystemMetrics(SM_CXSCREEN)); // 转换坐标系
    input.mi.dy = y * (65535.0f / GetSystemMetrics(SM_CYSCREEN));
    input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
    SendInput(1, &input, sizeof(INPUT));
}

void controller::simulateMouseClick()
{
    INPUT input[2] = {{0}};
    // 按下左键
    input[0].type = INPUT_MOUSE;
    input[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    // 释放左键
    input[1].type = INPUT_MOUSE;
    input[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(2, input, sizeof(INPUT));
}

void controller::simulateKeyPress(char key)
{
    INPUT input[2] = {{0}};
    // 按下按键
    input[0].type = INPUT_KEYBOARD;
    input[0].ki.wVk = VkKeyScanA(key);
    // 释放按键
    input[1].type = INPUT_KEYBOARD;
    input[1].ki.wVk = VkKeyScanA(key);
    input[1].ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(2, input, sizeof(INPUT));
}
