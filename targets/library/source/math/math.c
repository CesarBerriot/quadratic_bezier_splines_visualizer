#include "math.h"
#define _USE_MATH_DEFINES
#include <math.h>

static float radians_to_degrees(float);

float math_compute_angle_between_vectors(sfVector2f vector1, sfVector2f vector2)
{	// https://wumbo.net/formulas/angle-between-two-vectors-2d/
	return atan2(vector1.x * vector2.y - vector1.y * vector2.x, vector1.x * vector2.x + vector1.y * vector2.y);
}

float math_compute_vector_angle(sfVector2f vector)
{	sfVector2f normalized_vector = math_normalize_vector(vector);
	return radians_to_degrees(atan2(normalized_vector.x, normalized_vector.y));
}

sfVector2f math_negate_vector(sfVector2f vector)
{	return (sfVector2f)
	{	-vector.x,
		-vector.y
	};
}

sfVector2f math_add_vectors(sfVector2f vector1, sfVector2f vector2)
{	return (sfVector2f)
	{	vector1.x + vector2.x,
		vector1.y + vector2.y
	};
}

sfVector2f math_subtract_vectors(sfVector2f vector1, sfVector2f vector2)
{	return math_add_vectors(vector1, math_negate_vector(vector2));
}

float math_compute_vector_length(sfVector2f vector)
{	return sqrt(pow(vector.x, 2) + pow(vector.y, 2));
}

sfVector2f math_divide_vector(sfVector2f vector, float factor)
{	return (sfVector2f)
	{	vector.x / factor,
		vector.y / factor
	};
}

sfVector2f math_normalize_vector(sfVector2f vector)
{	return math_divide_vector(vector, math_compute_vector_length(vector));
}

static float radians_to_degrees(float radians)
{	return radians * 180 / M_PI;
}
