#include <gui/main_screen/MainView.hpp>
#include "BitmapDatabase.hpp"
#include <touchgfx/Color.hpp>

#define IAQ_LEVEL_GOOD 100
#define IAQ_LEVEL_MODERATE 200
#define IAQ_LEVEL_BAD 500

float IAQAverage24Hour[4];

/* Variables imported from main */
uint8_t hours;
uint8_t minutes;
uint8_t seconds;
uint8_t year;
uint8_t month;
uint8_t date;
uint8_t weekDay;

extern uint32_t (*pfHAL_GetTick)(void);                                                   /* Pointer to HAL_GetTick imported from main*/
extern float gui_iaq;

static uint32_t lastTickValue;                                                   /* Variable monitoring last tick value (HAL_GetTick) */

MainView::MainView()
{
    lastTickValue = pfHAL_GetTick();                                                             /* Initialize with actual tick value */
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
    if(pfHAL_GetTick() - lastTickValue >= 30000)
    {
        displayIAQGraph24Hour();
        lastTickValue = pfHAL_GetTick();
    }
    else
    {
        //do nothing
    }
}

void MainView::IAQSelect()
{
    line2.setVisible(true);
    remove(line2);
    line2.invalidate();
    line2.setX(IAQ_button.getX());
    add(line2);
    IAQ_button.setBitmaps(touchgfx::Bitmap(BITMAP_IAQ_DARK_ID), touchgfx::Bitmap(BITMAP_IAQ_DARK_ID));
    CO2_button.setBitmaps(touchgfx::Bitmap(BITMAP_CO2_LIGHT_ID), touchgfx::Bitmap(BITMAP_CO2_LIGHT_ID));
    VOC_button.setBitmaps(touchgfx::Bitmap(BITMAP_VOC_LIGHT_ID), touchgfx::Bitmap(BITMAP_VOC_LIGHT_ID));
    hum_button.setBitmaps(touchgfx::Bitmap(BITMAP_HUM_LIGHT_ID), touchgfx::Bitmap(BITMAP_HUM_LIGHT_ID));
    pres_button.setBitmaps(touchgfx::Bitmap(BITMAP_PRES_LIGHT_ID), touchgfx::Bitmap(BITMAP_PRES_LIGHT_ID));
    temp_button.setBitmaps(touchgfx::Bitmap(BITMAP_TEMP_LIGHT_ID), touchgfx::Bitmap(BITMAP_TEMP_LIGHT_ID));
    ContainerVisibilityOff();
    IAQ_container.setVisible(true);
    remove(IAQ_container);
    IAQ_container.invalidate();
    add(IAQ_container);
    box1.invalidate();
}

void MainView::CO2Select()
{
    line2.setVisible(true);
    remove(line2);
    line2.invalidate();
    line2.setX(CO2_button.getX());
    add(line2);
    IAQ_button.setBitmaps(touchgfx::Bitmap(BITMAP_IAQ_LIGHT_ID), touchgfx::Bitmap(BITMAP_IAQ_LIGHT_ID));
    CO2_button.setBitmaps(touchgfx::Bitmap(BITMAP_CO2_DARK_ID), touchgfx::Bitmap(BITMAP_CO2_DARK_ID));
    VOC_button.setBitmaps(touchgfx::Bitmap(BITMAP_VOC_LIGHT_ID), touchgfx::Bitmap(BITMAP_VOC_LIGHT_ID));
    hum_button.setBitmaps(touchgfx::Bitmap(BITMAP_HUM_LIGHT_ID), touchgfx::Bitmap(BITMAP_HUM_LIGHT_ID));
    pres_button.setBitmaps(touchgfx::Bitmap(BITMAP_PRES_LIGHT_ID), touchgfx::Bitmap(BITMAP_PRES_LIGHT_ID));
    temp_button.setBitmaps(touchgfx::Bitmap(BITMAP_TEMP_LIGHT_ID), touchgfx::Bitmap(BITMAP_TEMP_LIGHT_ID));
    ContainerVisibilityOff();
    CO2_container.setVisible(true);
    remove(CO2_container);
    CO2_container.invalidate();
    add(CO2_container);
    box1.invalidate();
}

