/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef IMAGEVIEWBASE_HPP
#define IMAGEVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/image_screen/ImagePresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/containers/buttons/Buttons.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/EasingEquations.hpp>
#include <touchgfx/mixins/MoveAnimator.hpp>

class ImageViewBase : public touchgfx::View<ImagePresenter>
{
public:
    ImageViewBase();
    virtual ~ImageViewBase() {}
    virtual void setupScreen();

    /*
     * Virtual Action Handlers
     */
    virtual void rightButtonClicked()
    {
        // Override and implement this function in Image
    }

    virtual void leftButtonClicked()
    {
        // Override and implement this function in Image
    }

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::Box background;
    touchgfx::MoveAnimator< touchgfx::Image > image;
    touchgfx::BoxWithBorderButtonStyle< touchgfx::ClickButtonTrigger > flexButton1;
    touchgfx::Button menuLeftButton;
    touchgfx::Button menuRightButton;
    touchgfx::Button button1;

private:

    /*
     * Callback Declarations
     */
    touchgfx::Callback<ImageViewBase, const touchgfx::AbstractButton&> buttonCallback;
    touchgfx::Callback<ImageViewBase, const touchgfx::AbstractButtonContainer&> flexButtonCallback;

    /*
     * Callback Handler Declarations
     */
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);
    void flexButtonCallbackHandler(const touchgfx::AbstractButtonContainer& src);

};

#endif // IMAGEVIEWBASE_HPP
