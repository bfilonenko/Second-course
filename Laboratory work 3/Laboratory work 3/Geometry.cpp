#include "Geometry.h"


template<>
template<>
Vector3<int>::Vector3(const Vector3<float> &vector) : x(int(vector.x + 0.5f)), y(int(vector.y + 0.5f)), z(int(vector.z + 0.5f))
{

}

template<>
template<>
Vector3<float>::Vector3(const Vector3<int> &vector) : x(float(vector.x)), y(float(vector.y)), z(float(vector.z))
{

}