#include "..\include\dxmatrix.h"
#define HALF_PI (1.570796326794897)

using namespace DX;

/* CAMERA */

D3DXMATRIX Camera::getRotationMatrix()
{
	D3DXMATRIX result;
	D3DXMatrixLookAtLH(&result, &D3DXVECTOR3(0, 0, 0), &viewingDirection, &up);
	return result;
}

void Camera::updateMatrix()
{
	D3DXMatrixLookAtLH(&matrix, &position, &lookAt, &up);
	updateVectors();
}

void Camera::updateMatrixRotation()
{
	lookAt = position + viewingDirection;
	D3DXMatrixLookAtLH(&matrix, &position, &lookAt, &up);
}

void Camera::updateVectors()
{
	D3DXVec3Normalize(&viewingDirection, &(lookAt - position));
	D3DXVECTOR3 tmp;
	D3DXVec3Normalize(&right, D3DXVec3Cross(&tmp, &up, &viewingDirection));
}

void Camera::setPosition(D3DXVECTOR3 newPosition)
{
	position = newPosition;
	updateMatrix();
}

void Camera::setLookAt(D3DXVECTOR3 newLookAt)
{
	lookAt = newLookAt;
	updateMatrix();
}

void Camera::setUp(D3DXVECTOR3 newUp)
{
	up = newUp;
	updateMatrix();
}

void Camera::move(D3DXVECTOR3 movement)
{
	position += movement;
	updateMatrixRotation();
}

void Camera::move(float distance)
{
	move(viewingDirection*distance);
}

void Camera::rotate(float angle, Axis axis)
{
	D3DXVECTOR3 xAxis(1,0,0);
	D3DXVECTOR3 yAxis(0,1,0);
	D3DXVECTOR3 zAxis(0,0,1);
	switch (axis)
	{
		case X_AXIS:		
			angleX += angle;
			if (angleX > HALF_PI)
				angleX = HALF_PI;
			if (angleX < -HALF_PI)
				angleX = -HALF_PI;
			/*tmpViewingDirection = cosa*viewingDirection - sina*up;
			tmpUp = sina*viewingDirection + cosa*up;
			viewingDirection = tmpViewingDirection;
			up = tmpUp;*/
			break;
		case Y_AXIS:
			angleY += angle;	
			/*tmpRight = cosa*right - sina*viewingDirection;
			tmpViewingDirection = sina*right + cosa*viewingDirection;
			viewingDirection = tmpViewingDirection;
			right = tmpRight;*/
			break;
		case Z_AXIS:
			angleZ += angle;
			/*tmpRight = cosa*right + sina*up;
			tmpUp = -sina*right + cosa*up;
			right = tmpRight;
			up = tmpUp;*/
			break;

	}
	float cosya = cosf(angleY);
	float sinya = sinf(angleY);
	float cosxa = cosf(angleX);
	float sinxa = sinf(angleX);
	D3DXVec3Normalize(&viewingDirection, &(sinya*xAxis + cosya*zAxis - sinxa*yAxis));
	D3DXVec3Normalize(&right, &(-sinya*zAxis + cosya*xAxis));
	D3DXVec3Normalize(&up, D3DXVec3Cross(&up, &viewingDirection, &right));
	//up = -sinxa*zAxis + cosxa*yAxis;
	updateMatrixRotation();
}

float Camera::getAngle(Axis axis)
{
	switch (axis)
	{
		case X_AXIS:
			return angleX;
		case Y_AXIS:
			return angleY;
		case Z_AXIS:
			return angleZ;
	}

}

void Camera::setData(D3DXVECTOR3 newPosition, D3DXVECTOR3 newLookAt, D3DXVECTOR3 newUp)
{
	position = newPosition;
	lookAt = newLookAt;
	up = newUp;
	updateMatrix();
}