void MainView::VOCSelect()
{
    line2.setVisible(true);
    remove(line2);
    line2.invalidate();
    line2.setX(VOC_button.getX());
    add(line2);
    IAQ_button.setBitmaps(touchgfx::Bitmap(BITMAP_IAQ_LIGHT_ID), touchgfx::Bitmap(BITMAP_IAQ_LIGHT_ID));
    CO2_button.setBitmaps(touchgfx::Bitmap(BITMAP_CO2_LIGHT_ID), touchgfx::Bitmap(BITMAP_CO2_LIGHT_ID));
    VOC_button.setBitmaps(touchgfx::Bitmap(BITMAP_VOC_DARK_ID), touchgfx::Bitmap(BITMAP_VOC_DARK_ID));
    hum_button.setBitmaps(touchgfx::Bitmap(BITMAP_HUM_LIGHT_ID), touchgfx::Bitmap(BITMAP_HUM_LIGHT_ID));
    pres_button.setBitmaps(touchgfx::Bitmap(BITMAP_PRES_LIGHT_ID), touchgfx::Bitmap(BITMAP_PRES_LIGHT_ID));
    temp_button.setBitmaps(touchgfx::Bitmap(BITMAP_TEMP_LIGHT_ID), touchgfx::Bitmap(BITMAP_TEMP_LIGHT_ID));
    ContainerVisibilityOff();
    VOC_container.setVisible(true);
    remove(VOC_container);
    VOC_container.invalidate();
    add(VOC_container);
    box1.invalidate();
}

void MainView::humSelect()
{
    line2.setVisible(true);
    remove(line2);
    line2.invalidate();
    line2.setX(hum_button.getX());
    add(line2);
    IAQ_button.setBitmaps(touchgfx::Bitmap(BITMAP_IAQ_LIGHT_ID), touchgfx::Bitmap(BITMAP_IAQ_LIGHT_ID));
    CO2_button.setBitmaps(touchgfx::Bitmap(BITMAP_CO2_LIGHT_ID), touchgfx::Bitmap(BITMAP_CO2_LIGHT_ID));
    VOC_button.setBitmaps(touchgfx::Bitmap(BITMAP_VOC_LIGHT_ID), touchgfx::Bitmap(BITMAP_VOC_LIGHT_ID));
    hum_button.setBitmaps(touchgfx::Bitmap(BITMAP_HUM_DARK_ID), touchgfx::Bitmap(BITMAP_HUM_DARK_ID));
    pres_button.setBitmaps(touchgfx::Bitmap(BITMAP_PRES_LIGHT_ID), touchgfx::Bitmap(BITMAP_PRES_LIGHT_ID));
    temp_button.setBitmaps(touchgfx::Bitmap(BITMAP_TEMP_LIGHT_ID), touchgfx::Bitmap(BITMAP_TEMP_LIGHT_ID));
    ContainerVisibilityOff();
    hum_container.setVisible(true);
    remove(hum_container);
    hum_container.invalidate();
    add(hum_container);
    box1.invalidate();
}

void MainView::presSelect()
{
    line2.setVisible(true);
    remove(line2);
    line2.invalidate();
    line2.setX(pres_button.getX());
    add(line2);
    IAQ_button.setBitmaps(touchgfx::Bitmap(BITMAP_IAQ_LIGHT_ID), touchgfx::Bitmap(BITMAP_IAQ_LIGHT_ID));
    CO2_button.setBitmaps(touchgfx::Bitmap(BITMAP_CO2_LIGHT_ID), touchgfx::Bitmap(BITMAP_CO2_LIGHT_ID));
    VOC_button.setBitmaps(touchgfx::Bitmap(BITMAP_VOC_LIGHT_ID), touchgfx::Bitmap(BITMAP_VOC_LIGHT_ID));
    hum_button.setBitmaps(touchgfx::Bitmap(BITMAP_HUM_LIGHT_ID), touchgfx::Bitmap(BITMAP_HUM_LIGHT_ID));
    pres_button.setBitmaps(touchgfx::Bitmap(BITMAP_PRES_DARK_ID), touchgfx::Bitmap(BITMAP_PRES_DARK_ID));
    temp_button.setBitmaps(touchgfx::Bitmap(BITMAP_TEMP_LIGHT_ID), touchgfx::Bitmap(BITMAP_TEMP_LIGHT_ID));
    ContainerVisibilityOff();
    pres_container.setVisible(true);
    remove(pres_container);
    pres_container.invalidate();
    add(pres_container);
    box1.invalidate();
}

