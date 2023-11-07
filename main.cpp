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
    srand ( ( int ) time ( 0 ) );//随机数种子
    POINT a;
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
    int my_x =
//    Sleep ( 1000 ) ;
//    x = 1 ;//生成随机数
//    y = 1;//生成随机数
//    SetCursorPos(x , y ) ;//将鼠标移动到屏幕的（x ， y）的点上


    // 模拟鼠标左键按下
//    INPUT input_down = {0};
//    input_down.type = INPUT_MOUSE;
//    input_down.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
//    SendInput(1, &input_down, sizeof(INPUT));
    return 0 ;
}