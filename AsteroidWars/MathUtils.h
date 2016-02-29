#pragma once
#include "SFML\Graphics.hpp"
#include <cmath>

#define PI 3.14159265359

namespace FunMath
{
	const static float Distance(const sf::Vector2f& p1, const sf::Vector2f& p2)
	{
		return std::sqrtf(std::powf(p2.x - p1.x, 2) + std::powf(p2.y - p1.y, 2));
	}

	const static float LenghtOfVector(const sf::Vector2f& p)
	{
		return std::sqrtf(std::powf(p.x, 2) + std::powf(p.y, 2));
	}

	const static float AngleOfTwoVectors(const sf::Vector2f& p1, const sf::Vector2f& p2)
	{
		return std::acosf(((p1.x * p2.x) + (p1.y * p2.y)) / (LenghtOfVector(p1) * LenghtOfVector(p2)));
	}

	const static sf::Vector2f DirectionVector(const float angle)
	{
		return sf::Vector2f(std::cosf(angle), std::sinf(angle));
	}

	const static float ToDegrees(const float radians)
	{
		return radians * (180 / PI);
	}

	const static float ToRadians(const float degrees)
	{
		return degrees * (PI / 180);
	}

	static void NormalizeVector2f(sf::Vector2f& p)
	{
		float lenght = LenghtOfVector(p);
		p.x = p.x / lenght;
		p.y = p.y / lenght;
	}
}