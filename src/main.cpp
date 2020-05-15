#include "lib/window/src/window.h"
#include "lib/gfx/src/gfx.h"
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
	auto gfx = ngCreateGfx("game", NG_MAKE_VERSION(0, 1, 0));

	ngEventsLoopRun(cb);

	ngDestroyGfx(gfx);
	ngDestroyWindow(window);

	return 0;
}
