#pragma once
#include "SFML\Graphics.hpp"
#include <cmath>

#define PI 3.14159265359
#define DEGREES_PER_RADIAN	57.29577951f
#define MIN(a,b)    (((a) < (b)) ? (a) : (b))

namespace FunMath
{
	static float CLAMPDIR180(float dir)
	{
		float outDirAbs = fabsf(dir);
		float outDir;

		if (outDirAbs > 360.0f)
		{
			if (outDirAbs > 720.0f)
			{
				outDir = fmodf(dir, 360.0f);
			}
			else
			{
				outDir = (dir > 0.0f) ? dir - 360.0f : dir + 360.0f;
			}
			outDirAbs = fabsf(outDir);
		}
		else
		{
			outDir = dir;
		}

		if (outDirAbs > 180.0f)
		{
			if (outDir > 0.0f)
			{
				outDir -= 360.0f;
			}
			else
			{
				outDir += 360.0f;
			}
		}
		return outDir;
	}

	const static float LERP(float t, float a, float b)
	{
		return a + (b - a)*t;
	}

	#define SECTOR_SIZE 20.0f
	const static int GETSECTOR(sf::Vector2f &vec)
	{
		// Zero degree angle along the +X axis
		float dir = atan2f(vec.y, vec.x);

		float outDirAbs = fabsf(dir * DEGREES_PER_RADIAN);
		float outDir;

		if (outDirAbs > 360.0f)
		{
			if (outDirAbs > 720.0f)
			{
				outDir = fmodf(dir, 360.0f);
			}
			else
			{
				outDir = (dir > 0.0f) ? dir - 360.0f : dir + 360.0f;
			}
			outDirAbs = fabsf(outDir);
		}
		else
		{
			if (dir < 0.0f)
				outDir = dir + 360.0f;
			else
				outDir = dir;
		}

		return ((int)(dir / SECTOR_SIZE));
	}

	const static float TODEGREES(float radians)
	{
		return (radians * DEGREES_PER_RADIAN);
	}

	const static float CLAMPDIR360(float dir)
	{
		float outDirAbs = fabsf(dir);
		float outDir;

		if (outDirAbs > 360.0f)
		{
			if (outDirAbs > 720.0f)
			{
				outDir = fmodf(dir, 360.0f);
			}
			else
			{
				outDir = (dir > 0.0f) ? dir - 360.0f : dir + 360.0f;
			}
			outDirAbs = fabsf(outDir);
		}
		else
		{
			if (dir < 0.0f)
				outDir = dir + 360.0f;
			else
				outDir = dir;
		}
		return outDir;
	}

	const static float Distance(const sf::Vector2f& p1, const sf::Vector2f& p2)
	{
		return std::sqrtf(std::powf(p2.x - p1.x, 2) + std::powf(p2.y - p1.y, 2));
	}

	const static float Magnitude(const sf::Vector2f& p)
	{
		return std::sqrtf(std::powf(p.x, 2) + std::powf(p.y, 2));
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