#include "config.h"

config yo;									// Конфиг со всякой шнягой полезной внутри
varStorage v;
void (*pt2Func)() = nullptr; 				// Указатель на функцию для CASE

mapWAVES mWaves; 							// list for: IRDA - function - WEB
// waveItem c; 								// копия данных в оперативной работе вытащенная из откуда-то ( мапы м вавами или из  сейвника)
std::map<int, waveItem>::iterator mbIter;


int temperList[NUM_TEMPS] = {
	0xFF3300,0xFF3800,0xFF4500,0xFF4700,0xFF5200,0xFF5300,0xFF5D00,0xFF5D00,0xFF6600,0xFF6500,0xFF6F00,0xFF6D00,0xFF7600,0xFF7300,0xFF7C00,0xFF7900,
	0xFF8200,0xFF7E00,0xFF8700,0xFF8300,0xFF8D0B,0xFF8912,0xFF921D,0xFF8E21,0xFF9829,0xFF932C,0xFF9D33,0xFF9836,0xFFA23C,0xFF9D3F,0xFFA645,0xFFA148,0xFFAA4D,0xFFA54F,
	0xFFAE54,0xFFA957,0xFFB25B,0xFFAD5E,0xFFB662,0xFFB165,0xFFB969,0xFFB46B,0xFFBD6F,0xFFB872,0xFFC076,0xFFBB78,0xFFC37C,0xFFBE7E,0xFFC682,0xFFC184, 0xFFFFFF
};   								// массив с номерами цветов по верхней части таблицы Кельвина

int powInt(int x, int y)
{
    for (int i = 0; i < y; i++) { x *= 10;  }
    return x;
}

int parseInt(char* chars)
{
    int sum = 0;
    int len = strlen(chars);
    for (int x = 0; x < len; x++) 
	{
        int n = chars[len - (x + 1)] - '0';
        sum = sum + powInt(n, x);
    }
    return sum;
}

bool isBetween( uint8_t number, uint8_t lowwer, uint8_t higher)
{
		// yo.c1 = CHSV( 0,0,0);	
	return lowwer <= number &&  number <= higher;	
}

// int arr[5];

uint8_t map88( uint8_t x, uint8_t in_min, uint8_t in_max) 
{
	// arr[4] = 1;
	
    const uint8_t divisor = in_max - in_min;
    const uint8_t delta = x - in_min;

    return (( delta << 8) + (divisor >> 1)) / divisor;
}

