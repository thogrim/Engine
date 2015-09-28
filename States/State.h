#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../ActionObserver.h"
//#include "../ResourceHolder.h"

class Application;
class Action;

class State: public sf::Drawable, public ActionObserver{
public:
	State(Application& app);
	~State();
//protected:
//	virtual void loadTextures() = 0;
//	virtual void loadFonts() = 0;
//	virtual void loadSound() = 0;

public:
	virtual void onActionFinish() = 0;
	//void loadResources();
	virtual void processKeyPressed(sf::Keyboard::Key key)=0;
	virtual void processResized(const sf::Event::SizeEvent& size)=0;
	//void processAnotherEventType()=0;
	virtual void update(const sf::Time& dt) = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

protected:
	//TODO
	//assert in get method?
	class EnterStateAction{
	public:
		EnterStateAction()
			:prototype_(nullptr){
		}
		Action* get() const{
			return prototype_;
		}
		void set(Action* a){
			prototype_ = a;
		}
	private:
		Action* prototype_;
	};

	void setAction(Action* action);
	virtual Action* checkEnterStateActions(Action* action) = 0;
	//void changeState(State* state);

	Application& app_;
	Action* action_;
	sf::View camera_;
	//TextureHolder textures_;
	//FontHolder fonts_;
};