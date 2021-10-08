#include "tm4c123gh6pm.h"
#include "SSD1306.h"

void Delay1ms(unsigned long ms) {
	unsigned long time = ms * 13333;
	while (time)
		time--;
}

int main() {
	SSD1306_Init(SSD1306_WITH_PLL);
	SSD1306_SetCursor(3, 4);
	SSD1306_Write_Str("Hello, world!");
	while (1) {
	}
}
