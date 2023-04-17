////////////////////////////////////////////////////////////////////////////////
// Filename: inputclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "inputclass.h"


InputClass::InputClass()
{
	m_moveLeftRight = 0.0f;
	m_moveBackForward = 0.0f;
	m_camYaw = 0.0f;
	m_camPitch = 0.0f;
}


InputClass::InputClass(const InputClass& other)
{
}


InputClass::~InputClass()
{
}


void InputClass::Initialize(HINSTANCE hInstance, HWND hwnd)
{
	int i;
	

	// Initialize all the keys to being released and not pressed.
	for(i=0; i<256; i++)
	{
		m_keys[i] = false;
	}

	InitDirectInput(hInstance, hwnd);

	return;
}

bool InputClass::InitDirectInput(HINSTANCE hInstance, HWND hwnd)
{
	HRESULT hr;

	hr = DirectInput8Create(hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&m_DirectInput,
		NULL);

	hr = m_DirectInput->CreateDevice(GUID_SysKeyboard,
		&m_DIKeyboard,
		NULL);

	hr = m_DirectInput->CreateDevice(GUID_SysMouse,
		&m_DIMouse,
		NULL);

	hr = m_DIKeyboard->SetDataFormat(&c_dfDIKeyboard);
	hr = m_DIKeyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	hr = m_DIMouse->SetDataFormat(&c_dfDIMouse);
	hr = m_DIMouse->SetCooperativeLevel(hwnd, DISCL_EXCLUSIVE | DISCL_NOWINKEY | DISCL_FOREGROUND);

	return true;
}

void InputClass::DetectInput(double time, HWND hwnd, CameraClass* camera)
{
	DIMOUSESTATE mouseCurrState;

	BYTE keyboardState[256];

	m_DIKeyboard->Acquire();
	m_DIMouse->Acquire();

	m_DIMouse->GetDeviceState(sizeof(DIMOUSESTATE), &mouseCurrState);

	m_DIKeyboard->GetDeviceState(sizeof(keyboardState), (LPVOID)&keyboardState);

	if (keyboardState[DIK_ESCAPE] & 0x80)
		PostMessage(hwnd, WM_DESTROY, 0, 0);

	float speed = 15.0f * (float)time;

	if (keyboardState[DIK_A] & 0x80)
	{
		m_moveLeftRight -= speed;
	}
	if (keyboardState[DIK_D] & 0x80)
	{
		m_moveLeftRight += speed;
	}
	if (keyboardState[DIK_W] & 0x80)
	{
		m_moveBackForward += speed;
	}
	if (keyboardState[DIK_S] & 0x80)
	{
		m_moveBackForward -= speed;
	}
	if ((mouseCurrState.lX != m_mouseLastState.lX) || (mouseCurrState.lY != m_mouseLastState.lY))
	{
		m_camYaw += m_mouseLastState.lX * 0.001f;

		m_camPitch += mouseCurrState.lY * 0.001f;

		m_mouseLastState = mouseCurrState;
	}

	camera->UpdateCamera(m_camPitch, m_camYaw, &m_moveLeftRight, &m_moveBackForward);

	return;
}
