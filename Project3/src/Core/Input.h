#ifndef INPUT_H
#define INPUT_H

#include "Includes.h"
#include <map>

class InputBooleans
{
public:
	//special keys
	bool space;
	bool esc;
	bool f1;
	bool f2;
	bool f3;
	bool f4;
	bool f5;
	bool f6;
	bool f7;
	bool f8;
	bool f9;
	bool f10;
	bool f11;
	bool f12;
	bool f13;
	bool f14;
	bool f15;
	bool f16;
	bool f17;
	bool f18;
	bool f19;
	bool f20;
	bool f21;
	bool f22;
	bool f23;
	bool f24;
	bool f25;
	bool upArrow;
	bool downArrow;
	bool leftArrow;
	bool rightArrow;
	bool leftShift;
	bool rightShift;
	bool leftControl;
	bool rightControl;
	bool leftAlt;
	bool rightAlt;
	bool tab;
	bool enter;
	bool backspace;
	bool insert;
	bool deleteKey;
	bool pageUp;
	bool pageDown;
	bool home;
	bool end;
	bool kp0;
	bool kp1;
	bool kp2;
	bool kp3;
	bool kp4;
	bool kp5;
	bool kp6;
	bool kp7;
	bool kp8;
	bool kp9;
	bool kpDivide;
	bool kpMultiply;
	bool kpAdd;
	bool kpSubtract;
	bool kpDecimal;
	bool kpEqual;
	bool kpEnter;
	bool numLock;
	bool capsLock;
	bool scrollLock;

	//not actual keys...likely for a gamepad
	bool pause;
	bool lsuper;
	bool rsuper;
	bool menu;

	//letters
	bool a;
	bool b;
	bool c;
	bool d;
	bool e;
	bool f;
	bool g;
	bool h;
	bool i;
	bool j;
	bool k;
	bool l;
	bool m;
	bool n;
	bool o;
	bool p;
	bool q;
	bool r;
	bool s;
	bool t;
	bool u;
	bool v;
	bool w;
	bool x;
	bool y;
	bool z;

	//numbers
	bool n1;
	bool n2;
	bool n3;
	bool n4;
	bool n5;
	bool n6;
	bool n7;
	bool n8;
	bool n9;
	bool n0;

	//other
	bool comma;
	bool period;
	bool forwardSlash;
	bool semicolon;
	bool leftBracket;
	bool rightBracket;
};

class Input
{
private:
	InputBooleans status_;
	std::map<int, int> translation_;
	

	void Init();

public:
	Input(void);
	~Input();

	InputBooleans* getStatus();

	int translate(int ourVal);
	void editTranslation(int defaultVal, int newVal);
	static void GLFWCALL handle_keypress(int key, int press);
};


#endif