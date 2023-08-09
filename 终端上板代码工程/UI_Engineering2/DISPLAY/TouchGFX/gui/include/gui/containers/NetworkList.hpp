#ifndef NETWORKLIST_HPP
#define NETWORKLIST_HPP

#include <gui_generated/containers/NetworkListBase.hpp>
#include <BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>
class NetworkList : public NetworkListBase
{
public:
    NetworkList();
    virtual ~NetworkList() {}

    virtual void initialize();
    void setupElement(BitmapId bmpID, TEXTS text);
protected:
};

#endif // NETWORKLIST_HPP
