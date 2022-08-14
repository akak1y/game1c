#include <iostream>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>
#include <cstdlib>

using namespace sf;
using namespace std;
int main()
{
	//ШРИФТ
	Font font;
	font.loadFromFile("fonts/arial.ttf");
	Text textfps("", font, 15);
	textfps.setOutlineColor(Color::Yellow);
	textfps.setFillColor(Color::White);
	textfps.setStyle(Text::Regular);
	textfps.setPosition(1, 1);

	//ОКНО
	RenderWindow window(VideoMode(1080, 720), "game1", Style::Close);
	window.setFramerateLimit(120);
	window.setVerticalSyncEnabled(false);

	//РИСУНОК
	Texture herotexture;
	herotexture.loadFromFile("images/hero.png");

	//СПРАЙТ
	Sprite herosprite;
	herosprite.setTexture(herotexture);
	//herosprite.setTextureRect(IntRect(1 * imX, 0 * imY, 1 * imX, 1 * imY));
	herosprite.setPosition(1080/2, 720-96);
	
	Clock clock;
	
	int imX = 100, imY = 100;
	float speed = 300;
	int cadr = 0;
	float setFps = 120;
	int fps = 0;
	float boofSpriteX = 0, boofSpriteY = 0;

	while (window.isOpen())
	{
		cadr++;
		float time = clock.getElapsedTime().asMicroseconds();
		time = time / 1000;
		fps = cadr / time * 1000;

		if (time >= 1000) {
			clock.restart();
			cadr = 0;
		}


		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		herosprite.setTextureRect(IntRect(1 * imX, 0 * imY, 1 * imX, 1 * imY));
		if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::W)))){//Space
			herosprite.move(0, -speed / fps);
			herosprite.setTextureRect(IntRect(0 * imX, 1 * imY, 1 * imX, 1 * imY));
		}
		if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::A)))){
			herosprite.move(-speed / fps, 0);
			herosprite.setTextureRect(IntRect(0 * imX, 2 *imY, 1 * imX, 1 * imY));
		}
		if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::S)))){//LShift
			herosprite.move(0, speed / fps);
			herosprite.setTextureRect(IntRect(0 * imX, 3 * imY, 1 * imX, 1 * imY));
		}
		if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::D)))){
			herosprite.move(speed / fps, 0);
			herosprite.setTextureRect(IntRect(0 * imX, 0 * imY, 1 * imX, 1 * imY));
		}

		Vector2f posSprite = herosprite.getPosition();
		float posX = posSprite.x;
		float posY = posSprite.y;

		if (posY > 720 - imY) { posY = 720 - imY; }
		if (posY < 0) { posY = 0; }
		if (posX > 1080 - imX) { posX = 1080 - imX; }
		if (posX < 0) { posX = 0; }
		herosprite.setPosition(posX, posY);


		float speedX = posX - boofSpriteX;
		float speedY = posY - boofSpriteY;
		boofSpriteX = posX;
		boofSpriteY = posY;
		
		
		window.clear();
		window.draw(herosprite);

		textfps.setString("FPS: " + to_string(fps) + " | POS: " + to_string(posX) + ", " + to_string(posY) + " | SPEED: " + to_string(speedX) + ", " + to_string(speedY));
		window.draw(textfps);
		window.display();
	}

	return 0;
}