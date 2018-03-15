#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Player.h"
#include "Platform.h"

static const float VIEW_HEIGHT = 512.0f; //tenere la grandezza uguale su tutti i monitor

void ResizeView(const sf::RenderWindow& window, sf::View& view) //la view rimane corretta ogni volta che la cambi
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y); //prende il rapporto della window ogni volta che cambia la grandezza
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}


int main()
{

	sf::RenderWindow window(sf::VideoMode(512, 512), "Prova", sf::Style::Default); /*costruttore base di finestra chiamato window di Sfml che contiene VideoMode,
	il quale contiene un valore di altezza e di larghezza, un nome, ed impostare uno stile(in questo caso stile di Default che comprende resize,title,close*/
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT)); //l'oggetto view deve essere inizializzato con la posizione del player e la size della finestra

	sf::Texture playerTexture;
	playerTexture.loadFromFile("Texture.png");
 

	Player player(&playerTexture, sf::Vector2u(3, 9), 0.3f, 500.0f, 200.0f); //un'istanza di un'animazione

	std::vector<Platform> platforms; //crea un vettore che contiene tutte le platform, il quale serve per evitare di scrivere la collisione con SFFADASFAS
	//il player per ogni singola tipologia di platform

	platforms.push_back(Platform(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 200.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 0.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(1000.0f, 200.0f), sf::Vector2f(500.0f, 500.0f)));

	float deltaTime = 0.0f;
	sf::Clock clock; //creo l'oggetto clock

	while (window.isOpen()) //crea un while loop per tenere aperta la finestra con un metodo
	{
		deltaTime = clock.restart().asSeconds();
		if (deltaTime > 1.0f / 20.0f)
			deltaTime = 1.0f / 20.0f;
		
		sf::Event evento; //impostiamo l'evento
			while (window.pollEvent(evento))
			{
				switch (evento.type)
				{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::Resized:
					ResizeView(window, view);
					std::cout << "Nuova larghezza: "<< evento.size.width << " Nuova altezza: "<< evento.size.height << std::endl; // mettiamo il caso in cui il tipo è quello della finestra e permette il drag e mostriamo di quanto allargo
					break;
				
				}
		}

			player.Update(deltaTime);

			sf::Vector2f direction; //questa è la direzione che passeremo alla OnCollision function


			for (Platform& platform : platforms)   //ciclo che scorre tutto il vettore platform e checka se il player entra in collisione con esse
				if (platform.GetCollider().CheckCollision(player.GetCollider(), direction, 1.0f))
					player.OnCollision(direction);

			view.setCenter(player.GetPosition());
						
			window.clear(sf::Color(150,150,150)); //permette di pulire il buffer dall'immagine precedente nel draw
			window.setView(view);
			player.Draw(window); //disegna la figura
			for (Platform& platform : platforms)
			    platform.Draw(window);
			
			window.display(); //disegna nel buffer dietro la figura effettiva del frame
	}
	return 0;
}
