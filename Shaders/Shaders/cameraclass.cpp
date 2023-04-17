////////////////////////////////////////////////////////////////////////////////
// Filename: cameraclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "cameraclass.h"


CameraClass::CameraClass()
{
	m_position.x = 0.0f;
	m_position.y = 0.0f;
	m_position.z = -10.0f;

	m_rotation.x = 0.0f;
	m_rotation.y = 0.0f;
	m_rotation.z = 0.0f;

	m_defaultForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	m_defaultRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	m_camForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	m_camRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	m_camUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	m_camPosition = XMLoadFloat3(&m_position);
}


CameraClass::CameraClass(const CameraClass& other)
{
}


CameraClass::~CameraClass()
{
}


void CameraClass::SetPosition(float x, float y, float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}


void CameraClass::SetRotation(float x, float y, float z)
{
	m_rotation.x = x;
	m_rotation.y = y;
	m_rotation.z = z;
}


XMFLOAT3 CameraClass::GetPosition()
{
	return m_position;
}


XMFLOAT3 CameraClass::GetRotation()
{
	return m_rotation;
}

// This uses the position and rotation of the camera to build and to update the view matrix.
void CameraClass::Render()
{
	//XMVECTOR up, position, lookAt;
	//float yaw, pitch, roll;
	//XMMATRIX rotationMatrix;

	//// Setup the vector that points upwards.
	//up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	//// Setup the position of the camera in the world.
	//position = XMLoadFloat3(&m_position);

	//// Setup where the camera is looking by default.
	//lookAt = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

	//// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	//pitch = m_rotation.x * 0.0174532925f;
	//yaw   = m_rotation.y * 0.0174532925f;
	//roll  = m_rotation.z * 0.0174532925f;

	//// Create the rotation matrix from the yaw, pitch, and roll values.
	//rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	//// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	//lookAt = XMVector3TransformCoord(lookAt, rotationMatrix);
	//up = XMVector3TransformCoord(up, rotationMatrix);

	//// Translate the rotated camera position to the location of the viewer.
	//lookAt = position + lookAt;

	//// Finally create the view matrix from the three updated vectors.
	//m_viewMatrix = XMMatrixLookAtLH(position, lookAt, up);

	return;
}


void CameraClass::GetViewMatrix(XMMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
}

void CameraClass::UpdateCamera(float camPitch, float camYaw, float* moveLeftRight, float* moveBackForward)
{
	m_camRotationMatrix = XMMatrixRotationRollPitchYaw(camPitch, camYaw, 0.0f);

	m_camTarget = XMVector3TransformCoord(m_defaultForward, m_camRotationMatrix);
	m_camTarget = XMVector3Normalize(m_camTarget);

	XMMATRIX RotateYTempMatrix;
	RotateYTempMatrix = XMMatrixRotationY(camYaw);

	m_camRight = XMVector3TransformCoord(m_defaultRight, RotateYTempMatrix);
	m_camUp = XMVector3TransformCoord(m_camUp, RotateYTempMatrix);
	m_camForward = XMVector3TransformCoord(m_defaultForward, RotateYTempMatrix);

	m_camPosition += *moveLeftRight * m_camRight;
	m_camPosition += *moveBackForward * m_camForward;

	if (*moveBackForward < 0.0f)
		m_camPosition += camPitch * m_camUp;
	else if (*moveBackForward > 0.0f)
		m_camPosition -= camPitch * m_camUp;

	XMStoreFloat3(&m_position, m_camPosition);

	*moveLeftRight = 0.0f;
	*moveBackForward = 0.0f;

	m_camTarget = m_camPosition + m_camTarget;

	m_viewMatrix = XMMatrixLookAtLH(m_camPosition, m_camTarget, m_camUp);
}
