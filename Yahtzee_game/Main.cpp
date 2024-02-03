#include <iostream>
#include <ctime>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

#include "Die.h"
#include "ScoreTable.h"
#include "Game.h"
#include "MySprite.h"
#include "Button.h"
#include <map>
#include <conio.h>




void runUdpServer(unsigned short port)
{
	// Create a socket to receive a message from anyone
	sf::UdpSocket socket;

	// Listen to messages on the specified port
	if (socket.bind(port) != sf::Socket::Done)
		return;
	std::cout << "Server is listening to port " << port << ", waiting for a message... " << std::endl;
	// Wait for a message
	char in[128];
	std::size_t received;
	sf::IpAddress sender;
	unsigned short senderPort;
	if (socket.receive(in, sizeof(in), received, sender, senderPort) != sf::Socket::Done)
		return;
	std::cout << "Message received from client " << sender << ": \"" << in << "\"" << std::endl;

	// Send an answer to the client
	const char out[] = "Hi, I'm the server";
	if (socket.send(out, sizeof(out), sender, senderPort) != sf::Socket::Done)
		return;
	std::cout << "Message sent to the client: \"" << out << "\"" << std::endl;

}
void runUdpClient(unsigned short port)
{

	sf::IpAddress server;
	do
	{
		std::cout << "Type the address or name of the server to connect to: ";
		std::cin >> server;
	} while (server == sf::IpAddress::None);


	sf::UdpSocket socket;


	const char out[] = "Hi, I'm a client";
	if (socket.send(out, sizeof(out), server, port) != sf::Socket::Done)
		return;
	std::cout << "Message sent to the server: \"" << out << "\"" << std::endl;


	char in[128];
	std::size_t received;
	sf::IpAddress sender;
	unsigned short senderPort;
	if (socket.receive(in, sizeof(in), received, sender, senderPort) != sf::Socket::Done)
		return;
	std::cout << "Message received from " << sender << ": \"" << in << "\"" << std::endl;
}

int main()
{
	int windowWidth = 800;
	int windowHeight = 800;
	Game game(windowWidth, windowHeight, "Yahtzee!");
	game.Run();
	



	return 0;
}