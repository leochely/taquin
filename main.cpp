/* CSCI 261 : Final Project : Numbers puzzle
*
* Author: Leo CHELY
*
* The game of numbers puzzle (also called "taquin" in French, that's why the class is called taquin)
*
*/

#include <iostream>
#include <string>
using namespace std;
#include "Taquin.h"
#include "Leaderboard.h"
#include <SFML/Graphics.hpp>
using namespace sf;

int main() {
	Taquin taquin;
	float positionX[4]; // Arrays for the positions of the numbers
	float positionY[4];
	Event event;
	
	for (int i = 0; i < 4; ++i) { // Creates the positions for the numners
		positionX[i] = float(640) / float(4)*i + float(60);
		positionY[i] = float(640) / float(4)*i + float(55);
	}

	Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		cerr << "Couldn't load the font";
	}

	Texture texture;
	texture.setSmooth(true);
	if (!texture.loadFromFile("image.png")){
		cerr << "Couldn't load the texture" << endl;
	}

	taquin.Introduction(font);

    RenderWindow window(VideoMode(640, 640), "Taquin Ultimate HD Edition Prenium"); //Game window

    while (window.isOpen()) {
        window.clear();
		Sprite sprite;
		sprite.setOrigin(Vector2f(100.f, 117.f));
		sprite.scale(2.2f, 2.2f);
		sprite.setTexture(texture);
		sprite.setPosition(Vector2f(float(320), float(300)));
		window.draw(sprite);

		for (int i = 1; i < 4; ++i) { // Draws the horizontal lines
			RectangleShape line;
			line.setSize(Vector2f(float(640), 10));
			line.setPosition(Vector2f(0, float(640) / float(4)*float(i)));
			line.setFillColor(Color::White);
			window.draw(line);
		}

		for (int i = 1; i < 4; ++i) { // Draws the vertical lines
			RectangleShape line;
			line.setSize(Vector2f(10, float(640)));
			line.setPosition(Vector2f(float(640) / float(4)*float(i),0));
			line.setFillColor(Color::White);
			window.draw(line);
		}

		for (int i = 0; i < 4; ++i) { // Draws the numbers at the right position
			for (int j = 0; j < 4; ++j) {
				Text text;
				text.setFont(font);
				text.setCharacterSize(float(50));
				text.setPosition(Vector2f(positionX[j], positionY[i]));
				text.setString(taquin.getNumber(i,j));
				text.setFillColor(Color::White);
				window.draw(text);
			}
		} 
		
		if (taquin.isCompleted()) { // Closes the window if the game is completed
			window.close();
		}
 
        window.display();

        
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

			if (event.type == Event::MouseButtonPressed) {  // Gets the position of the click to modify the array
				if (event.mouseButton.button == Mouse::Left) {
					taquin.moreMoves();
					if (event.mouseButton.x < (float(640) / float(4))) {
						if (event.mouseButton.y < (float(640) / float(4))) {
							taquin.Play(1, 1);
						}
						else if (event.mouseButton.y < (float(2)*float(640) / float(4))) {
							taquin.Play(2, 1);
						}
						else if (event.mouseButton.y < (float(3)*float(640) / float(4))) {
							taquin.Play(3, 1);
						}
						else {
							taquin.Play(4,1);
						}
					}
					else if (event.mouseButton.x < (float(2)*float(640) / float(4))) {
						if (event.mouseButton.y < (float(640) / float(4))) {
							taquin.Play(1,2);
						}
						else if (event.mouseButton.y < (float(2)*float(640) / float(4))) {
							taquin.Play(2, 2);
						}
						else if (event.mouseButton.y < (float(3)*float(640) / float(4))) {
							taquin.Play(3, 2);
						}
						else {
							taquin.Play(4,2);
						}
					}
					else if (event.mouseButton.x < (float(3)*float(640) / float(4))) {
						if (event.mouseButton.y < (float(640) / float(4))) {
							taquin.Play(1, 3);
						}
						else if (event.mouseButton.y < (float(2)*float(640) / float(4))) {
							taquin.Play(2,3);
						}
						else if (event.mouseButton.y < (float(3)*float(640) / float(4))) {
							taquin.Play(3, 3);
						}
						else {
							taquin.Play(4,3);
						}
					}
					else if (event.mouseButton.x < (float(4)*float(640) / float(4))) {
						if (event.mouseButton.y < (float(640) / float(4))) {
							taquin.Play(1,4);
						}
						else if (event.mouseButton.y < (float(2)*float(640) / float(4))) {
							taquin.Play(2,4);
						}
						else if (event.mouseButton.y < (float(3)*float(640) / float(4))) {
							taquin.Play(3,4);
						}
						else {
							taquin.Play(4, 4);
						}
					}
				}
			}
        }
    }

	if (taquin.isCompleted()) { // When the game is completed, opens an other window to congratulate the player
		RenderWindow window2(VideoMode(700, 100), "gg bro");
		while (window2.isOpen()) {
			window2.clear();

			Text text;
			text.setFont(font);
			text.setCharacterSize(float(25));
			text.setPosition(Vector2f(float(30),float(25)));
			text.setString("Congratulations! You won this game in: "+taquin.getMoves()+" moves!");
			text.setFillColor(Color::White);
			window2.draw(text);
		
			window2.display();

			while (window2.pollEvent(event)) {
				if (event.type == Event::Closed)
					window2.close();
			}
		}
		Leaderboard leaderboard;
		leaderboard.getInput();
		leaderboard.update(stoi(taquin.getMoves()));
		leaderboard.show();

	}
	else { // If the player quitted the game, opens a window to display a message
		RenderWindow window3(VideoMode(300, 100), "You gave up :(");
		while (window3.isOpen()) {
			window3.clear();

			Text text;
			text.setFont(font);
			text.setCharacterSize(float(25));
			text.setPosition(Vector2f(float(25), float(25)));
			text.setString("Come try again later! ;)");
			text.setFillColor(Color::White);
			window3.draw(text);

			window3.display();

			while (window3.pollEvent(event)) {
				if (event.type == Event::Closed)
					window3.close();
			}
		}

	}

    return EXIT_SUCCESS;
}
