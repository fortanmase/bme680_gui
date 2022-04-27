#ifndef MAINVIEW_HPP
#define MAINVIEW_HPP

#include <gui_generated/main_screen/MainViewBase.hpp>
#include <gui/main_screen/MainPresenter.hpp>
#include <math.h>

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

class MainView : public MainViewBase
{
public:
    MainView();
    virtual ~MainView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    void handleTickEvent();
    virtual void IAQSelect();
    virtual void CO2Select();
    virtual void VOCSelect();
    virtual void humSelect();
    virtual void presSelect();
    virtual void tempSelect();
    virtual void liveSelect();
    virtual void graphsBackButton();
    void handleClickEvent(const ClickEvent& evt);
    void handleDragEvent(const DragEvent& evt);
    void handleGestureEvent(const GestureEvent& evt);
protected:
    void containerVisibilityOff(void);

    void resetOneHourAverage(void);
    void reset24HourAverage(void);
    void calculateOneHourAverage(void);
    void calculate24HourAverage(void);

    void setIAQGraphRangeY24Hour(void);
    void displayIAQGraph24Hour(float IAQValue);

    void setCO2GraphRangeY24Hour(void);
    void displayCO2Graph24Hour(float CO2Value);

    void setVOCGraphRangeY24Hour(void);
    void displayVOCGraph24Hour(float VOCValue);

    void setPresGraphRangeY24Hour(void);
    void displayPresGraph24Hour(float presValue);

    void setHumGraphRangeY24Hour(void);
    void displayHumGraph24Hour(float humValue);

    void setTempGraphRangeY24Hour(void);
    void displayTempGraph24Hour(float tempValue);

    void resetSelectFlags(void);

    enum class ClickStatus {
        RELEASED,
        CLICKED,
        CLICK_DRAGGING
    };
    ClickStatus clickStatus;
    void filterData(void);
    void displayTemperatureGraph(float temperatureValue);
    void displayHumidityGraph(float humidityValue);
    void displayPressureGraph(float pressureValue);
    void displayIAQGraph(float IAQValue);

    void setTempGraphMajorYAxisLabel(void);
    void setHumGraphMajorYAxisLabel(void);
    void setPresGraphMajorYAxisLabel(void);
    void setIAQGraphMajorYAxisLabel(void);
};

class kalman
{
    private:
    float err_measure = 0.8;  //noise coef
    float kalman_gain, current_estimate;
    float err_estimate = err_measure;
    float last_estimate;
    public:
    float kalmanFilter(float input, float q)
    {
        kalman_gain = err_estimate / (err_estimate + err_measure);
        current_estimate = last_estimate + kalman_gain * (input - last_estimate);
        err_estimate =  (1.0 - kalman_gain) * err_estimate + fabs(last_estimate - current_estimate) * q;
        last_estimate = current_estimate;
        return current_estimate;
    }
};

#endif // MAINVIEW_HPP
