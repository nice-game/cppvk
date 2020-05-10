#include "window.h"

using namespace std;

const auto CLASS_NAME = L"vkWindow";

thread_local Opt<Event> EVENT = None();

wstring getLastErrorMessage() {
	auto err = GetLastError();
	LPWSTR buf = nullptr;
	size_t size = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, err, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPWSTR)&buf, 0, nullptr
	);
	wstring message(buf, size);
	LocalFree(buf);
	return message;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		case WM_CLOSE: EVENT = Some(Event::Close);
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void EventsLoop::run(function<ControlFlow(Event)> cb) {
	MSG msg = {};
	ControlFlow flow = ControlFlow::Poll;
	while (true) {
		auto found_msg = true;
		switch (flow) {
			case ControlFlow::Exit: return;
			case ControlFlow::Poll:
				found_msg = PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE);
				break;
			case ControlFlow::Wait:
				GetMessage(&msg, nullptr, 0, 0);
				break;
		}
		if (found_msg) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		flow = cb(EVENT.take().unwrap_or(Event::EventsCleared));
	}
}

Result<Window, wstring> Window::create() {
	auto hInstance = GetModuleHandle(nullptr);

	WNDCLASS wc = {};
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	auto res = RegisterClass(&wc);
	if (!res) return Err(getLastErrorMessage());

	HWND hwnd = CreateWindowEx(
		0, CLASS_NAME, L"window", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		nullptr, nullptr, hInstance, nullptr
	);
	if (!hwnd) return Err(getLastErrorMessage());

	ShowWindow(hwnd, SW_SHOW);

	return Ok(Window { hwnd });
}
