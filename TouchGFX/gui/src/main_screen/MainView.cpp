#include <gui/main_screen/MainView.hpp>


uint8_t hours;
uint8_t minutes;
uint8_t seconds;
uint8_t year;
uint8_t month;
uint8_t date;
MainView::MainView()
{

}

void MainView::setupScreen()
{
    MainViewBase::setupScreen();
}

void MainView::tearDownScreen()
{
    MainViewBase::tearDownScreen();
}

void MainView::handleTickEvent()
{
    digitalClock1.setTime24Hour(hours, minutes, seconds);
}
