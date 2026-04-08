#include <windows.h>

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdLine, int cmdShow)
{
    return MessageBox(NULL, "Hello, world!", "caption", 0);
}
