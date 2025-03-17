#include "controller.h"
#include <QDebug>
controller::controller() {}

void controller::simulateMouseMove(int x, int y)
{
    INPUT input = {0};
    input.type = INPUT_MOUSE;
    // GetSystemMetrics(SM_CXSCREEN)获取屏幕的宽度，GetSystemMetrics(SM_CYSCREEN)获取屏幕的高度
    // dx和dy是鼠标的坐标，这里的坐标是绝对坐标，范围是0~65535
    // 0,0是屏幕的左上角，65535,65535是屏幕的右下角
    // x,y是传入的参数，范围是0~GetSystemMetrics(SM_CXSCREEN), 0~GetSystemMetrics(SM_CYSCREEN)
    // x,y的范围是屏幕的宽高
    input.mi.dx = x * (65535.0f / GetSystemMetrics(SM_CXSCREEN)); // 转换坐标系
    input.mi.dy = y * (65535.0f / GetSystemMetrics(SM_CYSCREEN));
    input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE; // 移动鼠标，MOUSEEVENTF_ABSOLUTE表示绝对坐标, MOUSEEVENTF_MOVE表示移动
    SendInput(1, &input, sizeof(INPUT));
}

void controller::simulateMouseClick()
{
    INPUT input[2] = {{0}};
    // 按下左键
    input[0].type = INPUT_MOUSE;    // 鼠标事件
    input[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN; // 按下左键
    // 释放左键
    input[1].type = INPUT_MOUSE;    // 鼠标事件
    input[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;  // 释放左键
    // SendInput函数用于发送输入事件, 2表示发送两个输入, input是一个数组, 里面有两个INPUT结构体, 第三个参数是结构体的大小
    // INPUT结构题由type成员和一个联合体成员mi组成, type表示输入的类型, mi是一个联合体, 里面包含了鼠标事件和键盘事件的具体信息
    SendInput(2, input, sizeof(INPUT));
}

void controller::simulateKeyPress(char key)
{
    INPUT input[2] = {{0}};
    // 按下按键
    input[0].type = INPUT_KEYBOARD;
    input[0].ki.wVk = VkKeyScanA(key);//VkKeyScanA函数用于将字符转换为虚拟键码，即可以输入字符包括字母、数字、符号等
    // 释放按键
    input[1].type = INPUT_KEYBOARD;
    input[1].ki.wVk = VkKeyScanA(key);//VkKeyScanA函数用于将字符转换为虚拟键码，即可以输入字符包括字母、数字、符号等
    input[1].ki.dwFlags = KEYEVENTF_KEYUP;


    SHORT vk = VkKeyScanA(key);
    BYTE shift_needed = HIBYTE(vk); // 检查是否需要Shift键
    qDebug()<<"shift_needed:"<<shift_needed;//为true，需额外发送Shift键状态

    if(shift_needed)
    {
        INPUT shift_down = {0};
        shift_down.type = INPUT_KEYBOARD;
        shift_down.ki.wVk = VK_SHIFT;
        SendInput(1, &shift_down, sizeof(INPUT));
    }



    SendInput(2, input, sizeof(INPUT));//2表示发送两个输入, input是一个数组, 里面有两个INPUT结构体, 第三个参数是结构体的大小

    if(shift_needed)
    {
        INPUT shift_up = {0};
        shift_up.type = INPUT_KEYBOARD;
        shift_up.ki.wVk = VK_SHIFT;
        shift_up.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &shift_up, sizeof(INPUT));
    };


}

/*
 * // 将汉字“你”转换为Unicode编码
        char unicodeChar = '你';
        ushort unicodeScanCode = (ushort)unicodeChar;

        // 准备按下按键的INPUT结构
        INPUT[] inputs = new INPUT[2];
        inputs[0].type = INPUT_KEYBOARD;
        inputs[0].Anonymous.ki.wVk = 0;
        inputs[0].Anonymous.ki.wScan = unicodeScanCode;
        inputs[0].Anonymous.ki.dwFlags = KEYBD_EVENT_FLAGS_KEYEVENTF_UNICODE;
        inputs[0].Anonymous.ki.time = 0;
        inputs[0].Anonymous.ki.dwExtraInfo = UIntPtr.Zero;

        // 准备松开按键的INPUT结构
        inputs[1].type = INPUT_KEYBOARD;
        inputs[1].Anonymous.ki.wVk = 0;
        inputs[1].Anonymous.ki.wScan = unicodeScanCode;
        inputs[1].Anonymous.ki.dwFlags = KEYBD_EVENT_FLAGS_KEYEVENT*F_UNICODE | KEYBD_EVENT_FLAGS_KEYEVENTF_KEYUP;
        inputs[1].Anonymous.ki.time = 0;
        inputs[1].Anonymous.ki.dwExtraInfo = UIntPtr.Zero;

        int sizeOfInput = Marshal.SizeOf(typeof(INPUT));
        uint result = SendInput((uint)inputs.Length, inputs, sizeOfInput);
        if (result == 0)
        {
            int errorCode = Marshal.GetLastWin32Error();
            Console.WriteLine($"输入Unicode字符失败，错误码：{errorCode}");
        }
*/
