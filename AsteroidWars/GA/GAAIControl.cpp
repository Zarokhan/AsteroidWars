#include "GAAIControl.h"
#include "../MathUtils.h"

void GAAIControl::UpdatePerceptions(float delta, int index)
{
	Ship* ship = (Ship*)Session->ships[index];
	if (!ship)
		return;

	// determine current game evasion state
	int collisionState = -1;
	int directionState = -1;
	int distanceState = -1;

	// Store closest asteroids
	if (ship->nearest)
	{
		sf::Vector2f normDelta = ship->nearest->getPosition() - ship->getPosition();
		FunMath::NormalizeVector2f(normDelta);

		// Asteroid collision determination
		float speed = FunMath::Magnitude(ship->GetVelocity());
		float distance = ship->nearest_asteroid_distance;
		float astSpeed = FunMath::Magnitude(ship->nearest->GetVelocity());
		sf::Vector2f temp = ship->GetVelocity();
		float shpSpeedAdj = DOT(temp, normDelta) * speed;
		temp = ship->nearest->GetVelocity();
		float astSpeedAdj = DOT(temp, -normDelta) * speed;
		speed = shpSpeedAdj + astSpeedAdj;
		speed = MIN(speed, START_SPEED);
		collisionState = (int)FunMath::LERP(speed / START_SPEED, 0.f, 9.f);

		// Direction determination
		directionState = FunMath::GETSECTOR(normDelta);

		// Distance determination
		distanceState = MIN((int)(distance / ship->nearest->getTextureRect().width), 4);

	}
	if (collisionState == -1)
		currentEvasionSituation = -1;
	else
		currentEvasionSituation = (collisionState * 10) + (directionState * 18) + distanceState;
}
