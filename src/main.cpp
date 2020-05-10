#include <iostream>
#include "lib/window/src/window.h"

using namespace std;

int main() {
	auto window = Window::create();
	// I'll probably have to pass an EventsLoop instance to Window::create() later, but this works for now
	EventsLoop().run([](auto event) {
		switch (event) {
			case Event::Close: return ControlFlow::Exit;
			default: return ControlFlow::Poll;
		}
	});
	return 0;
}
