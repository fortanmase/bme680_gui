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
    void ContainerVisibilityOff(void);
    void setIAQGraphRangeY24Hour(void);
    void displayIAQGraph24Hour(void);
};

#endif // MAINVIEW_HPP
