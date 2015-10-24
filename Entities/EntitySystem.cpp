#include "EntitySystem.h"

EntitySystem::EntitySystem()
	:transformSystem_(),
	velocitySystem_(),
	rotateSystem_(),
	collisionSystem_(),
	spriteSystem_(),	
	lastID_(0),
	freeIDs_(),
	drawHitboxes_(true),
	textures_(){
	//texture 1 for static entity
	std::unique_ptr<sf::Texture> tex1(new sf::Texture());
	if (!tex1->loadFromFile("res/img/bonus.png")){
		std::cout << "tex 1 not loaded!\n";
	}
	textures_.push_back(std::move(tex1));
	//texture 2 for rotating entity
	std::unique_ptr<sf::Texture> tex2(new sf::Texture());
	if (!tex2->loadFromFile("res/img/debug.png")){
		std::cout << "tex 2 not loaded!\n";
	}
	textures_.push_back(std::move(tex2));
}

void EntitySystem::createRotatingEntity(const sf::Vector2f& position){
	//get new ID
	unsigned int ID = getNewID();

	//transform component
	sf::Transformable transformComp;
	transformComp.setPosition(position);
	transformSystem_.addComponent(ID, transformComp);
	sf::Transformable& transform = transformSystem_.getComponent(ID);

	//rotating component
	rotateSystem_.addComponent(ID, RotateComponent(90.f,transform));

	//sprite component
	SpriteComponent sc(*textures_[0],transform);
	spriteSystem_.addComponent(ID, SpriteComponent(*textures_[1], transform));
}

void EntitySystem::createStaticEntity(const sf::Vector2f& position){
	//get new ID
	unsigned int ID = getNewID();

	//transform component
	sf::Transformable transformComp;
	transformComp.setPosition(position);
	transformSystem_.addComponent(ID, transformComp);
	sf::Transformable& transform = transformSystem_.getComponent(ID);

	//sprite component
	spriteSystem_.addComponent(ID, SpriteComponent(*textures_[0], transform));
}

void EntitySystem::createSolidEntity(const sf::Vector2f& position){
	//get new ID
	unsigned int ID = getNewID();

	//transform component
	sf::Transformable transformComp;
	transformComp.setPosition(position);
	transformSystem_.addComponent(ID, transformComp);
	sf::Transformable& transform = transformSystem_.getComponent(ID);

	//sprite component
	spriteSystem_.addComponent(ID, SpriteComponent(*textures_[0], transform));

	//collision component
	collisionSystem_.addComponent(ID, CollisionComponent(new VisitableRectangleShape(sf::Vector2f(60.f,60.f)), transform));
}

void EntitySystem::removeEntity(unsigned int ID){
	transformSystem_.removeComponent(ID);
	velocitySystem_.removeComponent(ID);
	rotateSystem_.removeComponent(ID);
	collisionSystem_.removeComponent(ID);
	spriteSystem_.removeComponent(ID);
	freeIDs_.push(ID);
}

unsigned int EntitySystem::getNewID(){
	if (!freeIDs_.empty()){
		unsigned int ID = freeIDs_.front();
		freeIDs_.pop();
		return ID;
	}
	else{
		return lastID_++;
	}
}

void EntitySystem::update(const sf::Time& dt){
	velocitySystem_.update(dt);
	rotateSystem_.update(dt);
}

void EntitySystem::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	target.draw(spriteSystem_);
	if (drawHitboxes_)
		target.draw(collisionSystem_);
}
