#ifndef EMPTYCONTAINER_HPP
#define EMPTYCONTAINER_HPP

#include <gui_generated/containers/EmptyContainerBase.hpp>

class EmptyContainer : public EmptyContainerBase
{
public:
    EmptyContainer();
    virtual ~EmptyContainer() {}

    virtual void initialize();
protected:
};

#endif // EMPTYCONTAINER_HPP