void Camera::frontView()
{
	lookAt = D3DXVECTOR3(0, 0, 0);
	
	position.x = lookAt.x;
	position.y = lookAt.y;
	position.z = lookAt.z - 1;
	up = D3DXVECTOR3(0, 1, 0);
	updateMatrix();
	D3DXMatrixIdentity(&objectCorrection);
}

void Camera::isometricView(float angle)
{
	float a = 1.0f / cos(angle);
	position.x = lookAt.x;
	position.y = lookAt.y - 1;
	position.z = lookAt.z - sin(angle)*a;
	D3DXVec3Cross(&up, &(lookAt-position), &D3DXVECTOR3(1, 0, 0));
	updateMatrix();
}

void Camera::getViewFrustumPlanes(D3DXPLANE plane[6])
{	
	D3DXVECTOR3 v = getViewingDirection();
	D3DXVECTOR3 r = getRight();
	D3DXVECTOR3 u = getUp();
	D3DXVECTOR3 e = getPosition();
	D3DXVECTOR3 normal;
	float v_near = projMatrix->getNearClip();
	float v_far = projMatrix->getFarClip();
	float r_max = (v_near / projMatrix->getMatrix()._11);
	float u_max = (v_near / projMatrix->getMatrix()._22);
	
	// Near:
	plane[0].a = v.x;
	plane[0].b = v.y;
	plane[0].c = v.z;
	plane[0].d = -(D3DXVec3Dot(&v, &e) + v_near);

	// Far:
	plane[1].a = -v.x;
	plane[1].b = -v.y;
	plane[1].c = -v.z;
	plane[1].d = (D3DXVec3Dot(&v, &e) + v_far);

	float invLength = 1 / sqrt(v_near*v_near + r_max*r_max);
	// Left:
	normal = (v_near*r + r_max*v) * invLength;
	plane[2].a = normal.x;
	plane[2].b = normal.y;
	plane[2].c = normal.z;
	plane[2].d = -D3DXVec3Dot(&normal, &e);				

	// Right:
	normal = (-v_near*r + r_max*v) * invLength;
	plane[3].a = normal.x;
	plane[3].b = normal.y;
	plane[3].c = normal.z;
	plane[3].d = -D3DXVec3Dot(&normal, &e);

	invLength = 1 / sqrt(v_near*v_near + u_max*u_max);
	// Top:
	normal = (-v_near*u + u_max*v) * invLength;
	plane[4].a = normal.x;
	plane[4].b = normal.y;
	plane[4].c = normal.z;
	plane[4].d = -D3DXVec3Dot(&normal, &e);
	
	// Bottom:
	normal = (v_near*u + u_max*v) * invLength;
	plane[5].a = normal.x;
	plane[5].b = normal.y;
	plane[5].c = normal.z;
	plane[5].d = -D3DXVec3Dot(&normal, &e);
	
	

}


/* ---------------------------------------------------------- */


/* PROJECTION */

void Projection::updateViewingWindow()
{
	viewingWindow.x = tan(fov/2.0f)*nearClip;
	viewingWindow.y = viewingWindow.x / aspect;
}

void Projection::updateMatrix()
{
	D3DXMatrixPerspectiveFovLH(&matrix, fov, aspect, nearClip, farClip);
	device->SetTransform(D3DTS_PROJECTION, &matrix);
	updateViewingWindow();
}

void Projection::setAspect(double newAspect)
{
	aspect = newAspect;
	updateMatrix();
}

void Projection::setNearClip(double newNear)
{
	nearClip = newNear;
	updateMatrix();
}

void Projection::setFarClip(double newFar)
{
	farClip = newFar;
	updateMatrix();
}

void Projection::setFov(double newFov)
{
	fov = newFov;
	updateMatrix();
}

void Projection::setData(double newAspect, double newNearClip, double newFarClip, double newFov)
{
	aspect = newAspect;
	nearClip = newNearClip;
	farClip = newFarClip;
	fov = newFov;
}

