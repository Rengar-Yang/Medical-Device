#include <gui/containers/languageSelectorElementCenter.hpp>

languageSelectorElementCenter::languageSelectorElementCenter()
{

}

void languageSelectorElementCenter::initialize()
{
    languageSelectorElementCenterBase::initialize();
}

void languageSelectorElementCenter::setupElement(BitmapId bmpID, TEXTS text)
{
	languageText.setTypedText(TypedText(text));
	languageText.setBaselineY(26);
	languageText.invalidate();

	flagImage.setBitmap(Bitmap(bmpID));
	flagImage.invalidate();
}