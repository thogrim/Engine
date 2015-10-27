#include "AnimationSystem.h"
#include "SpriteSystem.h"

AnimationSystem::AnimationSystem(SpriteSystem& spriteSystem)
	:BaseSystem(),
	spriteSystem_(spriteSystem){
}

void AnimationSystem::update(const sf::Time& dt){
	for (auto& comp : components_){
		auto& anim = comp.second;
		if (anim.timePassed_ > anim.frameDuration_){
			if (++anim.currentFrame_ >= anim.nFrames_)
				anim.currentFrame_ = 0;
			sf::IntRect newFrame(sf::Vector2i(anim.frameSize_.x*anim.currentFrame_,0),sf::Vector2i(anim.frameSize_));
			spriteSystem_.components_.at(comp.first).sprite_.setTextureRect(newFrame);
			anim.timePassed_ = sf::Time::Zero;
		}
		comp.second.timePassed_ += dt;
	}
}