/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/containers/MenuElementBase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Color.hpp>

MenuElementBase::MenuElementBase()
{
    setWidth(390);
    setHeight(70);
    scrollTextArea.setXY(93, 23);
    scrollTextArea.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    scrollTextArea.setLinespacing(0);
    Unicode::snprintf(scrollTextAreaBuffer, SCROLLTEXTAREA_SIZE, "%s", touchgfx::TypedText(T_SINGLEUSEID67).getText());
    scrollTextArea.setWildcard(scrollTextAreaBuffer);
    scrollTextArea.resizeToCurrentText();
    scrollTextArea.setTypedText(touchgfx::TypedText(T_SINGLEUSEID66));

    add(scrollTextArea);
}

void MenuElementBase::initialize()
{

}
