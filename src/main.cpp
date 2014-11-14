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

/////////////////////////////////////////////////
/// \brief The main function
///
/// This function starts and handles the game
///
/////////////////////////////////////////////////
int main(void)
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Galanext");
    window.setVerticalSyncEnabled(true);

    Space space;
    Spaceship player("resources/player.png", PLAYER_SPACESHIP_SPEED);
    KeyboardSpaceshipController keyboardPlayer(&player);
    JoystickSpaceshipController joystickPlayer(&player);
    player.addController(&keyboardPlayer);
    player.addController(&joystickPlayer);

    sf::Clock clock;

    while(window.isOpen())
    {
        if(clock.getElapsedTime().asSeconds() > 0.02f)
        {
            sf::Event event;

            clock.restart();

            while(window.pollEvent(event))
            {
                if(event.type == sf::Event::Closed)
                    window.close();
            }

            space.refresh();
            player.refresh();

            window.clear();
            window.draw(space);
            window.draw(player);
            if(player.getShot() != 0)
                window.draw(*player.getShot());
            window.display();
        }
        else
            sf::sleep(sf::seconds(0.02f - clock.getElapsedTime().asSeconds()));
    }

    return EXIT_SUCCESS;
}
