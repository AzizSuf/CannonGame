/*
 * Created: 01.01.23
 * Author : Aziz Sufyanov
 * e-mail : aziz-sufyanov@mail.ru
 *
 */

#include "Game.h"

 // For build without console
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
int main()
{
	Game game;
	game.run();

	return 0;
}
