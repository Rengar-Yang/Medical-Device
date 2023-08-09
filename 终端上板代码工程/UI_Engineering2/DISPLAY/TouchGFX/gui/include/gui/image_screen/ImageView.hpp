#ifndef IMAGEVIEW_HPP
#define IMAGEVIEW_HPP

#include <gui_generated/image_screen/ImageViewBase.hpp>
#include <gui/image_screen/ImagePresenter.hpp>

class ImageView : public ImageViewBase
{
public:
    ImageView();
    virtual ~ImageView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

	void handleTickEvent();

	void handleKeyEvent(uint8_t key);

    virtual void rightButtonClicked();

	virtual void leftButtonClicked();
protected:
	static const int NUMBER_OF_IMAGES = 3;

	uint32_t tickCounter;

	uint8_t selectedImageIndex;   // add to resolve problem.

	void updateSelectedImage(uint8_t newImageIndex);
};

#endif // IMAGEVIEW_HPP
