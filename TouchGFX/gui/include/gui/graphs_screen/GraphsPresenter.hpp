#ifndef GRAPHSPRESENTER_HPP
#define GRAPHSPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class GraphsView;

class GraphsPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    GraphsPresenter(GraphsView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~GraphsPresenter() {};

private:
    GraphsPresenter();

    GraphsView& view;
};

#endif // GRAPHSPRESENTER_HPP
