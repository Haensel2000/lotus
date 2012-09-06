#pragma once

#include "dxinclude.h"
#include "dxbasic.h"

namespace DX
{

	class Projection
	{
		private:
			double fov;
			double aspect;
			double nearClip;
			double farClip;
			D3DXMATRIX matrix;
			PDIRECT3DDEVICE device;
			D3DXVECTOR2 viewingWindow; // the dimensions of the real viewingWindow are from -x to +x
			 // and from -y to +y
			void updateViewingWindow();
			void updateMatrix();
		public:
			Projection(PDIRECT3DDEVICE dev, double aspect, double nearClip = 1.0f, double farClip = 50.0f, double fov = D3DX_PI/4) :
			  device(dev), aspect(aspect), nearClip(nearClip), farClip(farClip), fov(fov) 
			{
				updateMatrix();
			}
			void setAspect(double newAspect);
			void setNearClip(double newNear);
			void setFarClip(double newFar);
			void setFov(double newFov);
			void setData(double newAspect, double newNearClip, double newFarClip, double newFov);

			float getAspect() { return aspect; }
			float getNearClip() { return nearClip; }
			float getFarClip() { return farClip; }
			float getFov() { return fov; }
			D3DXMATRIX getMatrix() { return matrix; }
			D3DXVECTOR2 getViewingWindow() { return viewingWindow; }
	};

	class Camera
	{
		private:
			D3DXVECTOR3 position;
			D3DXVECTOR3 lookAt;
			D3DXVECTOR3 up;
			D3DXVECTOR3 right;
			D3DXVECTOR3 viewingDirection;
			D3DXMATRIX matrix;
			D3DXMATRIX objectCorrection;
			PDIRECT3DDEVICE device;	
			Projection* projMatrix;
			float angleX;
			float angleY;
			float angleZ;	
			void updateMatrix();
			void updateMatrixRotation();
			void updateVectors();
		public:
			Camera(PDIRECT3DDEVICE dev, Projection* projMatrix) : device(dev),
				projMatrix(projMatrix), position(0.0, 0.0, -1.0), lookAt(0.0, 0.0, 1.0),
				up(0.0, 1.0, 0.0), angleX(0), angleY(0), angleZ(0)
			{			
				updateMatrix();
				D3DXMatrixIdentity(&objectCorrection);
			}
			Camera(PDIRECT3DDEVICE dev, Projection* projMatrix, D3DXVECTOR3 position,
				D3DXVECTOR3 lookAt = D3DXVECTOR3(0.0, 0.0, 1.0), D3DXVECTOR3 up = D3DXVECTOR3(0.0, 1.0, 0.0)) : device(dev), projMatrix(projMatrix),
				position(position), lookAt(lookAt), up(up), angleX(0), angleY(0), angleZ(0)
			{
				updateMatrix();
				D3DXMatrixIdentity(&objectCorrection);		
			}
			void setPosition(D3DXVECTOR3 newPosition);
			D3DXVECTOR3 getPosition() { return position; }
			void setLookAt(D3DXVECTOR3 newLookAt);
			D3DXVECTOR3 getLookAt() { return lookAt; }
			D3DXVECTOR3 getViewingDirection() { return viewingDirection; }
			void setUp(D3DXVECTOR3 newUp);
			D3DXVECTOR3 getUp() { return up; }
			D3DXVECTOR3 getRight() { return right; }
			void setData(D3DXVECTOR3 newPosition, D3DXVECTOR3 newLookAt, D3DXVECTOR3 newUp);
			void move(D3DXVECTOR3 movement);
			void move(float distance);
			void rotate(float angle, Axis axis);
			// X_AXIS: the cam. describes a rotation around the "right" vector
			// Y_AXIS: the cam. describes a rotation around the "up" vector
			// Z_AXIS: the cam. describes a rotation around the viewingdirection
			float getAngle(Axis axis);
			D3DXMATRIX getMatrix() { return matrix; }
			D3DXMATRIX getRotationMatrix();
			D3DXMATRIX getCorrectionMatrix() { return objectCorrection; }
			void frontView();
			void isometricView(float angle = D3DX_PI/4);
			void getViewFrustumPlanes(D3DXPLANE plane[6]);


	};

	
}