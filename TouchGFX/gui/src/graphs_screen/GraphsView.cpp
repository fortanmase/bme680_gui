/***********************************************************************************************************************
 *  include files
 ***********************************************************************************************************************/
#include <gui/graphs_screen/GraphsView.hpp>
#include <math.h>
#include <stdlib.h>

/***********************************************************************************************************************
 *  macros definition
 ***********************************************************************************************************************/
#define PI 3.14159265358979323846264338327950288419716939937510582
#define RAD(degree) (PI * degree)/180

/***********************************************************************************************************************
 *  variable declarations
 ***********************************************************************************************************************/
extern uint32_t (*pfHAL_GetTick)(void);    //pointer to HAL_GetTick()
float gui_temperature;
float gui_humidity;
float gui_pressure;
float gui_iaq;
/***********************************************************************************************************************
 *  functions definition
 ***********************************************************************************************************************/
GraphsView::GraphsView()
{

}

/*  generated function for screen setup  */
void GraphsView::setupScreen()
{
/*  user implementation  */
    GraphsViewBase::setupScreen();
    lastTickValue = pfHAL_GetTick();
}

void GraphsView::tearDownScreen()
{
    GraphsViewBase::tearDownScreen();
}
/*  function call based on ticks (loop)  */
uint8_t flag = 0;
float testValue = 0;
float sineWave = 0;
float triangWave = 0;
void GraphsView::handleTickEvent()
{
    if((pfHAL_GetTick() - lastTickValue) >= 1)
    {
        if(flag == 0)
        {
            if(triangWave < 5)
            {
                triangWave += 0.13;
            }
            else
            {
                triangWave = 5;
                flag = 1;
            }
        }
        if(flag == 1)
        {
            if(triangWave > -5)
            {
                triangWave -= 0.13;
            }
            else
            {
                triangWave = -5;
                flag = 0;
            }
        }
        sineWave = sinf(RAD(testValue++))*10;
    }
    if((pfHAL_GetTick() - lastTickValue) >= 100)
    {
        lastTickValue = pfHAL_GetTick();
        displayTemperatureGraph(sineWave);
        displayHumidityGraph(triangWave);
    }
}

void GraphsView::handleClickEvent(const ClickEvent& evt)
{
    bool tempGraphAreaClicked = false;
    bool humGraphAreaClicked = false;

    if(TempGraph.getAbsoluteRect().intersect(evt.getX(), evt.getY()))
    {
        tempGraphAreaClicked = true;
    }
    else if(HumGraph.getAbsoluteRect().intersect(evt.getX(), evt.getY()))
    {
        humGraphAreaClicked = true;
    }

    // Click Event occurred
    if (evt.getType() == ClickEvent::PRESSED)
    {
        if(tempGraphAreaClicked)
        {
            // Click Event occurred within the graph
            clickStatus = ClickStatus::CLICKED;
        }
        else if(humGraphAreaClicked)
        {
            clickStatus = ClickStatus::CLICKED;
        }
        GraphsViewBase::handleClickEvent(evt); // act normally
    }
    else if (evt.getType() == ClickEvent::RELEASED)
    {
        if(clickStatus == ClickStatus::CLICK_DRAGGING)
        {
            SwipeArea.handleClickEvent(evt);
        }
        else
        {
            // Not dragging, allow passing the event to the graph
            GraphsViewBase::handleClickEvent(evt);
        }
        clickStatus = ClickStatus::RELEASED;
    }
}

void GraphsView::handleDragEvent(const DragEvent& evt)
{
    bool dragIntersect = false;

    if((TempGraph.getAbsoluteRect().intersect(evt.getOldX(), evt.getOldY())) ||
       ( HumGraph.getAbsoluteRect().intersect(evt.getOldX(), evt.getOldY())))
    {
        dragIntersect = true;
    }


    if(dragIntersect)
    {
        // Drag occurred within a graph
        if(abs(evt.getDeltaX()) > 2 && clickStatus == ClickStatus::CLICKED)
        {
            // We are now dragging, cancel any graph touch by creating a new click event
            // and forwarding it to the rest of the view
            ClickEvent cancelEvt(ClickEvent::CANCEL, evt.getOldX(), evt.getOldY(), 1);
            GraphsViewBase::handleClickEvent(cancelEvt);
            clickStatus = ClickStatus::CLICK_DRAGGING;
        }
    }

    if(clickStatus == ClickStatus::CLICK_DRAGGING)
    {
        // We are dragging, forward drag events to swipe container only
        SwipeArea.handleDragEvent(evt);
    }
    else
    {
        // No dragging within a graph occured, act normally
        GraphsViewBase::handleDragEvent(evt);
    }
}

