#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include "Collider.h"

class Player
{
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight); //il costruttore deve inizializzare questi valori
	~Player();

	void Update(float deltaTime); //deltatime � l'unico presente
	void Draw(sf::RenderWindow& window); 
	void OnCollision(sf::Vector2f direction);

	sf::Vector2f GetPosition() { return body.getPosition();} //prende la posizione del body
	Collider GetCollider() { return Collider(body); }

private:
	sf::RectangleShape body;
	Animation animation;
	unsigned int row; //� la riga corrispondente all'animazione
	float speed;
	bool faceRight; //indicher� la direzione

	sf::Vector2f velocity;
	bool canJump;
	float jumpHeight;


};

