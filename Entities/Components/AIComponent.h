#pragma once

#include <vector>
#include <memory>
#include "../EntityBehaviours/EntityBehaviour.h"

struct AIComponent{
	//AIComponent(const std::initializer_list<EntityBehaviour*>& behaviours)
	//	:behaviours_(),
	//	currentBehaviour_(0){
	//	behaviours_.reserve(behaviours.size());
	//	for (const auto& bhvr : behaviours){
	//		behaviours_.emplace_back(bhvr);
	//	}
	//}
	AIComponent(const std::vector<EntityBehaviour*>& behaviours)
		:behaviours_(),
		currentBehaviour_(0){
		behaviours_.reserve(behaviours.size());
		for (const auto& bhvr : behaviours){
			behaviours_.emplace_back(bhvr);
		}
	}
	AIComponent()
		:behaviours_(),
		currentBehaviour_(0){
	}
	AIComponent(const AIComponent&) = delete;
	AIComponent(AIComponent&& aiComp)
		:behaviours_(std::move(aiComp.behaviours_)),
		currentBehaviour_(0){
	}
	std::vector<std::unique_ptr<EntityBehaviour>> behaviours_;
	unsigned int currentBehaviour_;
};