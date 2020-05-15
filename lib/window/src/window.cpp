#include "window.h"
#include "lib/util/src/log.h"
#include "lib/util/src/os.h"
#include <codecvt>
#include <locale>
#include <string>

using namespace std;

thread_local bool KNOWN_EVENT = false;
thread_local Event EVENT = {};

struct Window {
	HWND hwnd;
	bool destroyed;
};

string getLastErrorMessage() {
	auto err = GetLastError();
	LPWSTR buf = nullptr;
	size_t size = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, err, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPWSTR)&buf, 0, nullptr
	);
	wstring message(buf, size);
	LocalFree(buf);
	return wstring_convert<codecvt_utf8<wchar_t>, wchar_t>().to_bytes(message);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		case WM_CLOSE:
			KNOWN_EVENT = true;
			EVENT = Event::Close;

			auto window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			window->destroyed = true;

			break;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

Window* ngCreateWindow() {
	auto hInstance = GetModuleHandle(nullptr);

	auto className = L"vkWindow";

	WNDCLASS wc = {};
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = className;
	if (!RegisterClass(&wc)) DIE(getLastErrorMessage().c_str());

	HWND hwnd = CreateWindowEx(
		0, className, L"window", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		nullptr, nullptr, hInstance, nullptr
	);
	if (!hwnd) DIE(getLastErrorMessage().c_str());

	ShowWindow(hwnd, SW_SHOW);

	auto ret = new Window { hwnd };
	SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)ret);
	return ret;
}

void ngDestroyWindow(Window* window) {
	if (!window->destroyed) {
		if (!DestroyWindow(window->hwnd)) DIE(getLastErrorMessage().c_str());
	}
	delete window;
}

void ngEventsLoopRun(ControlFlow(*cb)(Event)) {
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

			if (KNOWN_EVENT) {
				flow = cb(EVENT);
			}
		} else {
			flow = cb(Event::EventsCleared);
		}
	}
}
