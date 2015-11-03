#include "EntitySystem.h"
#include "Player.h"

EntitySystem::EntitySystem(Player& player)
	:transformSystem_(),
	velocitySystem_(),
	rotateSystem_(),
	collisionSystem_(),
	spriteSystem_(),
	animationSystem_(spriteSystem_),
	aiSystem_(*this),
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

void EntitySystem::addTransformComponent(const sf::Vector2f& position){
	sf::Transformable transform{};
	transform.setPosition(position);
	//transformSystem_.addComponent(lastID_, std::move(sf::Transformable{}));
	transformSystem_.addComponent(lastID_, transform);
	//transformSystem_.components_[lastID_].setPosition(position);
}

void EntitySystem::addVelocityComponent(const sf::Vector2f& velocity){
	sf::Transformable& transform = transformSystem_.getComponent(lastID_);
	velocitySystem_.addComponent(lastID_, VelocityComponent{velocity,transform});
}

void EntitySystem::addRotateComponent(float rotationVelocity){
	sf::Transformable& transform = transformSystem_.getComponent(lastID_);
	rotateSystem_.addComponent(lastID_, RotateComponent{rotationVelocity,transform});
}

void EntitySystem::addCollisionComponent(VisitableShape* shape){
	sf::Transformable& transform = transformSystem_.getComponent(lastID_);
	collisionSystem_.addComponent(lastID_, CollisionComponent{shape,transform});
}

void EntitySystem::addSpriteComponent(const sf::Texture& texture){
	sf::Transformable& transform = transformSystem_.getComponent(lastID_);
	spriteSystem_.addComponent(lastID_, SpriteComponent{texture,transform});
}

void EntitySystem::addAnimationComponent(const sf::Vector2i& frameSize, unsigned int nFrames, const sf::Time& frameDuration){
	animationSystem_.addComponent(lastID_, AnimationComponent{frameSize,nFrames,frameDuration});
}

void EntitySystem::addAiComponent(const std::initializer_list<EntityBehaviour*>& behaviours){
	for (auto& bhvr : behaviours){
		bhvr->setObserver(&aiSystem_);
	}
	aiSystem_.addComponent(lastID_, AIComponent{behaviours});
}

void EntitySystem::createRotatingEntity(const sf::Vector2f& position){
	//get new ID
	//unsigned int ID = getNewID();

	////transform component
	//sf::Transformable transformComp;
	//transformComp.setPosition(position);
	//transformSystem_.addComponent(ID, transformComp);
	//sf::Transformable& transform = transformSystem_.getComponent(ID);

	////rotating component
	//rotateSystem_.addComponent(ID, RotateComponent(90.f,transform));

	////sprite component
	//SpriteComponent sc(*textures_[0],transform);
	//spriteSystem_.addComponent(ID, SpriteComponent(*textures_[1], transform));

	getNewID();
	addTransformComponent(position);
	addRotateComponent(90.f);
	addSpriteComponent(*textures_[0]);
}

void EntitySystem::createStaticEntity(const sf::Vector2f& position){
	////get new ID
	//unsigned int ID = getNewID();

	////transform component
	//sf::Transformable transformComp;
	//transformComp.setPosition(position);
	//transformSystem_.addComponent(ID, transformComp);
	//sf::Transformable& transform = transformSystem_.getComponent(ID);

	////sprite component
	//spriteSystem_.addComponent(ID, SpriteComponent(*textures_[0], transform));

	getNewID();
	addTransformComponent(position);
	addSpriteComponent(*textures_[0]);
}

void EntitySystem::createSolidEntity(const sf::Vector2f& position){
	//get new ID
	//unsigned int ID = getNewID();

	////transform component
	//sf::Transformable transformComp;
	//transformComp.setPosition(position);
	//transformSystem_.addComponent(ID, transformComp);
	//sf::Transformable& transform = transformSystem_.getComponent(ID);

	////sprite component
	//spriteSystem_.addComponent(ID, SpriteComponent(*textures_[0], transform));
	//
	////collision component
	//collisionSystem_.addComponent(ID, CollisionComponent(new VisitableRectangleShape(sf::Vector2f(30.f, 30.f)), transform));
	
	getNewID();
	addTransformComponent(position);
	addSpriteComponent(*textures_[1]);
	addCollisionComponent(new VisitableRectangleShape(sf::Vector2f(30.f, 30.f)));
}

void EntitySystem::createAnimatedEntity(const sf::Vector2f& position){
	////get new ID
	//unsigned int ID = getNewID();

	////transform component
	//sf::Transformable transformComp;
	//transformComp.setPosition(position);
	//transformSystem_.addComponent(ID, transformComp);
	//sf::Transformable& transform = transformSystem_.getComponent(ID);

	////animation component
	//sf::Vector2i frameSize(30, 30);
	//AnimationComponent animComp(frameSize, 3, sf::seconds(1.f));
	//animationSystem_.addComponent(ID, animComp);

	////sprite component
	//SpriteComponent sprite(*textures_[2], transform);
	//sprite.sprite_.setTextureRect(sf::IntRect(0,0,frameSize.x,frameSize.y));
	//spriteSystem_.addComponent(ID, sprite);

	getNewID();
	addTransformComponent(position);
	addAnimationComponent(sf::Vector2i(30,30), 3, sf::seconds(1.f));
	addSpriteComponent(*textures_[2]);
}

