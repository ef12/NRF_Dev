/*
 * main.cpp
 *
 *  Created on: Oct 29, 2017
 *      Author: Ehud Frank
 */
#include "app.hpp"

application app;
int main(void) {
	app.init();
	app.run();
	while (true)
		;
}

/**
 *@}
 **/
