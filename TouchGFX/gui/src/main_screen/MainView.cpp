#include <gui/main_screen/MainView.hpp>
#include "BitmapDatabase.hpp"
#include <touchgfx/Color.hpp>

#define IAQ_LEVEL_GOOD 0
#define IAQ_LEVEL_MODERATE 100
#define IAQ_LEVEL_BAD 200

#define CO2_LEVEL_GOOD 0
#define CO2_LEVEL_MODERATE 600
#define CO2_LEVEL_BAD 2500

#define VOC_LEVEL_GOOD 0
#define VOC_LEVEL_MODERATE 350
#define VOC_LEVEL_BAD 8300

#define HUM_LEVEL_GOOD 40
#define HUM_LEVEL_MODERATE_HIGH 50
#define HUM_LEVEL_MODERATE_LOW 40
#define HUM_LEVEL_BAD_HIGH 80
#define HUM_LEVEL_BAD_LOW 15

#define TEMP_LEVEL_GOOD 18
#define TEMP_LEVEL_MODERATE_HIGH 25
#define TEMP_LEVEL_MODERATE_LOW 18
#define TEMP_LEVEL_BAD_HIGH 33
#define TEMP_LEVEL_BAD_LOW 9

float IAQAverage24Hour[4]; /* 0 - total data value; 1 - data counter; 2 - 1 hour average value; 3 - 24 hour average value */
float CO2Average24Hour[4];
float VOCAverage24Hour[4];
float humAverage24Hour[4];
float presAverage24Hour[4];
float tempAverage24Hour[4];

uint8_t hourCnt = 0;

/* Variables imported from main */
uint8_t hours;
uint8_t minutes;
uint8_t seconds;
uint8_t year;
uint8_t month;
uint8_t date;
uint8_t weekDay;

extern uint32_t (*pfHAL_GetTick)(void);                                                   /* Pointer to HAL_GetTick imported from main*/
extern float gui_temperature;
extern float gui_humidity;
extern float gui_pressure;
extern float gui_iaq;
extern float gui_co2;
extern float gui_voc;
extern uint8_t gui_iaq_accuracy;

static uint32_t tickValue24Hour;                                                   /* Variable monitoring last tick value (HAL_GetTick) */
static uint32_t tickValueOneHour;

