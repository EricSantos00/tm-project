#include "main.h"

int HKD_ChangeTabColor(char* msg)
{
	char keyColor[2];
	int color = 0xFFCCCCCC;

	memcpy(keyColor, &msg[0], 1);
	keyColor[1] = '\0';

	if (!strcmp(msg, "NOVATO"))
		color = TNColor::White;

	else if (!strcmp(msg, "EXPLORADOR"))
		color = TNColor::Green;
	
	else if (!strcmp(msg, "PERITO"))
		color = TNColor::Green;
	
	else if (!strcmp(msg, "VETERANO"))
		color = TNColor::GreenYellow;

	else if (!strcmp(msg, "MORTAL"))
		color = TNColor::Blue;
	
	else if (!strcmp(msg, "MISTICO"))
		color = TNColor::Blue;

	else if (!strcmp(msg, "ARCANO"))
		color = TNColor::BlueNew;

	else if (!strcmp(msg, "PESADELO"))
		color = TNColor::Yellow;

	else if (!strcmp(msg, "ARCH"))
		color = TNColor::Yellow;

	else if (!strcmp(msg, "SUPREMO"))
		color = TNColor::Orange;

	else if (!strcmp(msg, "Ajudante|Iniciantes"))
		color = TNColor::Blue;

	else if (!strcmp(keyColor, " "))
		color = TNColor::Blue;

	else if (!strcmp(msg, "EternalWYD"))
		color = TNColor::Orange;

	return color;
}

