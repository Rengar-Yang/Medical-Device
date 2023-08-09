#include <gui/containers/NetSelectorElementCenter.hpp>

NetSelectorElementCenter::NetSelectorElementCenter()
{

}

void NetSelectorElementCenter::initialize()
{
    NetSelectorElementCenterBase::initialize();
}

void NetSelectorElementCenter::setupElement(BitmapId bmpID, TEXTS text)
{
	FunctionName.setTypedText(TypedText(text));
	FunctionName.setBaselineY(26);
	FunctionName.invalidate();

	FunctionLogo.setBitmap(Bitmap(bmpID));
	FunctionLogo.invalidate();
}