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
#include "EnemiesGroup.hpp"

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
    Spaceship *player(new Spaceship(RESOURCES_LOCATION + "player.png", PLAYER_SPACESHIP_SPEED));
    EnemiesGroup enemies(player);

    // adding all the spaceships to the vector
    allSpaceships.push_back(player);
    allSpaceships.insert(allSpaceships.end(), enemies.getSpaceships()->begin(), enemies.getSpaceships()->end());

    // adding the controllers
    player->addController(new KeyboardSpaceshipController(window, player, enemies.getSpaceships()));
    player->addController(new JoystickSpaceshipController(window, player, enemies.getSpaceships()));

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
            player->refresh();
            enemies.refresh();

            window.clear();

            window.draw(space);
            window.draw(*player);
            window.draw(enemies);

            window.display();
        }
        else
            sf::sleep(sf::seconds(0.02f - clock.getElapsedTime().asSeconds()));
    }

    // end of the program
    delete player;

    return EXIT_SUCCESS;
}
