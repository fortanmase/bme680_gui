/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef GRAPHSVIEWBASE_HPP
#define GRAPHSVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/graphs_screen/GraphsPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/containers/SwipeContainer.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/graph/GraphScroll.hpp>
#include <touchgfx/widgets/graph/GraphElements.hpp>
#include <touchgfx/widgets/canvas/PainterRGB565.hpp>
#include <touchgfx/widgets/graph/GraphLabels.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/widgets/canvas/Line.hpp>

class GraphsViewBase : public touchgfx::View<GraphsPresenter>
{
public:
    GraphsViewBase();
    virtual ~GraphsViewBase() {}
    virtual void setupScreen();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::SwipeContainer SwipeArea;
    touchgfx::Container Temperature;
    touchgfx::Box TempBox;
    touchgfx::GraphScroll<100> TempGraph;
    touchgfx::GraphElementLine TempGraphLine1;
    touchgfx::PainterRGB565 TempGraphLine1Painter;
    touchgfx::GraphElementGridX TempGraphMajorXAxisGrid;
    touchgfx::GraphLabelsY TempGraphMajorYAxisLabel;
    touchgfx::TextAreaWithOneWildcard textArea1;
    touchgfx::Line line1;
    touchgfx::PainterRGB565 line1Painter;
    touchgfx::Line line1_1;
    touchgfx::PainterRGB565 line1_1Painter;
    touchgfx::Line line1_2;
    touchgfx::PainterRGB565 line1_2Painter;
    touchgfx::Line line1_3;
    touchgfx::PainterRGB565 line1_3Painter;
    touchgfx::Line line1_4;
    touchgfx::PainterRGB565 line1_4Painter;
    touchgfx::Line line1_5;
    touchgfx::PainterRGB565 line1_5Painter;
    touchgfx::Line line1_6;
    touchgfx::PainterRGB565 line1_6Painter;
    touchgfx::Line line1_7;
    touchgfx::PainterRGB565 line1_7Painter;
    touchgfx::Line line1_8;
    touchgfx::PainterRGB565 line1_8Painter;
    touchgfx::Line line1_9;
    touchgfx::PainterRGB565 line1_9Painter;
    touchgfx::Line line1_10;
    touchgfx::PainterRGB565 line1_10Painter;
    touchgfx::Line line1_11;
    touchgfx::PainterRGB565 line1_11Painter;
    touchgfx::Line line1_12;
    touchgfx::PainterRGB565 line1_12Painter;
    touchgfx::TextAreaWithOneWildcard graphInterval1_0;
    touchgfx::TextAreaWithOneWildcard graphInterval1_1;
    touchgfx::Container Humidity;
    touchgfx::Box HumBox;
    touchgfx::GraphScroll<100> HumGraph;
    touchgfx::GraphElementLine HumGraphLine1;
    touchgfx::PainterRGB565 HumGraphLine1Painter;
    touchgfx::GraphElementGridX HumGraphMajorXAxisGrid;
    touchgfx::GraphLabelsY HumGraphMajorYAxisLabel;
    touchgfx::TextAreaWithOneWildcard textArea2;
    touchgfx::Line line2;
    touchgfx::PainterRGB565 line2Painter;
    touchgfx::Line line2_1;
    touchgfx::PainterRGB565 line2_1Painter;
    touchgfx::Line line2_2;
    touchgfx::PainterRGB565 line2_2Painter;
    touchgfx::Line line2_3;
    touchgfx::PainterRGB565 line2_3Painter;
    touchgfx::Line line2_4;
    touchgfx::PainterRGB565 line2_4Painter;
    touchgfx::Line line2_5;
    touchgfx::PainterRGB565 line2_5Painter;
    touchgfx::Line line2_6;
    touchgfx::PainterRGB565 line2_6Painter;
    touchgfx::Line line2_7;
    touchgfx::PainterRGB565 line2_7Painter;
    touchgfx::Line line2_8;
    touchgfx::PainterRGB565 line2_8Painter;
    touchgfx::Line line2_9;
    touchgfx::PainterRGB565 line2_9Painter;
    touchgfx::Line line2_10;
    touchgfx::PainterRGB565 line2_10Painter;
    touchgfx::Line line2_11;
    touchgfx::PainterRGB565 line2_11Painter;
    touchgfx::Line line2_12;
    touchgfx::PainterRGB565 line2_12Painter;
    touchgfx::TextAreaWithOneWildcard graphInterval2_0;
    touchgfx::TextAreaWithOneWildcard graphInterval2_1;
    touchgfx::Container Pressure;
    touchgfx::Box PresBox;
    touchgfx::GraphScroll<100> PresGraph;
    touchgfx::GraphElementLine PresGraphLine1;
    touchgfx::PainterRGB565 PresGraphLine1Painter;
    touchgfx::GraphElementGridX PresGraphMajorXAxisGrid;
    touchgfx::GraphLabelsY PresGraphMajorYAxisLabel;
    touchgfx::TextAreaWithOneWildcard textArea3;
    touchgfx::Line line3;
    touchgfx::PainterRGB565 line3Painter;
    touchgfx::Line line3_1;
    touchgfx::PainterRGB565 line3_1Painter;
    touchgfx::Line line3_2;
    touchgfx::PainterRGB565 line3_2Painter;
    touchgfx::Line line3_3;
    touchgfx::PainterRGB565 line3_3Painter;
    touchgfx::Line line3_4;
    touchgfx::PainterRGB565 line3_4Painter;
    touchgfx::Line line3_5;
    touchgfx::PainterRGB565 line3_5Painter;
    touchgfx::Line line3_6;
    touchgfx::PainterRGB565 line3_6Painter;
    touchgfx::Line line3_7;
    touchgfx::PainterRGB565 line3_7Painter;
    touchgfx::Line line3_8;
    touchgfx::PainterRGB565 line3_8Painter;
    touchgfx::Line line3_9;
    touchgfx::PainterRGB565 line3_9Painter;
    touchgfx::Line line3_10;
    touchgfx::PainterRGB565 line3_10Painter;
    touchgfx::Line line3_11;
    touchgfx::PainterRGB565 line3_11Painter;
    touchgfx::Line line3_12;
    touchgfx::PainterRGB565 line3_12Painter;
    touchgfx::TextAreaWithOneWildcard graphInterval3_0;
    touchgfx::TextAreaWithOneWildcard graphInterval3_1;
    touchgfx::Container IAQ;
    touchgfx::Box IAQBox;
    touchgfx::GraphScroll<100> IAQGraph;
    touchgfx::GraphElementLine IAQGraphLine1;
    touchgfx::PainterRGB565 IAQGraphLine1Painter;
    touchgfx::GraphElementGridX IAQGraphMajorXAxisGrid;
    touchgfx::GraphLabelsY IAQGraphMajorYAxisLabel;
    touchgfx::TextAreaWithOneWildcard textArea4;
    touchgfx::Line line4;
    touchgfx::PainterRGB565 line4Painter;
    touchgfx::Line line4_1;
    touchgfx::PainterRGB565 line4_1Painter;
    touchgfx::Line line4_2;
    touchgfx::PainterRGB565 line4_2Painter;
    touchgfx::Line line4_3;
    touchgfx::PainterRGB565 line4_3Painter;
    touchgfx::Line line4_4;
    touchgfx::PainterRGB565 line4_4Painter;
    touchgfx::Line line4_5;
    touchgfx::PainterRGB565 line4_5Painter;
    touchgfx::Line line4_6;
    touchgfx::PainterRGB565 line4_6Painter;
    touchgfx::Line line4_7;
    touchgfx::PainterRGB565 line4_7Painter;
    touchgfx::Line line4_8;
    touchgfx::PainterRGB565 line4_8Painter;
    touchgfx::Line line4_9;
    touchgfx::PainterRGB565 line4_9Painter;
    touchgfx::Line line4_10;
    touchgfx::PainterRGB565 line4_10Painter;
    touchgfx::Line line4_11;
    touchgfx::PainterRGB565 line4_11Painter;
    touchgfx::Line line4_12;
    touchgfx::PainterRGB565 line4_12Painter;
    touchgfx::TextAreaWithOneWildcard graphInterval4_0;
    touchgfx::TextAreaWithOneWildcard graphInterval4_1;

