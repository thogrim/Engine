#pragma once

#include <unordered_map>
#include <cassert>

template <typename ComponentType>
class BaseSystem{
public:
	BaseSystem();
	virtual ~BaseSystem(){}

	ComponentType& getComponent(const unsigned int);
	void addComponent(const unsigned int ID, ComponentType& component);
	void removeComponent(const unsigned int ID);

//protected:
	std::unordered_map<unsigned int, ComponentType> components_;
};

template <typename ComponentType>
BaseSystem<ComponentType>::BaseSystem()
	:components_(){
}

template <typename ComponentType>
ComponentType& BaseSystem<ComponentType>::getComponent(const unsigned int ID){
	assert(components_.count(ID) == 1 && "Component does not exsist!");
	return components_[ID];
}

template <typename ComponentType>
void BaseSystem<ComponentType>::addComponent(const unsigned int ID, ComponentType& component){
	assert(components_.count(ID) == 0 && "Component already exsists!");
	//components_.emplace(std::piecewise_construct, std::forward_as_tuple(ID), std::forward_as_tuple(std::move(component)));
	components_.emplace(ID, std::move(component));
}

template <typename ComponentType>
void BaseSystem<ComponentType>::removeComponent(const unsigned int ID){
	//assert(components_.count(ID) == 1 && "Component with ID: " + ID + " does not exist!");
	components_.erase(ID);
}