#include "stdafx.h"
#include <Windows.h>

#define DRAW_LINE 1
#define BRUSH 2
#define MOUSE 3

HINSTANCE _hInstance; // �ν��Ͻ� �ڵ� 
	// (������ �ü������ ����Ǵ� ���α׷����� �����ϱ� ���� ID��)
HWND _hWnd; // �ڵ� ������ ����, �������� �ڵ� ��ȣ�� �����ؼ� ���

// LPCSTR _lpszClass = TEXT("WINDOW API");

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance,
	LPSTR lpszCmdParam, int cmdShow) {

	MSG message; // �޽��� ����ü
	WNDCLASS wndClass; // ������ ���� ����ü

	// ������ ���� ����
	wndClass.cbClsExtra = 0; // Ŭ���� ���� �޸�
	wndClass.cbWndExtra = 0; // ������ ���� �޸�
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //
		// ������ ����
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW); //
		// Ŀ�� ������ ��� (�⺻)
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); //
		// ���� ������ ��� (�⺻)
	wndClass.hInstance = _hInstance; // ������ �ν��Ͻ� ��ȣ
	wndClass.lpfnWndProc = (WNDPROC)WndProc; // ������ ���ν���
		// (Ű, ���콺, ������â, �������� ������ ������� ����)
	wndClass.lpszClassName = WINNAME; // ������ Ŭ���� �̸�
		// (Ŭ���� �̸� �ٸ��� �ȳ���)
	wndClass.lpszMenuName = NULL; // ������ �޴� �̸�
	wndClass.style = CS_HREDRAW | CS_VREDRAW; // ������ â ��Ÿ��

	RegisterClass(&wndClass); // ������ ���� ���
	_hWnd = CreateWindow(
		WINNAME,
		WINNAME,
		WS_OVERLAPPEDWINDOW, // ������ ��Ÿ��
		WINSTARTX, // ������ â ������ǥ x
		WINSTARTY, // ������ â ������ǥ y
		WINSIZEX, // ������ â ����ũ��
		WINSIZEY, // ������ â ����ũ��
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL);

	ShowWindow(_hWnd, cmdShow); // ������ â�� ȭ�鿡 ����

	// GetMessage : �޼����� ������ �� �� ó��
	// PeekMessage : �޼����� ������ �ʾƵ� while���� ������Ʈ
	while (GetMessage(&message, 0, 0, 0)) {
		TranslateMessage(&message); // Ű���� �Է½� �� �޼��� ó�� ���
		DispatchMessage(&message); // �����쿡 �޼����� �������ִ� ����
	}

	return message.wParam;
}

