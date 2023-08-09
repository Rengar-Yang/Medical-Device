#ifndef IMAGEPRESENTER_HPP
#define IMAGEPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class ImageView;

class ImagePresenter : public touchgfx::Presenter, public ModelListener
{
public:
    ImagePresenter(ImageView& v);

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

    virtual ~ImagePresenter() {};

private:
    ImagePresenter();

    ImageView& view;
};


#endif // IMAGEPRESENTER_HPP
