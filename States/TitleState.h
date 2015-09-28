#pragma once

#include "State.h"
#include "../World.h"
#include "../ActionContainer.h"

class TitleState: public State{
public:
	TitleState(Application& app);
	~TitleState();

//private:
//	void loadTextures();
//	void loadFonts();
//	void loadSound();

public:
	void onActionFinish();
	void processKeyPressed(sf::Keyboard::Key key);
	void processResized(const sf::Event::SizeEvent& size);
	void update(const sf::Time& dt);
	//void render() const;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	Action* checkEnterStateActions(Action* action);
	//ResourceHolders
	World world_;
	sf::RectangleShape shape_;

	//actions just for testing
	//Action* action1_;
	//Action* action2_;
	ActionContainer ac_;
	ActionContainer ac2_;

	//actions that cause state changing
	EnterStateAction toGameState_;
};

