#pragma once
#include <SFML\Graphics.hpp>



class Collider
{
public:
	Collider(sf::RectangleShape& body);
	~Collider();

	void Move(float dx, float dy) { body.move(dx, dy); } //usiamo la move cos� non dobbiamo rendere body come variabile pubblica 

	bool CheckCollision(Collider& other, sf::Vector2f& direction, float push);//prende in ingresso other che � l'oggetto e push che indica di quanto viene spostato(0 o pi�)

	sf::Vector2f GetPosition() { return body.getPosition(); }
	sf::Vector2f GetHalfSize() { return body.getSize() / 0.2f; }

private:
	sf::RectangleShape& body;//passaggio a riferimento
};

