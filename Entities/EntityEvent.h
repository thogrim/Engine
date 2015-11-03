#pragma once

#include <SFML/System/Vector2.hpp>

////////////////////////////////////////////////////////////
///
/// \struct EntityEvent
/// 
/// EntitySystemEvent contains all necessary information
/// about entity event that just occured. This implementation
/// is very similar to SFML event system
///
////////////////////////////////////////////////////////////
struct EntityEvent{


	//struct AnimationChangeEvent{
	//	AnimationType newType_;
	//};

	////////////////////////////////////////////////////////////
	/// \brief Velocity change parameter
	///
	////////////////////////////////////////////////////////////
	//struct VelocityChangeEvent{

	//	sf::Vector2f newVelocity_;	///< New velocity value
	//};

	enum EventType{
		//AnimationChange,	//animation change request
		VelocityChange,		//velocity change request
		//TerrainHit		//entity collided with terrain
		DestroyEntity		//destroy entity request
	};

	//EnityEvent()
	//	:uid_(0),
	//	type_(){
	//}

	unsigned int uid_;	///< unique ID of entity that created event
	EventType type_;	///< Type of the event

	union{
		//visual studio does not support unrestricted unions
		//so that's why members are in unnamed struct
		//AnimationChange 	animType_; 	///< New animation Type do display
		//struct{ VelocityChangeEvent velocity_; };	///< Entity requested velocity change
		struct{
			sf::Vector2f newVelocity_;	///< Entity requested velocity change
		};
	};
};