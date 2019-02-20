#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

class Transform
{
public:
	Transform() {}
	~Transform() {}

	CVector3 Position;
	CVector3 Rotation;
	CVector3 Velocity;
	//Quaternion;

};

#endif