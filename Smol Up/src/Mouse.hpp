
#include <unordered_map>

struct MouseState
{
	bool down, pressed, released;
};

class Mouse
{
public:
	void update();

	void press(int button);
	void release(int button);

	bool is_down(int button);
	bool is_pressed(int button);
	bool is_released(int button);

	std::unordered_map<int, MouseState> button_state;
};