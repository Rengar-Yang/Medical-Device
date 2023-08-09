#include <gui/containers/NetworkList.hpp>

NetworkList::NetworkList()
{

}

void NetworkList::initialize()
{
    NetworkListBase::initialize();
}

void NetworkList::setupElement(BitmapId bmpID, TEXTS text)
{
	FunctionName.setTypedText(TypedText(text));
	FunctionName.setBaselineY(26);
	FunctionName.invalidate();

	FunctionLogo.setBitmap(Bitmap(bmpID));
	FunctionLogo.invalidate();
}