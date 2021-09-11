#include "Render.h"

#include <Windows.h>
#include <WinGDI.h>
#pragma comment(lib, "Msimg32.lib")

#include "FlatObject.h"
#include "Defines.h"

HWND Render::_hWnd;
HBITMAP Render::_bitmap;

int Render::_width;
int Render::_height;

void Render::Invalidate(RECT* rect) {
	InvalidateRect(_hWnd, rect, false);
	UpdateWindow(_hWnd);
}

void Render::Redraw(PAINTSTRUCT* pps) {
	PAINTSTRUCT ps = *pps;
	HDC hBitmapDC = CreateCompatibleDC(ps.hdc);
	HGDIOBJ hBitmapDCOldBitmap = SelectObject(hBitmapDC, _bitmap);

	HDC hBufferDC = CreateCompatibleDC(ps.hdc);
	HBITMAP hBufferDCBitmap = CreateCompatibleBitmap(ps.hdc, ps.rcPaint.right - ps.rcPaint.left,
		ps.rcPaint.bottom - ps.rcPaint.top);
	HGDIOBJ hBufferDCOldBitmap = SelectObject(hBufferDC, hBufferDCBitmap);
	
	RECT objectRect;
	FlatObject::GetRect(&objectRect);

	RECT rectForClear;
	rectForClear.left = 0;
	rectForClear.top = 0;
	rectForClear.right = ps.rcPaint.right - ps.rcPaint.left;
	rectForClear.bottom = ps.rcPaint.bottom - ps.rcPaint.top;
	FillRect(hBufferDC, &rectForClear, (HBRUSH)(COLOR_WINDOW + 1));

	TransparentBlt(hBufferDC, objectRect.left - ps.rcPaint.left, objectRect.top - ps.rcPaint.top,
		objectRect.right - objectRect.left, objectRect.bottom - objectRect.top,
		hBitmapDC, 0, 0, _width, _height, 0x00C67B71);

	BitBlt(ps.hdc, ps.rcPaint.left, ps.rcPaint.top, ps.rcPaint.right - ps.rcPaint.left, ps.rcPaint.bottom - ps.rcPaint.top,
		hBufferDC, 0, 0, SRCCOPY);

	DeleteObject(hBufferDCBitmap);

	SelectObject(hBufferDC, hBufferDCOldBitmap);
	DeleteObject(hBufferDC);

	SelectObject(hBitmapDC, hBitmapDCOldBitmap);
	DeleteObject(hBitmapDC);
}

void Render::SetHWND(HWND hWnd) {
	_hWnd = hWnd;
}

void Render::SetBitmap(HBITMAP bitmap) {
	BITMAP bmpData;
	GetObject(bitmap, sizeof(BITMAP), &bmpData);

	_bitmap = bitmap;
	_width = bmpData.bmWidth;
	_height = bmpData.bmHeight;
}

bool Render::IsTouching(int x, int y)
{
	HDC hDC = GetDC(_hWnd);
	COLORREF color = GetPixel(hDC, x, y);
	ReleaseDC(_hWnd, hDC);
	return color != 0xFFFFFF;
}

void Render::ClientRect(RECT* prect)
{
	GetClientRect(_hWnd, prect);
}
