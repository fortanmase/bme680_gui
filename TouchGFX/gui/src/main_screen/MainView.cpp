#include <gui/main_screen/MainView.hpp>
#include "BitmapDatabase.hpp"
#include <touchgfx/Color.hpp>

extern uint32_t (*pfHAL_GetTick)(void);                                                   /* Pointer to HAL_GetTick imported from main*/
extern float gui_temperature;
extern float gui_humidity;
extern float gui_pressure;
extern float gui_iaq;
extern float gui_co2;
extern float gui_voc;
extern uint8_t gui_iaq_accuracy;

/* Variables imported from main */
extern uint8_t hours;
extern uint8_t minutes;
extern uint8_t seconds;
extern uint8_t year;
extern uint8_t month;
extern uint8_t date;
extern uint8_t weekDay;

static uint8_t filterCounter = 0;
static kalman filterObject[5];

static float filtredTemp = 0;
static float filtredHum = 0;
static float filtredPres = 0;
static float filtredIAQ = 0;

static float calcIAQAverage[3];         //Array to calculate average data: 0 - 1 hour average, 1 - data counter, 2 - 24 hour average
static float calcCO2Average[3];
static float calcVOCAverage[3];
static float calcHumAverage[3];
static float calcPresAverage[3];
static float calcTempAverage[3];

static float IAQAverage24Hour[24];         /* Array to hold 24 hours average data */
static float CO2Average24Hour[24];
static float VOCAverage24Hour[24];
static float humAverage24Hour[24];
static float presAverage24Hour[24];
static float tempAverage24Hour[24];

static uint8_t hourCnt = 0;
static uint8_t lastHoursValue = 0;

static uint32_t tickValue24Hour;                                                   /* Variable monitoring last tick value (HAL_GetTick) */
static uint32_t tickValueOneHour;
static uint32_t lastTickValue;

static uint8_t IAQSelectFlag = 0;
static uint8_t CO2SelectFlag = 0;
static uint8_t VOCSelectFlag = 0;
static uint8_t humSelectFlag = 0;
static uint8_t presSelectFlag = 0;
static uint8_t tempSelectFlag = 0;

static uint8_t IAQInitFlag = 0;
static uint8_t CO2InitFlag = 0;
static uint8_t VOCInitFlag = 0;
static uint8_t humInitFlag = 0;
static uint8_t presInitFlag = 0;
static uint8_t tempInitFlag = 0;

MainView::MainView()
{
    tickValue24Hour = pfHAL_GetTick();                                                             /* Initialize with actual tick value */
    tickValueOneHour = pfHAL_GetTick();
    lastTickValue = pfHAL_GetTick();
    for(uint8_t i = 0; i < 3; i++)                                                                             /* Array initialization */
    {
        calcIAQAverage[i] = 0;
        calcCO2Average[i] = 0;
        calcVOCAverage[i] = 0;
        calcHumAverage[i] = 0;
        calcPresAverage[i] = 0;
        calcTempAverage[i] = 0;
    }

    for(uint8_t i = 0; i < 24; i++)                                                                             /* Array initialization */
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
        tickValueOneHour = pfHAL_GetTick();
    }
    else
    {
        //do nothing
    }

    if(pfHAL_GetTick() - tickValue24Hour >= 60000)
    {
        calculate24HourAverage();
        displayIAQGraph24Hour(calcIAQAverage[0]);
        displayCO2Graph24Hour(calcCO2Average[0]);
        displayVOCGraph24Hour(calcVOCAverage[0]);
        displayPresGraph24Hour(calcPresAverage[0]);
        displayHumGraph24Hour(calcHumAverage[0]);
        displayTempGraph24Hour(calcTempAverage[0]);
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

    if(pfHAL_GetTick() - lastTickValue >= 375)    /* we have 100 points on x-Axis so we have to add a new data point once in 1.66 sec */
    {                                             /* in order to hold a 10 min interval on the graph, the data is filtered 7 times     */
                                                  /* before displayed, so 238ms * 7 = 1.66 sec                                         */
        if(filterCounter == 8)
        {
            /* Display the graphs*/
            displayTemperatureGraph(filtredTemp);
            displayHumidityGraph(filtredHum);
            displayPressureGraph(filtredPres);
            displayIAQGraph(filtredIAQ);
            filterCounter = 0;
        }
        else
        {
            filterCounter++;
            filterData();
        }
        lastTickValue = pfHAL_GetTick();             /* refresh the actual tick value */
    }
    else
    {
        //do nothing
    }
}

void MainView::IAQSelect()
{
    resetSelectFlags();
    IAQSelectFlag = true;
    line2_menu.setVisible(true);
    line2_menu.setX(IAQ_button.getX());
    IAQ_button.setBitmaps(touchgfx::Bitmap(BITMAP_IAQ_DARK_ID), touchgfx::Bitmap(BITMAP_IAQ_DARK_ID));
    CO2_button.setBitmaps(touchgfx::Bitmap(BITMAP_CO2_LIGHT_ID), touchgfx::Bitmap(BITMAP_CO2_LIGHT_ID));
    VOC_button.setBitmaps(touchgfx::Bitmap(BITMAP_VOC_LIGHT_ID), touchgfx::Bitmap(BITMAP_VOC_LIGHT_ID));
    hum_button.setBitmaps(touchgfx::Bitmap(BITMAP_HUM_LIGHT_ID), touchgfx::Bitmap(BITMAP_HUM_LIGHT_ID));
    pres_button.setBitmaps(touchgfx::Bitmap(BITMAP_PRES_LIGHT_ID), touchgfx::Bitmap(BITMAP_PRES_LIGHT_ID));
    temp_button.setBitmaps(touchgfx::Bitmap(BITMAP_TEMP_LIGHT_ID), touchgfx::Bitmap(BITMAP_TEMP_LIGHT_ID));
    containerVisibilityOff();
    IAQ_container.setVisible(true);
    if(IAQInitFlag == true)
    {
        hours_xAxis_Container.setVisible(true);
    }
    else
    {
        //do nothing
    }
    box1.invalidate();
}

