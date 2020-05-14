#include "lib/window/src/window.h"
#include <iostream>

using namespace std;

ControlFlow cb(Event event) {
	switch (event) {
		case Event::Close: return ControlFlow::Exit;
		default: return ControlFlow::Wait;
	}
}

int main() {
	auto window = ngCreateWindow();

	ngEventsLoopRun(cb);

	ngDestroyWindow(window);

	return 0;
}
