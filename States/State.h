#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../ActionObserver.h"
//#include "../ResourceHolder.h"

class Application;
namespace Action{
	class SimpleAction;
}

class State: public sf::Drawable, public ActionObserver{
public:
	State(Application& app);
	~State();
private:
	virtual void loadTextures() = 0;
	virtual void loadFonts() = 0;
	virtual void loadSound() = 0;

public:
	virtual void onActionFinish() = 0;
	void loadResources();
	virtual void processKeyPressed(sf::Keyboard::Key key)=0;
	virtual void processResized(const sf::Event::SizeEvent& size)=0;
	//void processAnotherEventType()=0;
	virtual void update(const sf::Time& dt) = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

protected:
	void setAction(Action::SimpleAction* action);

	Application& app_;
	Action::SimpleAction* action_;
	sf::View camera_;
	//TextureHolder textures_;
	//FontHolder fonts_;
};