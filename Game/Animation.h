#pragma once
#include <SFML\Graphics.hpp>

class Animation
{
public:
	Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime); //prende un puntatore a texture, perchè siamo solo interessati alla texture, altrimenti dovremo mettere tutte le informazioni della texture
	~Animation();
	//creiamo un metodo update che prenderà in ingresso due variabili
	void Update(int row, float deltaTime, bool faceRight); //deltaTime è il tempo tra il frame precedente e quello corrente
	
public:
	sf::IntRect uvRect;//rettangolo che croppa l'immagine che ti serve nell'animazione

private:
	sf::Vector2u imageCount; //unsigned int in quanto non andrò a trovare coordinate negative, conta le varire animazioni
	sf::Vector2u currentImage; //tiene l'immagine a schermo

	float totalTime; //tempo che impiega l'animazione
	float switchTime; //tempo che impiega per cambiare animazione

};

