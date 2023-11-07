#include <iostream>
#include <windows.h>

bool isPaused = false;
const int screenWidth = GetSystemMetrics(SM_CXSCREEN);  // 获取屏幕宽度
const int screenHeight = GetSystemMetrics(SM_CYSCREEN); // 获取屏幕高度

// 键盘事件回调函数
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    // 检查键盘事件是否是按键按下的消息
    if (nCode == HC_ACTION && (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)) {
        KBDLLHOOKSTRUCT* pKeyboardHook = (KBDLLHOOKSTRUCT*)lParam;

        if ((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (pKeyboardHook->vkCode == 'Q')) {
            if (!isPaused) {
                // 获取鼠标位置
                POINT cursorPos;
                GetCursorPos(&cursorPos);

                // 输出鼠标位置
//                std::cout << "当前桌面像素坐标: (" << cursorPos.x << ", " << cursorPos.y << ")" << std::endl;
                int x = cursorPos.x * 3840 / screenWidth;
                int y = cursorPos.y * 2160 / screenHeight;
                std::cout << x << "." << y << std::endl;
            }
        }

        if ((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (pKeyboardHook->vkCode == 'P')) {
            isPaused = !isPaused;
            if (isPaused) {
                std::cout << "监控已暂停." << std::endl;
            } else {
                std::cout << "监控已恢复." << std::endl;
            }
        }
    }

    // 继续传递事件给下一个钩子
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main() {
    system("chcp 65001");
    // 安装键盘钩子
    HHOOK hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);

    // 消息循环，等待键盘事件
    MSG message;
    while (GetMessage(&message, NULL, 0, 0)) {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    // 卸载钩子
    UnhookWindowsHookEx(hKeyboardHook);

    return 0;
}