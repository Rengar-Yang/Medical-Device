#ifndef NETSELECTORELEMENT_HPP
#define NETSELECTORELEMENT_HPP

#include <gui_generated/containers/NetSelectorElementBase.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

class NetSelectorElement : public NetSelectorElementBase
{
public:
    NetSelectorElement();
    virtual ~NetSelectorElement() {}

    virtual void initialize();

    void setupElement(BitmapId bmpID, TEXTS text);
protected:
};

#endif // NETSELECTORELEMENT_HPP
