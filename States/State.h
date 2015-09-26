#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
//#include "../ResourceHolder.h"

class Application;

class State: public sf::Drawable{
public:
	State(Application& app);
	~State();
private:
	virtual void loadTextures() = 0;
	virtual void loadFonts() = 0;
	virtual void loadSound() = 0;

public:
	void loadResources();
	virtual void processKeyPressed(sf::Keyboard::Key key)=0;
	virtual void processResized(const sf::Event::SizeEvent& size)=0;
	//void processAnotherEventType()=0;
	virtual void update(const sf::Time& dt) = 0;
	//virtual void render() const = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

protected:
	Application& app_;
	sf::View camera_;
	//TextureHolder textures_;
	//FontHolder fonts_;
};