void EntitySystem::createSolidMovingEntity(const sf::Vector2f& position){
	////get new ID
	//unsigned int ID = getNewID();

	////transform component
	//sf::Transformable transformComp;
	//transformComp.setPosition(position);
	//transformSystem_.addComponent(ID, transformComp);
	//sf::Transformable& transform = transformSystem_.getComponent(ID);

	////velocity component
	//velocitySystem_.addComponent(ID, VelocityComponent(sf::Vector2f(-20.f,0),transform));

	////sprite component
	//spriteSystem_.addComponent(ID, SpriteComponent(*textures_[0], transform));

	////collision component
	//collisionSystem_.addComponent(ID, CollisionComponent(new VisitableRectangleShape(sf::Vector2f(30.f, 30.f)), transform));
	getNewID();
	addTransformComponent(position);
	addVelocityComponent(sf::Vector2f(-20.f, 0));
	addSpriteComponent(*textures_[0]);
	addCollisionComponent(new VisitableRectangleShape(sf::Vector2f(30.f, 30.f)));
}

void EntitySystem::createSimpleBehavEntity(const sf::Vector2f& position){
	getNewID();
	addTransformComponent(position);
	addVelocityComponent(sf::Vector2f(-10.f, 0.f));
	addSpriteComponent(*textures_[0]);

	//ai component
	//
	//event of first behaviour
	EntityEvent ev1;
	ev1.type_ = EntityEvent::VelocityChange;
	ev1.newVelocity_ = sf::Vector2f(100.f, 0.f);
	//event of second behaviour
	EntityEvent ev2;
	ev2.type_ = EntityEvent::VelocityChange;
	ev2.newVelocity_ = sf::Vector2f(0.f, 0.f);
	//event of third behaviour
	EntityEvent ev3;
	ev3.type_ = EntityEvent::VelocityChange;
	ev3.newVelocity_ = sf::Vector2f(-100.f, 0.f);
	//event of fourth behaviour
	EntityEvent ev4;
	ev4.type_ = EntityEvent::VelocityChange;
	ev4.newVelocity_ = sf::Vector2f(0.f, 0.f);
	//adding ai comp to ai system
	addAiComponent({
		new Wait(ev1, sf::seconds(1.f)),
		new Wait(ev2, sf::seconds(1.f)),
		new Wait(ev3, sf::seconds(1.f)),
		new Wait(ev4, sf::seconds(1.f))
	});
}

void EntitySystem::removeEntity(unsigned int ID){
	transformSystem_.removeComponent(ID);
	velocitySystem_.removeComponent(ID);
	rotateSystem_.removeComponent(ID);
	collisionSystem_.removeComponent(ID);
	spriteSystem_.removeComponent(ID);
	animationSystem_.removeComponent(ID);
	aiSystem_.removeComponent(ID);
	freeIDs_.push(ID);
}

//unsigned int EntitySystem::getNewID(){
//	if (!freeIDs_.empty()){
//		unsigned int ID = freeIDs_.front();
//		freeIDs_.pop();
//		return ID;
//	}
//	else{
//		return ++lastID_;
//	}
//}

void EntitySystem::getNewID(){
	if (!freeIDs_.empty()){
		lastID_ = freeIDs_.front();
		freeIDs_.pop();
	}
	else
		++lastID_;
}

void EntitySystem::processEvents(){
	while (!eventQueue_.empty()){
		//get event from the event queue
		EntityEvent ev = eventQueue_.front();
		switch (ev.type_){
		case EntityEvent::VelocityChange:
			velocitySystem_.components_.at(ev.uid_).velocity_ = ev.newVelocity_;
			break;
		case EntityEvent::DestroyEntity:
			removeEntity(ev.uid_);
			break;
		}
		//pop event from the queue
		eventQueue_.pop();
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
		//psv.sight_ = PlayerSight::NONE;
		collisionSysIt.second.shape_->accept(psv, collisionSysIt.second.transform_.getPosition());
		collisionSysIt.second.playerSight_ = psv.sight_;
	}
}

void EntitySystem::pushEvent(const EntityEvent& ev){
	eventQueue_.push(ev);
}

void EntitySystem::update(const sf::Time& dt){
	velocitySystem_.update(dt);
	rotateSystem_.update(dt);
	animationSystem_.update(dt);
	aiSystem_.update(dt);
}

void EntitySystem::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	target.draw(spriteSystem_);
	if (drawHitboxes_)
		target.draw(collisionSystem_);
}
