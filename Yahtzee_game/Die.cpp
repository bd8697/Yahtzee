#include "Die.h"

Die::Die() : faceValue{ 1 }, held{ false }
{
    DieRoll();
}

void Die::SetFace(int argFace)
{
    faceValue = argFace;
    dieSprite.SetTexture("../assetz/die_0" + std::to_string(faceValue) + ".png");
}

const int Die::GetFace()
{
	return faceValue;
}

mySprite& Die::GetDieSprite()
{
	return dieSprite;
}

void Die::DieRoll()
{
	int randomNumber = RandomINT(1, 6);
	SetFace(randomNumber);
	SetDisplayFaces(randomNumber);
}

int Die::RandomINT(int start, int end)
{
    static std::random_device rd;
    static std::mt19937 en(rd());
	std::uniform_int_distribution<int>dist(start, end);
	return dist(en);
}
void Die::ReverseStateHold()
{
	CheckHeld() ? DisableHeld() : EnableHeld();
}

void Die::EnableHeld()
{
	held = true;
}

void Die::DisableHeld()
{
	held = false;
}

const bool Die::CheckHeld() const
{
	return held;
}

Die::~Die() = default;

Die::Die(const Die & other)noexcept
{
	*this = other;
}

Die::Die(Die && other)noexcept
{
	*this = std::move(other);
}

Die & Die::operator=(const Die & other)noexcept
{
	faceValue = other.faceValue;
	held = other.held;
	return *this;
}

Die & Die::operator=(Die && other)noexcept
{
	faceValue = other.faceValue;
	held = other.held;
	other.faceValue = 1;
	other.held = false;
	return *this;
}

void::Die::SetDisplayFaces(const int& faceValue1)
{
	switch (faceValue1) {
	case 1:
		displayFaces[0] = "+-------+";
		displayFaces[1] = "|       |";
		displayFaces[2] = "|   o   |";
		displayFaces[3] = "|       |";
		displayFaces[4] = "+-------+";
		break;
	case 2:
		displayFaces[0] = "+-------+";
		displayFaces[1] = "| o     |";
		displayFaces[2] = "|       |";
		displayFaces[3] = "|     o |";
		displayFaces[4] = "+-------+";
		break;
	case 3:
		displayFaces[0] = "+-------+";
		displayFaces[1] = "| o     |";
		displayFaces[2] = "|   o   |";
		displayFaces[3] = "|     o |";
		displayFaces[4] = "+-------+";
		break;
	case 4:
		displayFaces[0] = "+-------+";
		displayFaces[1] = "| o   o |";
		displayFaces[2] = "|       |";
		displayFaces[3] = "| o   o |";
		displayFaces[4] = "+-------+";
		break;
	case 5:
		displayFaces[0] = "+-------+";
		displayFaces[1] = "| o   o |";
		displayFaces[2] = "|   o   |";
		displayFaces[3] = "| o   o |";
		displayFaces[4] = "+-------+";
		break;
	case 6:
		displayFaces[0] = "+-------+";
		displayFaces[1] = "| o   o |";
		displayFaces[2] = "| o   o |";
		displayFaces[3] = "| o   o |";
		displayFaces[4] = "+-------+";
		break;
	default:
		/*std::cout << "Error";*/
		try
		{
			if (faceValue1 > 6 || faceValue1 < 1)
				throw std::logic_error("ArgFace is not a number.");
		}
		catch (const std::logic_error & e)
		{
			std::cout << e.what() << "\n";
		}
	}
}

const std::string* Die::GetDisplayFaces() const
{
	return displayFaces;
}


//added for animation
//void Die::SwitchPosition()
//{
//	if (held == true)
//	{
//		dieSprite.theSprite.setPosition(onHoldPosition);
//	}
//	else
//	{
//		dieSprite.theSprite.setPosition(onReleasePosition);
//		dieSprite.theSprite.setRotation();
//	}
//}
//
//
//void Die::SetPositions(sf::Vector2f onHoldPos, sf::Vector2f onReleasePos)
//{
//	onHoldPosition = onHoldPos;
//	onReleasePosition = onReleasePos;
//}
//
//void Die::SetRotationAngle(float angle)
//{
//	rotationAngle = angle;
//}
//

