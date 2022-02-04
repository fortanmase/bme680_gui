#include <gui/graphs_screen/GraphsView.hpp>
#include <math.h>

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

extern uint32_t (*pfHAL_GetTick)(void);    /* Pointer to HAL_GetTick imported from main*/
/* Variables imported from main */
float gui_temperature = 0;
float gui_humidity = 0;
float gui_pressure = 0;
float gui_iaq = 0;
float gui_co2 = 0;

static uint32_t lastTickValue; /* Variable monitoring last tick value (HAL_GetTick) */
static uint8_t filterCounter = 0;
static kalman filterObj[5];

float filtredTemp = 0;
float filtredHum = 0;
float filtredPres = 0;
float filtredIAQ = 0;
float filtredCO2 = 0;

GraphsView::GraphsView()
{
    lastTickValue = pfHAL_GetTick(); /* Initialize with actual tick value */
}

/*  generated function for screen setup  */
void GraphsView::setupScreen()
{
/*  user implementation  */
    GraphsViewBase::setupScreen();
}

void GraphsView::tearDownScreen()
{
    GraphsViewBase::tearDownScreen();
}
/*  function call based on ticks (loop), call frequency = 60Hz (16.6ms)  */
void GraphsView::handleTickEvent()
{
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
}

void GraphsView::handleClickEvent(const ClickEvent& evt)
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
        GraphsViewBase::handleClickEvent(evt);              /* Act normally */
    }
    else if (evt.getType() == ClickEvent::RELEASED)         /* No Click Event or click event ended */
    {
        if(clickStatus == ClickStatus::CLICK_DRAGGING)      /* Drag event occured */
        {
            SwipeArea.handleClickEvent(evt);
        }
        else
        {
            GraphsViewBase::handleClickEvent(evt);          /* Not dragging, allow passing the event to the graph */
        }
        clickStatus = ClickStatus::RELEASED;
    }
}

void GraphsView::handleDragEvent(const DragEvent& evt)
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
            GraphsViewBase::handleClickEvent(cancelEvt);
            clickStatus = ClickStatus::CLICK_DRAGGING;
        }
    }

    if(clickStatus == ClickStatus::CLICK_DRAGGING)
    {
        SwipeArea.handleDragEvent(evt);             /* We are dragging, forward drag events to swipe container only */
    }
    else
    {
        GraphsViewBase::handleDragEvent(evt);       /* No dragging within a graph occured, act normally */
    }
}

void GraphsView::handleGestureEvent(const GestureEvent& evt)
{
    if(clickStatus == ClickStatus::CLICK_DRAGGING)
    {
        SwipeArea.handleGestureEvent(evt);          /* We are dragging, forward gesture events to swipe container only */
    }
    else
    {
        GraphsViewBase::handleGestureEvent(evt);    /* No dragging within a graph occured, act normally */
    }
}

void GraphsView::filterData(void)
{
    filtredTemp = filterObj[0].kalmanFilter(gui_temperature, 0.1f);
    filtredHum  = filterObj[1].kalmanFilter(gui_humidity, 0.05f);
    filtredPres = filterObj[2].kalmanFilter(gui_pressure, 0.001f);
    filtredIAQ  = filterObj[3].kalmanFilter(gui_iaq, 0.001);
    //filtredCO2  = filterObj[4].kalmanFilter(gui_co2, 1.0f);
}
/* Function for displaying the temperature graph */
void GraphsView::displayTemperatureGraph(float temperatureValue)
{
    TempGraph.addDataPoint(temperatureValue*100.0f);
    TempGraph.setGraphRangeYAuto(false, 5);
    TempGraphMajorYAxisLabel.setInterval(((TempGraph.getGraphRangeYMaxAsInt() - TempGraph.getGraphRangeYMinAsInt())/10));
    setTempGraphMajorYAxisLabel();
    Unicode::snprintfFloat(textArea1Buffer, TEXTAREA1_SIZE, "%.2f", temperatureValue);
    textArea1.invalidate();
}

/* Function for displaying the humidity graph */
void GraphsView::displayHumidityGraph(float humidityValue)
{
    HumGraph.addDataPoint(humidityValue*100);
    HumGraph.setGraphRangeYAuto(false, 5);
    HumGraphMajorYAxisLabel.setInterval(((HumGraph.getGraphRangeYMaxAsInt() - HumGraph.getGraphRangeYMinAsInt())/10));
    setHumGraphMajorYAxisLabel();
    Unicode::snprintfFloat(textArea2Buffer, TEXTAREA2_SIZE, "%.2f", humidityValue);
    textArea2.invalidate();
}

