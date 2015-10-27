#include "MathUtils.h"

namespace Math{
	float distance(const sf::Vector2f& point1, const sf::Vector2f& point2){
		return sqrt(pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2));
	}
}