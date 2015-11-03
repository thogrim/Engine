#pragma once

#include "EntityBehaviour.h"

class Wait: public EntityBehaviour{
public:
	Wait(const EntityEvent& ev, const sf::Time& duration);
	//~Wait();
	void update(const sf::Time& dt);
private:
	sf::Time timeLeft_;
	const sf::Time duration_;
};