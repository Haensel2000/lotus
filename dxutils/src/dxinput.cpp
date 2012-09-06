#include "..\include\dxinput.h"

using namespace DX;

/* class InputDevice */

/* private */

void InputDevice::cleanup()
{
	if (device)
	{
		device->Unacquire(); 
        device->Release();
	}
}

void InputDevice::error(const wchar_t* msg)
{
	cleanup();
	throw new Exception(msg);
}

/* public */

/* END InputDevice */




/* class KeyboardDevice */

/* private */
/* public */

KeyboardDevice::KeyboardDevice(PINPUT input, HWND windowHandle)
{
	if( FAILED( input->CreateDevice(GUID_SysKeyboard, &device, NULL) ) )
		error(L"KeyboardDevice::KeyboardDevice: CreateDevice() failed.");
	if ( FAILED( device->SetDataFormat(&c_dfDIKeyboard) ) ) 
		error(L"KeyboardDevice::KeyboardDevice: SetDataFormat() failed.");
	if ( FAILED( device->SetCooperativeLevel( windowHandle, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE ) ) )  
		error(L"KeyboardDevice::KeyboardDevice: SetCooperativeLevel() failed.");
	if ( FAILED( device->Acquire() ) )  
		error(L"KeyboardDevice::KeyboardDevice: Acquire() failed.");
}

void KeyboardDevice::update()
{
	memset(&state, 0, 256);
	if (FAILED(device->GetDeviceState(sizeof(state), &state)))
	{
		while (device->Acquire() == DIERR_INPUTLOST);
	}
}

/* END KeyboardDevice */



/* class MouseDevice */

/* private */
/* public */

MouseDevice::MouseDevice(PINPUT input, HWND windowHandle)
{
	if ( FAILED( input->CreateDevice(GUID_SysMouse, &device, NULL) ) ) 
		error(L"DXApplication::DXApplication mouse: CreateDevice() failed.");
	if ( FAILED( device->SetDataFormat(&c_dfDIMouse) ) ) 
		error(L"DXApplication::DXApplication mouse: SetDataFormat() failed.");
	if ( FAILED( device->SetCooperativeLevel( windowHandle, DISCL_EXCLUSIVE | DISCL_FOREGROUND ) ) )  
		error(L"DXApplication::DXApplication mouse: SetCooperativeLevel() failed.");
	acquire(true);
}

void MouseDevice::acquire(bool isActivated)
{
	if (isActivated)
			device->Acquire();
		else
			device->Unacquire();
}

void MouseDevice::update()
{
	memset(&state, sizeof(state), 0);
	if (FAILED(device->GetDeviceState(sizeof(DIMOUSESTATE), &state)))
	{
		while (device->Acquire() == DIERR_INPUTLOST);
	}
	for (int i = 0; i < 8; i++)
	{
		if (!buttonDown(i))
			buttonUp[i] = true;
	}
}

/* END MouseDevice */
