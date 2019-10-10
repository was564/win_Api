#include <Windows.h>

#define DRAW_LINE 1
#define BRUSH 2

HINSTANCE _hInstance; // �ν��Ͻ� �ڵ� 
	// (������ �ü������ ����Ǵ� ���α׷����� �����ϱ� ���� ID��)
HWND _hWnd; // �ڵ� ������ ����, �������� �ڵ� ��ȣ�� �����ؼ� ���

LPCWSTR _lpszClass = TEXT("WINDOW API");

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
	wndClass.lpszClassName = _lpszClass; // ������ Ŭ���� �̸�
		// (Ŭ���� �̸� �ٸ��� �ȳ���)
	wndClass.lpszMenuName = NULL; // ������ �޴� �̸�
	wndClass.style = CS_HREDRAW | CS_VREDRAW; // ������ â ��Ÿ��

	RegisterClass(&wndClass); // ������ ���� ���
	_hWnd = CreateWindow(
		_lpszClass,
		_lpszClass,
		WS_OVERLAPPEDWINDOW, // ������ ��Ÿ��
		50, // ������ â ������ǥ x
		50, // ������ â ������ǥ y
		800, // ������ â ����ũ��
		600, // ������ â ����ũ��
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

	int mode = BRUSH;
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
				SetPixel(hdc, 50 + i, 50 + i, RGB(0, 255, 0));
			}
		}
		break;
		
	case WM_DESTROY:
		PostQuitMessage(0); // ������â ����
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}