#include "Input.h"
#include "Game.h"

Input::Input(void)
{
	Init();
	memset(&status_, 0, 50);
}

Input::~Input()
{
	if(!translation_.empty())
	{
		translation_.clear();
	}
}

void Input::Init()
{
	//sets defaults in the translation map as equal. 
	//future implementation: load them from a file....

	//format is (WHAT_THEY_PRESS, WHAT_WE_READ_AS_DEFAULT)
	//we access the keys by translating the user-defined keys into our original defaults, so 
	//we can always base our actions on the default keys
	translation_.insert(std::pair<int, int>(GLFW_KEY_SPACE, GLFW_KEY_SPACE));
	translation_.insert(std::pair<int, int>(GLFW_KEY_SPECIAL, GLFW_KEY_SPECIAL));
	translation_.insert(std::pair<int, int>(GLFW_KEY_ESC, GLFW_KEY_ESC));
	translation_.insert(std::pair<int, int>(GLFW_KEY_F1, GLFW_KEY_F1));
	translation_.insert(std::pair<int, int>(GLFW_KEY_F2, GLFW_KEY_F2));
	translation_.insert(std::pair<int, int>(GLFW_KEY_F3, GLFW_KEY_F3));
	translation_.insert(std::pair<int, int>(GLFW_KEY_F4, GLFW_KEY_F4));
	translation_.insert(std::pair<int, int>(GLFW_KEY_F5, GLFW_KEY_F5));
	translation_.insert(std::pair<int, int>(GLFW_KEY_F6, GLFW_KEY_F6));
	translation_.insert(std::pair<int, int>(GLFW_KEY_F7, GLFW_KEY_F7));
	translation_.insert(std::pair<int, int>(GLFW_KEY_F8, GLFW_KEY_F8));
	translation_.insert(std::pair<int, int>(GLFW_KEY_F9, GLFW_KEY_F9));
	translation_.insert(std::pair<int, int>(GLFW_KEY_F10, GLFW_KEY_F10));
	translation_.insert(std::pair<int, int>(GLFW_KEY_F11, GLFW_KEY_F11));
	translation_.insert(std::pair<int, int>(GLFW_KEY_F12, GLFW_KEY_F12));
	translation_.insert(std::pair<int, int>(GLFW_KEY_F13, GLFW_KEY_F13));
	translation_.insert(std::pair<int, int>(GLFW_KEY_F14, GLFW_KEY_F14));
	translation_.insert(std::pair<int, int>(GLFW_KEY_F15, GLFW_KEY_F15));
	translation_.insert(std::pair<int, int>(GLFW_KEY_F16, GLFW_KEY_F16));
	translation_.insert(std::pair<int, int>(GLFW_KEY_F17, GLFW_KEY_F17));
	translation_.insert(std::pair<int, int>(GLFW_KEY_F18, GLFW_KEY_F18));
	translation_.insert(std::pair<int, int>(GLFW_KEY_F19, GLFW_KEY_F19));
	translation_.insert(std::pair<int, int>(GLFW_KEY_F20, GLFW_KEY_F20));
	translation_.insert(std::pair<int, int>(GLFW_KEY_F21, GLFW_KEY_F21));
	translation_.insert(std::pair<int, int>(GLFW_KEY_F22, GLFW_KEY_F22));
	translation_.insert(std::pair<int, int>(GLFW_KEY_F23, GLFW_KEY_F23));
	translation_.insert(std::pair<int, int>(GLFW_KEY_F24, GLFW_KEY_F24));
	translation_.insert(std::pair<int, int>(GLFW_KEY_F25, GLFW_KEY_F25));
	translation_.insert(std::pair<int, int>(GLFW_KEY_UP, GLFW_KEY_UP));
	translation_.insert(std::pair<int, int>(GLFW_KEY_DOWN, GLFW_KEY_DOWN));
	translation_.insert(std::pair<int, int>(GLFW_KEY_LEFT, GLFW_KEY_LEFT));
	translation_.insert(std::pair<int, int>(GLFW_KEY_RIGHT, GLFW_KEY_RIGHT));
	translation_.insert(std::pair<int, int>(GLFW_KEY_LSHIFT, GLFW_KEY_LSHIFT));
	translation_.insert(std::pair<int, int>(GLFW_KEY_RSHIFT, GLFW_KEY_RSHIFT));
	translation_.insert(std::pair<int, int>(GLFW_KEY_LCTRL, GLFW_KEY_LCTRL));
	translation_.insert(std::pair<int, int>(GLFW_KEY_RCTRL, GLFW_KEY_RCTRL));
	translation_.insert(std::pair<int, int>(GLFW_KEY_LALT, GLFW_KEY_LALT));
	translation_.insert(std::pair<int, int>(GLFW_KEY_RALT, GLFW_KEY_RALT));
	translation_.insert(std::pair<int, int>(GLFW_KEY_TAB, GLFW_KEY_TAB));
	translation_.insert(std::pair<int, int>(GLFW_KEY_ENTER, GLFW_KEY_ENTER));
	translation_.insert(std::pair<int, int>(GLFW_KEY_BACKSPACE, GLFW_KEY_BACKSPACE));
	translation_.insert(std::pair<int, int>(GLFW_KEY_INSERT, GLFW_KEY_INSERT));
	translation_.insert(std::pair<int, int>(GLFW_KEY_DEL, GLFW_KEY_DEL));
	translation_.insert(std::pair<int, int>(GLFW_KEY_PAGEUP, GLFW_KEY_PAGEUP));
	translation_.insert(std::pair<int, int>(GLFW_KEY_PAGEDOWN, GLFW_KEY_PAGEDOWN));
	translation_.insert(std::pair<int, int>(GLFW_KEY_HOME, GLFW_KEY_HOME));
	translation_.insert(std::pair<int, int>(GLFW_KEY_END, GLFW_KEY_END));
	translation_.insert(std::pair<int, int>(GLFW_KEY_KP_0, GLFW_KEY_KP_0));
	translation_.insert(std::pair<int, int>(GLFW_KEY_KP_1, GLFW_KEY_KP_1));
	translation_.insert(std::pair<int, int>(GLFW_KEY_KP_2, GLFW_KEY_KP_2));
	translation_.insert(std::pair<int, int>(GLFW_KEY_KP_3, GLFW_KEY_KP_3));
	translation_.insert(std::pair<int, int>(GLFW_KEY_KP_4, GLFW_KEY_KP_4));
	translation_.insert(std::pair<int, int>(GLFW_KEY_KP_5, GLFW_KEY_KP_5));
	translation_.insert(std::pair<int, int>(GLFW_KEY_KP_6, GLFW_KEY_KP_6));
	translation_.insert(std::pair<int, int>(GLFW_KEY_KP_7, GLFW_KEY_KP_7));
	translation_.insert(std::pair<int, int>(GLFW_KEY_KP_8, GLFW_KEY_KP_8));
	translation_.insert(std::pair<int, int>(GLFW_KEY_KP_9, GLFW_KEY_KP_9));
	translation_.insert(std::pair<int, int>(GLFW_KEY_KP_DIVIDE, GLFW_KEY_KP_DIVIDE));
	translation_.insert(std::pair<int, int>(GLFW_KEY_KP_MULTIPLY, GLFW_KEY_KP_MULTIPLY));
	translation_.insert(std::pair<int, int>(GLFW_KEY_KP_SUBTRACT, GLFW_KEY_KP_SUBTRACT));
	translation_.insert(std::pair<int, int>(GLFW_KEY_KP_ADD, GLFW_KEY_KP_ADD));
	translation_.insert(std::pair<int, int>(GLFW_KEY_KP_DECIMAL, GLFW_KEY_KP_DECIMAL));
	translation_.insert(std::pair<int, int>(GLFW_KEY_KP_EQUAL, GLFW_KEY_KP_EQUAL));
	translation_.insert(std::pair<int, int>(GLFW_KEY_KP_ENTER, GLFW_KEY_KP_ENTER));
	translation_.insert(std::pair<int, int>(GLFW_KEY_KP_NUM_LOCK, GLFW_KEY_KP_NUM_LOCK));
	translation_.insert(std::pair<int, int>(GLFW_KEY_CAPS_LOCK, GLFW_KEY_CAPS_LOCK));
	translation_.insert(std::pair<int, int>(GLFW_KEY_SCROLL_LOCK, GLFW_KEY_SCROLL_LOCK));
	translation_.insert(std::pair<int, int>(GLFW_KEY_PAUSE, GLFW_KEY_PAUSE));
	translation_.insert(std::pair<int, int>(GLFW_KEY_LSUPER, GLFW_KEY_LSUPER));
	translation_.insert(std::pair<int, int>(GLFW_KEY_RSUPER, GLFW_KEY_RSUPER));
	translation_.insert(std::pair<int, int>(GLFW_KEY_MENU, GLFW_KEY_MENU));

	translation_.insert(std::pair<int, int>('A', 'A'));
	translation_.insert(std::pair<int, int>('B', 'B'));
	translation_.insert(std::pair<int, int>('C', 'C'));
	translation_.insert(std::pair<int, int>('D', 'D'));
	translation_.insert(std::pair<int, int>('E', 'E'));
	translation_.insert(std::pair<int, int>('F', 'F'));
	translation_.insert(std::pair<int, int>('G', 'G'));
	translation_.insert(std::pair<int, int>('H', 'H'));
	translation_.insert(std::pair<int, int>('I', 'I'));
	translation_.insert(std::pair<int, int>('J', 'J'));
	translation_.insert(std::pair<int, int>('K', 'K'));
	translation_.insert(std::pair<int, int>('L', 'L'));
	translation_.insert(std::pair<int, int>('M', 'M'));
	translation_.insert(std::pair<int, int>('N', 'N'));
	translation_.insert(std::pair<int, int>('O', 'O'));
	translation_.insert(std::pair<int, int>('P', 'P'));
	translation_.insert(std::pair<int, int>('Q', 'Q'));
	translation_.insert(std::pair<int, int>('R', 'R'));
	translation_.insert(std::pair<int, int>('S', 'S'));
	translation_.insert(std::pair<int, int>('T', 'T'));
	translation_.insert(std::pair<int, int>('U', 'U'));
	translation_.insert(std::pair<int, int>('V', 'V'));
	translation_.insert(std::pair<int, int>('W', 'W'));
	translation_.insert(std::pair<int, int>('X', 'X'));
	translation_.insert(std::pair<int, int>('Y', 'Y'));
	translation_.insert(std::pair<int, int>('Z', 'Z'));

	translation_.insert(std::pair<int, int>('1', '1'));
	translation_.insert(std::pair<int, int>('2', '2'));
	translation_.insert(std::pair<int, int>('3', '3'));
	translation_.insert(std::pair<int, int>('4', '4'));
	translation_.insert(std::pair<int, int>('5', '5'));
	translation_.insert(std::pair<int, int>('6', '6'));
	translation_.insert(std::pair<int, int>('7', '7'));
	translation_.insert(std::pair<int, int>('8', '8'));
	translation_.insert(std::pair<int, int>('9', '9'));
	translation_.insert(std::pair<int, int>('0', '0'));

	translation_.insert(std::pair<int, int>(',', ','));
	translation_.insert(std::pair<int, int>('.', '.'));
	translation_.insert(std::pair<int, int>('/', '/'));
	translation_.insert(std::pair<int, int>(';', ';'));
	translation_.insert(std::pair<int, int>('[', '['));
	translation_.insert(std::pair<int, int>(']', ']'));
}

