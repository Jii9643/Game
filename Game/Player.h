#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include "Collider.h"

class Player
{
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight); //il costruttore deve inizializzare questi valori
	~Player();

	void Update(float deltaTime); //deltatime è l'unico presente
	void Draw(sf::RenderWindow& window); 
	void OnCollision(sf::Vector2f direction);

	sf::Vector2f GetPosition() { return body.getPosition();} //prende la posizione del body
	Collider GetCollider() { return Collider(body); }

private:
	sf::RectangleShape body;
	Animation animation;
	unsigned int row; //è la riga corrispondente all'animazione
	float speed;
	bool faceRight; //indicherà la direzione

	sf::Vector2f velocity;
	bool canJump;
	float jumpHeight;


};

