#pragma once

#include "State.h"
#include "../World.h"

class TitleState: public State{
public:
	TitleState(Application& app);
	~TitleState();

private:
	void loadTextures();
	void loadFonts();
	void loadSound();

public:
	void onActionFinish();
	void processKeyPressed(sf::Keyboard::Key key);
	void processResized(const sf::Event::SizeEvent& size);
	void update(const sf::Time& dt);
	//void render() const;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	//ResourceHolders
	World world_;
	sf::RectangleShape shape_;

	//actions just for testing
	Action::SimpleAction* action1_;
	Action::SimpleAction* action2_;

	//actions that cause state changing
	const Action::SimpleAction* enterGameStateAction_;
};

