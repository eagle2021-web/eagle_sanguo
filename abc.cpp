#include <bits/stdc++.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>

using namespace std ;
int main ( ){
    // 设置输出流的编码格式为UTF-8
//    _setmode(_fileno(stdout), _O_WTEXT);
    system("chcp 65001");
    POINT cursorPos;
    if (GetCursorPos(&cursorPos)) {
        std::cout << "当前鼠标坐标：(" << cursorPos.x << ", " << cursorPos.y << ")" << std::endl;
    } else {
        std::cout << "无法获取鼠标坐标" << std::endl;
    }

    int screenWidth = GetSystemMetrics(SM_CXSCREEN);  // 获取屏幕宽度
    int screenHeight = GetSystemMetrics(SM_CYSCREEN); // 获取屏幕高度
    cout<< "screenWidth = " << screenWidth << endl;
    cout<< "screenHeight = " << screenHeight << endl;
    // 获取鼠标的X坐标
    int x = cursorPos.x;

    // 获取鼠标的Y坐标
    int y = cursorPos.y;

    // 进行适配计算
    int adaptedX = (x * 3840) / screenWidth;     // 适配X坐标
    int adaptedY = (y * 2160) / screenHeight;    // 适配Y坐标

    // 输出适配后的坐标
    std::cout << "适配后的鼠标坐标：(" << adaptedX << ", " << adaptedY << ")" << std::endl;
    SetCursorPos (391, 259);
    int my_x = 1447;
    int my_y = 2128;
    int t_x = my_x * screenWidth / 3840;
    int t_y = my_y * screenHeight / 2160;
    SetCursorPos (t_x, t_y);
    cout << t_x << endl;
    cout << t_y << endl;
    std::cout << "当前鼠标屏幕坐标：(" << t_x << ", " << t_y << ")" << std::endl;

    // 模拟鼠标左键按下
    INPUT input_down = {0};
    input_down.type = INPUT_MOUSE;
    input_down.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &input_down, sizeof(INPUT));

    // 模拟鼠标左键松开
    INPUT input_up = {0};
    input_up.type = INPUT_MOUSE;
    input_up.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &input_up, sizeof(INPUT));

    std::cout << "已模拟鼠标左键按下和松开事件" << std::endl;

    Sleep(5000);
    SendInput(1, &input_down, sizeof(INPUT));
    SendInput(1, &input_up, sizeof(INPUT));

    std::cout << "已模拟鼠标左键按下和松开事件" << std::endl;
    return 0 ;
}