    /*
     * Wildcard Buffers
     */
    static const uint16_t TEXTAREA1_SIZE = 20;
    touchgfx::Unicode::UnicodeChar textArea1Buffer[TEXTAREA1_SIZE];
    static const uint16_t GRAPHINTERVAL1_0_SIZE = 20;
    touchgfx::Unicode::UnicodeChar graphInterval1_0Buffer[GRAPHINTERVAL1_0_SIZE];
    static const uint16_t GRAPHINTERVAL1_1_SIZE = 20;
    touchgfx::Unicode::UnicodeChar graphInterval1_1Buffer[GRAPHINTERVAL1_1_SIZE];
    static const uint16_t TEXTAREA2_SIZE = 20;
    touchgfx::Unicode::UnicodeChar textArea2Buffer[TEXTAREA2_SIZE];
    static const uint16_t GRAPHINTERVAL2_0_SIZE = 20;
    touchgfx::Unicode::UnicodeChar graphInterval2_0Buffer[GRAPHINTERVAL2_0_SIZE];
    static const uint16_t GRAPHINTERVAL2_1_SIZE = 20;
    touchgfx::Unicode::UnicodeChar graphInterval2_1Buffer[GRAPHINTERVAL2_1_SIZE];
    static const uint16_t TEXTAREA3_SIZE = 20;
    touchgfx::Unicode::UnicodeChar textArea3Buffer[TEXTAREA3_SIZE];
    static const uint16_t GRAPHINTERVAL3_0_SIZE = 20;
    touchgfx::Unicode::UnicodeChar graphInterval3_0Buffer[GRAPHINTERVAL3_0_SIZE];
    static const uint16_t GRAPHINTERVAL3_1_SIZE = 20;
    touchgfx::Unicode::UnicodeChar graphInterval3_1Buffer[GRAPHINTERVAL3_1_SIZE];
    static const uint16_t TEXTAREA4_SIZE = 20;
    touchgfx::Unicode::UnicodeChar textArea4Buffer[TEXTAREA4_SIZE];
    static const uint16_t GRAPHINTERVAL4_0_SIZE = 20;
    touchgfx::Unicode::UnicodeChar graphInterval4_0Buffer[GRAPHINTERVAL4_0_SIZE];
    static const uint16_t GRAPHINTERVAL4_1_SIZE = 20;
    touchgfx::Unicode::UnicodeChar graphInterval4_1Buffer[GRAPHINTERVAL4_1_SIZE];

private:

    /*
     * Canvas Buffer Size
     */
    static const uint16_t CANVAS_BUFFER_SIZE = 12000;
    uint8_t canvasBuffer[CANVAS_BUFFER_SIZE];
};

#endif // GRAPHSVIEWBASE_HPP
