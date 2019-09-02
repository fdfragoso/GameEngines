#include <iostream>

#include "AnimationCmp.hpp"
#include "RandomEngine.hpp"

using namespace SRE;

Animation::Animation(std::vector<Sprite*> sprites, float durationMs)
	: sprites(sprites), durationMs(durationMs)
{
	minTime = durationMs / sprites.size();
}

AnimationCmp::AnimationCmp(GameObject *gameObject)
	:Component(gameObject)
{
	isPlaying = true;
	resetAnim = false;
	currentIndex = 0;
	clockInit = 0;
}

AnimationCmp::~AnimationCmp() {
	for (auto e : animations) {
		//e.second->sprites.clear();
		delete e.second;
	}
	animations.clear();
}


void AnimationCmp::createAnim(std::string name, Animation * anim) {
	if (animations.find(name) == animations.end()) {
		animations.emplace(name, anim);
	}
}

void AnimationCmp::setAnim(std::string name) {
	if (currentAnimName == name) {
		return;
	}
	if (animations.find(name) != animations.end()) {
		currentAnimName = name;
		currentIndex = 0;
		clockInit = 0;
	}
}

void AnimationCmp::play() {
	if (!isPlaying) {
		if (resetAnim) {
			currentIndex = 0;
		}
		clockInit = clock();
	}
	isPlaying = true;
	resetAnim = false;
}

void AnimationCmp::stop() {
	isPlaying = false;
	resetAnim = true;
}

void AnimationCmp::pause() {
	isPlaying = false;
	resetAnim = false;
}

Sprite* AnimationCmp::getCurrentSprite() {
	if (animations.find(currentAnimName) != animations.end()) {
		if (clockInit == 0) {
			clockInit = clock();
		}
		auto minTime = animations[currentAnimName]->minTime;
		auto sprites = animations[currentAnimName]->sprites;
		auto currentSprite = sprites[currentIndex];
		if (isPlaying) {
			auto diffTime = (clock() - clockInit) / CLOCKS_PER_MS;
			if (diffTime >= minTime) {
				currentIndex = (currentIndex + 1) % sprites.size();
				clockInit = clock();
			}
		}
		return currentSprite;
	}
	return nullptr;
}

void AnimationCmp::setCurrentAnimDuration(float duration) {
	auto currentAnim = animations[currentAnimName];
	currentAnim->durationMs = duration;
	currentAnim->minTime = duration / currentAnim->sprites.size();
}

float AnimationCmp::getCurrentAnimDuration() {
	auto currentAnim = animations[currentAnimName];
	return currentAnim->durationMs;
}