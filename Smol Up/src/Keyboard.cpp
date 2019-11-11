#include "Keyboard.hpp"

void Keyboard::update()
{
	for (auto elm : key_state)
	{
		key_state[elm.first].pressed = false;
		key_state[elm.first].released = false;
	}
}

void Keyboard::press(int key)
{
	key_state[key].down = true;
	key_state[key].pressed = true;
}

void Keyboard::release(int key)
{
	key_state[key].down = false;
	key_state[key].released = true;
}

bool Keyboard::is_down(int key)
{
	if (key_state.find(key) != key_state.end())
	{
		return key_state[key].down;
	}
	return false;
}

bool Keyboard::is_pressed(int key)
{
	if (key_state.find(key) != key_state.end())
	{
		return key_state[key].pressed;
	}
	return false;
}

bool Keyboard::is_released(int key)
{
	if (key_state.find(key) != key_state.end())
	{
		return key_state[key].released;
	}
	return false;
}

std::string kb::key_name(int key)
{
	switch (key)
	{
	case GLFW_KEY_A:
		return "A";
		break;
	case GLFW_KEY_B:
		return "B";
		break;
	case GLFW_KEY_C:
		return "C";
		break;
	case GLFW_KEY_D:
		return "D";
		break;
	case GLFW_KEY_E:
		return "E";
		break;
	case GLFW_KEY_F:
		return "F";
		break;
	case GLFW_KEY_G:
		return "G";
		break;
	case GLFW_KEY_H:
		return "H";
		break;
	case GLFW_KEY_I:
		return "I";
		break;
	case GLFW_KEY_J:
		return "J";
		break;
	case GLFW_KEY_K:
		return "K";
		break;
	case GLFW_KEY_L:
		return "L";
		break;
	case GLFW_KEY_M:
		return "M";
		break;
	case GLFW_KEY_N:
		return "N";
		break;
	case GLFW_KEY_O:
		return "O";
		break;
	case GLFW_KEY_P:
		return "P";
		break;
	case GLFW_KEY_Q:
		return "Q";
		break;
	case GLFW_KEY_R:
		return "R";
		break;
	case GLFW_KEY_S:
		return "S";
		break;
	case GLFW_KEY_T:
		return "T";
		break;
	case GLFW_KEY_U:
		return "U";
		break;
	case GLFW_KEY_V:
		return "V";
		break;
	case GLFW_KEY_W:
		return "W";
		break;
	case GLFW_KEY_X:
		return "X";
		break;
	case GLFW_KEY_Y:
		return "Y";
		break;
	case GLFW_KEY_Z:
		return "Z";
		break;
	case GLFW_KEY_0:
		return "0";
		break;
	case GLFW_KEY_1:
		return "1";
		break;
	case GLFW_KEY_2:
		return "2";
		break;
	case GLFW_KEY_3:
		return "3";
		break;
	case GLFW_KEY_4:
		return "4";
		break;
	case GLFW_KEY_5:
		return "5";
		break;
	case GLFW_KEY_6:
		return "6";
		break;
	case GLFW_KEY_7:
		return "7";
		break;
	case GLFW_KEY_8:
		return "8";
		break;
	case GLFW_KEY_9:
		return "9";
		break;
	case GLFW_KEY_SPACE:
		return "SPACE";
		break;
	case GLFW_KEY_ENTER:
		return "ENTER";
		break;
	case GLFW_KEY_ESCAPE:
		return "ESCAPE";
		break;
	case GLFW_KEY_LEFT:
		return "LEFT";
		break;
	case GLFW_KEY_RIGHT:
		return "RIGHT";
		break;
	case GLFW_KEY_UP:
		return "UP";
		break;
	case GLFW_KEY_DOWN:
		return "down";
		break;
	case GLFW_KEY_GRAVE_ACCENT:
		return "`";
		break;
	case GLFW_KEY_MINUS:
		return "-";
		break;
	case GLFW_KEY_EQUAL:
		return "=";
		break;
	case GLFW_KEY_BACKSPACE:
		return "BACKSPACE";
		break;
	case GLFW_KEY_TAB:
		return "TAB";
		break;
	case GLFW_KEY_LEFT_BRACKET:
		return "[";
		break;
	case GLFW_KEY_RIGHT_BRACKET:
		return "]";
		break;
	case GLFW_KEY_BACKSLASH:
		return "\\";
		break;
	case GLFW_KEY_SLASH:
		return "/";
		break;
	case GLFW_KEY_CAPS_LOCK:
		return "CAPS LOCK";
		break;
	case GLFW_KEY_SEMICOLON:
		return ";";
		break;
	case GLFW_KEY_APOSTROPHE:
		return "'";
		break;
	case GLFW_KEY_LEFT_SHIFT:
		return "LSHIFT";
		break;
	case GLFW_KEY_RIGHT_SHIFT:
		return "RSHIFT";
		break;
	case GLFW_KEY_COMMA:
		return ",";
		break;
	case GLFW_KEY_PERIOD:
		return ".";
		break;
	case GLFW_KEY_LEFT_CONTROL:
		return "LCTRL";
		break;
	case GLFW_KEY_RIGHT_CONTROL:
		return "RCTRL";
		break;
	case GLFW_KEY_LEFT_ALT:
		return "LALT";
		break;
	case GLFW_KEY_RIGHT_ALT:
		return "RALT";
		break;
	case GLFW_KEY_INSERT:
		return "INSERT";
		break;
	case GLFW_KEY_HOME:
		return "HOME";
		break;
	case GLFW_KEY_DELETE:
		return "DELETE";
		break;
	case GLFW_KEY_END:
		return "END";
		break;
	case GLFW_KEY_PAGE_UP:
		return "PAGE UP";
		break;
	case GLFW_KEY_PAGE_DOWN:
		return "PAGE DOWN";
		break;
	case GLFW_KEY_F1:
		return "F1";
		break;
	case GLFW_KEY_F2:
		return "F2";
		break;
	case GLFW_KEY_F3:
		return "F3";
		break;
	case GLFW_KEY_F4:
		return "F4";
		break;
	case GLFW_KEY_F5:
		return "F5";
		break;
	case GLFW_KEY_F6:
		return "F6";
		break;
	case GLFW_KEY_F7:
		return "F7";
		break;
	case GLFW_KEY_F8:
		return "F8";
		break;
	case GLFW_KEY_F9:
		return "F9";
		break;
	case GLFW_KEY_F10:
		return "F10";
		break;
	case GLFW_KEY_F11:
		return "F11";
		break;
	case GLFW_KEY_F12:
		return "F12";
		break;
	case GLFW_KEY_KP_0:
		return "NUMPAD 0";
		break;
	case GLFW_KEY_KP_1:
		return "NUMPAD 1";
		break;
	case GLFW_KEY_KP_2:
		return "NUMPAD 2";
		break;
	case GLFW_KEY_KP_3:
		return "NUMPAD 3";
		break;
	case GLFW_KEY_KP_4:
		return "NUMPAD 4";
		break;
	case GLFW_KEY_KP_5:
		return "NUMPAD 5";
		break;
	case GLFW_KEY_KP_6:
		return "NUMPAD 6";
		break;
	case GLFW_KEY_KP_7:
		return "NUMPAD 7";
		break;
	case GLFW_KEY_KP_8:
		return "NUMPAD 8";
		break;
	case GLFW_KEY_KP_9:
		return "NUMPAD 9";
		break;
	case GLFW_KEY_KP_ADD:
		return "NUMPAD +";
		break;
	case GLFW_KEY_KP_DECIMAL:
		return "NUMPAD .";
		break;
	case GLFW_KEY_KP_DIVIDE:
		return "NUMPAD /";
		break;
	case GLFW_KEY_KP_ENTER:
		return "NUMPAD ENTER";
		break;
	case GLFW_KEY_KP_EQUAL:
		return "NUMPAD =";
		break;
	case GLFW_KEY_KP_MULTIPLY:
		return "NUMPAD *";
		break;
	case GLFW_KEY_KP_SUBTRACT:
		return "NUMPAD -";
		break;
	case GLFW_KEY_PRINT_SCREEN:
		return "PRINTSCREEN";
		break;
	case GLFW_KEY_SCROLL_LOCK:
		return "SCROLL LOCK";
		break;
	case GLFW_KEY_PAUSE:
		return "PAUSE";
		break;
	default:
		return "UNDEFINED";
		break;
	}
}
