 +---------------------------------------------------+
 |                                                   |
 |                  G A L A N E X T                  |
 |                                                   |
 |                    R E A D M E                    |
 |                                                   |
 +---------------------------------------------------+
 
 Galanext is a Galaxian-like game made by InternationalKoder.
 The game is not finished yet, it is still under development. It is written in C++ with the SFML API (see https://github.com/LaurentGomila/SFML for details).
 
 AUTHORS:
 
 - InternationalKoder (international_koder@yahoo.com)
 
 DOWNLOAD:
 
 You can find the latest release on the git repository (https://github.com/InternationalKoder/Galanext).
 
 USING GALANEXT:
 
 If you are using a GNU/Linux system, you can directly run the "StartGalanext.sh" file in the root folder. Make sure that the "resources" and "shared-libs" folders are next to the "Galanext" and "StartGalanext.sh" files.
 If this one doesn't work or if you're useing another operating system, you have to compile the program.
 To compile the game, you need a C++ compiler and the SFML 2.1 API for this compiler. You can also use the given shared libraries to compile the game. Then you just have to compile all the files which are in the "src" folder.
 
 LICENSE:
 
 All the project is under the GNU GPLv3 license, the source files are included with the game.
 
 CHANGELOG:

 Dec 6, 2014:
 + The enemies randomly fire

 Dec 4, 2014:
 + Added the support of different rows of enemies (2 rows for the moment)

 Dec 2, 2014:
 + Added a group of enemies

 Nov 29, 2014:
 + Added animation to the spaceships
 + The game is paused when the window is not active
 
 Nov 28, 2014:
 + Added a pause menu you can trigger with a keyboard or with a joystick
 
 Nov 22, 2014:
 * Fixed a bug which happened when the program was closed

 Nov 17, 2014:
 + Added a moving enemy you can destroy
 * Changed the build script to get the most optimized (for speed) program.
 
 Nov 15, 2014:
 * Changed the build script so that you can compile Galanext with the provided libraries. You can compile the game without installing the SFML library.
 
 Nov 14, 2014:
 + Added a script to build the program (requires SFML 2.1)
 * You can now control the spaceship with a joystick
 
 Nov 11, 2014:
 + Added the shared libraries to the root folder so that you can run Galanext on any GNU/Linux computer.
 + Added a StartGalanext.sh script which runs the game using the files in the "shared-libs" folder, everyone should run the given executable through this script.
 * Doxyfile given rather than the whole documentation
 * Shortened the doxyfile
 
 Nov 9, 2014:
 * Initial version with only a moving space background and a spaceship you can move with the keyboard. The spaceship is also able to fire.
