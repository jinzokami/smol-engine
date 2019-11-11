
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

	void get_position(float &x, float &y);
	void get_delta(float &dx, float &dy);

	void set_position(float x, float y);

	std::unordered_map<int, MouseState> button_state;

	float x;
	float y;
	float last_x;
	float last_y;
};