void MainView::CO2Select()
{
    resetSelectFlags();
    CO2SelectFlag = true;
    line2_menu.setVisible(true);
    line2_menu.setX(CO2_button.getX());
    IAQ_button.setBitmaps(touchgfx::Bitmap(BITMAP_IAQ_LIGHT_ID), touchgfx::Bitmap(BITMAP_IAQ_LIGHT_ID));
    CO2_button.setBitmaps(touchgfx::Bitmap(BITMAP_CO2_DARK_ID), touchgfx::Bitmap(BITMAP_CO2_DARK_ID));
    VOC_button.setBitmaps(touchgfx::Bitmap(BITMAP_VOC_LIGHT_ID), touchgfx::Bitmap(BITMAP_VOC_LIGHT_ID));
    hum_button.setBitmaps(touchgfx::Bitmap(BITMAP_HUM_LIGHT_ID), touchgfx::Bitmap(BITMAP_HUM_LIGHT_ID));
    pres_button.setBitmaps(touchgfx::Bitmap(BITMAP_PRES_LIGHT_ID), touchgfx::Bitmap(BITMAP_PRES_LIGHT_ID));
    temp_button.setBitmaps(touchgfx::Bitmap(BITMAP_TEMP_LIGHT_ID), touchgfx::Bitmap(BITMAP_TEMP_LIGHT_ID));
    containerVisibilityOff();
    CO2_container.setVisible(true);
    if(CO2InitFlag == true)
    {
        hours_xAxis_Container.setVisible(true);
    }
    else
    {
        //do nothing
    }
    box1.invalidate();
}

void MainView::VOCSelect()
{
    resetSelectFlags();
    VOCSelectFlag = true;
    line2_menu.setVisible(true);
    line2_menu.setX(VOC_button.getX());
    IAQ_button.setBitmaps(touchgfx::Bitmap(BITMAP_IAQ_LIGHT_ID), touchgfx::Bitmap(BITMAP_IAQ_LIGHT_ID));
    CO2_button.setBitmaps(touchgfx::Bitmap(BITMAP_CO2_LIGHT_ID), touchgfx::Bitmap(BITMAP_CO2_LIGHT_ID));
    VOC_button.setBitmaps(touchgfx::Bitmap(BITMAP_VOC_DARK_ID), touchgfx::Bitmap(BITMAP_VOC_DARK_ID));
    hum_button.setBitmaps(touchgfx::Bitmap(BITMAP_HUM_LIGHT_ID), touchgfx::Bitmap(BITMAP_HUM_LIGHT_ID));
    pres_button.setBitmaps(touchgfx::Bitmap(BITMAP_PRES_LIGHT_ID), touchgfx::Bitmap(BITMAP_PRES_LIGHT_ID));
    temp_button.setBitmaps(touchgfx::Bitmap(BITMAP_TEMP_LIGHT_ID), touchgfx::Bitmap(BITMAP_TEMP_LIGHT_ID));
    containerVisibilityOff();
    VOC_container.setVisible(true);
    if(VOCInitFlag == true)
    {
        hours_xAxis_Container.setVisible(true);
    }
    else
    {
        //do nothing
    }
    box1.invalidate();
}

void MainView::humSelect()
{
    resetSelectFlags();
    humSelectFlag = true;
    line2_menu.setVisible(true);
    line2_menu.setX(hum_button.getX());
    IAQ_button.setBitmaps(touchgfx::Bitmap(BITMAP_IAQ_LIGHT_ID), touchgfx::Bitmap(BITMAP_IAQ_LIGHT_ID));
    CO2_button.setBitmaps(touchgfx::Bitmap(BITMAP_CO2_LIGHT_ID), touchgfx::Bitmap(BITMAP_CO2_LIGHT_ID));
    VOC_button.setBitmaps(touchgfx::Bitmap(BITMAP_VOC_LIGHT_ID), touchgfx::Bitmap(BITMAP_VOC_LIGHT_ID));
    hum_button.setBitmaps(touchgfx::Bitmap(BITMAP_HUM_DARK_ID), touchgfx::Bitmap(BITMAP_HUM_DARK_ID));
    pres_button.setBitmaps(touchgfx::Bitmap(BITMAP_PRES_LIGHT_ID), touchgfx::Bitmap(BITMAP_PRES_LIGHT_ID));
    temp_button.setBitmaps(touchgfx::Bitmap(BITMAP_TEMP_LIGHT_ID), touchgfx::Bitmap(BITMAP_TEMP_LIGHT_ID));
    containerVisibilityOff();
    hum_container.setVisible(true);
    if(humInitFlag == true)
    {
        hours_xAxis_Container.setVisible(true);
    }
    else
    {
        //do nothing
    }
    box1.invalidate();
}

