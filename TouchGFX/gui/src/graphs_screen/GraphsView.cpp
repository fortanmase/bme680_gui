#include <gui/graphs_screen/GraphsView.hpp>

extern uint32_t (*pfHAL_GetTick)(void);    /* Pointer to HAL_GetTick imported from main*/
/* Variables imported from main */
float gui_temperature;
float gui_humidity;
float gui_pressure;
float gui_iaq;
float gui_co2;

uint32_t lastTickValue; /* Variable monitoring last tick value (HAL_GetTick) */
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
    if(pfHAL_GetTick() - lastTickValue >= 3000)     /* wait 3 seconds till data from BME680 gets ready*/
    {
        /* Display the graphs*/
        displayTemperatureGraph(gui_temperature);
        displayHumidityGraph(gui_humidity);
        displayPressureGraph(gui_pressure/100/1.33333);
        displayIAQGraph(gui_iaq);
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

/* Function for displaying the temperature graph */
void GraphsView::displayTemperatureGraph(float temperatureValue)
{
    TempGraph.addDataPoint(temperatureValue*100);
    TempGraph.setGraphRangeYAuto(false, 3);
    TempGraphMajorYAxisLabel.setInterval(((TempGraph.getGraphRangeYMaxAsInt() - TempGraph.getGraphRangeYMinAsInt())/10));
    TempGraphMajorYAxisGrid.setInterval (((TempGraph.getGraphRangeYMaxAsInt() - TempGraph.getGraphRangeYMinAsInt())/10));
    setTempGraphMajorYAxisLabel();
    Unicode::snprintfFloat(textArea1Buffer, TEXTAREA1_SIZE, "%.2f", temperatureValue);
    textArea1.invalidate();
    TempGraph.invalidate();
}

/* Function for displaying the humidity graph */
void GraphsView::displayHumidityGraph(float humidityValue)
{
    HumGraph.addDataPoint(humidityValue*100);
    HumGraph.setGraphRangeYAuto(false, 3);
    HumGraphMajorYAxisLabel.setInterval(((HumGraph.getGraphRangeYMaxAsInt() - HumGraph.getGraphRangeYMinAsInt())/10));
    HumGraphMajorYAxisGrid.setInterval (((HumGraph.getGraphRangeYMaxAsInt() - HumGraph.getGraphRangeYMinAsInt())/10));
    setHumGraphMajorYAxisLabel();
    Unicode::snprintfFloat(textArea2Buffer, TEXTAREA2_SIZE, "%.2f", humidityValue);
    textArea2.invalidate();
    HumGraph.invalidate();
}

/* Function for displaying the pressure graph */
void GraphsView::displayPressureGraph(float pressureValue)
{
    PresGraph.addDataPoint(pressureValue*100);
    PresGraph.setGraphRangeYAuto(false, 3);
    PresGraphMajorYAxisLabel.setInterval(((PresGraph.getGraphRangeYMaxAsInt() - PresGraph.getGraphRangeYMinAsInt())/10));
    PresGraphMajorYAxisGrid.setInterval (((PresGraph.getGraphRangeYMaxAsInt() - PresGraph.getGraphRangeYMinAsInt())/10));
    setPresGraphMajorYAxisLabel();
    Unicode::snprintfFloat(textArea3Buffer, TEXTAREA3_SIZE, "%.2f", pressureValue);
    textArea3.invalidate();
    PresGraph.invalidate();
}

/* Function for displaying the IAQ graph */
void GraphsView::displayIAQGraph(float IAQValue)
{
    IAQGraph.addDataPoint(IAQValue*100);
    IAQGraph.setGraphRangeYAuto(false, 3);
    IAQGraphMajorYAxisLabel.setInterval(((IAQGraph.getGraphRangeYMaxAsInt() - IAQGraph.getGraphRangeYMinAsInt())/10));
    IAQGraphMajorYAxisGrid.setInterval (((IAQGraph.getGraphRangeYMaxAsInt() - IAQGraph.getGraphRangeYMinAsInt())/10));
    setIAQGraphMajorYAxisLabel();
    Unicode::snprintfFloat(textArea4Buffer, TEXTAREA4_SIZE, "%.2f", IAQValue);
    textArea4.invalidate();
    IAQGraph.invalidate();
}

/* Function for setting the temperature graph Y axis labels */
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

/* Function for setting the humidity graph Y axis labels */
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

/* Function for setting the pressure graph Y axis labels */
void GraphsView::setPresGraphMajorYAxisLabel(void)
{
    int GraphRangeYMinAsInt = PresGraph.getGraphRangeYMinAsInt();
    int IntervalAsInt       = PresGraphMajorYAxisLabel.getIntervalAsInt();
    Unicode::snprintfFloat( graphInterval3_10Buffer, GRAPHINTERVAL3_10_SIZE, "%.1f", ((float)(GraphRangeYMinAsInt + IntervalAsInt *  0)/100));
    Unicode::snprintfFloat( graphInterval3_9Buffer,  GRAPHINTERVAL3_9_SIZE,  "%.1f", ((float)(GraphRangeYMinAsInt + IntervalAsInt *  1)/100));
    Unicode::snprintfFloat( graphInterval3_8Buffer,  GRAPHINTERVAL3_8_SIZE,  "%.1f", ((float)(GraphRangeYMinAsInt + IntervalAsInt *  2)/100));
    Unicode::snprintfFloat( graphInterval3_7Buffer,  GRAPHINTERVAL3_7_SIZE,  "%.1f", ((float)(GraphRangeYMinAsInt + IntervalAsInt *  3)/100));
    Unicode::snprintfFloat( graphInterval3_6Buffer,  GRAPHINTERVAL3_6_SIZE,  "%.1f", ((float)(GraphRangeYMinAsInt + IntervalAsInt *  4)/100));
    Unicode::snprintfFloat( graphInterval3_5Buffer,  GRAPHINTERVAL3_5_SIZE,  "%.1f", ((float)(GraphRangeYMinAsInt + IntervalAsInt *  5)/100));
    Unicode::snprintfFloat( graphInterval3_4Buffer,  GRAPHINTERVAL3_4_SIZE,  "%.1f", ((float)(GraphRangeYMinAsInt + IntervalAsInt *  6)/100));
    Unicode::snprintfFloat( graphInterval3_3Buffer,  GRAPHINTERVAL3_3_SIZE,  "%.1f", ((float)(GraphRangeYMinAsInt + IntervalAsInt *  7)/100));
    Unicode::snprintfFloat( graphInterval3_2Buffer,  GRAPHINTERVAL3_2_SIZE,  "%.1f", ((float)(GraphRangeYMinAsInt + IntervalAsInt *  8)/100));
    Unicode::snprintfFloat( graphInterval3_1Buffer,  GRAPHINTERVAL3_1_SIZE,  "%.1f", ((float)(GraphRangeYMinAsInt + IntervalAsInt *  9)/100));
    Unicode::snprintfFloat( graphInterval3Buffer,    GRAPHINTERVAL3_SIZE,    "%.1f", ((float)(GraphRangeYMinAsInt + IntervalAsInt * 10)/100));
    graphInterval3_10.invalidate();
    graphInterval3_9.invalidate();
    graphInterval3_8.invalidate();
    graphInterval3_7.invalidate();
    graphInterval3_6.invalidate();
    graphInterval3_5.invalidate();
    graphInterval3_4.invalidate();
    graphInterval3_3.invalidate();
    graphInterval3_2.invalidate();
    graphInterval3_1.invalidate();
    graphInterval3.invalidate();
}

/* Function for setting the IAQ graph Y axis labels */
void GraphsView::setIAQGraphMajorYAxisLabel(void)
{
    int GraphRangeYMinAsInt = IAQGraph.getGraphRangeYMinAsInt();
    int IntervalAsInt       = IAQGraphMajorYAxisLabel.getIntervalAsInt();
    Unicode::snprintfFloat( graphInterval4_10Buffer, GRAPHINTERVAL4_10_SIZE, "%.1f", ((float)(GraphRangeYMinAsInt + IntervalAsInt *  0)/100));
    Unicode::snprintfFloat( graphInterval4_9Buffer,  GRAPHINTERVAL4_9_SIZE,  "%.1f", ((float)(GraphRangeYMinAsInt + IntervalAsInt *  1)/100));
    Unicode::snprintfFloat( graphInterval4_8Buffer,  GRAPHINTERVAL4_8_SIZE,  "%.1f", ((float)(GraphRangeYMinAsInt + IntervalAsInt *  2)/100));
    Unicode::snprintfFloat( graphInterval4_7Buffer,  GRAPHINTERVAL4_7_SIZE,  "%.1f", ((float)(GraphRangeYMinAsInt + IntervalAsInt *  3)/100));
    Unicode::snprintfFloat( graphInterval4_6Buffer,  GRAPHINTERVAL4_6_SIZE,  "%.1f", ((float)(GraphRangeYMinAsInt + IntervalAsInt *  4)/100));
    Unicode::snprintfFloat( graphInterval4_5Buffer,  GRAPHINTERVAL4_5_SIZE,  "%.1f", ((float)(GraphRangeYMinAsInt + IntervalAsInt *  5)/100));
    Unicode::snprintfFloat( graphInterval4_4Buffer,  GRAPHINTERVAL4_4_SIZE,  "%.1f", ((float)(GraphRangeYMinAsInt + IntervalAsInt *  6)/100));
    Unicode::snprintfFloat( graphInterval4_3Buffer,  GRAPHINTERVAL4_3_SIZE,  "%.1f", ((float)(GraphRangeYMinAsInt + IntervalAsInt *  7)/100));
    Unicode::snprintfFloat( graphInterval4_2Buffer,  GRAPHINTERVAL4_2_SIZE,  "%.1f", ((float)(GraphRangeYMinAsInt + IntervalAsInt *  8)/100));
    Unicode::snprintfFloat( graphInterval4_1Buffer,  GRAPHINTERVAL4_1_SIZE,  "%.1f", ((float)(GraphRangeYMinAsInt + IntervalAsInt *  9)/100));
    Unicode::snprintfFloat( graphInterval4Buffer,    GRAPHINTERVAL4_SIZE,    "%.1f", ((float)(GraphRangeYMinAsInt + IntervalAsInt * 10)/100));
    graphInterval4_10.invalidate();
    graphInterval4_9.invalidate();
    graphInterval4_8.invalidate();
    graphInterval4_7.invalidate();
    graphInterval4_6.invalidate();
    graphInterval4_5.invalidate();
    graphInterval4_4.invalidate();
    graphInterval4_3.invalidate();
    graphInterval4_2.invalidate();
    graphInterval4_1.invalidate();
    graphInterval4.invalidate();
}

