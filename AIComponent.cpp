#include "stdafx.h"
#include "AIComponent.h"

//Moevemnt functions
sf::Vector2f AIComponent::follow()
{
	return this->targetDir;
}

sf::Vector2f AIComponent::keepDistance(const float threshold)
{
	if (this->distance > threshold) {
		return this->targetDir;
	}
	else {
		return -this->targetDir;
	}
}

sf::Vector2f AIComponent::stayStill()
{
	return sf::Vector2f(0,0);
}

sf::Vector2f AIComponent::runAway(const float threshold)
{
	if (this->distance < threshold) {
		return -this->targetDir;
	}
	else return sf::Vector2f(0, 0);
	
}

sf::Vector2f AIComponent::roam()
{
	return this->roamDir;
}

//Constructor================
AIComponent::AIComponent(sf::Sprite& sprite, enemyType type, enemyState& state)
	:sprite(sprite), type(type), state(state)
{
	this->aggro = false;
	this->distance = 0.f;
	this->roamTimer = 0.f;
	this->roamTimerMax = 15.f; //changing roaming direction after that time

	this->roamDir = util::normalize(sf::Vector2f(rand() % 2 - 1, rand() % 2 - 1));
	switch (this->type) {
	case enemyType::REGULAR:
		this->aggroDistance = 800.f;
		break;
	case enemyType::COMMANDO:
		this->aggroDistance = 1300.f;
		break;
	case enemyType::STATIONARY:
		this->aggroDistance = 1500.f;
		break;
	case enemyType::BOSS:
		this->aggroDistance = 700.f;
		break;

	default:
		this->aggroDistance = 0.f;
		break;
	}

	this->triggerArea.setRadius(this->aggroDistance);
	this->triggerArea.setFillColor(sf::Color::Transparent);
	this->triggerArea.setOutlineThickness(3.f);
	this->triggerArea.setOutlineColor(sf::Color::Red);

	sf::Vector2f roamDirTemp(
		sf::Vector2f(
			static_cast<float>(rand() % 200) / 100 - 1.f,
			static_cast<float>(rand() % 200) / 100 - 1.f
			));
	this->roamDir = util::normalize(roamDirTemp);
}

AIComponent::~AIComponent()
{
}

const bool AIComponent::isAggro() const
{
	return this->aggro;
}

sf::Vector2f AIComponent::nextMove(const sf::Vector2f& target_dir, const float& distance)
{
	this->targetDir = target_dir;
	this->distance = distance;

	if (this->aggro == false) { //enemies roam if far away from player
		return this->roamDir;
	}
	else if (this->state == enemyState::GRAVE) { //enemies run away from player when wounded
		return this->runAway(900.f);
	}
	else { //regular moveemnt of enemes
		switch (this->type)
		{
		case enemyType::REGULAR:
			return this->follow();
			break;
		case enemyType::COMMANDO:
			return this->keepDistance(500.f);
			break;
		case enemyType::STATIONARY:
			return this->stayStill();
			break;
		case enemyType::BOSS:
			return this->follow();
			break;

		default:
			return this->follow();
			break;
		}
	}
}

void AIComponent::update(const float& dt)
{
	this->roamTimer += dt;
	if (this->distance < this->aggroDistance) { //enemies roam if far away from player
		this->aggro = true;
	}
	else this->aggro = false;

	if (this->roamTimer > this->roamTimerMax) {
		this->roamTimer = 0.f;
		sf::Vector2f roamDirTemp(
			sf::Vector2f(
				static_cast<float>(rand() % 200)/100 - 1.f,
				static_cast<float>(rand() % 200)/100 - 1.f
				));

		this->roamDir = util::normalize(roamDirTemp);
	}

	this->triggerArea.setPosition(
		this->sprite.getPosition().x + this->sprite.getGlobalBounds().width / 2 - this->triggerArea.getGlobalBounds().width/2,
		this->sprite.getPosition().y + this->sprite.getGlobalBounds().height / 2 - this->triggerArea.getGlobalBounds().height/2
		);
}

void AIComponent::render(sf::RenderTarget& target) const
{
	target.draw(this->triggerArea);
}

