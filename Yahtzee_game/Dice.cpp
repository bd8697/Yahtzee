#include "Dice.h"
#include "Console.h"

Dice::Dice(const short int argTotal, const int rolls) : total(argTotal), rollsLeft(rolls)
{
	for (int i = 0; i < argTotal; i++) {
		diceArray[i] = std::make_shared<Die>();
		diceContainer[i].SetTexture("../assetz/die_faded_50opac.png");

	}

	soundBuffer.loadFromFile("../assetz/tap.wav");
	tap.setBuffer(soundBuffer);
	soundBuffer2.loadFromFile("../assetz/au.wav");
	au.setBuffer(soundBuffer2);
}

Dice::~Dice() = default;

void Dice::DiceRoll()
{
	for (auto& die : diceArray)
		if (!die->CheckHeld())
			die->DieRoll();
}

std::array<std::shared_ptr<Die>, 5>& Dice::GetDiceArray()
{
    return diceArray;
}

void Dice::DecreaseRolls()
{
	rollsLeft--;
}

int Dice::GetRollsLeft()
{
	return rollsLeft;
}

void Dice::SetRollsLeft(const int& rolls)
{
	rollsLeft = rolls;
}


void Dice::Print() const
{
	int gapBetweenDie = 7;
	Console console;
	console.SetConsoleDimensions();

	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	int drawAtPos = console.GetConsoleLength() / 2 - ((diceArray[0]->GetDisplayFaces()[0].length() * 5 + gapBetweenDie * 4) / 2);
	SetConsoleTextAttribute(hConsole, 14); // 14 represents the color
	for (int i = 0; i < 5; i++) // a die is outputted on 5 lines
	{
		for (int j = 0; j < drawAtPos; j++) {
			std::cout << ' ';
		}
		for (auto& x : diceArray)
		{
			std::cout << x->GetDisplayFaces()[i];
			for (int j = 0; j < gapBetweenDie; j++) {
				std::cout << " ";
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	for (int i = 0; i < drawAtPos - 1; i++) {
		std::cout << ' ';
	}
	SetConsoleTextAttribute(hConsole, 2);
	for (auto& x : diceArray) {
		std::cout << (true ? "   HELD  " : "         ");
		for (int j = 0; j < gapBetweenDie; j++) {
			std::cout << " ";
		}
	}
	std::cout << std::endl;
}

void Dice::DrawHand(sf::RenderWindow& window, const float& scale, const float& size, const float& pozX, const float& pozY, const int& alpha)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);

	for (int i = 0; i < diceArray.size(); i++)
	{
	    std::shared_ptr<Die> die = diceArray[i];
		if (mousePos.x > (pozX + 1.5 * size * i)
			&& mousePos.x < (pozX + 1.5 * size * i + size)
			&& ((mousePos.y > (pozY / 1.5) && mousePos.y < (pozY / 1.5 + size) && !die->CheckHeld()) || (mousePos.y > (pozY) && mousePos.y < (pozY + size) && die->CheckHeld()))
			&& rollsLeft < 3
			&& sf::Mouse::isButtonPressed(sf::Mouse::Left)) // todo: store window size in variable (saves time)
		{
			if (clickedOn == i)
			{
				clickedOnCounter++;
			}
			else
			{
				clickedOnCounter = 0;
			}
			clickedOn = i;
			
			if (clickedOnCounter > 5)
			{
				au.play();
			}
			else
			{
				tap.play();
			}
			die->ReverseStateHold();
			std::cout << i << std::endl;
		}

		if (die->CheckHeld())
		{
			die->GetDieSprite().theSprite.setScale(scale, scale);
			die->GetDieSprite().theSprite.setPosition(pozX + 1.5 * size * i, pozY);
			die->GetDieSprite().theSprite.setColor(sf::Color(255, 255, 255, 255));
			window.draw(die->GetDieSprite().theSprite);
		}
		else
		{
			diceContainer[i].theSprite.setScale(scale, scale);
			diceContainer[i].theSprite.setPosition(pozX + 1.5 * size * i, pozY);
			window.draw(diceContainer[i].theSprite);

			die->GetDieSprite().theSprite.setScale(scale, scale);
			die->GetDieSprite().theSprite.setPosition(pozX + 1.5 * size * i, pozY / 1.5);
            die->GetDieSprite().theSprite.setColor(sf::Color(255, 255, 255, alpha));
            window.draw(die->GetDieSprite().theSprite);

			//added for animation
		/*	die->GetDieSprite().theSprite.setScale(scale, scale);

			switch (i)
			{
			case 0:
			{
				die->GetDieSprite().theSprite.setPosition(pozX + 1.5 * size * i, pozY/2);
				die->GetDieSprite().theSprite.setRotation(30.f);
				break;
			}
			case 1:
			{
				die->GetDieSprite().theSprite.setPosition(pozX + 1.5 * size * i, (pozY / 2)+15);
				die->GetDieSprite().theSprite.setRotation(75.f);
				break;
			}
			case 2:
			{
				die->GetDieSprite().theSprite.setPosition(pozX + 1.5 * size * i, (pozY / 2)-10);
				die->GetDieSprite().theSprite.setRotation(15.f);
				break;
			}
			case 3:
			{
				die->GetDieSprite().theSprite.setPosition(pozX + 1.5 * size * i, (pozY / 2));
				die->GetDieSprite().theSprite.setRotation(60.f);
				break;
			}
			case 4:
			{
				die->GetDieSprite().theSprite.setPosition(pozX + 1.5 * size * i, (pozY / 2)-20);
				die->GetDieSprite().theSprite.setRotation(90.f);
				break;
			}
			}

			window.draw(die->GetDieSprite().theSprite);*/
		}

	}
}


void Dice::ReleaseAllDice()
{
	for (auto& die : diceArray)
		if (die->CheckHeld())
			die->ReverseStateHold();
}

void Dice::ToggleDice(unsigned int argIndex)
{
	try
	{
		if (argIndex > 5) throw std::out_of_range("Dice array is out of bounds.");
		else diceArray[argIndex]->ReverseStateHold();
	}
	catch (std::out_of_range & e)
	{
		std::cout << e.what();
	}
}
