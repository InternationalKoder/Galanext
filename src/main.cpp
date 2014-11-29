//    Galanext is a Galaxian-like game
//    Copyright (C) 2014  InternationalKoder
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

#include <SFML/Graphics.hpp>
#include <vector>
#include "constants.hpp"
#include "Space.hpp"
#include "Spaceship.hpp"
#include "KeyboardSpaceshipController.hpp"
#include "JoystickSpaceshipController.hpp"
#include "AISpaceshipController.hpp"

/////////////////////////////////////////////////
/// \brief The main function
///
/// This function starts and handles the game
///
/////////////////////////////////////////////////
int main(void)
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
    window.setVerticalSyncEnabled(true);

    Space space;

    std::vector<Spaceship*> allSpaceships;

    // creating the spaceships
    Spaceship* player(new Spaceship(RESOURCES_LOCATION + "player.png", PLAYER_SPACESHIP_SPEED));
    Spaceship* enemy(new Spaceship(RESOURCES_LOCATION + "enemy1.png", ENEMY_SPACESHIP_SPEED, sf::Vector2f(0.0f, 10.0f)));

    // adding all the spaceships to the vector
    allSpaceships.push_back(player);
    allSpaceships.push_back(enemy);

    // adding the controllers
    KeyboardSpaceshipController keyboardPlayer(window, player, &allSpaceships);
    player->addController(&keyboardPlayer);

    JoystickSpaceshipController joystickPlayer(window, player, &allSpaceships);
    player->addController(&joystickPlayer);

    AISpaceshipController aiEnemy(enemy, &allSpaceships);
    enemy->addController(&aiEnemy);

    sf::Clock clock;

    while(window.isOpen())
    {
        if(clock.getElapsedTime().asMilliseconds() > 20)
        {
            sf::Event event;

            clock.restart();

            while(window.pollEvent(event))
            {
                if(event.type == sf::Event::Closed)
                    window.close();
                else if(event.type == sf::Event::LostFocus)
                {
                    // pauses the game when focus is lost
                    bool resume(false);
                    while(!resume)
                    {
                        window.pollEvent(event);
                        if(event.type == sf::Event::GainedFocus)
                            resume = true;

                        sf::sleep(sf::milliseconds(100));
                    }
                }
            }

            space.refresh();

            for(unsigned int i = 0 ; i < allSpaceships.size() ; i++)
                allSpaceships[i]->refresh();

            window.clear();

            window.draw(space);
            for(unsigned int i = 0 ; i < allSpaceships.size() ; i++)
                window.draw(*allSpaceships[i]);

            window.display();
        }
        else
            sf::sleep(sf::seconds(0.02f - clock.getElapsedTime().asSeconds()));
    }

    // end of the program
    for(unsigned int i = 0 ; i < allSpaceships.size() ; i++)
        delete allSpaceships.at(i);

    return EXIT_SUCCESS;
}
