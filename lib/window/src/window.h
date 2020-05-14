#pragma once

enum ControlFlow {
	Exit,
	Poll,
	Wait,
};

enum Event {
	Close,
	EventsCleared,
};

struct Window;

Window* ngCreateWindow();
void ngDestroyWindow(Window* window);

void ngEventsLoopRun(ControlFlow(*cb)(Event));
