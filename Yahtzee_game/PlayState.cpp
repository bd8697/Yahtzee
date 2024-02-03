#include "PlayState.h"
#include "GameOver.h"

#include "../Winners/Winners/WinnersHierarchy.h"

PlayState::PlayState(GameDataRef data, Game& game) : _data(data), _game(game)
{

}

void PlayState::Init()
{
	_data->assets.LoadFont("Button font", "../assetz/Fonts/Angelina Alt Demo.ttf");
	// die texture is 86 x 86 pixels. die should be 10% of window size, so die is the perfect size for a window size of 860 x 860 pixels. Scale die for any other window size.
	dieScale = (float)(_data->window.getSize().x / (scaleDie.GetDieSprite().theSprite.getGlobalBounds().width * 10));
	dieSize = scaleDie.GetDieSprite().theSprite.getGlobalBounds().width * dieScale;
	drawAtX = (_data->window.getSize().x - (5 + 2.5) * dieSize) / 2; //start drawing at (windowsize - whole containersize) / 2
	drawAtY = 700 * dieScale;
	// we can resize the whole window based on the scale, but we got no time fo dat

	int fontSize = _data->window.getSize().x / 50;
	//try {
	//	font.loadFromFile("../assetz/Fonts/Righteous-Regular.ttf");
	//}
	//catch (int e) {
	//	std::cout << "Font could not be loaded.";
	//}
	font = _data->assets.GetFont("Buttons font2");
	text.setFont(font);
	text.setCharacterSize(fontSize);
	text.setFillColor(sf::Color(252, 247, 94));
	text.setStyle(sf::Text::Bold);
	text.setPosition(0, 0);

	alertText.setFont(font);
	alertText.setCharacterSize(14);
	alertText.setString("Roll");
	alertText.setFillColor(sf::Color::White);
	alertText.setStyle(sf::Text::Regular);
	alertText.setPosition((_data->window.getSize().x - alertText.getLocalBounds().width) / 2, _data->window.getSize().y / 3.95);

	playerTurn.setFont(font);
	playerTurn.setCharacterSize(_data->window.getSize().x / 25);
	playerTurn.setFillColor(sf::Color(252, 247, 94));
	playerTurn.setStyle(sf::Text::Bold);
	playerTurn.setPosition(_data->window.getSize().x / 3, _data->window.getSize().y / 2.25);

	timeText.setFont(font);
	timeText.setCharacterSize(22);
	timeText.setFillColor(sf::Color::White);

	//Background music button

	if (!music.openFromFile("../assetz/backgroundMusic.ogg"))
	{
		std::cout << "Error on loading sound!\n";
	}
	else
	{
		music.setVolume(5);
		music.play();
	}
	soundButton->SetTextureOn("../assetz/Sound/SoundOff.png");
	soundButton->SetTextureOff("../assetz/Sound/SoundOn.png");
	soundButton->ChangeTexture(musicOn);
	soundButton->SetPosition({ 5.0f,  _data->window.getSize().y - 30.0f });
	musicOn = !musicOn;

	//Spin button
	spinButton.SetPosition(_data->window);

	//Game over
	_data->assets.LoadTexture("Game Over container", "../assetz/rounded-rectangle.png");
	_data->assets.LoadTexture("Crown", "../assetz/crown.png");

	container.setTexture(_data->assets.GetTexture("Game Over container"));
	container.scale(0.7f, 0.7f);
	container.setPosition((_data->window.getSize().x / 2) - (container.getGlobalBounds().width/2), (_data->window.getSize().y / 2) - (container.getGlobalBounds().height/2));

	winnerName.setFont(font);
	winnerName.setCharacterSize(50);
	winnerName.setString("player");
	winnerName.setFillColor(sf::Color::White);
	winnerName.setStyle(sf::Text::Regular);
	winnerName.setPosition(_data->window.getSize().x / 2 - container.getGlobalBounds().width / 3.5, container.getPosition().y +(container.getGlobalBounds().height/2.5)); //depends on container


	winnerScore.setFont(font);
	winnerScore.setCharacterSize(50);
	winnerScore.setFillColor(sf::Color::White);
	winnerScore.setPosition(_data->window.getSize().x / 2- container.getGlobalBounds().width/3.7, winnerName.getPosition().y +(container.getGlobalBounds().height/5)); //depends on winnerName and container


	crown.setTexture(_data->assets.GetTexture("Crown"));
	crown.scale(0.2f, 0.2f);
	crown.setPosition(_data->window.getSize().x / 2 - crown.getGlobalBounds().width/2, winnerName.getPosition().y -(crown.getGlobalBounds().height/1.2));//depends on winerName

	


	
}

void PlayState::HandleInput()
{
}

