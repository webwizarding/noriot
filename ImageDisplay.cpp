#include "ImageDisplay.h"
#include <windows.h>
#include <gdiplus.h>

using namespace Gdiplus;

HBITMAP LoadBitmapFromResource(HINSTANCE hInstance, int resId) {
    HRSRC hRes = FindResource(hInstance, MAKEINTRESOURCE(resId), RT_BITMAP);
    if (!hRes) return nullptr;

    HGLOBAL hMem = LoadResource(hInstance, hRes);
    if (!hMem) return nullptr;

    void* pData = LockResource(hMem);
    DWORD size = SizeofResource(hInstance, hRes);
    HGLOBAL hBuffer = GlobalAlloc(GMEM_MOVEABLE, size);
    void* pBuffer = GlobalLock(hBuffer);
    memcpy(pBuffer, pData, size);
    GlobalUnlock(hBuffer);

    IStream* pStream = nullptr;
    HRESULT hr = CreateStreamOnHGlobal(hBuffer, TRUE, &pStream);

    HBITMAP hBitmap = nullptr;
    if (SUCCEEDED(hr)) {
        Bitmap* bitmap = Bitmap::FromStream(pStream);
        bitmap->GetHBITMAP(Color::Black, &hBitmap);
        delete bitmap;
        pStream->Release();
    }

    return hBitmap;
}

void DisplayCoconutImage(HINSTANCE hInstance) {
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

    HBITMAP hBitmap = LoadBitmapFromResource(hInstance, IDI_COCONUT_IMAGE);

    if (!hBitmap) {
        MessageBox(nullptr, L"Failed to load image", L"Error", MB_OK | MB_ICONERROR);
        return;
    }

    for (int i = 0; i < 10; ++i) {
        HWND hwnd = CreateWindowEx(
            0, L"STATIC", L"Coconut Alert",
            WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            CW_USEDEFAULT, CW_USEDEFAULT, 400, 400,
            nullptr, nullptr, nullptr, nullptr
        );

        SendMessage(hwnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
    }

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    DeleteObject(hBitmap);
    GdiplusShutdown(gdiplusToken);
}
