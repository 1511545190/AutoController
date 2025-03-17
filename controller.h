#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <Windows.h>
#pragma comment(lib, "user32.lib")
class controller
{
public:
    controller();


    // 模拟鼠标移动（绝对坐标）
    static void simulateMouseMove(int x, int y);

    // 模拟鼠标点击
    static void simulateMouseClick();

    // 模拟键盘输入（如按下 'A'）
    static void simulateKeyPress(char key);
};

#endif // CONTROLLER_H
