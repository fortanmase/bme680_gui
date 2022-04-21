#ifndef MAINVIEW_HPP
#define MAINVIEW_HPP

#include <gui_generated/main_screen/MainViewBase.hpp>
#include <gui/main_screen/MainPresenter.hpp>

class MainView : public MainViewBase
{
public:
    MainView();
    virtual ~MainView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void IAQSelect();
    virtual void CO2Select();
    virtual void VOCSelect();
    virtual void humSelect();
    virtual void presSelect();
    virtual void tempSelect();
    void handleTickEvent();
protected:
    void containerVisibilityOff(void);
    void resetOneHourAverage(void);
    void reset24HourAverage(void);
    void calculateOneHourAverage(void);
    void calculate24HourAverage(void);

    void setIAQGraphRangeY24Hour(void);
    void displayIAQGraph24Hour(void);

    void setCO2GraphRangeY24Hour(void);
    void displayCO2Graph24Hour(void);

    void setVOCGraphRangeY24Hour(void);
    void displayVOCGraph24Hour(void);

    void setPresGraphRangeY24Hour(void);
    void displayPresGraph24Hour(void);

    void setHumGraphRangeY24Hour(void);
    void displayHumGraph24Hour(void);

    void setTempGraphRangeY24Hour(void);
    void displayTempGraph24Hour(void);
};

#endif // MAINVIEW_HPP
