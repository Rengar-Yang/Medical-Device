#include <gui/containers/NetSelectorElement.hpp>

NetSelectorElement::NetSelectorElement()
{

}

void NetSelectorElement::initialize()
{
    NetSelectorElementBase::initialize();
}

void NetSelectorElement::setupElement(BitmapId bmpID, TEXTS text)
{
	FunctionName.setTypedText(TypedText(text));
	FunctionName.setBaselineY(26);
	FunctionName.invalidate();

	FunctionLogo.setBitmap(Bitmap(bmpID));
	FunctionLogo.invalidate();
}