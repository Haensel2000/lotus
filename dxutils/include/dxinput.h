#pragma once

#include "dxinclude.h"
#include "dxbasic.h"

namespace DX
{
	
	class InputDevice
	{
		protected:
			PINPUTDEVICE device;
			virtual void cleanup();
			void error(const wchar_t* msg);
		public:
			~InputDevice() { cleanup(); }
	};
	
	class KeyboardDevice : public InputDevice
	{
		private:
			char state[256];
		public:
			KeyboardDevice( PINPUT input, HWND windowHandle );
			void update();
			bool keyDown( unsigned char key ) const { return (state[key] & 0x80) ? true : false; }
	};

	class MouseDevice : public InputDevice
	{
		private:
			DIMOUSESTATE state;
			bool buttonUp[8];
		public:
			MouseDevice( PINPUT input, HWND windowHandle );
			void update();
			void acquire(bool isActivated);
			DIMOUSESTATE getState() { return state; }
			bool buttonDown( int button) const { return (state.rgbButtons[button] & 0x80) ? true : false; }
			bool buttonClick( int button) 
			{ 
				if ((state.rgbButtons[button] & 0x80) && buttonUp[button])
				{
					buttonUp[button] = false;
					return true;
				}
				return false;
			}
			int xChange() const { return state.lX; }
			int yChange() const { return state.lY; }
			int zChange() const { return state.lZ; }
	};
}