void GraphsView::handleGestureEvent(const GestureEvent& evt)
{
    if(clickStatus == ClickStatus::CLICK_DRAGGING)
    {
        // We are dragging, forward gesture events to swipe container only
        SwipeArea.handleGestureEvent(evt);
    }
    else
    {
        // No dragging within a graph occured, act normally
        GraphsViewBase::handleGestureEvent(evt);
    }
}

/*  function for displaying the temperature graph  */
void GraphsView::displayTemperatureGraph(float temperatureValue)
{
    TempGraph.setGraphRangeYAuto(false, 3);
    TempGraphMajorYAxisLabel.setInterval(((TempGraph.getGraphRangeYMaxAsInt() - TempGraph.getGraphRangeYMinAsInt())/10));
    TempGraphMajorYAxisGrid.setInterval (((TempGraph.getGraphRangeYMaxAsInt() - TempGraph.getGraphRangeYMinAsInt())/10));
    TempGraph.addDataPoint(temperatureValue*100);
    setTempGraphMajorYAxisLabel();
    Unicode::snprintfFloat(textArea1Buffer, TEXTAREA1_SIZE, "%.2f", temperatureValue);
    textArea1.invalidate();
}

/*  function for displaying the humidity graph  */
void GraphsView::displayHumidityGraph(float humidityValue)
{
    HumGraph.setGraphRangeYAuto(false, 3);
    HumGraphMajorYAxisLabel.setInterval(((HumGraph.getGraphRangeYMaxAsInt() - HumGraph.getGraphRangeYMinAsInt())/10));
    HumGraphMajorYAxisGrid.setInterval (((HumGraph.getGraphRangeYMaxAsInt() - HumGraph.getGraphRangeYMinAsInt())/10));
    HumGraph.addDataPoint(humidityValue*100);
    setHumGraphMajorYAxisLabel();
    Unicode::snprintfFloat(textArea2Buffer, TEXTAREA2_SIZE, "%.2f", humidityValue);
    textArea2.invalidate();
}

void GraphsView::setTempGraphMajorYAxisLabel(void)
{
    int GraphRangeYMinAsInt = TempGraph.getGraphRangeYMinAsInt();
    int IntervalAsInt       = TempGraphMajorYAxisLabel.getIntervalAsInt();
    Unicode::snprintfFloat( graphInterval1_10Buffer, GRAPHINTERVAL1_10_SIZE, "%.1f", ((float)(GraphRangeYMinAsInt + IntervalAsInt *  0)/100));
    Unicode::snprintfFloat( graphInterval1_9Buffer,  GRAPHINTERVAL1_9_SIZE,  "%.1f", ((float)(GraphRangeYMinAsInt + IntervalAsInt *  1)/100));
    Unicode::snprintfFloat( graphInterval1_8Buffer,  GRAPHINTERVAL1_8_SIZE,  "%.1f", ((float)(GraphRangeYMinAsInt + IntervalAsInt *  2)/100));
    Unicode::snprintfFloat( graphInterval1_7Buffer,  GRAPHINTERVAL1_7_SIZE,  "%.1f", ((float)(GraphRangeYMinAsInt + IntervalAsInt *  3)/100));
    Unicode::snprintfFloat( graphInterval1_6Buffer,  GRAPHINTERVAL1_6_SIZE,  "%.1f", ((float)(GraphRangeYMinAsInt + IntervalAsInt *  4)/100));
    Unicode::snprintfFloat( graphInterval1_5Buffer,  GRAPHINTERVAL1_5_SIZE,  "%.1f", ((float)(GraphRangeYMinAsInt + IntervalAsInt *  5)/100));
    Unicode::snprintfFloat( graphInterval1_4Buffer,  GRAPHINTERVAL1_4_SIZE,  "%.1f", ((float)(GraphRangeYMinAsInt + IntervalAsInt *  6)/100));
    Unicode::snprintfFloat( graphInterval1_3Buffer,  GRAPHINTERVAL1_3_SIZE,  "%.1f", ((float)(GraphRangeYMinAsInt + IntervalAsInt *  7)/100));
    Unicode::snprintfFloat( graphInterval1_2Buffer,  GRAPHINTERVAL1_2_SIZE,  "%.1f", ((float)(GraphRangeYMinAsInt + IntervalAsInt *  8)/100));
    Unicode::snprintfFloat( graphInterval1_1Buffer,  GRAPHINTERVAL1_1_SIZE,  "%.1f", ((float)(GraphRangeYMinAsInt + IntervalAsInt *  9)/100));
    Unicode::snprintfFloat( graphInterval1Buffer,    GRAPHINTERVAL1_SIZE,    "%.1f", ((float)(GraphRangeYMinAsInt + IntervalAsInt * 10)/100));
    graphInterval1_10.invalidate();
    graphInterval1_9.invalidate();
    graphInterval1_8.invalidate();
    graphInterval1_7.invalidate();
    graphInterval1_6.invalidate();
    graphInterval1_5.invalidate();
    graphInterval1_4.invalidate();
    graphInterval1_3.invalidate();
    graphInterval1_2.invalidate();
    graphInterval1_1.invalidate();
    graphInterval1.invalidate();
}

