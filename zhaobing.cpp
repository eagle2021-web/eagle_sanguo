#include <iostream>
#include <fstream>
#include <fstream>
#include <sstream>
#include <string>
#include <thread>
#include <mutex>
#ifndef _INC_WINUSER

#include <windows.h>

#endif

#include <winuser.h>
#include <synchapi.h>
#include <functional>

using namespace std;
const int screenWidth = GetSystemMetrics(SM_CXSCREEN);  // 获取屏幕宽度
const int screenHeight = GetSystemMetrics(SM_CYSCREEN); // 获取屏幕高度
void simulateMouseMove(int t_x, int t_y) {
    const int STEPS = 10;  // 移动的步数
    POINT cursorPos;
    GetCursorPos(&cursorPos);
    int currentX = cursorPos.x, currentY = cursorPos.y;
    double deltaX = static_cast<double>(t_x - currentX) / STEPS;
    double deltaY = static_cast<double>(t_y - currentY) / STEPS;

    for (int i = 0; i <= STEPS; i++) {
        currentX = static_cast<int>(currentX + deltaX);
        currentY = static_cast<int>(currentY + deltaY);

        SetCursorPos(currentX, currentY);
        mouse_event(MOUSEEVENTF_MOVE, 0, 0, 0, 0);

        Sleep(10);  // 暂停10毫秒
    }
    SetCursorPos(t_x, t_y);
}

void dianji(int my_x, int my_y) {

    int t_x = my_x * screenWidth / 3840;
    int t_y = my_y * screenHeight / 2160;
    simulateMouseMove(t_x, t_y);
    std::cout << "当前鼠标屏幕坐标：(" << t_x << ", " << t_y << ")" << std::endl;

    // 模拟鼠标左键按下
    INPUT input_down = {0};
    input_down.type = INPUT_MOUSE;
    input_down.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &input_down, sizeof(INPUT));
    std::cout << "已模拟鼠标左键按下和松开事件" << std::endl;
    // 模拟鼠标左键松开123
    INPUT input_up = {0};
    input_up.type = INPUT_MOUSE;
    input_up.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &input_up, sizeof(INPUT));
    Sleep(1000);
    std::cout << "已模拟鼠标左键按下和松开事件" << std::endl;
}
void simulateKeyPress(WORD key)
{
    INPUT input;
    ZeroMemory(&input, sizeof(INPUT));

    input.type = INPUT_KEYBOARD;
    input.ki.wVk = key;
    input.ki.dwFlags = 0;

    SendInput(1, &input, sizeof(INPUT));
}

void simulateKeyRelease(WORD key)
{
    INPUT input;
    ZeroMemory(&input, sizeof(INPUT));

    input.type = INPUT_KEYBOARD;
    input.ki.wVk = key;
    input.ki.dwFlags = KEYEVENTF_KEYUP;

    SendInput(1, &input, sizeof(INPUT));
}

void simulateDeleteKey()
{
    simulateKeyPress(VK_DELETE);
    simulateKeyRelease(VK_DELETE);
}
void simulateKeyboardInput(const std::string &text) {

    for (size_t i = 0; i < text.length(); i++) {
        INPUT inputs[2];
        ZeroMemory(inputs, sizeof(inputs));

        inputs[0].type = INPUT_KEYBOARD;
        inputs[0].ki.wVk = 0;
        inputs[0].ki.wScan = text[i];
        inputs[0].ki.dwFlags = KEYEVENTF_UNICODE;

        inputs[1].type = INPUT_KEYBOARD;
        inputs[1].ki.wVk = 0;
        inputs[1].ki.wScan = text[i];
        inputs[1].ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;

        UINT result = SendInput(2, inputs, sizeof(INPUT));
        if (result == 0) {
            std::cerr << "无法模拟键盘输入" << std::endl;
        }
        Sleep(300);
    }
    simulateDeleteKey(); //模拟del键
    Sleep(1000);
// 暂停100毫秒（0.1秒）

}

void diankaishuliang() {
    dianji(2600, 1000);  // 点击招募
    dianji(2860, 1340);  // 进入文本框
}
void querenzhaobing(){
    dianji(2700,1670);
    dianji(3333,1682);
}
std::mutex inputMutex;  // 互斥锁，用于保护键盘输入
bool isInputReceived = false;  // 是否接收到键盘输入的标志

bool isRunning = true;
void inputThread() {
    std::cout << "等待键盘输入..." << std::endl;
    while (true) {
        // 检测 Alt + E 组合键是否被按下
        if ((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState('E') & 0x8000)) {
            inputMutex.lock();
            isInputReceived = true;  // 设置接收到键盘输入的标志
            isRunning = false;  // 设置停止标志变量
            inputMutex.unlock();
            break;
        }
    }
}
int main(int argc, char *argv[]) {
    system("chcp 65001");
    if (argc < 2) {
        std::cout << "请提供文件路径作为命令行参数" << std::endl;
        return 1;
    }

    std::ifstream file("zhaobing.txt");
    if (file.is_open()) {
        std::thread inputThreadObj(inputThread);// 创建键盘输入监控线程

        dianji(1447, 2128);
        std::string line;
        while (std::getline(file, line)) {
            cout << "line = " << line << endl;
            if(!isRunning)break;
            std::stringstream ss(line);  // 用于逗号分隔和转换为数字的 stringstream
            std::string segment;
            int count = 0;            int x, y;
            while (std::getline(ss, segment, '.')) {
                if (count == 0) {
                    x = std::stoi(segment);
                } else if (count == 1) {
                    y = std::stoi(segment);
                }
                count++;
            }
            // 利用 x 和 y 进行后续操作，比如输出它们的值
            std::cout << "x = " << x << ", y = " << y << std::endl;
            dianji(x, y);
            diankaishuliang();
            simulateKeyboardInput("700");
            querenzhaobing();

            // 检查是否接收到键盘输入，如果接收到则结束主线程
            inputMutex.lock();
            if (isInputReceived) {
                inputMutex.unlock();
                break;
            }
            inputMutex.unlock();        }
        file.close();
//        inputThreadObj.join();  // 等待键盘输入监控线程结束
    } else {
        std::cout << "无法打开文件" << std::endl;
    }

    return 0;
}