MainView::MainView()
{
    tickValue24Hour = pfHAL_GetTick();                                                             /* Initialize with actual tick value */
    for(uint8_t i = 0; i < 3; i++)                                                                            /* Array initialization */
    {
        IAQAverage24Hour[i] = 0;
        CO2Average24Hour[i] = 0;
        VOCAverage24Hour[i] = 0;
        humAverage24Hour[i] = 0;
        presAverage24Hour[i] = 0;
        tempAverage24Hour[i] = 0;
    }
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
    if(pfHAL_GetTick() - tickValueOneHour >= 3000)
    {
        calculateOneHourAverage();
        Unicode::snprintfFloat(text_24HBuffer, TEXT_24H_SIZE, "%.1f", gui_humidity);
        text_24H.invalidate();
        tickValueOneHour = pfHAL_GetTick();
    }
    else
    {
        //do nothing
    }

    if(pfHAL_GetTick() - tickValue24Hour >= 30000)
    {
        calculate24HourAverage();
        displayIAQGraph24Hour();
        displayCO2Graph24Hour();
        displayVOCGraph24Hour();
        displayPresGraph24Hour();
        displayHumGraph24Hour();
        displayTempGraph24Hour();
        resetOneHourAverage();
        if(hourCnt == 23)
        {
            reset24HourAverage();
            hourCnt = 0;
        }
        else
        {
            hourCnt++;
        }
        tickValue24Hour = pfHAL_GetTick();
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
    containerVisibilityOff();
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
    containerVisibilityOff();
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
    containerVisibilityOff();
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
    containerVisibilityOff();
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
    containerVisibilityOff();
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
    containerVisibilityOff();
    temp_container.setVisible(true);
    remove(temp_container);
    temp_container.invalidate();
    add(temp_container);
    box1.invalidate();
}

void MainView::resetOneHourAverage(void)
{
    for(uint8_t i = 0; i < 2; i++)
    {
        IAQAverage24Hour[i] = 0;
        CO2Average24Hour[i] = 0;
        VOCAverage24Hour[i] = 0;
        humAverage24Hour[i] = 0;
        presAverage24Hour[i] = 0;
        tempAverage24Hour[i] = 0;
    }
}

void MainView::reset24HourAverage(void)
{
    for(uint8_t i = 0; i < 3; i++)
    {
        IAQAverage24Hour[i] = 0;
        CO2Average24Hour[i] = 0;
        VOCAverage24Hour[i] = 0;
        humAverage24Hour[i] = 0;
        presAverage24Hour[i] = 0;
        tempAverage24Hour[i] = 0;
    }
}

void MainView::calculateOneHourAverage(void)
{
    IAQAverage24Hour[0] = ((IAQAverage24Hour[0] * IAQAverage24Hour[1]) + gui_iaq) / (IAQAverage24Hour[1] + 1);
    IAQAverage24Hour[1]++;

    CO2Average24Hour[0] = ((CO2Average24Hour[0] * CO2Average24Hour[1]) + gui_co2) / (CO2Average24Hour[1] + 1);
    CO2Average24Hour[1]++;

    VOCAverage24Hour[0] = ((VOCAverage24Hour[0] * VOCAverage24Hour[1]) + (gui_voc * 1000)) / (VOCAverage24Hour[1] + 1);
    VOCAverage24Hour[1]++;

    humAverage24Hour[0] = ((humAverage24Hour[0] * humAverage24Hour[1]) + gui_humidity) / (humAverage24Hour[1] + 1);
    humAverage24Hour[1]++;

    presAverage24Hour[0] = ((presAverage24Hour[0] * presAverage24Hour[1]) + gui_pressure) / (presAverage24Hour[1] + 1);
    presAverage24Hour[1]++;

    tempAverage24Hour[0] = ((tempAverage24Hour[0] * tempAverage24Hour[1]) + gui_temperature) / (tempAverage24Hour[1] + 1);
    tempAverage24Hour[1]++;
}

void MainView::calculate24HourAverage(void)
{
    IAQAverage24Hour[2] = ((IAQAverage24Hour[2] * hourCnt) + IAQAverage24Hour[0]) / (hourCnt + 1);
    CO2Average24Hour[2] = ((CO2Average24Hour[2] * hourCnt) + CO2Average24Hour[0]) / (hourCnt + 1);
    VOCAverage24Hour[2] = ((VOCAverage24Hour[2] * hourCnt) + VOCAverage24Hour[0]) / (hourCnt + 1);
    humAverage24Hour[2] = ((humAverage24Hour[2] * hourCnt) + humAverage24Hour[0]) / (hourCnt + 1);
    presAverage24Hour[2] = ((presAverage24Hour[2] * hourCnt) + presAverage24Hour[0]) / (hourCnt + 1);
    tempAverage24Hour[2] = ((tempAverage24Hour[2] * hourCnt) + tempAverage24Hour[0]) / (hourCnt + 1);
}

void MainView::containerVisibilityOff(void)
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

    IAQGraphGreenMax =  IAQGraphGreen.getGraphRangeYMaxAsFloat();
    IAQGraphYellowMax = IAQGraphYellow.getGraphRangeYMaxAsFloat();
    IAQGraphRedMax =    IAQGraphRed.getGraphRangeYMaxAsFloat();

    IAQGraphGreenMin =  IAQGraphGreen.getGraphRangeYMinAsFloat();
    IAQGraphYellowMin = IAQGraphYellow.getGraphRangeYMinAsFloat();
    IAQGraphRedMin =    IAQGraphRed.getGraphRangeYMinAsFloat();
    if((IAQGraphGreenMax > IAQGraphYellowMax) && (IAQGraphGreenMax > IAQGraphRedMax))
    {
        IAQGraphMax = IAQGraphGreenMax;
    }
    else if(((IAQGraphYellowMax > IAQGraphGreenMax) && (IAQGraphYellowMax > IAQGraphRedMax)))
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
    IAQGraphGreen.setGraphRangeY (IAQGraphMin, IAQGraphMax);
    IAQGraphYellow.setGraphRangeY(IAQGraphMin, IAQGraphMax);
    IAQGraphRed.setGraphRangeY   (IAQGraphMin, IAQGraphMax);
}
void MainView::displayIAQGraph24Hour(void)
{
    if(gui_iaq_accuracy == 0)
    {
        IAQ_wait.setVisible(true);
        IAQ_good.setVisible(false);
        IAQ_moderate.setVisible(false);
        IAQ_bad.setVisible(false);

        IAQ_text_run.setVisible(false);
        IAQ_text_wait.setVisible(true);
    }
    else
    {
        IAQ_wait.setVisible(false);
        IAQ_text_run.setVisible(true);
        IAQ_text_wait.setVisible(false);
        IAQ_value.setVisible(true);

        /*Setting of histogram bar color*/
        if(IAQAverage24Hour[0] > IAQ_LEVEL_GOOD && IAQAverage24Hour[0] < IAQ_LEVEL_MODERATE)
        {
            IAQGraphYellow.addDataPoint(0);
            IAQGraphRed.addDataPoint(0);
            IAQGraphGreen.addDataPoint(IAQAverage24Hour[0]);
        }
        else if(IAQAverage24Hour[0] > IAQ_LEVEL_MODERATE && IAQAverage24Hour[0] < IAQ_LEVEL_BAD)
        {
            IAQGraphGreen.addDataPoint(0);
            IAQGraphRed.addDataPoint(0);
            IAQGraphYellow.addDataPoint(IAQAverage24Hour[0]);
        }
        else if (IAQAverage24Hour[0] > IAQ_LEVEL_BAD)
        {
            IAQGraphGreen.addDataPoint(0);
            IAQGraphYellow.addDataPoint(0);
            IAQGraphRed.addDataPoint(IAQAverage24Hour[0]);
        }
        else
        {
            //do nothing
        }

        /* Setting of onboard screen color */
        if(IAQAverage24Hour[2] > IAQ_LEVEL_GOOD && IAQAverage24Hour[2] < IAQ_LEVEL_MODERATE)
        {
            IAQ_good.setVisible(true);
            IAQ_moderate.setVisible(false);
            IAQ_bad.setVisible(false);
        }
        else if(IAQAverage24Hour[2] > IAQ_LEVEL_MODERATE && IAQAverage24Hour[2] < IAQ_LEVEL_BAD)
        {
            IAQ_good.setVisible(false);
            IAQ_moderate.setVisible(true);
            IAQ_bad.setVisible(false);
        }
        else if (IAQAverage24Hour[2] > IAQ_LEVEL_BAD)
        {
            IAQ_good.setVisible(false);
            IAQ_moderate.setVisible(false);
            IAQ_bad.setVisible(true);
        }
        else
        {
            //do nothing
        }

        Unicode::snprintfFloat(IAQ_valueBuffer, IAQ_VALUE_SIZE, "%.1f", IAQAverage24Hour[2]);
        IAQ_value.invalidate();
        setIAQGraphRangeY24Hour();
    }
    box1.invalidate();
}

