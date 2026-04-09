#include <windows.h>

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdLine, int cmdShow)
{
    char strInst[100];
    int i = wsprintfA(strInst, "hInst: %x, hInstPrev: %x, *PSTR: %s, cmdShow: %d\n",
                      hInst, hInstPrev, cmdLine, cmdShow);

    return MessageBox(NULL, strInst, "Hello, world!", 0);
}
