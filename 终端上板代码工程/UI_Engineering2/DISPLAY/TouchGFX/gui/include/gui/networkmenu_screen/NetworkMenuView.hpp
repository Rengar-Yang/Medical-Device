#ifndef NETWORKMENUVIEW_HPP
#define NETWORKMENUVIEW_HPP

#include <gui_generated/networkmenu_screen/NetworkMenuViewBase.hpp>
#include <gui/networkmenu_screen/NetworkMenuPresenter.hpp>

class NetworkMenuView : public NetworkMenuViewBase
{
public:
    NetworkMenuView();
    virtual ~NetworkMenuView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    void handleKeyEvent(uint8_t key);
    void handleTickEvent();

    virtual void FunctionListUpdateItem(NetworkList& item, int16_t itemIndex);

    int FunctionIndex;

protected:

    Callback<NetworkMenuView, int16_t> scrollListClickedCallback;
    void scrollListClickHandler(int16_t itemSelected);
   
};

#endif // NETWORKMENUVIEW_HPP
