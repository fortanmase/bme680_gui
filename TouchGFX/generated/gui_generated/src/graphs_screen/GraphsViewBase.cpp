/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/graphs_screen/GraphsViewBase.hpp>
#include <touchgfx/Color.hpp>
#include "BitmapDatabase.hpp"
#include <texts/TextKeysAndLanguages.hpp>

GraphsViewBase::GraphsViewBase() :
    buttonCallback(this, &GraphsViewBase::buttonCallbackHandler)
{

    touchgfx::CanvasWidgetRenderer::setupBuffer(canvasBuffer, CANVAS_BUFFER_SIZE);

    __background.setPosition(0, 0, 800, 480);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));

    SwipeArea.setXY(0, 0);
    SwipeArea.setPageIndicatorBitmaps(touchgfx::Bitmap(BITMAP_DARK_PAGEINDICATOR_DOT_INDICATOR_SMALL_NORMAL_ID), touchgfx::Bitmap(BITMAP_DARK_PAGEINDICATOR_DOT_INDICATOR_SMALL_HIGHLIGHT_ID));
    SwipeArea.setPageIndicatorXY(370, 450);
    SwipeArea.setSwipeCutoff(50);
    SwipeArea.setEndSwipeElasticWidth(50);

    Temperature.setWidth(800);
    Temperature.setHeight(480);

    TempBox.setPosition(0, 0, 800, 480);
    TempBox.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    Temperature.add(TempBox);

    TempGraph.setScale(100);
    TempGraph.setGraphRangeX(0, 100);
    TempGraph.setPosition(141, 43, 577, 394);
    TempGraph.setGraphAreaMargin(8, 0, 20, 8);
    TempGraph.setGraphAreaPadding(0, 0, 0, 0);
    TempGraph.setGraphRangeY(0, 10);

    TempGraphMajorXAxisGrid.setScale(100);
    TempGraphMajorXAxisGrid.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    TempGraphMajorXAxisGrid.setInterval(10);
    TempGraphMajorXAxisGrid.setLineWidth(1);
    TempGraph.addGraphElement(TempGraphMajorXAxisGrid);

    TempGraphMajorYAxisLabel.setScale(100);
    TempGraphMajorYAxisLabel.setInterval(1);
    TempGraphMajorYAxisLabel.setLabelTypedText(touchgfx::TypedText(T_SINGLEUSEID34));
    TempGraphMajorYAxisLabel.setColor(touchgfx::Color::getColorFromRGB(20, 151, 197));
    TempGraphMajorYAxisLabel.setAlpha(0);
    TempGraph.addLeftElement(TempGraphMajorYAxisLabel);

    TempGraphLine1.setScale(100);
    TempGraphLine1Painter.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    TempGraphLine1.setPainter(TempGraphLine1Painter);
    TempGraphLine1.setLineWidth(2);
    TempGraph.addGraphElement(TempGraphLine1);
    Temperature.add(TempGraph);

    textArea1.setPosition(292, 9, 255, 29);
    textArea1.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textArea1.setLinespacing(0);
    Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID14).getText());
    textArea1.setWildcard(textArea1Buffer);
    textArea1.setTypedText(touchgfx::TypedText(T_SINGLEUSEID13));
    Temperature.add(textArea1);

    line1.setPosition(141, 399, 557, 58);
    line1Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line1.setPainter(line1Painter);
    line1.setStart(0, 30);
    line1.setEnd(576, 30);
    line1.setLineWidth(1);
    line1.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    Temperature.add(line1);

    line1_1.setPosition(141, 23, 582, 61);
    line1_1Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line1_1.setPainter(line1_1Painter);
    line1_1.setStart(0, 28);
    line1_1.setEnd(557, 28);
    line1_1.setLineWidth(1);
    line1_1.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    Temperature.add(line1_1);

    line1_2.setPosition(670, 47, 48, 401);
    line1_2Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line1_2.setPainter(line1_2Painter);
    line1_2.setStart(28, 382);
    line1_2.setEnd(28, 4);
    line1_2.setLineWidth(1);
    line1_2.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    Temperature.add(line1_2);

    line1_3.setPosition(117, 47, 48, 403);
    line1_3Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line1_3.setPainter(line1_3Painter);
    line1_3.setStart(24, 382);
    line1_3.setEnd(24, 4);
    line1_3.setLineWidth(1);
    line1_3.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    Temperature.add(line1_3);

    line1_4.setPosition(141, 361, 557, 58);
    line1_4Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line1_4.setPainter(line1_4Painter);
    line1_4.setStart(0, 30);
    line1_4.setEnd(576, 30);
    line1_4.setLineWidth(1);
    line1_4.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    Temperature.add(line1_4);

    line1_5.setPosition(141, 323, 557, 58);
    line1_5Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line1_5.setPainter(line1_5Painter);
    line1_5.setStart(0, 30);
    line1_5.setEnd(576, 30);
    line1_5.setLineWidth(1);
    line1_5.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    Temperature.add(line1_5);

    line1_6.setPosition(141, 286, 557, 58);
    line1_6Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line1_6.setPainter(line1_6Painter);
    line1_6.setStart(0, 30);
    line1_6.setEnd(576, 30);
    line1_6.setLineWidth(1);
    line1_6.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    Temperature.add(line1_6);

    line1_7.setPosition(141, 248, 557, 58);
    line1_7Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line1_7.setPainter(line1_7Painter);
    line1_7.setStart(0, 30);
    line1_7.setEnd(576, 30);
    line1_7.setLineWidth(1);
    line1_7.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    Temperature.add(line1_7);

    line1_8.setPosition(141, 210, 557, 58);
    line1_8Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line1_8.setPainter(line1_8Painter);
    line1_8.setStart(0, 30);
    line1_8.setEnd(576, 30);
    line1_8.setLineWidth(1);
    line1_8.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    Temperature.add(line1_8);

    line1_9.setPosition(141, 173, 557, 58);
    line1_9Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line1_9.setPainter(line1_9Painter);
    line1_9.setStart(0, 30);
    line1_9.setEnd(576, 30);
    line1_9.setLineWidth(1);
    line1_9.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    Temperature.add(line1_9);

    line1_10.setPosition(141, 135, 557, 58);
    line1_10Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line1_10.setPainter(line1_10Painter);
    line1_10.setStart(0, 30);
    line1_10.setEnd(576, 30);
    line1_10.setLineWidth(1);
    line1_10.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    Temperature.add(line1_10);

    line1_11.setPosition(141, 97, 557, 58);
    line1_11Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line1_11.setPainter(line1_11Painter);
    line1_11.setStart(0, 30);
    line1_11.setEnd(576, 30);
    line1_11.setLineWidth(1);
    line1_11.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    Temperature.add(line1_11);

    line1_12.setPosition(141, 60, 557, 58);
    line1_12Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line1_12.setPainter(line1_12Painter);
    line1_12.setStart(0, 30);
    line1_12.setEnd(576, 30);
    line1_12.setLineWidth(1);
    line1_12.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    Temperature.add(line1_12);

    graphInterval1_0.setPosition(61, 39, 74, 25);
    graphInterval1_0.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    graphInterval1_0.setLinespacing(0);
    graphInterval1_0Buffer[0] = 0;
    graphInterval1_0.setWildcard(graphInterval1_0Buffer);
    graphInterval1_0.setTypedText(touchgfx::TypedText(T_SINGLEUSEID23));
    Temperature.add(graphInterval1_0);

    graphInterval1_1.setPosition(61, 416, 74, 25);
    graphInterval1_1.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    graphInterval1_1.setLinespacing(0);
    graphInterval1_1Buffer[0] = 0;
    graphInterval1_1.setWildcard(graphInterval1_1Buffer);
    graphInterval1_1.setTypedText(touchgfx::TypedText(T_SINGLEUSEID33));
    Temperature.add(graphInterval1_1);
    SwipeArea.add(Temperature);

    Humidity.setWidth(800);
    Humidity.setHeight(480);

    HumBox.setPosition(0, 0, 800, 480);
    HumBox.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    Humidity.add(HumBox);

    HumGraph.setScale(100);
    HumGraph.setGraphRangeX(0, 100);
    HumGraph.setPosition(141, 43, 577, 394);
    HumGraph.setGraphAreaMargin(8, 0, 20, 8);
    HumGraph.setGraphAreaPadding(0, 0, 0, 0);
    HumGraph.setGraphRangeY(0, 1);

    HumGraphMajorXAxisGrid.setScale(100);
    HumGraphMajorXAxisGrid.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    HumGraphMajorXAxisGrid.setInterval(10);
    HumGraphMajorXAxisGrid.setLineWidth(1);
    HumGraph.addGraphElement(HumGraphMajorXAxisGrid);

    HumGraphMajorYAxisLabel.setScale(100);
    HumGraphMajorYAxisLabel.setInterval(1);
    HumGraphMajorYAxisLabel.setLabelTypedText(touchgfx::TypedText(T_SINGLEUSEID34));
    HumGraphMajorYAxisLabel.setColor(touchgfx::Color::getColorFromRGB(20, 151, 197));
    HumGraphMajorYAxisLabel.setAlpha(0);
    HumGraph.addLeftElement(HumGraphMajorYAxisLabel);

    HumGraphLine1.setScale(100);
    HumGraphLine1Painter.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    HumGraphLine1.setPainter(HumGraphLine1Painter);
    HumGraphLine1.setLineWidth(2);
    HumGraph.addGraphElement(HumGraphLine1);
    Humidity.add(HumGraph);

    textArea2.setPosition(292, 11, 255, 29);
    textArea2.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textArea2.setLinespacing(0);
    Unicode::snprintf(textArea2Buffer, TEXTAREA2_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID36).getText());
    textArea2.setWildcard(textArea2Buffer);
    textArea2.setTypedText(touchgfx::TypedText(T_SINGLEUSEID35));
    Humidity.add(textArea2);

    line2.setPosition(141, 399, 557, 58);
    line2Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line2.setPainter(line2Painter);
    line2.setStart(0, 30);
    line2.setEnd(576, 30);
    line2.setLineWidth(1);
    line2.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    Humidity.add(line2);

    line2_1.setPosition(141, 23, 582, 61);
    line2_1Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line2_1.setPainter(line2_1Painter);
    line2_1.setStart(0, 28);
    line2_1.setEnd(557, 28);
    line2_1.setLineWidth(1);
    line2_1.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    Humidity.add(line2_1);

    line2_2.setPosition(670, 47, 48, 401);
    line2_2Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line2_2.setPainter(line2_2Painter);
    line2_2.setStart(28, 382);
    line2_2.setEnd(28, 4);
    line2_2.setLineWidth(1);
    line2_2.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    Humidity.add(line2_2);

    line2_3.setPosition(117, 47, 48, 403);
    line2_3Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line2_3.setPainter(line2_3Painter);
    line2_3.setStart(24, 382);
    line2_3.setEnd(24, 4);
    line2_3.setLineWidth(1);
    line2_3.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    Humidity.add(line2_3);

    line2_4.setPosition(141, 361, 557, 58);
    line2_4Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line2_4.setPainter(line2_4Painter);
    line2_4.setStart(0, 30);
    line2_4.setEnd(576, 30);
    line2_4.setLineWidth(1);
    line2_4.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    Humidity.add(line2_4);

    line2_5.setPosition(141, 323, 557, 58);
    line2_5Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line2_5.setPainter(line2_5Painter);
    line2_5.setStart(0, 30);
    line2_5.setEnd(576, 30);
    line2_5.setLineWidth(1);
    line2_5.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    Humidity.add(line2_5);

    line2_6.setPosition(141, 286, 557, 58);
    line2_6Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line2_6.setPainter(line2_6Painter);
    line2_6.setStart(0, 30);
    line2_6.setEnd(576, 30);
    line2_6.setLineWidth(1);
    line2_6.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    Humidity.add(line2_6);

    line2_7.setPosition(141, 248, 557, 58);
    line2_7Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line2_7.setPainter(line2_7Painter);
    line2_7.setStart(0, 30);
    line2_7.setEnd(576, 30);
    line2_7.setLineWidth(1);
    line2_7.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    Humidity.add(line2_7);

    line2_8.setPosition(141, 210, 557, 58);
    line2_8Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line2_8.setPainter(line2_8Painter);
    line2_8.setStart(0, 30);
    line2_8.setEnd(576, 30);
    line2_8.setLineWidth(1);
    line2_8.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    Humidity.add(line2_8);

    line2_9.setPosition(141, 173, 557, 58);
    line2_9Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line2_9.setPainter(line2_9Painter);
    line2_9.setStart(0, 30);
    line2_9.setEnd(576, 30);
    line2_9.setLineWidth(1);
    line2_9.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    Humidity.add(line2_9);

    line2_10.setPosition(141, 135, 557, 58);
    line2_10Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line2_10.setPainter(line2_10Painter);
    line2_10.setStart(0, 30);
    line2_10.setEnd(576, 30);
    line2_10.setLineWidth(1);
    line2_10.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    Humidity.add(line2_10);

    line2_11.setPosition(141, 97, 557, 58);
    line2_11Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line2_11.setPainter(line2_11Painter);
    line2_11.setStart(0, 30);
    line2_11.setEnd(576, 30);
    line2_11.setLineWidth(1);
    line2_11.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    Humidity.add(line2_11);

    line2_12.setPosition(141, 60, 557, 58);
    line2_12Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line2_12.setPainter(line2_12Painter);
    line2_12.setStart(0, 30);
    line2_12.setEnd(576, 30);
    line2_12.setLineWidth(1);
    line2_12.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    Humidity.add(line2_12);

    graphInterval2_0.setPosition(61, 39, 74, 25);
    graphInterval2_0.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    graphInterval2_0.setLinespacing(0);
    graphInterval2_0Buffer[0] = 0;
    graphInterval2_0.setWildcard(graphInterval2_0Buffer);
    graphInterval2_0.setTypedText(touchgfx::TypedText(T_SINGLEUSEID37));
    Humidity.add(graphInterval2_0);

    graphInterval2_1.setPosition(61, 416, 74, 25);
    graphInterval2_1.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    graphInterval2_1.setLinespacing(0);
    graphInterval2_1Buffer[0] = 0;
    graphInterval2_1.setWildcard(graphInterval2_1Buffer);
    graphInterval2_1.setTypedText(touchgfx::TypedText(T_SINGLEUSEID47));
    Humidity.add(graphInterval2_1);
    SwipeArea.add(Humidity);

    Pressure.setWidth(800);
    Pressure.setHeight(480);

    PresBox.setPosition(0, 0, 800, 480);
    PresBox.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    Pressure.add(PresBox);

    PresGraph.setScale(100);
    PresGraph.setGraphRangeX(0, 100);
    PresGraph.setPosition(141, 43, 577, 394);
    PresGraph.setGraphAreaMargin(8, 0, 20, 8);
    PresGraph.setGraphAreaPadding(0, 0, 0, 0);
    PresGraph.setGraphRangeY(0, 1);

    PresGraphMajorXAxisGrid.setScale(100);
    PresGraphMajorXAxisGrid.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    PresGraphMajorXAxisGrid.setInterval(10);
    PresGraphMajorXAxisGrid.setLineWidth(1);
    PresGraph.addGraphElement(PresGraphMajorXAxisGrid);

    PresGraphMajorYAxisLabel.setScale(100);
    PresGraphMajorYAxisLabel.setInterval(1);
    PresGraphMajorYAxisLabel.setLabelTypedText(touchgfx::TypedText(T_SINGLEUSEID34));
    PresGraphMajorYAxisLabel.setColor(touchgfx::Color::getColorFromRGB(20, 151, 197));
    PresGraphMajorYAxisLabel.setAlpha(0);
    PresGraph.addLeftElement(PresGraphMajorYAxisLabel);

    PresGraphLine1.setScale(100);
    PresGraphLine1Painter.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    PresGraphLine1.setPainter(PresGraphLine1Painter);
    PresGraphLine1.setLineWidth(2);
    PresGraph.addGraphElement(PresGraphLine1);
    Pressure.add(PresGraph);

    textArea3.setPosition(292, 11, 255, 29);
    textArea3.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textArea3.setLinespacing(0);
    Unicode::snprintf(textArea3Buffer, TEXTAREA3_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID69).getText());
    textArea3.setWildcard(textArea3Buffer);
    textArea3.setTypedText(touchgfx::TypedText(T_SINGLEUSEID68));
    Pressure.add(textArea3);

    line3.setPosition(141, 399, 557, 58);
    line3Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line3.setPainter(line3Painter);
    line3.setStart(0, 30);
    line3.setEnd(576, 30);
    line3.setLineWidth(1);
    line3.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    Pressure.add(line3);

    line3_1.setPosition(141, 23, 582, 61);
    line3_1Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line3_1.setPainter(line3_1Painter);
    line3_1.setStart(0, 28);
    line3_1.setEnd(557, 28);
    line3_1.setLineWidth(1);
    line3_1.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    Pressure.add(line3_1);

    line3_2.setPosition(670, 47, 48, 401);
    line3_2Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line3_2.setPainter(line3_2Painter);
    line3_2.setStart(28, 382);
    line3_2.setEnd(28, 4);
    line3_2.setLineWidth(1);
    line3_2.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    Pressure.add(line3_2);

    line3_3.setPosition(117, 47, 48, 403);
    line3_3Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line3_3.setPainter(line3_3Painter);
    line3_3.setStart(24, 382);
    line3_3.setEnd(24, 4);
    line3_3.setLineWidth(1);
    line3_3.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    Pressure.add(line3_3);

    line3_4.setPosition(141, 361, 557, 58);
    line3_4Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line3_4.setPainter(line3_4Painter);
    line3_4.setStart(0, 30);
    line3_4.setEnd(576, 30);
    line3_4.setLineWidth(1);
    line3_4.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    Pressure.add(line3_4);

    line3_5.setPosition(141, 323, 557, 58);
    line3_5Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line3_5.setPainter(line3_5Painter);
    line3_5.setStart(0, 30);
    line3_5.setEnd(576, 30);
    line3_5.setLineWidth(1);
    line3_5.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    Pressure.add(line3_5);

    line3_6.setPosition(141, 286, 557, 58);
    line3_6Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line3_6.setPainter(line3_6Painter);
    line3_6.setStart(0, 30);
    line3_6.setEnd(576, 30);
    line3_6.setLineWidth(1);
    line3_6.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    Pressure.add(line3_6);

    line3_7.setPosition(141, 248, 557, 58);
    line3_7Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line3_7.setPainter(line3_7Painter);
    line3_7.setStart(0, 30);
    line3_7.setEnd(576, 30);
    line3_7.setLineWidth(1);
    line3_7.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    Pressure.add(line3_7);

    line3_8.setPosition(141, 210, 557, 58);
    line3_8Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line3_8.setPainter(line3_8Painter);
    line3_8.setStart(0, 30);
    line3_8.setEnd(576, 30);
    line3_8.setLineWidth(1);
    line3_8.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    Pressure.add(line3_8);

    line3_9.setPosition(141, 173, 557, 58);
    line3_9Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line3_9.setPainter(line3_9Painter);
    line3_9.setStart(0, 30);
    line3_9.setEnd(576, 30);
    line3_9.setLineWidth(1);
    line3_9.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    Pressure.add(line3_9);

    line3_10.setPosition(141, 135, 557, 58);
    line3_10Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line3_10.setPainter(line3_10Painter);
    line3_10.setStart(0, 30);
    line3_10.setEnd(576, 30);
    line3_10.setLineWidth(1);
    line3_10.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    Pressure.add(line3_10);

    line3_11.setPosition(141, 97, 557, 58);
    line3_11Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line3_11.setPainter(line3_11Painter);
    line3_11.setStart(0, 30);
    line3_11.setEnd(576, 30);
    line3_11.setLineWidth(1);
    line3_11.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    Pressure.add(line3_11);

    line3_12.setPosition(141, 60, 557, 58);
    line3_12Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line3_12.setPainter(line3_12Painter);
    line3_12.setStart(0, 30);
    line3_12.setEnd(576, 30);
    line3_12.setLineWidth(1);
    line3_12.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    Pressure.add(line3_12);

    graphInterval3_0.setPosition(61, 39, 74, 25);
    graphInterval3_0.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    graphInterval3_0.setLinespacing(0);
    graphInterval3_0Buffer[0] = 0;
    graphInterval3_0.setWildcard(graphInterval3_0Buffer);
    graphInterval3_0.setTypedText(touchgfx::TypedText(T_SINGLEUSEID70));
    Pressure.add(graphInterval3_0);

    graphInterval3_1.setPosition(61, 416, 74, 25);
    graphInterval3_1.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    graphInterval3_1.setLinespacing(0);
    graphInterval3_1Buffer[0] = 0;
    graphInterval3_1.setWildcard(graphInterval3_1Buffer);
    graphInterval3_1.setTypedText(touchgfx::TypedText(T_SINGLEUSEID80));
    Pressure.add(graphInterval3_1);
    SwipeArea.add(Pressure);

    IAQ.setWidth(800);
    IAQ.setHeight(480);

    IAQBox.setPosition(0, 0, 800, 480);
    IAQBox.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    IAQ.add(IAQBox);

    IAQGraph.setScale(100);
    IAQGraph.setGraphRangeX(0, 100);
    IAQGraph.setPosition(141, 43, 577, 394);
    IAQGraph.setGraphAreaMargin(8, 0, 20, 8);
    IAQGraph.setGraphAreaPadding(0, 0, 0, 0);
    IAQGraph.setGraphRangeY(0, 1);

    IAQGraphMajorXAxisGrid.setScale(100);
    IAQGraphMajorXAxisGrid.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    IAQGraphMajorXAxisGrid.setInterval(10);
    IAQGraphMajorXAxisGrid.setLineWidth(1);
    IAQGraph.addGraphElement(IAQGraphMajorXAxisGrid);

    IAQGraphMajorYAxisLabel.setScale(100);
    IAQGraphMajorYAxisLabel.setInterval(1);
    IAQGraphMajorYAxisLabel.setLabelTypedText(touchgfx::TypedText(T_SINGLEUSEID34));
    IAQGraphMajorYAxisLabel.setColor(touchgfx::Color::getColorFromRGB(20, 151, 197));
    IAQGraphMajorYAxisLabel.setAlpha(0);
    IAQGraph.addLeftElement(IAQGraphMajorYAxisLabel);

    IAQGraphLine1.setScale(100);
    IAQGraphLine1Painter.setColor(touchgfx::Color::getColorFromRGB(255, 0, 0));
    IAQGraphLine1.setPainter(IAQGraphLine1Painter);
    IAQGraphLine1.setLineWidth(2);
    IAQGraph.addGraphElement(IAQGraphLine1);
    IAQ.add(IAQGraph);

    textArea4.setPosition(292, 9, 342, 29);
    textArea4.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    textArea4.setLinespacing(0);
    Unicode::snprintf(textArea4Buffer, TEXTAREA4_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID82).getText());
    textArea4.setWildcard(textArea4Buffer);
    textArea4.setTypedText(touchgfx::TypedText(T_SINGLEUSEID81));
    IAQ.add(textArea4);

    line4.setPosition(141, 399, 557, 58);
    line4Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line4.setPainter(line4Painter);
    line4.setStart(0, 30);
    line4.setEnd(576, 30);
    line4.setLineWidth(1);
    line4.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    IAQ.add(line4);

    line4_1.setPosition(141, 23, 582, 61);
    line4_1Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line4_1.setPainter(line4_1Painter);
    line4_1.setStart(0, 28);
    line4_1.setEnd(557, 28);
    line4_1.setLineWidth(1);
    line4_1.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    IAQ.add(line4_1);

    line4_2.setPosition(670, 47, 48, 401);
    line4_2Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line4_2.setPainter(line4_2Painter);
    line4_2.setStart(28, 382);
    line4_2.setEnd(28, 4);
    line4_2.setLineWidth(1);
    line4_2.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    IAQ.add(line4_2);

    line4_3.setPosition(117, 47, 48, 403);
    line4_3Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line4_3.setPainter(line4_3Painter);
    line4_3.setStart(24, 382);
    line4_3.setEnd(24, 4);
    line4_3.setLineWidth(1);
    line4_3.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    IAQ.add(line4_3);

    line4_4.setPosition(141, 361, 557, 58);
    line4_4Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line4_4.setPainter(line4_4Painter);
    line4_4.setStart(0, 30);
    line4_4.setEnd(576, 30);
    line4_4.setLineWidth(1);
    line4_4.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    IAQ.add(line4_4);

    line4_5.setPosition(141, 323, 557, 58);
    line4_5Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line4_5.setPainter(line4_5Painter);
    line4_5.setStart(0, 30);
    line4_5.setEnd(576, 30);
    line4_5.setLineWidth(1);
    line4_5.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    IAQ.add(line4_5);

    line4_6.setPosition(141, 286, 557, 58);
    line4_6Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line4_6.setPainter(line4_6Painter);
    line4_6.setStart(0, 30);
    line4_6.setEnd(576, 30);
    line4_6.setLineWidth(1);
    line4_6.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    IAQ.add(line4_6);

    line4_7.setPosition(141, 248, 557, 58);
    line4_7Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line4_7.setPainter(line4_7Painter);
    line4_7.setStart(0, 30);
    line4_7.setEnd(576, 30);
    line4_7.setLineWidth(1);
    line4_7.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    IAQ.add(line4_7);

    line4_8.setPosition(141, 210, 557, 58);
    line4_8Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line4_8.setPainter(line4_8Painter);
    line4_8.setStart(0, 30);
    line4_8.setEnd(576, 30);
    line4_8.setLineWidth(1);
    line4_8.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    IAQ.add(line4_8);

    line4_9.setPosition(141, 173, 557, 58);
    line4_9Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line4_9.setPainter(line4_9Painter);
    line4_9.setStart(0, 30);
    line4_9.setEnd(576, 30);
    line4_9.setLineWidth(1);
    line4_9.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    IAQ.add(line4_9);

    line4_10.setPosition(141, 135, 557, 58);
    line4_10Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line4_10.setPainter(line4_10Painter);
    line4_10.setStart(0, 30);
    line4_10.setEnd(576, 30);
    line4_10.setLineWidth(1);
    line4_10.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    IAQ.add(line4_10);

    line4_11.setPosition(141, 97, 557, 58);
    line4_11Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line4_11.setPainter(line4_11Painter);
    line4_11.setStart(0, 30);
    line4_11.setEnd(576, 30);
    line4_11.setLineWidth(1);
    line4_11.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    IAQ.add(line4_11);

    line4_12.setPosition(141, 60, 557, 58);
    line4_12Painter.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    line4_12.setPainter(line4_12Painter);
    line4_12.setStart(0, 30);
    line4_12.setEnd(576, 30);
    line4_12.setLineWidth(1);
    line4_12.setLineEndingStyle(touchgfx::Line::BUTT_CAP_ENDING);
    IAQ.add(line4_12);

    graphInterval4_0.setPosition(61, 39, 74, 25);
    graphInterval4_0.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    graphInterval4_0.setLinespacing(0);
    graphInterval4_0Buffer[0] = 0;
    graphInterval4_0.setWildcard(graphInterval4_0Buffer);
    graphInterval4_0.setTypedText(touchgfx::TypedText(T_SINGLEUSEID83));
    IAQ.add(graphInterval4_0);

    graphInterval4_1.setPosition(61, 416, 74, 25);
    graphInterval4_1.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    graphInterval4_1.setLinespacing(0);
    graphInterval4_1Buffer[0] = 0;
    graphInterval4_1.setWildcard(graphInterval4_1Buffer);
    graphInterval4_1.setTypedText(touchgfx::TypedText(T_SINGLEUSEID93));
    IAQ.add(graphInterval4_1);
    SwipeArea.add(IAQ);
    SwipeArea.setSelectedPage(0);

    button1.setXY(7, 5);
    button1.setBitmaps(touchgfx::Bitmap(BITMAP_BACK_LIGHT_ID), touchgfx::Bitmap(BITMAP_BACK_DARK_ID));
    button1.setAction(buttonCallback);

    add(__background);
    add(SwipeArea);
    add(button1);
}

void GraphsViewBase::setupScreen()
{

}

void GraphsViewBase::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &button1)
    {
        //Interaction1
        //When button1 clicked change screen to Main
        //Go to Main with screen transition towards West
        application().gotoMainScreenCoverTransitionWest();
    }
}
