#include <windows.h>
#include <string>

const TCHAR CLSNAME[] = TEXT("helloworldWClass");
LRESULT CALLBACK winproc(HWND hwnd, UINT wm, WPARAM wp, LPARAM lp);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, PTSTR cmdline, int cmdshow)
{
    WNDCLASSEX wc{};
    MSG msg;
    HWND hwnd;

    MessageBox(NULL, std::string{"sizeof(wc): " + std::to_string(sizeof(wc))}.c_str(), 0, 0);

    return 0;
}
