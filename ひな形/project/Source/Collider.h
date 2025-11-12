#pragma once
#include "../Library/GameObject.h"

namespace ColliderLibrary {
	int hittest_point_polygon_2d(VECTOR2 A, VECTOR2 B, VECTOR2 C, VECTOR2 P);
	VECTOR2 sub_vector(const VECTOR2& a, const VECTOR2& b);
}
