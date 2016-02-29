#pragma once
#include "GameObject.h"

#define PROJECTILE_SPEED 50

class Projectile : public GameObject
{
	bool isDead = false;
	void AdjustRotation();

protected:
	virtual void OutOfBounds() override;
	virtual void Movement() override;

public:
	Projectile(const sf::Vector2f _position, const sf::Vector2f _direction);
	~Projectile();
	virtual void Update(float delta) override;

	inline const bool IsDead() const
	{
		return isDead;
	}
};