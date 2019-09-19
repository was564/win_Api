#include <Windows.h>

HINSTANCE _hInstance; // 인스턴스 핸들 
	// (윈도우 운영체제에서 실행되는 프로그램들을 구별하기 위한 ID값)
HWND _hWnd; // 핸들 윈도우 약자, 윈도우의 핸들 번호를 지정해서 사용

LPCWSTR _lpszClass = TEXT("WINDOW API");

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance,
	LPSTR lpszCmdParam, int cmdShow) {

	MSG message; // 메시지 구조체
	WNDCLASS wndClass; // 윈도우 정보 구조체

	// 윈도우 정보 세팅
	wndClass.cbClsExtra = 0; // 클래스 여분 메모리
	wndClass.cbWndExtra = 0; // 윈도우 여분 메모리
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //
		// 윈도우 배경색
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW); //
		// 커서 아이콘 모양 (기본)
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); //
		// 어플 아이콘 모양 (기본)
	wndClass.hInstance = _hInstance; // 윈도우 인스턴스 번호
	wndClass.lpfnWndProc = (WNDPROC)WndProc; // 윈도우 프로시저
		// (키, 마우스, 윈도우창, 깝빡임이 들어오면 절차대로 진행)
	wndClass.lpszClassName = _lpszClass; // 윈도우 클래스 이름
		// (클래스 이름 다르면 안나옴)
	wndClass.lpszMenuName = NULL; // 윈도우 메뉴 이름
	wndClass.style = CS_HREDRAW | CS_VREDRAW; // 윈도우 창 스타일

	RegisterClass(&wndClass); // 윈도우 정보 등록
	_hWnd = CreateWindow(
		_lpszClass,
		_lpszClass,
		WS_OVERLAPPEDWINDOW, // 윈도우 스타일
		50, // 윈도우 창 시작좌표 x
		50, // 윈도우 창 시작좌표 y
		800, // 윈도우 창 가로크기
		600, // 윈도우 창 세로크기
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL);

	ShowWindow(_hWnd, cmdShow); // 윈도우 창을 화면에 띄우기

	// GetMessage : 메세지가 들어오면 그 때 처리
	// PeekMessage : 메세지가 들어오지 않아도 while문은 업데이트
	while (GetMessage(&message, 0, 0, 0)) {
		TranslateMessage(&message); // 키보드 입력시 그 메세지 처리 담당
		DispatchMessage(&message); // 윈도우에 메세지를 전달해주는 역할
	}

	return message.wParam;
}

// hWnd : 어느 윈도우에서 메세지가 발생했는지 체크
// iMessage : 메세지 번호
// wParam : 키보드 입력 및 마우스 클릭 체크
// lParam : 마우스 좌표 불러오기

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {

	HDC hdc; // Handle Device Context(화면 그리기에 사용할 dc의 핸들값)
	PAINTSTRUCT ps; // 윈도우 클라이언트 영역을 그리는데 필요한 정보를 담고있는 구조체
		// ㄴ 그리는 속도를 비약적으로 상승시킴

	switch (iMessage)
	{
	case WM_PAINT: // 윈도우 화면에서 그림이나 문자를 띄워주는 영역
		hdc = BeginPaint(hWnd, &ps); // 그릴 화면 선택

		MoveToEx(hdc, 100, 100, NULL); // 좌표 설정

		Ellipse(hdc, 0, 0, 500, 500); // 원 그리기

		Rectangle(hdc, 100, 100, 400, 400); // 네모 그리기

		LineTo(hdc, 200, 200); // 선 그리고 좌표이동
		LineTo(hdc, 300, 100);
		LineTo(hdc, 100, 500);

		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0); // 윈도우창 삭제
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}