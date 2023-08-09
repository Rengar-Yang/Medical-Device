#ifndef NETSELECTORELEMENTCENTER_HPP
#define NETSELECTORELEMENTCENTER_HPP

#include <gui_generated/containers/NetSelectorElementCenterBase.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

class NetSelectorElementCenter : public NetSelectorElementCenterBase
{
public:
    NetSelectorElementCenter();
    virtual ~NetSelectorElementCenter() {}

    virtual void initialize();

    void setupElement(BitmapId bmpID, TEXTS text);
protected:
};

#endif // NETSELECTORELEMENTCENTER_HPP
