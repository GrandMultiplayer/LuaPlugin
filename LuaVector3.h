#ifndef __LUAVECTOR3_H__
#define __LUAVECTOR3_H__
struct Vector3 {
	float coord[3];

	Vector3(float x, float y, float z)
	{
		coord[0] = x;
		coord[1] = y;
		coord[2] = z;
	}
};

struct VecHelper
{
	template <unsigned index>
	static float get(Vector3 const* vec)
	{
		return vec->coord[index];
	}

	template <unsigned index>
	static void set(Vector3* vec, float value)
	{
		vec->coord[index] = value;
	}
};
#endif