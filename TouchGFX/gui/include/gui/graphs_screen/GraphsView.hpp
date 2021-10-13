#ifndef GRAPHSVIEW_HPP
#define GRAPHSVIEW_HPP

/***********************************************************************************************************************
 *  include files
 ***********************************************************************************************************************/
#include <gui_generated/graphs_screen/GraphsViewBase.hpp>
#include <gui/graphs_screen/GraphsPresenter.hpp>
/***********************************************************************************************************************
 *  class definitions
 ***********************************************************************************************************************/
class GraphsView : public GraphsViewBase
{
public:
/*  generated declarations  */
    GraphsView();
    virtual ~GraphsView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    void handleTickEvent();
    void handleClickEvent(const ClickEvent& evt);
    void handleDragEvent(const DragEvent& evt);
    void handleGestureEvent(const GestureEvent& evt);
protected:
/*  user declarations  */
    enum class ClickStatus {
        RELEASED,
        CLICKED,
        CLICK_DRAGGING
    };
    ClickStatus clickStatus;
    uint32_t lastTickValue = 0;
    void displayTemperatureGraph(float temperatureValue);
    void displayHumidityGraph(float humidityValue);
    void setTempGraphMajorYAxisLabel(void);
    void setHumGraphMajorYAxisLabel(void);
};

#endif // GRAPHSVIEW_HPP
