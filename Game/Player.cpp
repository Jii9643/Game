#include "Player.h"



Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight) : //devo mettere il costruttore di default manualmente 
	animation(texture, imageCount, switchTime) //lista di inizializzazione
{
	this->speed = speed;
	this->jumpHeight = jumpHeight;
	row = 0;
	faceRight = true;

	body.setSize(sf::Vector2f(100.0f, 150.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(206.0f, 206.0f);
	body.setTexture(texture);
}


Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	velocity.x *= 0.5f; //per non far accelerare player constantemente

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		velocity.x -= speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		velocity.x += speed;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump)
	{
		canJump = false;
		velocity.y = -sqrtf(2.0f * 981.0f * jumpHeight);
	}

	velocity.y += 981.0f * deltaTime;

	if (velocity.x == 0.0f) //se il nostro personaggio non si muove, quindi il movimento è zero allora prendo la prima riga di animazione che rappresenta lo stare fermi
	{
		row = 0;
	}
	else
	{
		row = 1; // se si muove


		if (velocity.x > 0.0f) //se il movimento sulle x è positivo allora sto andando a destra, viceversa se è negativo
			faceRight = true;
		else
			faceRight = false;
	}

	animation.Update(row, deltaTime, faceRight); //richiama se stesso e compie il movimento
	body.setTextureRect(animation.uvRect); //setta la texture del body a seconda della linea
	body.move(velocity * deltaTime); //ti va muovere il corpo
}

void Player::Draw(sf::RenderWindow& window) //ho bisogno di un riferimento perchè non ho bisogno tutte le informazioni della window
{
	window.draw(body);
}

void Player::OnCollision(sf::Vector2f direction)
{
	if (direction.x < 0.0f) //collisione parte sinistra
	{
		velocity.x = 0.0f;
	}
	else if (direction.x > 0.0f)
	{
		velocity.x = 0.0f;
	}
	if (direction.y < 0.0f) //collisione sotto
	{
		velocity.y = 0.0f;
		canJump = true;
	}
	else if (direction.y > 0.0f)
	{
		velocity.y = 0.0f; //collisione sopra
	}
}
