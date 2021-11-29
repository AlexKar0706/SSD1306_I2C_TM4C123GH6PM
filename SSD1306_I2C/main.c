#include "tm4c123gh6pm.h"
#include "i2c.h"
#include "SSD1306.h"

int main() {
	I2C_Init(I2C_WITH_PLL);
	SSD1306_Init();
	SSD1306_SetCursor(4, 3);
	SSD1306_WriteStr("Hello, world!");
	while (1) {
	}
}
