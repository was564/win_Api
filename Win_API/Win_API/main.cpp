#include <Windows.h>

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

	switch (iMessage)
	{
	case WM_PAINT: // ������ ȭ�鿡�� �׸��̳� ���ڸ� ����ִ� ����
		hdc = BeginPaint(hWnd, &ps); // �׸� ȭ�� ����

		MoveToEx(hdc, 100, 100, NULL); // ��ǥ ����

		Ellipse(hdc, 0, 0, 500, 500); // �� �׸���

		Rectangle(hdc, 100, 100, 400, 400); // �׸� �׸���

		LineTo(hdc, 200, 200); // �� �׸��� ��ǥ�̵�
		LineTo(hdc, 300, 100);
		LineTo(hdc, 100, 500);

		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0); // ������â ����
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}