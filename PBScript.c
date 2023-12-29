#include <stdio.h>
#include <stdlib.h>
#include <lgpio.h>
#include <math.h>
#include <unistd.h>

int main(){
	//power button pin
	int pinPB = 3;
	//fan pin
	int pinF = 14;

	//opening GPIO
	int h = lgGpiochipOpen(0);

	lgGpioClaimInput(h, 0, pinPB);
	lgGpioClaimOutput(h, 0, pinF, 0);

	sleep(10);
	//power on fan upon script running (every time computer starts)
	lgGpioWrite(h, pinF, 1);

	//printf("%i\n", lgGpioGetMode(h, pinF));

	//constantly checks for press
	while(1 == 1){
		int level = lgGpioRead(h,pinPB);

		//if press detected
		if (level == 0){
			//turns off fan
			lgGpioWrite(h, pinF, 0);

			//freeing resources
			lgGpioFree(h, pinF);
			lgGpioFree(h, pinPB);
			lgGpiochipClose(h);

			//printf("bang\n");

			//shuts down system
			system("sudo shutdown now");

			return 0;
		}
	}

	return 0;
}