void MainView::presSelect()
{
    resetSelectFlags();
    presSelectFlag = true;
    line2_menu.setVisible(true);
    line2_menu.setX(pres_button.getX());
    IAQ_button.setBitmaps(touchgfx::Bitmap(BITMAP_IAQ_LIGHT_ID), touchgfx::Bitmap(BITMAP_IAQ_LIGHT_ID));
    CO2_button.setBitmaps(touchgfx::Bitmap(BITMAP_CO2_LIGHT_ID), touchgfx::Bitmap(BITMAP_CO2_LIGHT_ID));
    VOC_button.setBitmaps(touchgfx::Bitmap(BITMAP_VOC_LIGHT_ID), touchgfx::Bitmap(BITMAP_VOC_LIGHT_ID));
    hum_button.setBitmaps(touchgfx::Bitmap(BITMAP_HUM_LIGHT_ID), touchgfx::Bitmap(BITMAP_HUM_LIGHT_ID));
    pres_button.setBitmaps(touchgfx::Bitmap(BITMAP_PRES_DARK_ID), touchgfx::Bitmap(BITMAP_PRES_DARK_ID));
    temp_button.setBitmaps(touchgfx::Bitmap(BITMAP_TEMP_LIGHT_ID), touchgfx::Bitmap(BITMAP_TEMP_LIGHT_ID));
    containerVisibilityOff();
    pres_container.setVisible(true);
    if(presInitFlag == true)
    {
        hours_xAxis_Container.setVisible(true);
    }
    else
    {
        //do nothing
    }
    box1.invalidate();
}

void MainView::tempSelect()
{
    resetSelectFlags();
    tempSelectFlag = true;
    line2_menu.setVisible(true);
    line2_menu.setX(temp_button.getX());
    IAQ_button.setBitmaps(touchgfx::Bitmap(BITMAP_IAQ_LIGHT_ID), touchgfx::Bitmap(BITMAP_IAQ_LIGHT_ID));
    CO2_button.setBitmaps(touchgfx::Bitmap(BITMAP_CO2_LIGHT_ID), touchgfx::Bitmap(BITMAP_CO2_LIGHT_ID));
    VOC_button.setBitmaps(touchgfx::Bitmap(BITMAP_VOC_LIGHT_ID), touchgfx::Bitmap(BITMAP_VOC_LIGHT_ID));
    hum_button.setBitmaps(touchgfx::Bitmap(BITMAP_HUM_LIGHT_ID), touchgfx::Bitmap(BITMAP_HUM_LIGHT_ID));
    pres_button.setBitmaps(touchgfx::Bitmap(BITMAP_PRES_LIGHT_ID), touchgfx::Bitmap(BITMAP_PRES_LIGHT_ID));
    temp_button.setBitmaps(touchgfx::Bitmap(BITMAP_TEMP_DARK_ID), touchgfx::Bitmap(BITMAP_TEMP_DARK_ID));
    containerVisibilityOff();
    temp_container.setVisible(true);
    if(tempInitFlag == true)
    {
        hours_xAxis_Container.setVisible(true);
    }
    else
    {
        //do nothing
    }
    box1.invalidate();
}

void MainView::liveSelect()
{
    containerVisibilityOff();
    graphs_container.setVisible(true);
    box1.invalidate();
}

void MainView::resetSelectFlags(void)
{
    IAQSelectFlag = 0;
    CO2SelectFlag = 0;
    VOCSelectFlag = 0;
    humSelectFlag = 0;
    presSelectFlag = 0;
    tempSelectFlag = 0;
}

void MainView::graphsBackButton()
{
    graphs_container.setVisible(false);
    if(IAQSelectFlag == true)
    {
        IAQ_container.setVisible(true);
        if(IAQInitFlag == true)
        {
            hours_xAxis_Container.setVisible(true);
        }
        else
        {
            //do nothing
        }
    }
    else if(CO2SelectFlag == true)
    {
        CO2_container.setVisible(true);
        if(CO2InitFlag == true)
        {
            hours_xAxis_Container.setVisible(true);
        }
        else
        {
            //do nothing
        }
    }
    else if(VOCSelectFlag == true)
    {
        VOC_container.setVisible(true);
        if(VOCInitFlag == true)
        {
            hours_xAxis_Container.setVisible(true);
        }
        else
        {
            //do nothing
        }
    }
    else if(humSelectFlag == true)
    {
        hum_container.setVisible(true);
        if(humInitFlag == true)
        {
            hours_xAxis_Container.setVisible(true);
        }
        else
        {
            //do nothing
        }
    }
    else if(presSelectFlag == true)
    {
        pres_container.setVisible(true);
        if(presInitFlag == true)
        {
            hours_xAxis_Container.setVisible(true);
        }
        else
        {
            //do nothing
        }
    }
    else if(tempSelectFlag == true)
    {
        temp_container.setVisible(true);
        if(tempInitFlag == true)
        {
            hours_xAxis_Container.setVisible(true);
        }
        else
        {
            //do nothing
        }
    }
    else
    {
        //do nothing
    }
    box1.invalidate();
}

void MainView::resetOneHourAverage(void)
{
    for(uint8_t i = 0; i < 2; i++)
    {
        calcIAQAverage[i] = 0;
        calcCO2Average[i] = 0;
        calcVOCAverage[i] = 0;
        calcHumAverage[i] = 0;
        calcPresAverage[i] = 0;
        calcTempAverage[i] = 0;
    }
}

void MainView::reset24HourAverage(void)
{
    for(uint8_t i = 0; i < 3; i++)
    {
        calcIAQAverage[i] = 0;
        calcCO2Average[i] = 0;
        calcVOCAverage[i] = 0;
        calcHumAverage[i] = 0;
        calcPresAverage[i] = 0;
        calcTempAverage[i] = 0;
    }
}

