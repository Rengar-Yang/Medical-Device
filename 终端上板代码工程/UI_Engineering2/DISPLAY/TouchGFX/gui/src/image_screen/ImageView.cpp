#include <gui/image_screen/ImageView.hpp>
#include <BitmapDatabase.hpp>

ImageView::ImageView():selectedImageIndex(0)
{
	tickCounter = 0;
}

void ImageView::setupScreen()
{
    ImageViewBase::setupScreen();

	//uint16_t delay = 150;
	//uint16_t animationDuration = 30;
}

void ImageView::tearDownScreen()
{
    ImageViewBase::tearDownScreen();
}

void ImageView::handleTickEvent()
{
	tickCounter++;
}

void ImageView::handleKeyEvent(uint8_t key)
{
	if (key == '6')
	{
		// Right
		updateSelectedImage((selectedImageIndex == NUMBER_OF_IMAGES - 1) ? 0 : selectedImageIndex + 1);
	}
	else if (key == '4')
	{
		// Left
		updateSelectedImage((selectedImageIndex == 0) ? NUMBER_OF_IMAGES - 1 : selectedImageIndex - 1);
	}
	else if (key == '8')
	{
		// Up
	}
	else if (key == '2')
	{
		// Down
	}
	else if (key == '5')
	{
		// Select
		application().gotoScreen1ScreenNoTransition();
	}
}

void ImageView::rightButtonClicked()
{
	updateSelectedImage((selectedImageIndex == NUMBER_OF_IMAGES - 1) ? 0 : selectedImageIndex + 1);
}

void ImageView::leftButtonClicked()
{
	updateSelectedImage((selectedImageIndex == 0) ? NUMBER_OF_IMAGES - 1 : selectedImageIndex - 1);
}

void ImageView::updateSelectedImage(uint8_t newImageIndex)
{
	selectedImageIndex = newImageIndex;

	switch (selectedImageIndex)
	{
	case 0:
		image.setBitmap(Bitmap(BITMAP_IMAGE0_ID));
		break;
	case 1:
		image.setBitmap(Bitmap(BITMAP_IMAGE01_ID));
		break;
	case 2:
		image.setBitmap(Bitmap(BITMAP_IMAGE02_ID));
		break;
	default:
		break;
	}
	image.invalidate();
}
