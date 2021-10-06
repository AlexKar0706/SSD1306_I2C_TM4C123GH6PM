#include "tm4c123gh6pm.h"
#include "SSD1306.h"

int main() {
	SSD1306_Init();
	SSD1306_SetCursor(4, 3);
	SSD1306_Write_Str("Hello, world!");
	while (1) {
	}
}
