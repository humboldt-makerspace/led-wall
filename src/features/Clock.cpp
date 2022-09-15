#include "features/Clock.hpp"
#include "system/Interface.hpp"

tm *Clock::gmtm;

void Clock::getTime(void)
{
	time_t now = time(0);
	gmtm = localtime(&now);
}

void Clock::showTimeDigits(void)
{
	getTime();

	Figures::displayNumber((big_number_t)(gmtm->tm_hour / 10), HR_1_POS, NUMBER_LEVEL);
	Figures::displayNumber((big_number_t)(gmtm->tm_hour % 10), HR_2_POS, NUMBER_LEVEL);

	Figures::displayColon(COLON_1_POS, COLON_HEIGHT);

	Figures::displayNumber((big_number_t)(gmtm->tm_min / 10), MIN_1_POS, NUMBER_LEVEL);
	Figures::displayNumber((big_number_t)(gmtm->tm_min % 10), MIN_2_POS, NUMBER_LEVEL);

	Figures::displayColon(COLON_2_POS, COLON_HEIGHT);

	Figures::displayNumber((big_number_t)(gmtm->tm_sec / 10), SEC_1_POS, NUMBER_LEVEL);
	Figures::displayNumber((big_number_t)(gmtm->tm_sec % 10), SEC_2_POS, NUMBER_LEVEL);
}

void Clock::showTimeWords(void)
{
	getTime();

	MessageBoard::displayTwoWordNumbers(gmtm->tm_hour / 10, gmtm->tm_hour % 10, FIRST_ROW_LEVEL);
	MessageBoard::displayTwoWordNumbers(gmtm->tm_min / 10, gmtm->tm_min % 10, 0);
}
