#include "Animation.h"



Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
this->imageCount = imageCount;  //puntatore a questa classe specifica
this->switchTime = switchTime;
totalTime = 0.0f; //inizia fermo ed inizializza
currentImage.x = 0; //immagine che abbiamo nella riga

uvRect.width = texture->getSize().x / float(imageCount.x); //mette la size della texture diviso quante immagini in x

uvRect.height = texture->getSize().y / float(imageCount.y); //mette la size della texture diviso quante immagini in y
}


Animation::~Animation()
{
}

void Animation::Update(int row, float deltaTime, bool faceRight) //booleano per constatare la direzione
{
	currentImage.y = row;
	totalTime += deltaTime;  //sommo il deltaTime
	if (totalTime >= switchTime) //se il totaltime è maggiore di quello di un animazione o l'altra puoi togliere il tempo dallo switch 
	{
		totalTime -= switchTime; //animazione più fluida grazie a questa sottrazione che permette di limare il totaltime con lo switch
		currentImage.x++; //continuiamo a scorrere gli sprite
		if (currentImage.x >= imageCount.x) //guardia per permettere di non andare a prendere valori della x vuoti, ma riniziare alla prima animazione
		{
			currentImage.x = 0;
		}
	}


	uvRect.top  = currentImage.y * uvRect.height; //prende la posizione dell'immagine partendo da in alto a sinistra e la croppa con l'altezza

	if (faceRight)
	{
		uvRect.left = currentImage.x * uvRect.width;
		uvRect.width = abs(uvRect.width);
	}
	else
	{
		uvRect.left = (currentImage.x + 1) * abs(uvRect.width); //per impostare il topleft corner come se fosse quello in alto a destra, ma ora bisogna flippare
		//usiamo abs per non permettere al top left corner di essere negativo una volta moltiplicato
		uvRect.width = -abs(uvRect.width);
	}
}
