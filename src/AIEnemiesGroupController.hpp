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

#ifndef AIENEMIESGROUPCONTROLLER_H
#define AIENEMIESGROUPCONTROLLER_H
#include "Spaceship.hpp"

class AIEnemiesGroupController
{
    public:

        /////////////////////////////////////////////////
		/// \brief Constructor
        ///
        /// \param spaceships The group's spaceships
        ///
        /////////////////////////////////////////////////
		AIEnemiesGroupController(std::vector<Spaceship*> *spaceships);

		/////////////////////////////////////////////////
		/// \brief Updates the spaceships
        ///
        /////////////////////////////////////////////////
		void events();

		/////////////////////////////////////////////////
		/// \brief Tells whether all the spaceships are able to move
		///
		/// \return True if all the spacehips are able to move
        ///
        /////////////////////////////////////////////////
		bool movePossibleAllSpaceships();

		/////////////////////////////////////////////////
		/// \brief Changes the direction of all the spaceships
        ///
        /////////////////////////////////////////////////
		void changeAllDirections();

		/////////////////////////////////////////////////
		/// \brief Moves all the spaceships
        ///
        /////////////////////////////////////////////////
		void moveAll();

		/////////////////////////////////////////////////
		/// \brief Tells whether any spaceship has fired
		///
		/// \return True if at least one spaceships has fired
        ///
        /////////////////////////////////////////////////
		bool hasFired();

		/////////////////////////////////////////////////
		/// \brief Tells whether the given spaceship is the first one of its column
		///
		/// \param spaceship The index of the spaceship to check
		///
		/// \return True if the spaceship is the first one of its column
        ///
        /////////////////////////////////////////////////

		bool isFirstOfColumn(const int& spaceship);

    private:

        std::vector<Spaceship*> *m_spaceships; ///< A pointer to the group's spaceships
};

#endif // AIENEMIESGROUPCONTROLLER_H