void MainView::setCO2GraphRangeY24Hour(void)
{
    uint16_t CO2GraphMin = 0;
    uint16_t CO2GraphMax = 0;
    uint16_t CO2GraphGreenMin = 0;
    uint16_t CO2GraphGreenMax = 0;
    uint16_t CO2GraphYellowMin = 0;
    uint16_t CO2GraphYellowMax = 0;
    uint16_t CO2GraphRedMin = 0;
    uint16_t CO2GraphRedMax = 0;

    CO2GraphGreen.setGraphRangeYAuto(false, 5);
    CO2GraphYellow.setGraphRangeYAuto(false, 5);
    CO2GraphRed.setGraphRangeYAuto(false, 5);

    CO2GraphGreenMax =  CO2GraphGreen.getGraphRangeYMaxAsFloat();
    CO2GraphYellowMax = CO2GraphYellow.getGraphRangeYMaxAsFloat();
    CO2GraphRedMax =    CO2GraphRed.getGraphRangeYMaxAsFloat();

    CO2GraphGreenMin =  CO2GraphGreen.getGraphRangeYMinAsFloat();
    CO2GraphYellowMin = CO2GraphYellow.getGraphRangeYMinAsFloat();
    CO2GraphRedMin =    CO2GraphRed.getGraphRangeYMinAsFloat();
    if((CO2GraphGreenMax > CO2GraphYellowMax) && (CO2GraphGreenMax > CO2GraphRedMax))
    {
        CO2GraphMax = CO2GraphGreenMax;
    }
    else if(((CO2GraphYellowMax > CO2GraphGreenMax) && (CO2GraphYellowMax > CO2GraphRedMax)))
    {
        CO2GraphMax = CO2GraphYellowMax;
    }
    else
    {
        CO2GraphMax = CO2GraphRedMax;
    }

    if((CO2GraphGreenMin < CO2GraphYellowMin) && (CO2GraphGreenMin < CO2GraphRedMin))
    {
        CO2GraphMin = CO2GraphGreenMin;
    }
    else if(((CO2GraphYellowMin < CO2GraphGreenMin) && (CO2GraphYellowMin < CO2GraphRedMin)))
    {
        CO2GraphMin = CO2GraphYellowMin;
    }
    else
    {
        CO2GraphMin = CO2GraphRedMin;
    }
    CO2GraphGreen.setGraphRangeY (CO2GraphMin, CO2GraphMax);
    CO2GraphYellow.setGraphRangeY(CO2GraphMin, CO2GraphMax);
    CO2GraphRed.setGraphRangeY   (CO2GraphMin, CO2GraphMax);
}

