#include <gui/containers/languageSelectorElement.hpp>

languageSelectorElement::languageSelectorElement()
{

}

void languageSelectorElement::initialize()
{
    languageSelectorElementBase::initialize();
}

void languageSelectorElement::setupElement(BitmapId bmpID, TEXTS text)
{
	languageText.setTypedText(TypedText(text));
	languageText.setBaselineY(26);
	languageText.invalidate();

	flagImage.setBitmap(Bitmap(bmpID));
	flagImage.invalidate();
}