void PlayState::Update(float dt)
{
	sf::Event event;

	while (this->_data->window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
		{
			this->_data->window.close();

			break;
		}
		case sf::Event::MouseButtonPressed:
		{
			if (soundButton->IsMouseOver(this->_data->window)) {

				if (!musicOn)
				{
					_game.getCurrentPlayer()->GetDice().SetRollsLeft(3);
					_game.nextPlayer();
					spinButton.UpdateRolls(_game.getCurrentPlayer()->GetDice().GetRollsLeft(), this->_data->window);
					music.pause();
					soundButton->ChangeTexture(musicOn);
					musicOn = true;
				}
				else
				{
					music.play();
					soundButton->ChangeTexture(musicOn);
					musicOn = false;
				}
			}
		}
		break;
		}
	}
}

void PlayState::Draw(float dt)
{
//	if (false)
	if (!_game.CheckForGameOver())
	{
		_data->window.clear();
		_data->window.draw(backgroundgr, 4, sf::Quads);
		std::shared_ptr<Player> player = _game.getCurrentPlayer();
		if (player->GetScoreTable().DrawTable(this->_data->window, this->_data->window.getSize().x / 30, this->_data->window.getSize().y / 30, text, timer, player->GetDice().GetRollsLeft()))
		{
			player->GetDice().ReleaseAllDice();
			player->RollDice();
			player->GetDice().SetRollsLeft(3);
			_game.nextPlayer();
			spinButton.UpdateRolls(player->GetDice().GetRollsLeft(), this->_data->window);
			_roundClock.restart();
			roundSeconds = 0;
			alertTextAlpha = 100;
			altertTextReverse = false;
		}
		player->GetDice().DrawHand(this->_data->window, dieScale, dieSize, drawAtX, drawAtY, alpha);
		if (alpha < 255)
		{
			alpha++;
		}
		//  std::cout<<alpha;
	 //	timer++;
		soundButton->Draw(_data->window);

		playerTurn.setString(player->GetName() + "'s turn");
		playerTurn.setPosition((this->_data->window.getSize().x - playerTurn.getLocalBounds().width) / 2, _data->window.getSize().y / 2.25);
		_data->window.draw(playerTurn);

		auto& diceArray = player->GetDice().GetDiceArray();

		elapsedTime = _clock.getElapsedTime();

		minutes = elapsedTime.asSeconds() / 60;
		seconds = floor(elapsedTime.asSeconds() - minutes * 60);

		roundSeconds = _roundClock.getElapsedTime().asSeconds();

		minutesString = std::to_string(minutes);

		if (seconds < 10) {
			secondsString = '0' + std::to_string(seconds);
		}
		else {
			secondsString = std::to_string(seconds);
		}

		if (minutes < 10) {
			minutesString = '0' + std::to_string(minutes);
		}
		else {
			minutesString = std::to_string(minutes);
		}

		if (roundSeconds > 3 && player->GetDice().GetRollsLeft() == 3) {
			
			if (alertTextAlpha <= 100) {
				altertTextReverse = false;

			}

			if (alertTextAlpha > 250) {
				altertTextReverse = true;
			}

			if (!altertTextReverse) {

				alertTextAlpha += dt * 7;
			}
			else {

				alertTextAlpha -= dt * 7;
			}

			alertText.setFillColor(sf::Color(255, 255, 255, alertTextAlpha));
			_data->window.draw(alertText);
		}


		timeText.setString(minutesString + timeDotsString + secondsString);
		timeText.setPosition((this->_data->window.getSize().x - timeText.getLocalBounds().width) / 2, this->_data->window.getSize().y / 35);
		_data->window.draw(timeText);


		bool canSpin = std::any_of(diceArray.begin(), diceArray.end(), [](std::shared_ptr<Die> die) {return !die->CheckHeld(); });
		if (spinButton.Spin(_data->window, _clock, player->GetDice().GetRollsLeft(), canSpin)) {
			alpha = 0;
			player->RollDice();
			player->Roll();
			player->QueryCandidates(); // check which queries are not working properly
			player->GetDice().DecreaseRolls();
			spinButton.UpdateRolls(player->GetDice().GetRollsLeft(), this->_data->window);
		}

		_data->window.display();
	}
	else
	{
		_data->window.clear();

		_data->window.draw(backgroundgr, 4, sf::Quads);
		_data->window.draw(container);
		_data->window.draw(crown);
		winnerName.setString(_game.winner->GetName());
		winnerName.setPosition((_data->window.getSize().x / 2) - (winnerName.getGlobalBounds().width / 2), (_data->window.getSize().y / 2) - (container.getGlobalBounds().height / 2)+ crown.getGlobalBounds().height * 1.5);
		_data->window.draw(winnerName);
		winnerScore.setString("Score: "+std::to_string(_game.winner->TotalScore()));
		_data->window.draw(winnerScore);


		static sf::Clock count;
		if (count.getElapsedTime().asSeconds() >= 5)
		{
			music.pause();
			_game.players.clear();
			_data->machine.AddState(new GameOver(_data, _game), true);
		}
		_data->window.display();
	}
}