void MainView::calculateOneHourAverage(void)
{
    calcIAQAverage[0] = ((calcIAQAverage[0] * calcIAQAverage[1]) + gui_iaq) / (calcIAQAverage[1] + 1);
    calcIAQAverage[1]++;

    calcCO2Average[0] = ((calcCO2Average[0] * calcCO2Average[1]) + gui_co2) / (calcCO2Average[1] + 1);
    calcCO2Average[1]++;

    calcVOCAverage[0] = ((calcVOCAverage[0] * calcVOCAverage[1]) + (gui_voc * 1000)) / (calcVOCAverage[1] + 1);
    calcVOCAverage[1]++;

    calcHumAverage[0] = ((calcHumAverage[0] * calcHumAverage[1]) + gui_humidity) / (calcHumAverage[1] + 1);
    calcHumAverage[1]++;

    calcPresAverage[0] = ((calcPresAverage[0] * calcPresAverage[1]) + gui_pressure) / (calcPresAverage[1] + 1);
    calcPresAverage[1]++;

    calcTempAverage[0] = ((calcTempAverage[0] * calcTempAverage[1]) + gui_temperature) / (calcTempAverage[1] + 1);
    calcTempAverage[1]++;
}

void MainView::calculate24HourAverage(void)
{
    calcIAQAverage[2] = ((calcIAQAverage[2] * hourCnt) + calcIAQAverage[0]) / (hourCnt + 1);
    calcCO2Average[2] = ((calcCO2Average[2] * hourCnt) + calcCO2Average[0]) / (hourCnt + 1);
    calcVOCAverage[2] = ((calcVOCAverage[2] * hourCnt) + calcVOCAverage[0]) / (hourCnt + 1);
    calcHumAverage[2] = ((calcHumAverage[2] * hourCnt) + calcHumAverage[0]) / (hourCnt + 1);
    calcPresAverage[2] = ((calcPresAverage[2] * hourCnt) + calcPresAverage[0]) / (hourCnt + 1);
    calcTempAverage[2] = ((calcTempAverage[2] * hourCnt) + calcTempAverage[0]) / (hourCnt + 1);
}

