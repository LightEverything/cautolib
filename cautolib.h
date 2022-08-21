#ifndef CAUTO_LIB
#define CAUTO_LIB

#include <iostream>
#include <cstdarg>
#include <windows.h>

namespace cautolib
{
	enum KeyValue
	{
		KeyBack = 0x08,
		KeyTab = 0x09,
		KeyEnter = 0x0D,
		KeyShitf = 0x10,
		KeyCtrl = 0x11,
		KeyAlt = 0x12,
		KeyCap = 0x14,
		KeyEsc = 0x1B,
		KeyPageUp = 0x21,
		KeyPageDown = 0x22,
		KeyEnd = 0x23,
		KeyHome = 0x24,
		KeyLeft = 0x25,
		KeyRight = 0x27,
		KeyUp = 0x26,
		KeyDown = 0x28,
		KeySelect = 0x29,
		KeyPrint = 0x2A,
		KeyDel = 0x2E,
		KeyPrtSc = 0x2C,
		KeySpace = 0x20,
		Key0 = 0x30,
		Key1 = 0x31,
		Key2 = 0x32,
		Key3 = 0x33,
		Key4 = 0x34,
		Key5 = 0x35,
		Key6 = 0x36,
		Key7 = 0x37,
		Key8 = 0x38,
		Key9 = 0x39,
		KeyA = 0x41,
		KeyB = 0x42,
		KeyC = 0x43,
		KeyD = 0x44,
		KeyE = 0x45,
		KeyF = 0x46,
		KeyG = 0x47,
		KeyH = 0x48,
		KeyI = 0x49,
		KeyJ = 0x4A,
		KeyK = 0x4B,
		KeyL = 0x4C,
		KeyM = 0x4D,
		KeyN = 0x4E,
		KeyO = 0x4F,
		KeyP = 0x50,
		KeyQ = 0x51,
		KeyR = 0x52,
		KeyS = 0x53,
		KeyT = 0x54,
		KeyU = 0x55,
		KeyV = 0x56,
		KeyW = 0x57,
		KeyX = 0x58,
		KeyY = 0x59,
		KeyZ = 0x5A,
		KeyLWIN = 0x5B,
		KeyRWIN = 0x5C,
		KeyF1 = 0x70,
		KeyF2 = 0x71,
		KeyF3 = 0x72,
		KeyF4 = 0x73,
		KeyF5 = 0x74,
		KeyF6 = 0x75,
		KeyF7 = 0x76,
		KeyF8 = 0x77,
		KeyF9 = 0x78,
		KeyF10 = 0x79,
		KeyF11 = 0x7A,
		KeyF12 = 0x7B,
		KeyNumlock = 0x90,
		KeyScrlock = 0x91,
		KeyLCtrl = 0xA2,
		KeyRCtrl = 0xA3,
		KeyLAtl = 0xA4 ,
		KeyRAtl = 0xA5,
		KeyLShift = 0xA0,
		KeyRShift = 0xA1,
	};

	enum KeyStatus
	{
		KeysUp = KEYEVENTF_KEYUP,
		KeysDown = 0x0000
	};

	namespace base
	{
		class BaseInput
		{
		public:
			BaseInput() {}
			virtual ~BaseInput() {}
			virtual bool input() = 0;
		};
	}

	namespace keyboard
	{
		using base::BaseInput;
		
		class VirtualKeyBoard : public BaseInput
		{
		public:

			VirtualKeyBoard() {}
			~VirtualKeyBoard() {}

			// 解除接口类
			virtual bool input(){ return false;}

			virtual bool input(const KeyValue& k)
			{
				INPUT userin[2] = {};
				// 按下
				userin[0].type = INPUT_KEYBOARD;
				userin[0].ki.wVk = k;
				userin[0].ki.dwFlags = KeyStatus::KeysDown;
				// 释放
				userin[1].type = INPUT_KEYBOARD;
				userin[1].ki.wVk = k;
				userin[1].ki.dwFlags = KeyStatus::KeysUp;

				return SendInput(ARRAYSIZE(userin), userin, sizeof(INPUT));
			}

			virtual bool input(const int num, ...)
			{
			    INPUT* userin = new INPUT[num * 2] {{0}};
				va_list plist;
				va_start(plist, num);

				int tmp = num;
				for (int i = 0; i < num; i++)
				{
					//  获取 k 的参数
					auto k = va_arg(plist, int);
					userin[i].type = INPUT_KEYBOARD;
					userin[i].ki.wVk = k;
					userin[i].ki.dwFlags = KeyStatus::KeysDown;

					userin[i + num].type = INPUT_KEYBOARD;
					userin[i + num].ki.wVk = k;
					userin[i + num].ki.dwFlags = KeyStatus::KeysUp;
				}

				bool reflag = SendInput(2 * num, userin, sizeof(INPUT));
				va_end(plist);
				delete[] userin;
				return reflag;
			}

			virtual bool fixInput(const KeyValue& k, const KeyStatus& st)
			{
				INPUT userin[1] = {};
				userin[0].type = INPUT_KEYBOARD;
				userin[0].ki.wVk = k;
				userin[0].ki.dwFlags = st;
				return SendInput(ARRAYSIZE(userin), userin, sizeof(INPUT));
			}

		private:
			// 不允许复制构造函数
			VirtualKeyBoard(VirtualKeyBoard& tmp) {}
			// 不允许赋值运算符号
			void operator=(VirtualKeyBoard& tmp) {}
		};
	}

	namespace setting
	{

	}
	
	namespace mouse
	{

	}
	
	namespace error
	{

	}

}

#endif // !CAUTO_LIB
