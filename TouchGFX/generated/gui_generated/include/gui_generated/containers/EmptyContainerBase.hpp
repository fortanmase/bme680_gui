/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef EMPTYCONTAINERBASE_HPP
#define EMPTYCONTAINERBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <touchgfx/containers/Container.hpp>

class EmptyContainerBase : public touchgfx::Container
{
public:
    EmptyContainerBase();
    virtual ~EmptyContainerBase() {}
    virtual void initialize();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

private:

};

#endif // EMPTYCONTAINERBASE_HPP