void MainView::displayCO2Graph24Hour(void)
{
    if(gui_iaq_accuracy == 0)
    {
        CO2_wait.setVisible(true);
        CO2_good.setVisible(false);
        CO2_moderate.setVisible(false);
        CO2_bad.setVisible(false);

        CO2_text_run.setVisible(false);
        CO2_text_wait.setVisible(true);
    }
    else
    {
        CO2_wait.setVisible(false);
        CO2_text_run.setVisible(true);
        CO2_text_wait.setVisible(false);
        CO2_value.setVisible(true);

        if(CO2Average24Hour[0] > CO2_LEVEL_GOOD && CO2Average24Hour[0] < CO2_LEVEL_MODERATE)
        {
            CO2GraphYellow.addDataPoint(0);
            CO2GraphRed.addDataPoint(0);
            CO2GraphGreen.addDataPoint((int)CO2Average24Hour[0]);
        }
        else if(CO2Average24Hour[0] > CO2_LEVEL_MODERATE && CO2Average24Hour[0] < CO2_LEVEL_BAD)
        {
            CO2GraphGreen.addDataPoint(0);
            CO2GraphRed.addDataPoint(0);
            CO2GraphYellow.addDataPoint((int)CO2Average24Hour[0]);
        }
        else if (CO2Average24Hour[0] > CO2_LEVEL_BAD)
        {
            CO2GraphGreen.addDataPoint(0);
            CO2GraphYellow.addDataPoint(0);
            CO2GraphRed.addDataPoint((int)CO2Average24Hour[0]);
        }
        else
        {
            //do nothing
        }

        if(CO2Average24Hour[2] > CO2_LEVEL_GOOD && CO2Average24Hour[2] < CO2_LEVEL_MODERATE)
        {
            CO2_good.setVisible(true);
            CO2_moderate.setVisible(false);
            CO2_bad.setVisible(false);
        }
        else if(CO2Average24Hour[2] > CO2_LEVEL_MODERATE && CO2Average24Hour[2] < CO2_LEVEL_BAD)
        {
            CO2_good.setVisible(false);
            CO2_moderate.setVisible(true);
            CO2_bad.setVisible(false);
        }
        else if (CO2Average24Hour[2] > CO2_LEVEL_BAD)
        {
            CO2_good.setVisible(false);
            CO2_moderate.setVisible(false);
            CO2_bad.setVisible(true);
        }
        else
        {
            //do nothing
        }

        Unicode::snprintfFloat(CO2_valueBuffer, CO2_VALUE_SIZE, "%.0f", CO2Average24Hour[2]);
        CO2_value.invalidate();
        setCO2GraphRangeY24Hour();
    }
    box1.invalidate();
}

