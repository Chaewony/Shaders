////////////////////////////////////////////////////////////////////////////////
// Filename: inputclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _INPUTCLASS_H_
#define _INPUTCLASS_H_

#include"cameraclass.h"
#include <dinput.h>
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

////////////////////////////////////////////////////////////////////////////////
// Class name: InputClass
////////////////////////////////////////////////////////////////////////////////
class InputClass
{
public:
	InputClass();
	InputClass(const InputClass&);
	~InputClass();

	void Initialize(HINSTANCE hInstance, HWND hwnd);
	void DetectInput(double time, HWND hwnd, CameraClass* camera);

private:
	bool InitDirectInput(HINSTANCE hInstance, HWND hwnd);
	bool m_keys[256];

	LPDIRECTINPUT8 m_DirectInput;
	IDirectInputDevice8* m_DIKeyboard;
	IDirectInputDevice8* m_DIMouse;

	DIMOUSESTATE m_mouseLastState;
	
	float m_moveLeftRight;
	float m_moveBackForward;

	float m_camYaw;
	float m_camPitch;
};

#endif