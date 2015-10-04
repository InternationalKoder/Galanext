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
#include "../include/Shot.hpp"
#include "../include/Spaceship.hpp"
#include "../include/KeyboardSpaceshipController.hpp"
#include "../include/CpuSpaceshipController.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

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
    srand(time(NULL));
    sf::err().rdbuf(NULL);
    int ticksCounter = 0;

    readOptions(argc, argv);

    Log::info("Starting Galanext version " + std::string(Galanext_VERSION_MAJOR) + "."
              + std::string(Galanext_VERSION_MINOR));


    // Loading the resources

    sf::Font font;
    if(font.loadFromFile(Config::RESOURCES_PATH + "xen3.ttf"))
    {
        Log::debug("Font '" + Config::RESOURCES_PATH + "xen3.ttf' successfully loaded");
    }
    else
    {
        Log::error("Can not load font '" + Config::RESOURCES_PATH + "xen3.ttf'");
    }

    sf::Texture playerSpaceshipT;
    if(playerSpaceshipT.loadFromFile(Config::RESOURCES_PATH + "player.png"))
    {
        Log::debug("Texture '" + Config::RESOURCES_PATH + "player.png' successfully loaded");
    }
    else
    {
        Log::error("Can not load texture '" + Config::RESOURCES_PATH + "player.png'");
    }

    sf::Texture enemy0SpaceshipT;
    if(enemy0SpaceshipT.loadFromFile(Config::RESOURCES_PATH + "enemy0.png"))
    {
        Log::debug("Texture '" + Config::RESOURCES_PATH + "enemy0.png' successfully loaded");
    }
    else
    {
        Log::error("Can not load texture '" + Config::RESOURCES_PATH + "enemy0.png'");
    }

    sf::Texture enemy1SpaceshipT;
    if(enemy1SpaceshipT.loadFromFile(Config::RESOURCES_PATH + "enemy1.png"))
    {
        Log::debug("Texture '" + Config::RESOURCES_PATH + "enemy1.png' successfully loaded");
    }
    else
    {
        Log::error("Can not load texture '" + Config::RESOURCES_PATH + "enemy1.png'");
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

    std::list<Spaceship*> playerSpaceships;
    std::list<Spaceship*> enemiesSpaceships;
    std::list<Shot*> allShots;

    Space space;

    unsigned int playerSpaceshipSW = playerSpaceshipT.getSize().x / Spaceship::NUMBER_ANIMATION;
    unsigned int playerSpaceshipSH = playerSpaceshipT.getSize().y;

    sf::Vector2f playerSpaceshipStartingPos(Config::WINDOW_WIDTH / 2 - playerSpaceshipSW / 2,
                                            Config::WINDOW_HEIGHT - playerSpaceshipSH - Config::BOTTOM_MARGIN);
    Spaceship playerSpaceship(playerSpaceshipT, playerSpaceshipStartingPos, &enemiesSpaceships);
    playerSpaceships.push_back(&playerSpaceship);

    KeyboardSpaceshipController keyboardController(shotT);
    keyboardController.addSpaceship(&playerSpaceship);
    Log::info("Using keyboard controller for player's spaceship");

    Spaceship enemies[Config::ENEMIES_LINES_COUNT][Config::ENEMIES_COLS_COUNT];
    CpuSpaceshipController cpuController(shotT);

    for(int i = 0 ; i < Config::ENEMIES_LINES_COUNT ; i++)
    {
        for(int j = 0 ; j < Config::ENEMIES_COLS_COUNT ; j++)
        {
            if(i == 0)
            {
                sf::Vector2f startingPos(50 * j, Config::TOP_MARGIN);
                enemies[0][j] = Spaceship(enemy0SpaceshipT, startingPos, &playerSpaceships);
            }
            else
            {
                sf::Vector2f startingPos(50 * j, Config::TOP_MARGIN + 50 * i);
                enemies[i][j] = Spaceship(enemy1SpaceshipT, startingPos, &playerSpaceships);
            }

            enemiesSpaceships.push_back(&enemies[i][j]);
            cpuController.addSpaceship(&enemies[i][j]);
        }
    }

    unsigned int score = 0;

    sf::Text scoreText("SCORE", font);
    scoreText.setColor(sf::Color::White);
    scoreText.setCharacterSize(18);

    unsigned int textPosY = Config::TOP_MARGIN / 2 - scoreText.getGlobalBounds().height;

    scoreText.setPosition(Config::SCORE_TEXT_POS_X, textPosY);

    sf::Text scoreValueText(std::to_string(score), font);
    scoreValueText.setColor(sf::Color::White);
    scoreValueText.setCharacterSize(18);
    unsigned int scoreValuePosX = Config::SCORE_TEXT_POS_X + scoreText.getGlobalBounds().width + Config::SCORE_MARGIN;
    scoreValueText.setPosition(scoreValuePosX, textPosY);


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
            ticksCounter++;
            if(ticksCounter >= 100)
            {
                Log::debug(std::to_string(1.0f / clock.getElapsedTime().asSeconds()) + " ticks/s");
                ticksCounter = 0;
            }

            sf::Event event;

            clock.restart();

            while(window.pollEvent(event))
            {
                if(event.type == sf::Event::Closed)
                    window.close();
            }

            // Refresh
            space.refresh();
            keyboardController.handleEvents(&allShots);
            cpuController.handleEvents(&allShots);

            std::list<Spaceship*> destroyedSpaceships;

            for(std::list<Shot*>::iterator it = allShots.begin() ; it != allShots.end() ; ++it)
            {
                Spaceship* destroyed = (*it)->refresh();
                if(destroyed != 0)
                {
                    destroyedSpaceships.push_back(destroyed);
                }
            }
            for(std::list<Spaceship*>::iterator it = playerSpaceships.begin() ; it != playerSpaceships.end() ; ++it)
            {
                (*it)->refresh();
            }
            for(std::list<Spaceship*>::iterator it = enemiesSpaceships.begin() ; it != enemiesSpaceships.end() ; ++it)
            {
                (*it)->refresh();

                for(std::list<Spaceship*>::iterator it2 = destroyedSpaceships.begin() ;
                    it2 != destroyedSpaceships.end() ; )
                {
                    if(*it == *it2)
                    {
                        score += 100;
                        Log::debug("Enemy spaceship destroyed: score +100");
                        it2 = destroyedSpaceships.erase(it2);
                    }
                    else
                    {
                        ++it2;
                    }
                }
            }
            scoreValueText.setString(std::to_string(score));

            // Display
            window.clear();
            space.display(window);
            for(std::list<Spaceship*>::iterator it = playerSpaceships.begin() ; it != playerSpaceships.end() ; ++it)
            {
                (*it)->display(window);
            }
            for(std::list<Spaceship*>::iterator it = enemiesSpaceships.begin() ; it != enemiesSpaceships.end() ; ++it)
            {
                (*it)->display(window);
            }
            for(std::list<Shot*>::iterator it = allShots.begin() ; it != allShots.end() ; ++it)
            {
                (*it)->display(window);
            }
            window.draw(scoreText);
            window.draw(scoreValueText);
            window.display();
        }
        else
            sf::sleep(sf::seconds(0.02f - clock.getElapsedTime().asSeconds()));
    }

    for(std::list<Shot*>::iterator it = allShots.begin() ; it != allShots.end() ; ++it)
    {
        delete (*it);
    }

    return EXIT_SUCCESS;
}
