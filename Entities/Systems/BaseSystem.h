#pragma once

#include <unordered_map>
#include <cassert>

//class BaseSystem{
//public:
//	BaseSystem();
//	virtual ~BaseSystem();
//private:
//	static unsigned int
//};

template <typename ComponentType>
class BaseSystem{
public:
	BaseSystem();
	virtual ~BaseSystem() = default;

	ComponentType& getComponent(unsigned int);
	void addComponent(unsigned int ID, const ComponentType& component);
	void removeComponent(unsigned int ID);

protected:
	std::unordered_map<unsigned int, ComponentType> components_;
};

template <typename ComponentType>
BaseSystem<ComponentType>::BaseSystem()
	:components_(){
}

template <typename ComponentType>
ComponentType& BaseSystem<ComponentType>::getComponent(unsigned int ID){
	assert(components_.count(ID) == 1 && "Component does not exsist!");
	return components_[ID];
}

template <typename ComponentType>
void BaseSystem<ComponentType>::addComponent(unsigned int ID, const ComponentType& component){
	assert(components_.count(ID) == 0 && "Component already exsists!");
	components_.emplace(ID, component);
}

template <typename ComponentType>
void BaseSystem<ComponentType>::removeComponent(unsigned int ID){
	//assert(components_.count(ID) == 1 && "Component with ID: " + ID + " does not exist!");
	components_.erase(ID);
}