/* Function for displaying the pressure graph */
void GraphsView::displayPressureGraph(float pressureValue)
{
    PresGraph.addDataPoint(pressureValue*100);
    PresGraph.setGraphRangeYAuto(false, 5);
    PresGraphMajorYAxisLabel.setInterval(((PresGraph.getGraphRangeYMaxAsInt() - PresGraph.getGraphRangeYMinAsInt())/10));
    setPresGraphMajorYAxisLabel();
    Unicode::snprintfFloat(textArea3Buffer, TEXTAREA3_SIZE, "%.2f", pressureValue);
    textArea3.invalidate();
}

/* Function for displaying the IAQ graph */
void GraphsView::displayIAQGraph(float IAQValue)
{
    IAQGraph.addDataPoint(IAQValue*100);
    IAQGraph.setGraphRangeYAuto(false, 5);
    IAQGraphMajorYAxisLabel.setInterval(((IAQGraph.getGraphRangeYMaxAsInt() - IAQGraph.getGraphRangeYMinAsInt())/10));
    setIAQGraphMajorYAxisLabel();
    Unicode::snprintfFloat(textArea4Buffer, TEXTAREA4_SIZE, "%.2f", IAQValue);
    textArea4.invalidate();
}

/* Function for setting the temperature graph Y axis labels */
void GraphsView::setTempGraphMajorYAxisLabel(void)
{
    int GraphRangeYMinAsInt = TempGraph.getGraphRangeYMinAsInt();
    int IntervalAsInt       = TempGraphMajorYAxisLabel.getIntervalAsInt();
    Unicode::snprintfFloat( graphInterval1_1Buffer, GRAPHINTERVAL1_1_SIZE, "%.2f", ((float)(GraphRangeYMinAsInt + IntervalAsInt *  0)/100));
    Unicode::snprintfFloat( graphInterval1_0Buffer, GRAPHINTERVAL1_0_SIZE, "%.2f", ((float)(GraphRangeYMinAsInt + IntervalAsInt * 10)/100));
    graphInterval1_1.invalidate();
    graphInterval1_0.invalidate();
}

/* Function for setting the humidity graph Y axis labels */
void GraphsView::setHumGraphMajorYAxisLabel(void)
{
    int GraphRangeYMinAsInt = HumGraph.getGraphRangeYMinAsInt();
    int IntervalAsInt       = HumGraphMajorYAxisLabel.getIntervalAsInt();
    Unicode::snprintfFloat( graphInterval2_1Buffer, GRAPHINTERVAL2_1_SIZE, "%.2f", ((float)(GraphRangeYMinAsInt + IntervalAsInt *  0)/100));
    Unicode::snprintfFloat( graphInterval2_0Buffer, GRAPHINTERVAL2_0_SIZE, "%.2f", ((float)(GraphRangeYMinAsInt + IntervalAsInt * 10)/100));
    graphInterval2_1.invalidate();
    graphInterval2_0.invalidate();
}

/* Function for setting the pressure graph Y axis labels */
void GraphsView::setPresGraphMajorYAxisLabel(void)
{
    int GraphRangeYMinAsInt = PresGraph.getGraphRangeYMinAsInt();
    int IntervalAsInt       = PresGraphMajorYAxisLabel.getIntervalAsInt();
    Unicode::snprintfFloat( graphInterval3_1Buffer, GRAPHINTERVAL3_1_SIZE, "%.2f", ((float)(GraphRangeYMinAsInt + IntervalAsInt *  0)/100));
    Unicode::snprintfFloat( graphInterval3_0Buffer, GRAPHINTERVAL3_0_SIZE, "%.2f", ((float)(GraphRangeYMinAsInt + IntervalAsInt * 10)/100));
    graphInterval3_1.invalidate();
    graphInterval3_0.invalidate();
}

/* Function for setting the IAQ graph Y axis labels */
void GraphsView::setIAQGraphMajorYAxisLabel(void)
{
    int GraphRangeYMinAsInt = IAQGraph.getGraphRangeYMinAsInt();
    int IntervalAsInt       = IAQGraphMajorYAxisLabel.getIntervalAsInt();
    Unicode::snprintfFloat( graphInterval4_1Buffer, GRAPHINTERVAL4_1_SIZE, "%.2f", ((float)(GraphRangeYMinAsInt + IntervalAsInt *  0)/100));
    Unicode::snprintfFloat( graphInterval4_0Buffer, GRAPHINTERVAL4_0_SIZE, "%.2f", ((float)(GraphRangeYMinAsInt + IntervalAsInt * 10)/100));
    graphInterval4_1.invalidate();
    graphInterval4_0.invalidate();
}

