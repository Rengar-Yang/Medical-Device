#ifndef NETWORKMENUPRESENTER_HPP
#define NETWORKMENUPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class NetworkMenuView;

class NetworkMenuPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    NetworkMenuPresenter(NetworkMenuView& v);

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

    virtual ~NetworkMenuPresenter() {};

    virtual int GetButton();

    virtual void NetDebug();
    virtual void CancelNetDebug();
    virtual void NetTime();
    virtual void CancelNetTime();
    virtual void ConnectWIFI();
    virtual void CancelConnectWIFI();

private:
    NetworkMenuPresenter();

    NetworkMenuView& view;
};

#endif // NETWORKMENUPRESENTER_HPP