void MainView::containerVisibilityOff(void)
{
    IAQ_container.setVisible (false);
    CO2_container.setVisible (false);
    VOC_container.setVisible (false);
    hum_container.setVisible (false);
    pres_container.setVisible(false);
    temp_container.setVisible(false);
    graphs_container.setVisible(false);
    hours_xAxis_Container.setVisible(false);
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
void MainView::displayIAQGraph24Hour(float IAQValue)
{
    if(gui_iaq_accuracy == 0)
    {
        IAQInitFlag = false;
        IAQ_wait.setVisible(true);
        IAQ_good.setVisible(false);
        IAQ_moderate.setVisible(false);
        IAQ_bad.setVisible(false);

        IAQ_text_run.setVisible(false);
        IAQ_text_wait.setVisible(true);
    }
    else
    {
        IAQInitFlag = true;
        IAQ_wait.setVisible(false);
        IAQ_text_run.setVisible(true);
        IAQ_text_wait.setVisible(false);
        IAQ_value.setVisible(true);

        /*Setting of histogram bar color*/
        if(IAQValue > IAQ_LEVEL_GOOD && IAQValue < IAQ_LEVEL_MODERATE)
        {
            IAQGraphYellow.addDataPoint(0);
            IAQGraphRed.addDataPoint(0);
            IAQGraphGreen.addDataPoint(IAQValue);
        }
        else if(IAQValue > IAQ_LEVEL_MODERATE && IAQValue < IAQ_LEVEL_BAD)
        {
            IAQGraphGreen.addDataPoint(0);
            IAQGraphRed.addDataPoint(0);
            IAQGraphYellow.addDataPoint(IAQValue);
        }
        else if (calcIAQAverage[0] > IAQ_LEVEL_BAD)
        {
            IAQGraphGreen.addDataPoint(0);
            IAQGraphYellow.addDataPoint(0);
            IAQGraphRed.addDataPoint(IAQValue);
        }
        else
        {
            //do nothing
        }

        /* Setting of onboard screen color */
        if(calcIAQAverage[2] > IAQ_LEVEL_GOOD && calcIAQAverage[2] < IAQ_LEVEL_MODERATE)
        {
            IAQ_good.setVisible(true);
            IAQ_moderate.setVisible(false);
            IAQ_bad.setVisible(false);
        }
        else if(calcIAQAverage[2] > IAQ_LEVEL_MODERATE && calcIAQAverage[2] < IAQ_LEVEL_BAD)
        {
            IAQ_good.setVisible(false);
            IAQ_moderate.setVisible(true);
            IAQ_bad.setVisible(false);
        }
        else if (calcIAQAverage[2] > IAQ_LEVEL_BAD)
        {
            IAQ_good.setVisible(false);
            IAQ_moderate.setVisible(false);
            IAQ_bad.setVisible(true);
        }
        else
        {
            //do nothing
        }

        Unicode::snprintfFloat(IAQ_valueBuffer, IAQ_VALUE_SIZE, "%.1f", calcIAQAverage[2]);
        setIAQGraphRangeY24Hour();
    }

    if(IAQSelectFlag == true && IAQInitFlag == true)
    {
        hours_xAxis_Container.setVisible(true);
    }
    else
    {
        //do nothing
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

void MainView::displayCO2Graph24Hour(float CO2Value)
{
    if(gui_iaq_accuracy == 0)
    {
        CO2InitFlag = false;
        CO2_wait.setVisible(true);
        CO2_good.setVisible(false);
        CO2_moderate.setVisible(false);
        CO2_bad.setVisible(false);

        CO2_text_run.setVisible(false);
        CO2_text_wait.setVisible(true);
    }
    else
    {
        CO2InitFlag = true;
        CO2_wait.setVisible(false);
        CO2_text_run.setVisible(true);
        CO2_text_wait.setVisible(false);
        CO2_value.setVisible(true);

        if(CO2Value > CO2_LEVEL_GOOD && CO2Value < CO2_LEVEL_MODERATE)
        {
            CO2GraphYellow.addDataPoint(0);
            CO2GraphRed.addDataPoint(0);
            CO2GraphGreen.addDataPoint((int) CO2Value);
        }
        else if(CO2Value > CO2_LEVEL_MODERATE && CO2Value < CO2_LEVEL_BAD)
        {
            CO2GraphGreen.addDataPoint(0);
            CO2GraphRed.addDataPoint(0);
            CO2GraphYellow.addDataPoint((int) CO2Value);
        }
        else if (calcCO2Average[0] > CO2_LEVEL_BAD)
        {
            CO2GraphGreen.addDataPoint(0);
            CO2GraphYellow.addDataPoint(0);
            CO2GraphRed.addDataPoint((int) CO2Value);
        }
        else
        {
            //do nothing
        }

        if(calcCO2Average[2] > CO2_LEVEL_GOOD && calcCO2Average[2] < CO2_LEVEL_MODERATE)
        {
            CO2_good.setVisible(true);
            CO2_moderate.setVisible(false);
            CO2_bad.setVisible(false);
        }
        else if(calcCO2Average[2] > CO2_LEVEL_MODERATE && calcCO2Average[2] < CO2_LEVEL_BAD)
        {
            CO2_good.setVisible(false);
            CO2_moderate.setVisible(true);
            CO2_bad.setVisible(false);
        }
        else if (calcCO2Average[2] > CO2_LEVEL_BAD)
        {
            CO2_good.setVisible(false);
            CO2_moderate.setVisible(false);
            CO2_bad.setVisible(true);
        }
        else
        {
            //do nothing
        }

        Unicode::snprintfFloat(CO2_valueBuffer, CO2_VALUE_SIZE, "%.0f", calcCO2Average[2]);
        setCO2GraphRangeY24Hour();
    }

    if(CO2SelectFlag == true && CO2InitFlag == true)
    {
        hours_xAxis_Container.setVisible(true);
    }
    else
    {
        //do nothing
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

void MainView::displayVOCGraph24Hour(float VOCValue)
{
    if(gui_iaq_accuracy == 0)
    {
        VOCInitFlag = false;
        VOC_wait.setVisible(true);
        VOC_good.setVisible(false);
        VOC_moderate.setVisible(false);
        VOC_bad.setVisible(false);

        VOC_text_run.setVisible(false);
        VOC_text_wait.setVisible(true);
    }
    else
    {
        VOCInitFlag = true;
        VOC_wait.setVisible(false);
        VOC_text_run.setVisible(true);
        VOC_text_wait.setVisible(false);
        VOC_value.setVisible(true);

        if(VOCValue > VOC_LEVEL_GOOD && VOCValue < VOC_LEVEL_MODERATE)
        {
            VOCGraphYellow.addDataPoint(0);
            VOCGraphRed.addDataPoint(0);
            VOCGraphGreen.addDataPoint((int) VOCValue);
        }
        else if(VOCValue > VOC_LEVEL_MODERATE && VOCValue < VOC_LEVEL_BAD)
        {
            VOCGraphGreen.addDataPoint(0);
            VOCGraphRed.addDataPoint(0);
            VOCGraphYellow.addDataPoint((int) VOCValue);
        }
        else if (VOCValue > VOC_LEVEL_BAD)
        {
            VOCGraphGreen.addDataPoint(0);
            VOCGraphYellow.addDataPoint(0);
            VOCGraphRed.addDataPoint((int) VOCValue);
        }
        else
        {
            //do nothing
        }

        if(calcVOCAverage[2] > VOC_LEVEL_GOOD && calcVOCAverage[2] < VOC_LEVEL_MODERATE)
        {
            VOC_good.setVisible(true);
            VOC_moderate.setVisible(false);
            VOC_bad.setVisible(false);
        }
        else if(calcVOCAverage[2] > VOC_LEVEL_MODERATE && calcVOCAverage[2] < VOC_LEVEL_BAD)
        {
            VOC_good.setVisible(false);
            VOC_moderate.setVisible(true);
            VOC_bad.setVisible(false);
        }
        else if (calcVOCAverage[2] > VOC_LEVEL_BAD)
        {
            VOC_good.setVisible(false);
            VOC_moderate.setVisible(false);
            VOC_bad.setVisible(true);
        }
        else
        {
            //do nothing
        }

        Unicode::snprintfFloat(VOC_valueBuffer, VOC_VALUE_SIZE, "%.0f", calcVOCAverage[2]);
        setVOCGraphRangeY24Hour();
    }

    if(VOCSelectFlag == true && VOCInitFlag == true)
    {
        hours_xAxis_Container.setVisible(true);
    }
    else
    {
        //do nothing
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
void MainView::displayHumGraph24Hour(float humValue)
{
    if(gui_humidity == 0)
    {
        humInitFlag = false;
        hum_wait.setVisible(true);
        hum_good.setVisible(false);
        hum_moderate.setVisible(false);
        hum_bad.setVisible(false);

        hum_text_run.setVisible(false);
        hum_text_wait.setVisible(true);
    }
    else
    {
        humInitFlag = true;
        hum_wait.setVisible(false);
        hum_value.setVisible(true);
        hum_text_run.setVisible(true);
        hum_text_wait.setVisible(false);

        if(humValue > HUM_LEVEL_GOOD && humValue < HUM_LEVEL_MODERATE_HIGH)
        {
            humGraphYellow.addDataPoint(0);
            humGraphRed.addDataPoint(0);
            humGraphGreen.addDataPoint(humValue);
        }
        else if( (humValue > HUM_LEVEL_MODERATE_HIGH && humValue < HUM_LEVEL_BAD_HIGH) ||
                 (humValue < HUM_LEVEL_MODERATE_LOW  && humValue > HUM_LEVEL_BAD_LOW)    )
        {
            humGraphGreen.addDataPoint(0);
            humGraphRed.addDataPoint(0);
            humGraphYellow.addDataPoint(humValue);
        }
        else if (humValue > HUM_LEVEL_BAD_HIGH || humValue < HUM_LEVEL_BAD_LOW)
        {
            humGraphGreen.addDataPoint(0);
            humGraphYellow.addDataPoint(0);
            humGraphRed.addDataPoint(humValue);
        }
        else
        {
            //do nothing
        }

        if(calcHumAverage[2] > HUM_LEVEL_GOOD && calcHumAverage[2] < HUM_LEVEL_MODERATE_HIGH)
        {
            hum_good.setVisible(true);
            hum_moderate.setVisible(false);
            hum_bad.setVisible(false);
        }
        else if( (calcHumAverage[2] > HUM_LEVEL_MODERATE_HIGH && calcHumAverage[2] < HUM_LEVEL_BAD_HIGH) ||
                 (calcHumAverage[2] < HUM_LEVEL_MODERATE_LOW  && calcHumAverage[2] > HUM_LEVEL_BAD_LOW)    )
        {
            hum_good.setVisible(false);
            hum_moderate.setVisible(true);
            hum_bad.setVisible(false);
        }
        else if (calcHumAverage[2] > HUM_LEVEL_BAD_HIGH || calcHumAverage[2] < HUM_LEVEL_BAD_LOW)
        {
            hum_good.setVisible(false);
            hum_moderate.setVisible(false);
            hum_bad.setVisible(true);
        }
        else
        {
            //do nothing
        }
        Unicode::snprintfFloat(hum_valueBuffer, HUM_VALUE_SIZE, "%.1f", calcHumAverage[2]);
        setHumGraphRangeY24Hour();
    }

    if(humSelectFlag == true && humInitFlag == true)
    {
        hours_xAxis_Container.setVisible(true);
    }
    else
    {
        //do nothing
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
void MainView::displayPresGraph24Hour(float presValue)
{
    if(gui_pressure == 0)
    {
        presInitFlag = false;
        pres_wait.setVisible(true);
        pres_run.setVisible(false);

        pres_text_run.setVisible(false);
        pres_text_wait.setVisible(true);
    }
    else
    {
        presInitFlag = true;
        pres_wait.setVisible(false);
        pres_run.setVisible(true);
        pres_value.setVisible(true);
        pres_text_run.setVisible(true);
        pres_text_wait.setVisible(false);
        presGraph.addDataPoint(presValue);

        Unicode::snprintfFloat(pres_valueBuffer, PRES_VALUE_SIZE, "%.1f", calcPresAverage[2]);
        setPresGraphRangeY24Hour();
    }

    if(presSelectFlag == true && presInitFlag == true)
    {
        hours_xAxis_Container.setVisible(true);
    }
    else
    {
        //do nothing
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
void MainView::displayTempGraph24Hour(float tempValue)
{
    if(gui_temperature == 0)
    {
        tempInitFlag = false;
        temp_wait.setVisible(true);
        temp_good.setVisible(false);
        temp_moderate.setVisible(false);
        temp_bad.setVisible(false);

        temp_text_run.setVisible(false);
        temp_text_wait.setVisible(true);
    }
    else
    {
        tempInitFlag = true;
        temp_wait.setVisible(false);
        temp_value.setVisible(true);
        temp_text_run.setVisible(true);
        temp_text_wait.setVisible(false);

        if(tempValue > TEMP_LEVEL_GOOD && tempValue < TEMP_LEVEL_MODERATE_HIGH)
        {
            tempGraphYellow.addDataPoint(0);
            tempGraphRed.addDataPoint(0);
            tempGraphGreen.addDataPoint(tempValue);
        }
        else if( (tempValue > TEMP_LEVEL_MODERATE_HIGH && tempValue < TEMP_LEVEL_BAD_HIGH) ||
                 (tempValue < TEMP_LEVEL_MODERATE_LOW  && tempValue > TEMP_LEVEL_BAD_LOW)    )
        {
            tempGraphGreen.addDataPoint(0);
            tempGraphRed.addDataPoint(0);
            tempGraphYellow.addDataPoint(tempValue);
        }
        else if (tempValue > TEMP_LEVEL_BAD_HIGH || tempValue < TEMP_LEVEL_BAD_LOW)
        {
            tempGraphGreen.addDataPoint(0);
            tempGraphYellow.addDataPoint(0);
            tempGraphRed.addDataPoint(tempValue);
        }
        else
        {
            //do nothing
        }

        if(calcTempAverage[2] > TEMP_LEVEL_GOOD && calcTempAverage[2] < TEMP_LEVEL_MODERATE_HIGH)
        {
            temp_good.setVisible(true);
            temp_moderate.setVisible(false);
            temp_bad.setVisible(false);
        }
        else if( (calcTempAverage[2] > TEMP_LEVEL_MODERATE_HIGH && calcTempAverage[2] < TEMP_LEVEL_BAD_HIGH) ||
                 (calcTempAverage[2] < TEMP_LEVEL_MODERATE_LOW  && calcTempAverage[2] > TEMP_LEVEL_BAD_LOW)    )
        {
            temp_good.setVisible(false);
            temp_moderate.setVisible(true);
            temp_bad.setVisible(false);
        }
        else if (calcTempAverage[2] > TEMP_LEVEL_BAD_HIGH || calcTempAverage[2] < TEMP_LEVEL_BAD_LOW)
        {
            temp_good.setVisible(false);
            temp_moderate.setVisible(false);
            temp_bad.setVisible(true);
        }
        else
        {
            //do nothing
        }

        Unicode::snprintfFloat(temp_valueBuffer, TEMP_VALUE_SIZE, "%.1f", calcTempAverage[2]);
        setTempGraphRangeY24Hour();
    }

    if(tempSelectFlag == true && tempInitFlag == true)
    {
        hours_xAxis_Container.setVisible(true);
    }
    else
    {
        //do nothing
    }
    box1.invalidate();
}

void MainView::handleClickEvent(const ClickEvent& evt)
{
    bool tempGraphAreaClicked = false;
    bool humGraphAreaClicked  = false;
    bool presGraphAreaClicked = false;
    bool IAQGraphAreaClicked  = false;

    if(TempGraph.getAbsoluteRect().intersect(evt.getX(), evt.getY()))           /* Check if temperature graph is clicked and get the coordinates */
    {
        tempGraphAreaClicked = true;
    }
    else if(HumGraph.getAbsoluteRect().intersect(evt.getX(), evt.getY()))       /* Check if humidity graph is clicked and get the coordinates */
    {
        humGraphAreaClicked = true;
    }
    else if(PresGraph.getAbsoluteRect().intersect(evt.getX(), evt.getY()))      /* Check if pressure graph is clicked and get the coordinates */
    {
        presGraphAreaClicked = true;
    }
    else if (IAQGraph.getAbsoluteRect().intersect(evt.getX(), evt.getY()))     /* Check if IAQ graph is clicked and get the coordinates */
    {
        IAQGraphAreaClicked = true;
    }
    else
    {
        // do nothing
    }

    if (evt.getType() == ClickEvent::PRESSED)       /* Click Event occurred */
    {
        if(tempGraphAreaClicked)
        {
            clickStatus = ClickStatus::CLICKED;     /* Click Event occurred within the temperature graph */
        }
        else if(humGraphAreaClicked)
        {
            clickStatus = ClickStatus::CLICKED;     /* Click Event occurred within the humidity graph */
        }
        else if(presGraphAreaClicked)
        {
            clickStatus = ClickStatus::CLICKED;     /* Click Event occurred within the pressure graph */
        }
        else if (IAQGraphAreaClicked)               /* Click Event occurred within the IAQ graph */
        {
            clickStatus = ClickStatus::CLICKED;
        }
        else
        {
            //do nothing
        }
        MainViewBase::handleClickEvent(evt);              /* Act normally */
    }
    else if (evt.getType() == ClickEvent::RELEASED)         /* No Click Event or click event ended */
    {
        if(clickStatus == ClickStatus::CLICK_DRAGGING)      /* Drag event occured */
        {
            SwipeArea.handleClickEvent(evt);
        }
        else
        {
            MainViewBase::handleClickEvent(evt);          /* Not dragging, allow passing the event to the graph */
        }
        clickStatus = ClickStatus::RELEASED;
    }
}

void MainView::handleDragEvent(const DragEvent& evt)
{
    bool dragIntersect = false;
    /* Check if drag event occured and get the coordinates */
    if( ( TempGraph.getAbsoluteRect().intersect(evt.getOldX(), evt.getOldY())) ||
        (  HumGraph.getAbsoluteRect().intersect(evt.getOldX(), evt.getOldY())) ||
        ( PresGraph.getAbsoluteRect().intersect(evt.getOldX(), evt.getOldY())) ||
        (  IAQGraph.getAbsoluteRect().intersect(evt.getOldX(), evt.getOldY()))    )
    {
        dragIntersect = true;
    }
    else
    {
        dragIntersect = false;
    }

    if(dragIntersect)
    {
        if(abs(evt.getDeltaX()) > 2 && clickStatus == ClickStatus::CLICKED)             /* Drag occurred within a graph */
        {
            ClickEvent cancelEvt(ClickEvent::CANCEL, evt.getOldX(), evt.getOldY(), 1);  /* We are now dragging, cancel any graph touch by creating a new click event and forwarding it to the rest of the view*/
            MainViewBase::handleClickEvent(cancelEvt);
            clickStatus = ClickStatus::CLICK_DRAGGING;
        }
    }

    if(clickStatus == ClickStatus::CLICK_DRAGGING)
    {
        SwipeArea.handleDragEvent(evt);             /* We are dragging, forward drag events to swipe container only */
    }
    else
    {
        MainViewBase::handleDragEvent(evt);       /* No dragging within a graph occured, act normally */
    }
}

void MainView::handleGestureEvent(const GestureEvent& evt)
{
    if(clickStatus == ClickStatus::CLICK_DRAGGING)
    {
        SwipeArea.handleGestureEvent(evt);          /* We are dragging, forward gesture events to swipe container only */
    }
    else
    {
        MainViewBase::handleGestureEvent(evt);    /* No dragging within a graph occured, act normally */
    }
}

void MainView::filterData(void)
{
    filtredTemp = filterObject[0].kalmanFilter(gui_temperature, 0.1f);
    filtredHum  = filterObject[1].kalmanFilter(gui_humidity, 0.05f);
    filtredPres = filterObject[2].kalmanFilter(gui_pressure, 0.001f);
    filtredIAQ  = filterObject[3].kalmanFilter(gui_iaq, 0.001);
}
/* Function for displaying the temperature graph */
void MainView::displayTemperatureGraph(float temperatureValue)
{
    TempGraph.addDataPoint(temperatureValue*100.0f);
    TempGraph.setGraphRangeYAuto(false, 5);
    TempGraphMajorYAxisLabel.setInterval(((TempGraph.getGraphRangeYMaxAsInt() - TempGraph.getGraphRangeYMinAsInt())/10));
    setTempGraphMajorYAxisLabel();
    Unicode::snprintfFloat(textArea1Buffer, TEXTAREA1_SIZE, "%.2f", temperatureValue);
    textArea1.invalidate();
}

/* Function for displaying the humidity graph */
void MainView::displayHumidityGraph(float humidityValue)
{
    HumGraph.addDataPoint(humidityValue*100);
    HumGraph.setGraphRangeYAuto(false, 5);
    HumGraphMajorYAxisLabel.setInterval(((HumGraph.getGraphRangeYMaxAsInt() - HumGraph.getGraphRangeYMinAsInt())/10));
    setHumGraphMajorYAxisLabel();
    Unicode::snprintfFloat(textArea2Buffer, TEXTAREA2_SIZE, "%.2f", humidityValue);
    textArea2.invalidate();
}

/* Function for displaying the pressure graph */
void MainView::displayPressureGraph(float pressureValue)
{
    PresGraph.addDataPoint(pressureValue*100);
    PresGraph.setGraphRangeYAuto(false, 5);
    PresGraphMajorYAxisLabel.setInterval(((PresGraph.getGraphRangeYMaxAsInt() - PresGraph.getGraphRangeYMinAsInt())/10));
    setPresGraphMajorYAxisLabel();
    Unicode::snprintfFloat(textArea3Buffer, TEXTAREA3_SIZE, "%.2f", pressureValue);
    textArea3.invalidate();
}

/* Function for displaying the IAQ graph */
void MainView::displayIAQGraph(float IAQValue)
{
    IAQGraph.addDataPoint(IAQValue*100);
    IAQGraph.setGraphRangeYAuto(false, 5);
    IAQGraphMajorYAxisLabel.setInterval(((IAQGraph.getGraphRangeYMaxAsInt() - IAQGraph.getGraphRangeYMinAsInt())/10));
    setIAQGraphMajorYAxisLabel();
    Unicode::snprintfFloat(textArea4Buffer, TEXTAREA4_SIZE, "%.2f", IAQValue);
    textArea4.invalidate();
}

/* Function for setting the temperature graph Y axis labels */
void MainView::setTempGraphMajorYAxisLabel(void)
{
    int GraphRangeYMinAsInt = TempGraph.getGraphRangeYMinAsInt();
    int IntervalAsInt       = TempGraphMajorYAxisLabel.getIntervalAsInt();
    Unicode::snprintfFloat( graphInterval1_1Buffer, GRAPHINTERVAL1_1_SIZE, "%.2f", ((float)(GraphRangeYMinAsInt + IntervalAsInt *  0)/100));
    Unicode::snprintfFloat( graphInterval1_0Buffer, GRAPHINTERVAL1_0_SIZE, "%.2f", ((float)(GraphRangeYMinAsInt + IntervalAsInt * 10)/100));
    graphInterval1_1.invalidate();
    graphInterval1_0.invalidate();
}

/* Function for setting the humidity graph Y axis labels */
void MainView::setHumGraphMajorYAxisLabel(void)
{
    int GraphRangeYMinAsInt = HumGraph.getGraphRangeYMinAsInt();
    int IntervalAsInt       = HumGraphMajorYAxisLabel.getIntervalAsInt();
    Unicode::snprintfFloat( graphInterval2_1Buffer, GRAPHINTERVAL2_1_SIZE, "%.2f", ((float)(GraphRangeYMinAsInt + IntervalAsInt *  0)/100));
    Unicode::snprintfFloat( graphInterval2_0Buffer, GRAPHINTERVAL2_0_SIZE, "%.2f", ((float)(GraphRangeYMinAsInt + IntervalAsInt * 10)/100));
    graphInterval2_1.invalidate();
    graphInterval2_0.invalidate();
}

/* Function for setting the pressure graph Y axis labels */
void MainView::setPresGraphMajorYAxisLabel(void)
{
    int GraphRangeYMinAsInt = PresGraph.getGraphRangeYMinAsInt();
    int IntervalAsInt       = PresGraphMajorYAxisLabel.getIntervalAsInt();
    Unicode::snprintfFloat( graphInterval3_1Buffer, GRAPHINTERVAL3_1_SIZE, "%.2f", ((float)(GraphRangeYMinAsInt + IntervalAsInt *  0)/100));
    Unicode::snprintfFloat( graphInterval3_0Buffer, GRAPHINTERVAL3_0_SIZE, "%.2f", ((float)(GraphRangeYMinAsInt + IntervalAsInt * 10)/100));
    graphInterval3_1.invalidate();
    graphInterval3_0.invalidate();
}

/* Function for setting the IAQ graph Y axis labels */
void MainView::setIAQGraphMajorYAxisLabel(void)
{
    int GraphRangeYMinAsInt = IAQGraph.getGraphRangeYMinAsInt();
    int IntervalAsInt       = IAQGraphMajorYAxisLabel.getIntervalAsInt();
    Unicode::snprintfFloat( graphInterval4_1Buffer, GRAPHINTERVAL4_1_SIZE, "%.2f", ((float)(GraphRangeYMinAsInt + IntervalAsInt *  0)/100));
    Unicode::snprintfFloat( graphInterval4_0Buffer, GRAPHINTERVAL4_0_SIZE, "%.2f", ((float)(GraphRangeYMinAsInt + IntervalAsInt * 10)/100));
    graphInterval4_1.invalidate();
    graphInterval4_0.invalidate();
}