void MainView::setVOCGraphRangeY24Hour(void)
{
    uint16_t VOCGraphMin = 0;
    uint16_t VOCGraphMax = 0;
    uint16_t VOCGraphGreenMin = 0;
    uint16_t VOCGraphGreenMax = 0;
    uint16_t VOCGraphYellowMin = 0;
    uint16_t VOCGraphYellowMax = 0;
    uint16_t VOCGraphRedMin = 0;
    uint16_t VOCGraphRedMax = 0;

    VOCGraphGreen.setGraphRangeYAuto(false, 5);
    VOCGraphYellow.setGraphRangeYAuto(false, 5);
    VOCGraphRed.setGraphRangeYAuto(false, 5);

    VOCGraphGreenMax =  VOCGraphGreen.getGraphRangeYMaxAsFloat();
    VOCGraphYellowMax = VOCGraphYellow.getGraphRangeYMaxAsFloat();
    VOCGraphRedMax =    VOCGraphRed.getGraphRangeYMaxAsFloat();

    VOCGraphGreenMin =  VOCGraphGreen.getGraphRangeYMinAsFloat();
    VOCGraphYellowMin = VOCGraphYellow.getGraphRangeYMinAsFloat();
    VOCGraphRedMin =    VOCGraphRed.getGraphRangeYMinAsFloat();
    if((VOCGraphGreenMax > VOCGraphYellowMax) && (VOCGraphGreenMax > VOCGraphRedMax))
    {
        VOCGraphMax = VOCGraphGreenMax;
    }
    else if(((VOCGraphYellowMax > VOCGraphGreenMax) && (VOCGraphYellowMax > VOCGraphRedMax)))
    {
        VOCGraphMax = VOCGraphYellowMax;
    }
    else
    {
        VOCGraphMax = VOCGraphRedMax;
    }

    if((VOCGraphGreenMin < VOCGraphYellowMin) && (VOCGraphGreenMin < VOCGraphRedMin))
    {
        VOCGraphMin = VOCGraphGreenMin;
    }
    else if(((VOCGraphYellowMin < VOCGraphGreenMin) && (VOCGraphYellowMin < VOCGraphRedMin)))
    {
        VOCGraphMin = VOCGraphYellowMin;
    }
    else
    {
        VOCGraphMin = VOCGraphRedMin;
    }
    VOCGraphGreen.setGraphRangeY (VOCGraphMin, VOCGraphMax);
    VOCGraphYellow.setGraphRangeY(VOCGraphMin, VOCGraphMax);
    VOCGraphRed.setGraphRangeY   (VOCGraphMin, VOCGraphMax);
}

void MainView::displayVOCGraph24Hour(void)
{
    if(gui_iaq_accuracy == 0)
    {
        VOC_wait.setVisible(true);
        VOC_good.setVisible(false);
        VOC_moderate.setVisible(false);
        VOC_bad.setVisible(false);

        VOC_text_run.setVisible(false);
        VOC_text_wait.setVisible(true);
    }
    else
    {
        VOC_wait.setVisible(false);
        VOC_text_run.setVisible(true);
        VOC_text_wait.setVisible(false);
        VOC_value.setVisible(true);

        if(VOCAverage24Hour[0] > VOC_LEVEL_GOOD && VOCAverage24Hour[0] < VOC_LEVEL_MODERATE)
        {
            VOCGraphYellow.addDataPoint(0);
            VOCGraphRed.addDataPoint(0);
            VOCGraphGreen.addDataPoint((int)VOCAverage24Hour[0]);
        }
        else if(VOCAverage24Hour[0] > VOC_LEVEL_MODERATE && VOCAverage24Hour[0] < VOC_LEVEL_BAD)
        {
            VOCGraphGreen.addDataPoint(0);
            VOCGraphRed.addDataPoint(0);
            VOCGraphYellow.addDataPoint((int)VOCAverage24Hour[0]);
        }
        else if (VOCAverage24Hour[0] > VOC_LEVEL_BAD)
        {
            VOCGraphGreen.addDataPoint(0);
            VOCGraphYellow.addDataPoint(0);
            VOCGraphRed.addDataPoint((int)VOCAverage24Hour[0]);
        }
        else
        {
            //do nothing
        }

        if(VOCAverage24Hour[2] > VOC_LEVEL_GOOD && VOCAverage24Hour[2] < VOC_LEVEL_MODERATE)
        {
            VOC_good.setVisible(true);
            VOC_moderate.setVisible(false);
            VOC_bad.setVisible(false);
        }
        else if(VOCAverage24Hour[2] > VOC_LEVEL_MODERATE && VOCAverage24Hour[2] < VOC_LEVEL_BAD)
        {
            VOC_good.setVisible(false);
            VOC_moderate.setVisible(true);
            VOC_bad.setVisible(false);
        }
        else if (VOCAverage24Hour[2] > VOC_LEVEL_BAD)
        {
            VOC_good.setVisible(false);
            VOC_moderate.setVisible(false);
            VOC_bad.setVisible(true);
        }
        else
        {
            //do nothing
        }

        Unicode::snprintfFloat(VOC_valueBuffer, VOC_VALUE_SIZE, "%.0f", VOCAverage24Hour[2]);
        VOC_value.invalidate();
        setVOCGraphRangeY24Hour();
    }
    box1.invalidate();
}

