//ESTA MACRO SÓLO APARECE UNA VEZ EN EL ARCHIVO QUE CONTENGA EL MAIN()
#define GLAD_BIN
#include "common.h"
#include "Object3D.h"
#include <iostream>
#include "EventManager.h"
#include "Render.h"
#include "System.h"


int main(int argc, char** argv)
{
	//inicializar GLFW
	System::render = new Render(); //crear ventanas opengl

	auto ship = new Ship("./data/ship.frs");
	ship->mat->alpha = 1.0f;
	ship->rotacion.z = 90;
	ship->posicion.y = -5;

	auto enemy = new Enemy("./data/ship.frs");
	enemy->mat->alpha = 1.0f;
	enemy->rotacion.z = -90;
	enemy->posicion.y = 5;



	System::render->addObject(ship); //copiar objeto a gpu
	System::render->addObject(enemy); //copiar objeto a gpu
	System::render->mainLoop(); //bucle de renderizado
	
	return 0;
}
