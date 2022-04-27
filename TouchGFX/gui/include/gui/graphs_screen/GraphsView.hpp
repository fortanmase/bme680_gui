#ifndef GRAPHSVIEW_HPP
#define GRAPHSVIEW_HPP

#include <gui_generated/graphs_screen/GraphsViewBase.hpp>
#include <gui/graphs_screen/GraphsPresenter.hpp>

class GraphsView : public GraphsViewBase
{
public:
/*  generated declarations  */
    GraphsView();
    virtual ~GraphsView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    void handleTickEvent();
protected:
/*  user declarations  */
};

#endif // GRAPHSVIEW_HPP