void MainView::setHumGraphRangeY24Hour(void)
{
    uint16_t humGraphMin = 0;
    uint16_t humGraphMax = 0;
    uint16_t humGraphGreenMin = 0;
    uint16_t humGraphGreenMax = 0;
    uint16_t humGraphYellowMin = 0;
    uint16_t humGraphYellowMax = 0;
    uint16_t humGraphRedMin = 0;
    uint16_t humGraphRedMax = 0;

    humGraphGreen.setGraphRangeYAuto(false, 5);
    humGraphYellow.setGraphRangeYAuto(false, 5);
    humGraphRed.setGraphRangeYAuto(false, 5);

    humGraphGreenMax =  humGraphGreen.getGraphRangeYMaxAsFloat();
    humGraphYellowMax = humGraphYellow.getGraphRangeYMaxAsFloat();
    humGraphRedMax =    humGraphRed.getGraphRangeYMaxAsFloat();

    humGraphGreenMin =  humGraphGreen.getGraphRangeYMinAsFloat();
    humGraphYellowMin = humGraphYellow.getGraphRangeYMinAsFloat();
    humGraphRedMin =    humGraphRed.getGraphRangeYMinAsFloat();
    if((humGraphGreenMax > humGraphYellowMax) && (humGraphGreenMax > humGraphRedMax))
    {
        humGraphMax = humGraphGreenMax;
    }
    else if(((humGraphYellowMax > humGraphGreenMax) && (humGraphYellowMax > humGraphRedMax)))
    {
        humGraphMax = humGraphYellowMax;
    }
    else
    {
        humGraphMax = humGraphRedMax;
    }

    if((humGraphGreenMin < humGraphYellowMin) && (humGraphGreenMin < humGraphRedMin))
    {
        humGraphMin = humGraphGreenMin;
    }
    else if(((humGraphYellowMin < humGraphGreenMin) && (humGraphYellowMin < humGraphRedMin)))
    {
        humGraphMin = humGraphYellowMin;
    }
    else
    {
        humGraphMin = humGraphRedMin;
    }
    humGraphGreen.setGraphRangeY (humGraphMin, humGraphMax);
    humGraphYellow.setGraphRangeY(humGraphMin, humGraphMax);
    humGraphRed.setGraphRangeY   (humGraphMin, humGraphMax);
}
void MainView::displayHumGraph24Hour(void)
{
    if(gui_humidity == 0)
    {
        hum_wait.setVisible(true);
        hum_good.setVisible(false);
        hum_moderate.setVisible(false);
        hum_bad.setVisible(false);

        hum_text_run.setVisible(false);
        hum_text_wait.setVisible(true);
    }
    else
    {
        hum_wait.setVisible(false);
        hum_value.setVisible(true);
        hum_text_run.setVisible(true);
        hum_text_wait.setVisible(false);

        if(humAverage24Hour[0] > HUM_LEVEL_GOOD && humAverage24Hour[0] < HUM_LEVEL_MODERATE_HIGH)
        {
            humGraphYellow.addDataPoint(0);
            humGraphRed.addDataPoint(0);
            humGraphGreen.addDataPoint(humAverage24Hour[0]);
        }
        else if( (humAverage24Hour[0] > HUM_LEVEL_MODERATE_HIGH && humAverage24Hour[0] < HUM_LEVEL_BAD_HIGH) ||
                 (humAverage24Hour[0] < HUM_LEVEL_MODERATE_LOW  && humAverage24Hour[0] > HUM_LEVEL_BAD_LOW)    )
        {
            humGraphGreen.addDataPoint(0);
            humGraphRed.addDataPoint(0);
            humGraphYellow.addDataPoint(humAverage24Hour[0]);
        }
        else if (humAverage24Hour[0] > HUM_LEVEL_BAD_HIGH && humAverage24Hour[0] < HUM_LEVEL_BAD_LOW)
        {
            humGraphGreen.addDataPoint(0);
            humGraphYellow.addDataPoint(0);
            humGraphRed.addDataPoint(humAverage24Hour[0]);
        }
        else
        {
            //do nothing
        }

        if(humAverage24Hour[2] > HUM_LEVEL_GOOD && humAverage24Hour[2] < HUM_LEVEL_MODERATE_HIGH)
        {
            hum_good.setVisible(true);
            hum_moderate.setVisible(false);
            hum_bad.setVisible(false);
        }
        else if( (humAverage24Hour[2] > HUM_LEVEL_MODERATE_HIGH && humAverage24Hour[2] < HUM_LEVEL_BAD_HIGH) ||
                 (humAverage24Hour[2] < HUM_LEVEL_MODERATE_LOW  && humAverage24Hour[2] > HUM_LEVEL_BAD_LOW)    )
        {
            hum_good.setVisible(false);
            hum_moderate.setVisible(true);
            hum_bad.setVisible(false);
        }
        else if (humAverage24Hour[2] > HUM_LEVEL_BAD_HIGH && humAverage24Hour[2] < HUM_LEVEL_BAD_LOW)
        {
            hum_good.setVisible(false);
            hum_moderate.setVisible(false);
            hum_bad.setVisible(true);
        }
        else
        {
            //do nothing
        }

        Unicode::snprintfFloat(text_1HBuffer, TEXT_1H_SIZE, "%.1f", humAverage24Hour[0]);
        Unicode::snprintfFloat(hum_valueBuffer, HUM_VALUE_SIZE, "%.1f", humAverage24Hour[2]);
        hum_value.invalidate();
        setHumGraphRangeY24Hour();
    }
    box1.invalidate();
}