// hWnd : ��� �����쿡�� �޼����� �߻��ߴ��� üũ
// iMessage : �޼��� ��ȣ
// wParam : Ű���� �Է� �� ���콺 Ŭ�� üũ
// lParam : ���콺 ��ǥ �ҷ�����

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {

	HDC hdc; // Handle Device Context(ȭ�� �׸��⿡ ����� dc�� �ڵ鰪)
	PAINTSTRUCT ps; // ������ Ŭ���̾�Ʈ ������ �׸��µ� �ʿ��� ������ ����ִ� ����ü
		// �� �׸��� �ӵ��� ��������� ��½�Ŵ

	
	static RECT _rc1;
	static RECT _rc2;

	int mode = MOUSE;
	if (mode == DRAW_LINE || mode == BRUSH) {
		switch (iMessage)
		{

		case WM_PAINT: // ������ ȭ�鿡�� �׸��̳� ���ڸ� ����ִ� ����
			if (mode == DRAW_LINE) {
				hdc = BeginPaint(hWnd, &ps); // �׸� ȭ�� ����

				MoveToEx(hdc, 100, 100, NULL); // ��ǥ ����

				Ellipse(hdc, 0, 0, 500, 500); // �� �׸���

				Rectangle(hdc, 100, 100, 400, 400); // �׸� �׸���

				LineTo(hdc, 200, 200); // �� �׸��� ��ǥ�̵�
				LineTo(hdc, 300, 100);
				LineTo(hdc, 100, 500);

				EndPaint(hWnd, &ps);
				break;
			}
			else if (mode == BRUSH) {
				hdc = BeginPaint(hWnd, &ps);

				// �ܻ� �귯���� �����ϸ� �귯�� ���� �μ��� ����
				HBRUSH brush = CreateSolidBrush(RGB(200, 100, 50));

				// �귯�� ���
				HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);

				// ������ �簢�� �׸���
				Rectangle(hdc, 100, 100, 200, 200);

				SelectObject(hdc, oldBrush); // ���� �귯�� ����

				DeleteObject(brush); // �귯�� ����

				HBRUSH brush2 = CreateSolidBrush(RGB(0, 255, 150));
				HBRUSH oldBrush2 = (HBRUSH)SelectObject(hdc, brush);
				SelectObject(hdc, brush2);
				Rectangle(hdc, 200, 200, 300, 300);
				SelectObject(hdc, oldBrush2);
				DeleteObject(brush2);

				// �� ���� (�� ���, �� ����. �� ����)
				HPEN pen = CreatePen(PS_DASH, 1, RGB(255, 0, 0));
				HPEN oldPen = (HPEN)SelectObject(hdc, pen);
				MoveToEx(hdc, 50, 100, NULL);
				LineTo(hdc, 500, 400);
				SelectObject(hdc, oldPen);
				DeleteObject(pen);

				SetPixel(hdc, 50, 50, RGB(0, 0, 255));

				for (int i = 0; i < 100; i++) {
					SetPixel(hdc, 400 + i, 400 + i, RGB(0, 255, 0));
				}
				break;
			}
			
		case WM_DESTROY:
			PostQuitMessage(0); // ������â ����
			break;

		default:
			break;
		}
	}

	else if (mode == MOUSE) {
		char strPT[128];
		static POINT pt = { 0,0 };
		static RECT _rc1;
		static RECT _rc2;
		switch (iMessage)
		{
		case WM_CREATE:
			_rc1 = RectMakeCenter(WINSIZEX / 2 - 200, WINSIZEY / 2, 100, 100);
			_rc2 = RectMakeCenter(WINSIZEX / 2 + 200, WINSIZEY / 2, 100, 100);

		case WM_PAINT:

			hdc = BeginPaint(hWnd, &ps);

			sprintf_s(strPT, "X : %d,	Y : %d", pt.x, pt.y);
			TextOut(hdc, 10, 10, strPT, strlen(strPT));

			Rectangle(hdc, _rc1.left, _rc1.top, _rc1.right, _rc1.bottom);
			Rectangle(hdc, _rc2.left, _rc2.top, _rc2.right, _rc2.bottom);

			EndPaint(hWnd, &ps);
			break;

		case WM_MOUSEMOVE:
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			InvalidateRect(hWnd, NULL, true);
			break;

		case WM_KEYDOWN:
			switch (wParam)
			{
			case VK_ESCAPE:
				PostQuitMessage(0);
				break;
				
			case VK_LEFT:
				_rc1.left -= 5;
				_rc1.right -= 5;
				InvalidateRect(_hWnd, NULL, true);
				break;

			case VK_RIGHT:
				_rc1.left += 5;
				_rc1.right += 5;
				if (_rc1.right > _rc2.left &&
					_rc1.bottom > _rc2.top &&
					_rc1.top < _rc2.bottom) {
					_rc2.left += 5;
					_rc2.right += 5;
				}
				InvalidateRect(_hWnd, NULL, true);
				break;
				
			case VK_UP:
				_rc1.top -= 5;
				_rc1.bottom -= 5;
				InvalidateRect(_hWnd, NULL, true);
				break;

			case VK_DOWN:
				_rc1.top += 5;
				_rc1.bottom += 5;
				InvalidateRect(_hWnd, NULL, true);
				break;
			}
			break;

		case WM_LBUTTONDOWN:
			hdc = GetDC(_hWnd);
			TextOut(hdc, WINSIZEX / 3, 0, "���� ���콺 ��ư Ŭ��!", strlen("���� ���콺 ��ư Ŭ��!"));
			ReleaseDC(_hWnd, hdc);
			break;

		case WM_RBUTTONDOWN:
			hdc = GetDC(_hWnd);
			TextOut(hdc, WINSIZEX * 2 / 3 + 20, 0, "������ ���콺 ��ư Ŭ��!", strlen("������ ���콺 ��ư Ŭ��!"));
			ReleaseDC(_hWnd, hdc);
			break;
		
		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:
			break;
		}
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}