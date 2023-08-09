#include <gui/networkmenu_screen/NetworkMenuView.hpp>
#include <texts/TextKeysAndLanguages.hpp>

NetworkMenuView::NetworkMenuView():
	scrollListClickedCallback(this, &NetworkMenuView::scrollListClickHandler)
{
	FunctionList.setItemSelectedCallback(scrollListClickedCallback);
}

void NetworkMenuView::setupScreen()
{
    NetworkMenuViewBase::setupScreen();
    HAL::getInstance()->setFrameRateCompensation(true);
	touchgfx::HAL::getInstance()->setDragThreshold(5);

	FunctionIndex = 0;
	FunctionList.animateToItem(1);
}

void NetworkMenuView::tearDownScreen()
{
    NetworkMenuViewBase::tearDownScreen();
    HAL::getInstance()->setFrameRateCompensation(false);
	touchgfx::HAL::getInstance()->setDragThreshold(0);
	presenter->CancelNetTime();
	presenter->CancelConnectWIFI();
}

void NetworkMenuView::handleKeyEvent(uint8_t key)
{
	if (FunctionList.isAnimating())
	{
		return;
	}
	if (key == '6')
	{
		// Right
	}
	else if (key == '4')
	{
		// Left
	}
	else if (key == 1)
	{
		// Up
		FunctionIndex+=1;
		if (FunctionIndex > 2) FunctionIndex = 0;
		if (FunctionIndex < 0) FunctionIndex = 2;
		FunctionList.animateToItem(FunctionIndex);
	}
	else if (key == 3)
	{
		// Down
		FunctionIndex-=1;
		if (FunctionIndex > 2) FunctionIndex = 0;
		if (FunctionIndex < 0) FunctionIndex = 2;
		FunctionList.animateToItem(FunctionIndex);
	}
	else if (key == 2)
	{
		// Select
		application().gotoScreen1ScreenNoTransition();
	}
}

void NetworkMenuView::FunctionListUpdateItem(NetworkList& item, int16_t itemIndex)
{
	switch (itemIndex)
	{
	case 0:
		item.setupElement(BITMAP_WIFIBIG_ID, T_WIFI);
		break;
	case 1:
		item.setupElement(BITMAP_UPDATEBIG_ID, T_UPDATE);
		break;
	case 2:
		item.setupElement(BITMAP_NETWORKTIMEBIG_ID, T_NETWORKTIME);
		break;
	default:
		break;
	}
}


void NetworkMenuView::scrollListClickHandler(int16_t itemSelected)
{
	switch (itemSelected)
	{
	case 0:
		presenter->ConnectWIFI();
		break;
	case 1:
		application().gotoDebugWindowScreenNoTransition();
		break;
	case 2:
		notification1.setVisible(1);
		notification1.invalidate();
		presenter->NetTime();
		break;
	default:
		break;
	}

	headline.invalidate();
}

void NetworkMenuView::handleTickEvent()
{
	handleKeyEvent(presenter->GetButton());//°´¼ü¼ì²â
}