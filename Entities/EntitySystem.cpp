#include "EntitySystem.h"
#include "Player.h"

EntitySystem::EntitySystem(Player& player)
	:transformSystem_(),
	velocitySystem_(),
	rotateSystem_(),
	collisionSystem_(),
	spriteSystem_(),
	animationSystem_(spriteSystem_),
	lastID_(0),
	freeIDs_(),
	drawHitboxes_(true),
	textures_(),
	player_(player),
	playerCollided_(false){
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
	//texture 3 for animated entity
	std::unique_ptr<sf::Texture> tex3(new sf::Texture());
	if (!tex3->loadFromFile("res/img/anim.png")){
		std::cout << "tex 3 not loaded!\n";
	}
	textures_.push_back(std::move(tex3));
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
	collisionSystem_.addComponent(ID, CollisionComponent(new VisitableRectangleShape(sf::Vector2f(30.f, 30.f)), transform));
}

void EntitySystem::createAnimatedEntity(const sf::Vector2f& position){
	//get new ID
	unsigned int ID = getNewID();

	//transform component
	sf::Transformable transformComp;
	transformComp.setPosition(position);
	transformSystem_.addComponent(ID, transformComp);
	sf::Transformable& transform = transformSystem_.getComponent(ID);

	//animation component
	sf::Vector2i frameSize(30, 30);
	AnimationComponent animComp(frameSize, 3, sf::seconds(1.f));
	animationSystem_.addComponent(ID, animComp);

	//sprite component
	SpriteComponent sprite(*textures_[2], transform);
	sprite.sprite_.setTextureRect(sf::IntRect(0,0,frameSize.x,frameSize.y));
	spriteSystem_.addComponent(ID, sprite);
}

void EntitySystem::removeEntity(unsigned int ID){
	transformSystem_.removeComponent(ID);
	velocitySystem_.removeComponent(ID);
	rotateSystem_.removeComponent(ID);
	collisionSystem_.removeComponent(ID);
	spriteSystem_.removeComponent(ID);
	animationSystem_.removeComponent(ID);
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

void EntitySystem::checkPlayerCollisions(){
	PlayerCollisionVisitor pcv(player_);
	//c is collisionSysIt
	for (const auto& c : collisionSystem_.components_){
		//if component is in players sight
		if (c.second.playerSight_ != PlayerSight::NONE){
			const VisitableShape& collisionShape = *c.second.shape_;
			pcv.sight_ = c.second.playerSight_;
			collisionShape.accept(pcv, c.second.transform_.getPosition());
			//if (pcv.collisionExists_)
			//	onPlayerCollision(c.first,c.second);
		}
	}
}

void EntitySystem::updatePlayerSight(){
	PlayerSightVisitor psv(player_);
	for (auto& collisionSysIt : collisionSystem_.components_){
		collisionSysIt.second.shape_->accept(psv, collisionSysIt.second.transform_.getPosition());
		collisionSysIt.second.playerSight_ = psv.sight_;
	}
}

void EntitySystem::update(const sf::Time& dt){
	velocitySystem_.update(dt);
	rotateSystem_.update(dt);
	animationSystem_.update(dt);
}

void EntitySystem::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	target.draw(spriteSystem_);
	if (drawHitboxes_)
		target.draw(collisionSystem_);
}
