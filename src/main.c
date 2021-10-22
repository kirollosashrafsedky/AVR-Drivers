#include "main.h"
#include "App/app.h"

int main(void) {
	app_init();
	while(1)
	{
		app_update();
	}
	return 0;
}
