#define SFML_NO_DEPRECATED_WARNINGS
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>

//Client

int main()
{

	sf::IpAddress ip = sf::IpAddress("");//your ipaddress to work
	sf::TcpSocket socket;
	bool done = false;
	std::string id;
	std::string text = "";
	std::cout << "Enter online id: ";
	std::cin >> id;
	socket.connect(ip, 2000);
	sf::RenderWindow Window(sf::VideoMode(800, 600, 32), "Chat");
	std::vector<sf::Text> chat;

	sf::Packet packet;
	packet << id;
	socket.send(packet);
	socket.setBlocking(false);

	Window.setTitle(id);

	sf::Font font;
	font.loadFromFile("Roboto-BlackItalic.ttf");

	while (Window.isOpen())
	{
		sf::Event event;
		while (Window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				Window.close();
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
					Window.close();
				else if (event.key.code == sf::Keyboard::Return)
				{
					sf::Packet packet;
					packet << id + ": " + text;
					socket.send(packet);
					sf::Text displayText(text, font, 20);
					displayText.setColor(sf::Color::Red);
					chat.push_back(displayText);
					text = "";
				}
				break;
			case sf::Event::TextEntered:
				text += event.text.unicode;
				break;
			default:
				break;
			}
		}

		sf::Packet packet;
		socket.receive(packet);

		std::string temtext;
		if (packet >> temtext)
		{
			sf::Text displatText(temtext, font, 20);
			displatText.setColor(sf::Color::Green);//received for sb else
			chat.push_back(displatText);
		}

		int i = 0;
		for (i; i < chat.size(); ++i)
		{
			chat[i].setPosition(0, i * 20);
			Window.draw(chat[i]);
		}

		sf::Text drawText(text, font, 20);
		drawText.setColor(sf::Color::Red);
		drawText.setPosition(0, i * 20);
		Window.draw(drawText);

		Window.display();
		Window.clear();
	}


	return 0;
}