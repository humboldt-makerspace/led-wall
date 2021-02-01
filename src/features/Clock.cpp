#include "features/Clock.hpp"
#include "system/Interface.hpp"

tm* Clock::gmtm;

void Clock::getTime (void)
{
	time_t now = time(0);
  	//time(&now);
  	gmtm = localtime(&now); 
	
	//gmtm = gmtime(&now);
}

void Clock::showTime (void)
{	
	getTime();
	
	Figures::displayFigure((Figure)(gmtm->tm_hour / 10), HR_1_POS, NUMBER_HEIGHT);
	Figures::displayFigure((Figure)(gmtm->tm_hour % 10), HR_2_POS, NUMBER_HEIGHT);

	Figures::displayColon(COLON_1_POS, COLON_HEIGHT);

	Figures::displayFigure((Figure)(gmtm->tm_min / 10), MIN_1_POS, NUMBER_HEIGHT);
	Figures::displayFigure((Figure)(gmtm->tm_min % 10), MIN_2_POS, NUMBER_HEIGHT);

	Figures::displayColon(COLON_2_POS, COLON_HEIGHT);

	Figures::displayFigure((Figure)(gmtm->tm_sec / 10), SEC_1_POS, NUMBER_HEIGHT);
	Figures::displayFigure((Figure)(gmtm->tm_sec % 10), SEC_2_POS, NUMBER_HEIGHT);

	/*
	Serial.print(gmtm->tm_hour);
	Serial.print(" ");
	Serial.print(gmtm->tm_min);
	Serial.print(" ");
	Serial.println(gmtm->tm_sec);
	*/
}
