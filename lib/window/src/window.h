#include "lib/util/src/result.h"
#include "os.h"
#include <functional>
#include <string>

enum ControlFlow {
	Exit,
	Poll,
	Wait,
};

enum Event {
	Close,
	EventsCleared,
};

struct EventsLoop {
	void run(std::function<ControlFlow(Event)> cb);
};

struct Window {
	HWND hwnd;

	static Result<Window, std::wstring> create();
};
