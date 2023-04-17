////////////////////////////////////////////////////////////////////////////////
// Filename: cameraclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _CAMERACLASS_H_
#define _CAMERACLASS_H_


//////////////
// INCLUDES //
//////////////
#include <directxmath.h>

#include "AlignedAllocationPolicy.h"

using namespace DirectX;

////////////////////////////////////////////////////////////////////////////////
// Class name: CameraClass
////////////////////////////////////////////////////////////////////////////////
class CameraClass : public AlignedAllocationPolicy<16>
{
public:
	CameraClass();
	CameraClass(const CameraClass&);
	~CameraClass();

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);

	XMFLOAT3 GetPosition();
	XMFLOAT3 GetRotation();

	void Render();
	void GetViewMatrix(XMMATRIX&);

	void UpdateCamera(float camPitch, float camYaw, float* moveLeftRight, float* moveBackForward);

private:
	XMFLOAT3 m_position;
	XMFLOAT3 m_rotation;
	XMMATRIX m_viewMatrix;

	XMVECTOR m_camTarget;
	XMVECTOR m_camPosition;
	XMMATRIX m_camRotationMatrix;
	XMVECTOR m_defaultForward;
	XMVECTOR m_defaultRight;
	XMVECTOR m_camForward;
	XMVECTOR m_camRight;
	XMVECTOR m_camUp;
	XMMATRIX m_camView;
};

#endif