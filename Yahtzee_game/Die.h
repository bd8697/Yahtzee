#pragma once
#include <random>
#include <iostream>
#include "MySprite.h"
class Die
{
public:
	Die();
	Die(const Die& other)noexcept;
	Die(Die&& other)noexcept;
	Die& operator =(const Die& other)noexcept;
	Die& operator =(Die&& other)noexcept;
	~Die();
	const int GetFace();
	void SetFace(int argFace);
    mySprite& GetDieSprite();
	void DieRoll();
	void ReverseStateHold();
	const bool CheckHeld() const;
	const std::string* GetDisplayFaces() const;

	//added for animation
	/*void SwitchPosition();
	void SetPositions(sf::Vector2f onHoldPos, sf::Vector2f onReleasePos);
	void SetRotationAngle(float angle);*/



private:
	void EnableHeld();
	void DisableHeld();
	int RandomINT(int start, int end);
public:
	void SetDisplayFaces(const int& faceValue1);
private:
	int faceValue;
	bool held;
	mySprite dieSprite;
	std::string displayFaces[5];
	sf::Context context; // need this to declare sfml texture before we oepn a new window.



	//added for animation
	/*sf::Vector2f onHoldPosition;
	sf::Vector2f onReleasePosition;
	float rotationAngle;*/
};


