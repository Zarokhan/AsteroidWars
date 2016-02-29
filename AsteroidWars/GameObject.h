#pragma once
#include "SFML\Graphics.hpp"

#define CAMERA_WIDTH 1920
#define CAMERA_HEIGHT 1080

class GameObject : public sf::Sprite
{
	sf::Texture texture;

protected:
	float speed;
	float rotation_speed;
	sf::Vector2f velocity;
	sf::Vector2f direction;
	
	// Handles out of bound objects
	virtual void OutOfBounds() = 0;
	virtual void Movement() = 0;

public:
	GameObject(const char* path)
	{
		texture.loadFromFile(path);
		texture.setSmooth(true);
		setTexture(texture, true);

		setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	}
	virtual void Update(float delta) = 0;
	virtual ~GameObject() { }

	inline const sf::Vector2f GetDirection() const
	{
		return direction;
	}

	inline const sf::Vector2f GetVelocity() const
	{
		return velocity;
	}
};