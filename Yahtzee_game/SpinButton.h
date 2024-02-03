#include <SFML\Window\Mouse.hpp>
#include "mySprite.h"
#include <SFML\Audio\Sound.hpp>
#include <SFML\Audio\SoundBuffer.hpp>

class SpinButton {

public:
	SpinButton();
	bool Spin(sf::RenderWindow& window, sf::Clock& clock, const int& rolls, const bool canSpin);
	void SetPosition(sf::RenderWindow& window);
	void UpdateRolls(const int& rolls, sf::RenderWindow& window);

private:
	mySprite spinButton;
	sf::Vector2i mousePos;
	bool inButton = false;
	int maxLoops = 3;
	int loops = 0;
	sf::Text rollsLeft;
	sf::Font font;
	sf::SoundBuffer soundBuffer;
	sf::Sound roll;

	double lastTick;
};