void GLFWCALL Input::handle_keypress(int key, int press)
{
	//printf("%d, %d\n", key, press);
	Input* input = GAME->getInput();
	if(press != GLFW_PRESS && press != GLFW_RELEASE) return;
	bool result = (bool)press;

		switch(input->translate(key))
		{
			case GLFW_KEY_ESC:			input->getStatus()->esc = result; break;
			case GLFW_KEY_SPACE:		input->getStatus()->space = result; break;
			case GLFW_KEY_F1:			input->getStatus()->f1 = result; break;
			case GLFW_KEY_F2:			input->getStatus()->f2 = result; break;
			case GLFW_KEY_F3:			input->getStatus()->f3 = result; break;
			case GLFW_KEY_F4:			input->getStatus()->f4 = result; break;
			case GLFW_KEY_F5:			input->getStatus()->f5 = result; break;
			case GLFW_KEY_F6:			input->getStatus()->f6 = result; break;
			case GLFW_KEY_F7:			input->getStatus()->f7 = result; break;
			case GLFW_KEY_F8:			input->getStatus()->f8 = result; break;
			case GLFW_KEY_F9:			input->getStatus()->f9 = result; break;
			case GLFW_KEY_F10:			input->getStatus()->f10 = result; break;
			case GLFW_KEY_F11:			input->getStatus()->f11 = result; break;
			case GLFW_KEY_F12:			input->getStatus()->f12 = result; break;
			case GLFW_KEY_F13:			input->getStatus()->f13 = result; break;
			case GLFW_KEY_F14:			input->getStatus()->f14 = result; break;
			case GLFW_KEY_F15:			input->getStatus()->f15 = result; break;
			case GLFW_KEY_F16:			input->getStatus()->f16 = result; break;
			case GLFW_KEY_F17:			input->getStatus()->f17 = result; break;
			case GLFW_KEY_F18:			input->getStatus()->f18 = result; break;
			case GLFW_KEY_F19:			input->getStatus()->f19 = result; break;
			case GLFW_KEY_F20:			input->getStatus()->f20 = result; break;
			case GLFW_KEY_F21:			input->getStatus()->f21 = result; break;
			case GLFW_KEY_F22:			input->getStatus()->f22 = result; break;
			case GLFW_KEY_F23:			input->getStatus()->f23 = result; break;
			case GLFW_KEY_F24:			input->getStatus()->f24 = result; break;
			case GLFW_KEY_F25:			input->getStatus()->f25 = result; break;
			case GLFW_KEY_UP:			input->getStatus()->upArrow = result; break;
			case GLFW_KEY_DOWN:			input->getStatus()->downArrow = result; break;
			case GLFW_KEY_LEFT:			input->getStatus()->leftArrow = result; break;
			case GLFW_KEY_RIGHT:		input->getStatus()->rightArrow = result; break;
			case GLFW_KEY_LSHIFT:		input->getStatus()->leftShift = result; break;
			case GLFW_KEY_RSHIFT:		input->getStatus()->rightShift = result; break;
			case GLFW_KEY_LCTRL:		input->getStatus()->leftControl = result; break;
			case GLFW_KEY_RCTRL:		input->getStatus()->rightControl = result; break;
			case GLFW_KEY_LALT:			input->getStatus()->leftAlt = result; break;
			case GLFW_KEY_RALT:			input->getStatus()->rightAlt = result; break;
			case GLFW_KEY_TAB:			input->getStatus()->tab = result; break;
			case GLFW_KEY_ENTER:		input->getStatus()->enter = result; break;
			case GLFW_KEY_BACKSPACE:	input->getStatus()->backspace = result; break;
			case GLFW_KEY_INSERT:		input->getStatus()->insert = result; break;
			case GLFW_KEY_DEL:			input->getStatus()->deleteKey = result; break;
			case GLFW_KEY_PAGEUP:		input->getStatus()->pageUp = result; break;
			case GLFW_KEY_PAGEDOWN:		input->getStatus()->pageDown = result; break;
			case GLFW_KEY_HOME:			input->getStatus()->home = result; break;
			case GLFW_KEY_END:			input->getStatus()->end = result; break;
			case GLFW_KEY_KP_0:			input->getStatus()->kp0 = result; break;
			case GLFW_KEY_KP_1:			input->getStatus()->kp1 = result; break;
			case GLFW_KEY_KP_2:			input->getStatus()->kp2 = result; break;
			case GLFW_KEY_KP_3:			input->getStatus()->kp3 = result; break;
			case GLFW_KEY_KP_4:			input->getStatus()->kp4 = result; break;
			case GLFW_KEY_KP_5:			input->getStatus()->kp5 = result; break;
			case GLFW_KEY_KP_6:			input->getStatus()->kp6 = result; break;
			case GLFW_KEY_KP_7:			input->getStatus()->kp7 = result; break;
			case GLFW_KEY_KP_8:			input->getStatus()->kp8 = result; break;
			case GLFW_KEY_KP_9:			input->getStatus()->kp9 = result; break;
			case GLFW_KEY_KP_DIVIDE:	input->getStatus()->kpDivide = result; break;
			case GLFW_KEY_KP_MULTIPLY:	input->getStatus()->kpMultiply = result; break;
			case GLFW_KEY_KP_SUBTRACT:	input->getStatus()->kpSubtract = result; break;
			case GLFW_KEY_KP_ADD:		input->getStatus()->kpAdd = result; break;
			case GLFW_KEY_KP_DECIMAL:	input->getStatus()->kpDecimal = result; break;
			case GLFW_KEY_KP_EQUAL:		input->getStatus()->kpEqual = result; break;
			case GLFW_KEY_KP_ENTER:		input->getStatus()->kpEnter = result; break;
			case GLFW_KEY_KP_NUM_LOCK:	input->getStatus()->numLock = result; break;
			case GLFW_KEY_CAPS_LOCK:	input->getStatus()->capsLock = result; break;
			case GLFW_KEY_SCROLL_LOCK:	input->getStatus()->scrollLock = result; break;

			case GLFW_KEY_PAUSE:		input->getStatus()->pause = result; break;
			case GLFW_KEY_LSUPER:		input->getStatus()->lsuper = result; break;
			case GLFW_KEY_RSUPER:		input->getStatus()->rsuper = result; break;
			case GLFW_KEY_MENU:			input->getStatus()->menu = result; break;

			case 'A':	input->getStatus()->a = result; break;
			case 'B':	input->getStatus()->b = result; break;
			case 'C':	input->getStatus()->c = result; break;
			case 'D':	input->getStatus()->d = result; break;
			case 'E':	input->getStatus()->e = result; break;
			case 'F':	input->getStatus()->f = result; break;
			case 'G':	input->getStatus()->g = result; break;
			case 'H':	input->getStatus()->h = result; break;
			case 'I':	input->getStatus()->i = result; break;
			case 'J':	input->getStatus()->j = result; break;
			case 'K':	input->getStatus()->k = result; break;
			case 'L':	input->getStatus()->l = result; break;
			case 'M':	input->getStatus()->m = result; break;
			case 'N':	input->getStatus()->n = result; break;
			case 'O':	input->getStatus()->o = result; break;
			case 'P':	input->getStatus()->p = result; break;
			case 'Q':	input->getStatus()->q = result; break;
			case 'R':	input->getStatus()->r = result; break;
			case 'S':	input->getStatus()->s = result; break;
			case 'T':	input->getStatus()->t = result; break;
			case 'U':	input->getStatus()->u = result; break;
			case 'V':	input->getStatus()->v = result; break;
			case 'W':	input->getStatus()->w = result; break;
			case 'X':	input->getStatus()->x = result; break;
			case 'Y':	input->getStatus()->y = result; break;
			case 'Z':	input->getStatus()->z = result; break;

			case '0':	input->getStatus()->n0 = result; break;
			case '1':	input->getStatus()->n1 = result; break;
			case '2':	input->getStatus()->n2 = result; break;
			case '3':	input->getStatus()->n3 = result; break;
			case '4':	input->getStatus()->n4 = result; break;
			case '5':	input->getStatus()->n5 = result; break;
			case '6':	input->getStatus()->n6 = result; break;
			case '7':	input->getStatus()->n7 = result; break;
			case '8':	input->getStatus()->n8 = result; break;
			case '9':	input->getStatus()->n9 = result; break;

			case ',':	input->getStatus()->comma = result; break;
			case '.':	input->getStatus()->period = result; break;
			case '/':	input->getStatus()->forwardSlash = result; break;
			case ';':	input->getStatus()->semicolon = result; break;
			case '[':	input->getStatus()->leftBracket = result; break;
			case ']':	input->getStatus()->rightBracket = result; break;
		}
}

int Input::translate(int ourVal)
{
	return translation_[ourVal];
}

void Input::editTranslation(int defaultVal, int newVal)
{
	translation_[newVal] = defaultVal;
}

InputBooleans* Input::getStatus()
{
	return &status_;
}