void GraphsView::setHumGraphMajorYAxisLabel(void)
{
    int GraphRangeYMinAsInt = HumGraph.getGraphRangeYMinAsInt();
    int IntervalAsInt       = HumGraphMajorYAxisLabel.getIntervalAsInt();
    Unicode::snprintfFloat( graphInterval2_10Buffer, GRAPHINTERVAL2_10_SIZE, "%.1f", ((float)(GraphRangeYMinAsInt + IntervalAsInt *  0)/100));
    Unicode::snprintfFloat( graphInterval2_9Buffer,  GRAPHINTERVAL2_9_SIZE,  "%.1f", ((float)(GraphRangeYMinAsInt + IntervalAsInt *  1)/100));
    Unicode::snprintfFloat( graphInterval2_8Buffer,  GRAPHINTERVAL2_8_SIZE,  "%.1f", ((float)(GraphRangeYMinAsInt + IntervalAsInt *  2)/100));
    Unicode::snprintfFloat( graphInterval2_7Buffer,  GRAPHINTERVAL2_7_SIZE,  "%.1f", ((float)(GraphRangeYMinAsInt + IntervalAsInt *  3)/100));
    Unicode::snprintfFloat( graphInterval2_6Buffer,  GRAPHINTERVAL2_6_SIZE,  "%.1f", ((float)(GraphRangeYMinAsInt + IntervalAsInt *  4)/100));
    Unicode::snprintfFloat( graphInterval2_5Buffer,  GRAPHINTERVAL2_5_SIZE,  "%.1f", ((float)(GraphRangeYMinAsInt + IntervalAsInt *  5)/100));
    Unicode::snprintfFloat( graphInterval2_4Buffer,  GRAPHINTERVAL2_4_SIZE,  "%.1f", ((float)(GraphRangeYMinAsInt + IntervalAsInt *  6)/100));
    Unicode::snprintfFloat( graphInterval2_3Buffer,  GRAPHINTERVAL2_3_SIZE,  "%.1f", ((float)(GraphRangeYMinAsInt + IntervalAsInt *  7)/100));
    Unicode::snprintfFloat( graphInterval2_2Buffer,  GRAPHINTERVAL2_2_SIZE,  "%.1f", ((float)(GraphRangeYMinAsInt + IntervalAsInt *  8)/100));
    Unicode::snprintfFloat( graphInterval2_1Buffer,  GRAPHINTERVAL2_1_SIZE,  "%.1f", ((float)(GraphRangeYMinAsInt + IntervalAsInt *  9)/100));
    Unicode::snprintfFloat( graphInterval2Buffer,    GRAPHINTERVAL1_SIZE,    "%.1f", ((float)(GraphRangeYMinAsInt + IntervalAsInt * 10)/100));
    graphInterval2_10.invalidate();
    graphInterval2_9.invalidate();
    graphInterval2_8.invalidate();
    graphInterval2_7.invalidate();
    graphInterval2_6.invalidate();
    graphInterval2_5.invalidate();
    graphInterval2_4.invalidate();
    graphInterval2_3.invalidate();
    graphInterval2_2.invalidate();
    graphInterval2_1.invalidate();
    graphInterval2.invalidate();
}

