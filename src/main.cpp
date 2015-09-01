//    Galanext is a Galaxian-like game
//    Copyright (C) 2014-2015  InternationalKoder
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see http://www.gnu.org/licenses/.

#include "../include/version.hpp"
#include "../include/Config.hpp"
#include "../include/Log.hpp"
#include "../include/Space.hpp"
#include "../include/Spaceship.hpp"
#include "../include/Shot.hpp"
#include "../include/KeyboardSpaceshipController.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

void readOptions(int argc, char* argv[])
{
    // Getting the option for the log

    Log::setLevel(Log::NONE);

    if(argc == 2)
    {
        std::string option1 = std::string(argv[1]);
        if(option1 == "-n")
        {
            Log::setLevel(Log::NONE);
        }
        else if(option1 == "-e")
        {
            Log::setLevel(Log::ERROR);
        }
        else if(option1 == "-w")
        {
            Log::setLevel(Log::WARN);
        }
        else if(option1 == "-i")
        {
            Log::setLevel(Log::INFO);
        }
        else if(option1 == "-d")
        {
            Log::setLevel(Log::DEBUG);
        }
        else
        {
            std::cout << "'" << argv[1] << "' is not a valid option. Valid options are:" << std::endl;
            std::cout << "\t-n\tDon't display any message" << std::endl;
            std::cout << "\t-e\tDisplay the error messages" << std::endl;
            std::cout << "\t-w\tDisplay warning and error messages" << std::endl;
            std::cout << "\t-i\tDisplay information, warning and error messages" << std::endl;
            std::cout << "\t-d\tDisplay debug, information, warning and error messages" << std::endl;
            std::cout << std::endl << "The game will be started without any option." << std::endl;
        }
    }
    else if(argc != 1)
    {
        std::cout << "Incorrect option number. The game will be started without any option." << std::endl;
    }
}

/////////////////////////////////////////////////
///
/// \brief The main function
///
/// This function starts and handles the game
///
/////////////////////////////////////////////////
int main(int argc, char*  argv[])
{
    sf::err().rdbuf(NULL);

    readOptions(argc, argv);

    Log::info("Starting Galanext version " + std::string(Galanext_VERSION_MAJOR) + "."
              + std::string(Galanext_VERSION_MINOR));


    // Loading the resources

    sf::Texture playerSpaceshipT;
    if(playerSpaceshipT.loadFromFile(Config::RESOURCES_PATH + "player.png"))
    {
        Log::debug("Texture '" + Config::RESOURCES_PATH + "player.png' successfully loaded");
    }
    else
    {
        Log::error("Can not load texture '" + Config::RESOURCES_PATH + "player.png'");
    }

    sf::Texture shotT;
    if(shotT.loadFromFile(Config::RESOURCES_PATH + "shot.png"))
    {
        Log::debug("Texture '" + Config::RESOURCES_PATH + "shot.png' successfully loaded");
    }
    else
    {
        Log::error("Can not load texture '" + Config::RESOURCES_PATH + "shot.png'");
    }


    // Creating the objects

    Space space;

    unsigned int playerSpaceshipSW = playerSpaceshipT.getSize().x / Spaceship::NUMBER_ANIMATION;
    unsigned int playerSpaceshipSH = playerSpaceshipT.getSize().y;

    sf::Vector2f playerSpaceshipStartingPos(Config::WINDOW_WIDTH / 2 - playerSpaceshipSW / 2,
                                            Config::WINDOW_HEIGHT - playerSpaceshipSH - Config::BOTTOM_MARGIN);
    Spaceship playerSpaceship(playerSpaceshipT, playerSpaceshipStartingPos);

    KeyboardSpaceshipController keyboardController(shotT);
    keyboardController.addSpaceship(&playerSpaceship);
    Log::info("Using keyboard controller for player's spaceship");


    // Opening the window

    Log::debug("Opening window with resolution " + std::to_string(Config::WINDOW_WIDTH) + "x"
               + std::to_string(Config::WINDOW_HEIGHT));
    sf::RenderWindow window(sf::VideoMode(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT), Config::WINDOW_TITLE);
    window.setVerticalSyncEnabled(true);
    Log::debug("Done opening window");



    // Game loop

    sf::Clock clock;

    while(window.isOpen())
    {
        if(clock.getElapsedTime().asMilliseconds() > 20)
        {
            Log::debug(std::to_string(1.0f / clock.getElapsedTime().asSeconds()) + " ticks/s");
            sf::Event event;

            clock.restart();

            while(window.pollEvent(event))
            {
                if(event.type == sf::Event::Closed)
                    window.close();
            }

            space.refresh();
            keyboardController.handleEvents();
            playerSpaceship.refresh();

            window.clear();
            space.display(window);
            keyboardController.displayShots(window);
            playerSpaceship.display(window);
            window.display();
        }
        else
            sf::sleep(sf::seconds(0.02f - clock.getElapsedTime().asSeconds()));
    }

    return EXIT_SUCCESS;
}