void MainView::setPresGraphRangeY24Hour(void)
{
    uint16_t presGraphMin = 0;
    uint16_t presGraphMax = 0;

    presGraph.setGraphRangeYAuto(false, 5);
    presGraphMax =  presGraph.getGraphRangeYMaxAsFloat();
    presGraphMin =  presGraph.getGraphRangeYMinAsFloat();
    presGraph.setGraphRangeY (presGraphMin, presGraphMax);
}
void MainView::displayPresGraph24Hour(void)
{
    if(gui_pressure == 0)
    {
        pres_wait.setVisible(true);
        pres_run.setVisible(false);

        pres_text_run.setVisible(false);
        pres_text_wait.setVisible(true);
    }
    else
    {
        pres_wait.setVisible(false);
        pres_run.setVisible(true);
        pres_value.setVisible(true);
        pres_text_run.setVisible(true);
        pres_text_wait.setVisible(false);
        presGraph.addDataPoint(presAverage24Hour[0]);

        Unicode::snprintfFloat(pres_valueBuffer, PRES_VALUE_SIZE, "%.1f", presAverage24Hour[2]);
        pres_value.invalidate();
        setPresGraphRangeY24Hour();
    }
    box1.invalidate();
}

void MainView::setTempGraphRangeY24Hour(void)
{
    uint16_t tempGraphMin = 0;
    uint16_t tempGraphMax = 0;
    uint16_t tempGraphGreenMin = 0;
    uint16_t tempGraphGreenMax = 0;
    uint16_t tempGraphYellowMin = 0;
    uint16_t tempGraphYellowMax = 0;
    uint16_t tempGraphRedMin = 0;
    uint16_t tempGraphRedMax = 0;

    tempGraphGreen.setGraphRangeYAuto(false, 5);
    tempGraphYellow.setGraphRangeYAuto(false, 5);
    tempGraphRed.setGraphRangeYAuto(false, 5);

    tempGraphGreenMax =  tempGraphGreen.getGraphRangeYMaxAsFloat();
    tempGraphYellowMax = tempGraphYellow.getGraphRangeYMaxAsFloat();
    tempGraphRedMax =    tempGraphRed.getGraphRangeYMaxAsFloat();

    tempGraphGreenMin =  tempGraphGreen.getGraphRangeYMinAsFloat();
    tempGraphYellowMin = tempGraphYellow.getGraphRangeYMinAsFloat();
    tempGraphRedMin =    tempGraphRed.getGraphRangeYMinAsFloat();
    if((tempGraphGreenMax > tempGraphYellowMax) && (tempGraphGreenMax > tempGraphRedMax))
    {
        tempGraphMax = tempGraphGreenMax;
    }
    else if(((tempGraphYellowMax > tempGraphGreenMax) && (tempGraphYellowMax > tempGraphRedMax)))
    {
        tempGraphMax = tempGraphYellowMax;
    }
    else
    {
        tempGraphMax = tempGraphRedMax;
    }

    if((tempGraphGreenMin < tempGraphYellowMin) && (tempGraphGreenMin < tempGraphRedMin))
    {
        tempGraphMin = tempGraphGreenMin;
    }
    else if(((tempGraphYellowMin < tempGraphGreenMin) && (tempGraphYellowMin < tempGraphRedMin)))
    {
        tempGraphMin = tempGraphYellowMin;
    }
    else
    {
        tempGraphMin = tempGraphRedMin;
    }
    tempGraphGreen.setGraphRangeY (tempGraphMin, tempGraphMax);
    tempGraphYellow.setGraphRangeY(tempGraphMin, tempGraphMax);
    tempGraphRed.setGraphRangeY   (tempGraphMin, tempGraphMax);
}
void MainView::displayTempGraph24Hour(void)
{
    if(gui_temperature == 0)
    {
        temp_wait.setVisible(true);
        temp_good.setVisible(false);
        temp_moderate.setVisible(false);
        temp_bad.setVisible(false);

        temp_text_run.setVisible(false);
        temp_text_wait.setVisible(true);
    }
    else
    {
        temp_wait.setVisible(false);
        temp_value.setVisible(true);
        temp_text_run.setVisible(true);
        temp_text_wait.setVisible(false);

        if(tempAverage24Hour[0] > TEMP_LEVEL_GOOD && tempAverage24Hour[0] < TEMP_LEVEL_MODERATE_HIGH)
        {
            tempGraphYellow.addDataPoint(0);
            tempGraphRed.addDataPoint(0);
            tempGraphGreen.addDataPoint(tempAverage24Hour[0]);
        }
        else if( (tempAverage24Hour[0] > TEMP_LEVEL_MODERATE_HIGH && tempAverage24Hour[0] < TEMP_LEVEL_BAD_HIGH) ||
                 (tempAverage24Hour[0] < TEMP_LEVEL_MODERATE_LOW  && tempAverage24Hour[0] > TEMP_LEVEL_BAD_LOW)    )
        {
            tempGraphGreen.addDataPoint(0);
            tempGraphRed.addDataPoint(0);
            tempGraphYellow.addDataPoint(tempAverage24Hour[0]);
        }
        else if (tempAverage24Hour[0] > TEMP_LEVEL_BAD_HIGH && tempAverage24Hour[0] < TEMP_LEVEL_BAD_LOW)
        {
            tempGraphGreen.addDataPoint(0);
            tempGraphYellow.addDataPoint(0);
            tempGraphRed.addDataPoint(tempAverage24Hour[0]);
        }
        else
        {
            //do nothing
        }

        if(tempAverage24Hour[2] > TEMP_LEVEL_GOOD && tempAverage24Hour[2] < TEMP_LEVEL_MODERATE_HIGH)
        {
            temp_good.setVisible(true);
            temp_moderate.setVisible(false);
            temp_bad.setVisible(false);
        }
        else if( (tempAverage24Hour[2] > TEMP_LEVEL_MODERATE_HIGH && tempAverage24Hour[2] < TEMP_LEVEL_BAD_HIGH) ||
                 (tempAverage24Hour[2] < TEMP_LEVEL_MODERATE_LOW  && tempAverage24Hour[2] > TEMP_LEVEL_BAD_LOW)    )
        {
            temp_good.setVisible(false);
            temp_moderate.setVisible(true);
            temp_bad.setVisible(false);
        }
        else if (tempAverage24Hour[2] > TEMP_LEVEL_BAD_HIGH && tempAverage24Hour[2] < TEMP_LEVEL_BAD_LOW)
        {
            temp_good.setVisible(false);
            temp_moderate.setVisible(false);
            temp_bad.setVisible(true);
        }
        else
        {
            //do nothing
        }

        Unicode::snprintfFloat(temp_valueBuffer, TEMP_VALUE_SIZE, "%.1f", tempAverage24Hour[2]);
        temp_value.invalidate();
        setTempGraphRangeY24Hour();
    }
    box1.invalidate();
}
