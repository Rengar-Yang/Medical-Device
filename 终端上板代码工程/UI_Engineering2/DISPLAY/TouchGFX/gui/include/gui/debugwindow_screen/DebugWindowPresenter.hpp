#ifndef DEBUGWINDOWPRESENTER_HPP
#define DEBUGWINDOWPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class DebugWindowView;

class DebugWindowPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    DebugWindowPresenter(DebugWindowView& v);

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

    virtual ~DebugWindowPresenter() {};

    virtual void NetTime();
    virtual int GetButton();
    virtual void CancelNetTime();
    virtual void NetDebug();
    virtual void CancelNetDebug();
    virtual void PostData();
    virtual void CancelPostData();

    virtual int GetHumidity();
    virtual int GetTemperature();
    virtual int GetHeartRate();
    virtual int GetSPO2();
    virtual int GetDebugResult();
private:
    DebugWindowPresenter();

    DebugWindowView& view;
};

#endif // DEBUGWINDOWPRESENTER_HPP
