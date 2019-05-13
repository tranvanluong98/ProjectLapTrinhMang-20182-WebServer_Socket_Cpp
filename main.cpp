#include "WebServer.h"

void main()
{
	WebServer webServer("0.0.0.0", 6969);
	if (webServer.init() != 0)
		return;

	webServer.run();

	system("pause");
}