#include "Collider.h"


Collider::Collider(sf::RectangleShape& body) : //passando body io passo un riferimento e non una variabile
  body(body)
{
}


Collider::~Collider()
{
}

bool Collider::CheckCollision(Collider & other, sf::Vector2f& direction, float push)
{
	sf::Vector2f otherPosition = other.GetPosition();
	sf::Vector2f otherHalfSize = other.GetHalfSize();
	sf::Vector2f thisPosition = GetPosition();
	sf::Vector2f thisHalfSize = GetHalfSize();

	float deltaX = otherPosition.x - thisPosition.x; //deltaX è la distanza tra i centri dei due oggetti nell'asse x
	float deltaY = otherPosition.y - thisPosition.y; //deltaY è la distanza tra i centri dei due oggetti nell'asse Y
	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x); //controllano se i due oggetti si intersecano rispetto alla x
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y); //controllano se i due oggetti si intersecano rispetto alla y

	if (intersectX < 0.0f && intersectY < 0.0f)
	{
		push = std::min(std::max(push, 0.0f), 1.0f);

		if (intersectX > intersectY) //controlla in che direzione spingere 
		{
			if (deltaX > 0.0f)
			{
				Move(intersectX * (1.0f - push), 0.0f); //spinta dell'oggetto proprio
				other.Move(-intersectX * push, 0.0f); //spinta opposta dell'altro oggetto

				direction.x = 1.0f;
				direction.y = 0.0f;
			}
			else                                                                                //asse X
			{
				Move(-intersectX * (1.0f - push), 0.0f); //spinta dell'oggetto proprio
				other.Move(intersectX * push, 0.0f);   //spinta opposta dell'altro oggetto

				direction.x = -1.0f;
				direction.y = 0.0f;
			}
		}
		else
		{
			if (deltaY > 0.0f)
			{
				Move(0.0f, intersectY * (1.0f - push)); //spinta dell'oggetto proprio
				other.Move(0.0f, -intersectY * push);   //spinta opposta dell'altro oggetto

				direction.x = 0.0f;
				direction.y = 1.0f;
			}
			else                                                                                //asse Y
			{
				Move(0.0f, -intersectY * (1.0f - push)); //spinta dell'oggetto proprio
				other.Move(0.0f, intersectY * push);  //spinta opposta dell'altro oggetto

				direction.x = 0.0f;
				direction.y = -1.0f;
			}
		
		}

		return true;
	}


	return false;
}