void MainView::tempSelect()
{
    line2.setVisible(true);
    remove(line2);
    line2.invalidate();
    line2.setX(temp_button.getX());
    add(line2);
    IAQ_button.setBitmaps(touchgfx::Bitmap(BITMAP_IAQ_LIGHT_ID), touchgfx::Bitmap(BITMAP_IAQ_LIGHT_ID));
    CO2_button.setBitmaps(touchgfx::Bitmap(BITMAP_CO2_LIGHT_ID), touchgfx::Bitmap(BITMAP_CO2_LIGHT_ID));
    VOC_button.setBitmaps(touchgfx::Bitmap(BITMAP_VOC_LIGHT_ID), touchgfx::Bitmap(BITMAP_VOC_LIGHT_ID));
    hum_button.setBitmaps(touchgfx::Bitmap(BITMAP_HUM_LIGHT_ID), touchgfx::Bitmap(BITMAP_HUM_LIGHT_ID));
    pres_button.setBitmaps(touchgfx::Bitmap(BITMAP_PRES_LIGHT_ID), touchgfx::Bitmap(BITMAP_PRES_LIGHT_ID));
    temp_button.setBitmaps(touchgfx::Bitmap(BITMAP_TEMP_DARK_ID), touchgfx::Bitmap(BITMAP_TEMP_DARK_ID));
    ContainerVisibilityOff();
    temp_container.setVisible(true);
    remove(temp_container);
    temp_container.invalidate();
    add(temp_container);
    box1.invalidate();
}

void MainView::ContainerVisibilityOff(void)
{
    IAQ_container.setVisible (false);
    CO2_container.setVisible (false);
    VOC_container.setVisible (false);
    hum_container.setVisible (false);
    pres_container.setVisible(false);
    temp_container.setVisible(false);
}

void MainView::setIAQGraphRangeY24Hour(void)
{
    uint16_t IAQGraphMin = 0;
    uint16_t IAQGraphMax = 0;
    uint16_t IAQGraphGreenMin = 0;
    uint16_t IAQGraphGreenMax = 0;
    uint16_t IAQGraphYellowMin = 0;
    uint16_t IAQGraphYellowMax = 0;
    uint16_t IAQGraphRedMin = 0;
    uint16_t IAQGraphRedMax = 0;

    IAQGraphGreen.setGraphRangeYAuto(false, 5);
    IAQGraphYellow.setGraphRangeYAuto(false, 5);
    IAQGraphRed.setGraphRangeYAuto(false, 5);

    IAQGraphGreenMax = IAQGraphGreen.getGraphRangeYMaxAsFloat();
    IAQGraphYellowMax = IAQGraphYellow.getGraphRangeYMaxAsFloat();
    IAQGraphRedMax = IAQGraphRed.getGraphRangeYMaxAsFloat();

    IAQGraphGreenMin = IAQGraphGreen.getGraphRangeYMinAsFloat();
    IAQGraphYellowMin = IAQGraphYellow.getGraphRangeYMinAsFloat();
    IAQGraphRedMin = IAQGraphRed.getGraphRangeYMinAsFloat();
    if((IAQGraphGreenMax > IAQGraphYellowMax) && (IAQGraphGreenMax >IAQGraphRedMax))
    {
        IAQGraphMax = IAQGraphGreenMax;
    }
    else if(((IAQGraphYellowMax > IAQGraphGreenMax) && (IAQGraphYellowMax >IAQGraphRedMax)))
    {
        IAQGraphMax = IAQGraphYellowMax;
    }
    else
    {
        IAQGraphMax = IAQGraphRedMax;
    }

    if((IAQGraphGreenMin < IAQGraphYellowMin) && (IAQGraphGreenMin < IAQGraphRedMin))
    {
        IAQGraphMin = IAQGraphGreenMin;
    }
    else if(((IAQGraphYellowMin < IAQGraphGreenMin) && (IAQGraphYellowMin < IAQGraphRedMin)))
    {
        IAQGraphMin = IAQGraphYellowMin;
    }
    else
    {
        IAQGraphMin = IAQGraphRedMin;
    }
    IAQGraphGreen.setGraphRangeY(IAQGraphMin, IAQGraphMax);
    IAQGraphYellow.setGraphRangeY(IAQGraphMin, IAQGraphMax);
    IAQGraphRed.setGraphRangeY(IAQGraphMin, IAQGraphMax);
}
void MainView::displayIAQGraph24Hour(void)
{
    if(gui_iaq <= IAQ_LEVEL_GOOD)
    {
        IAQGraphYellow.addDataPoint(0);
        IAQGraphRed.addDataPoint(0);
        IAQGraphGreen.addDataPoint((int)gui_iaq);
    }
    else if(gui_iaq >= IAQ_LEVEL_GOOD && gui_iaq <= IAQ_LEVEL_BAD)
    {
        IAQGraphGreen.addDataPoint(0);
        IAQGraphRed.addDataPoint(0);
        IAQGraphYellow.addDataPoint((int)gui_iaq);
    }
    else
    {
        IAQGraphGreen.addDataPoint(0);
        IAQGraphYellow.addDataPoint(0);
        IAQGraphRed.addDataPoint((int)gui_iaq);
    }
    Unicode::snprintfFloat(IAQ_valueBuffer, IAQ_VALUE_SIZE, "%.1f", gui_iaq);
    IAQ_value.invalidate();
    setIAQGraphRangeY24Hour();
}
