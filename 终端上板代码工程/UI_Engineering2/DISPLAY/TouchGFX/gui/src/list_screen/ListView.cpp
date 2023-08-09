#include <gui/list_screen/ListView.hpp>
#include <texts/TextKeysAndLanguages.hpp>

ListView::ListView() :
	scrollWheelSelectedItemCallback(this, &ListView::scrollWheelSelectedItemHandler)
{

}

void ListView::setupScreen()
{
    ListViewBase::setupScreen();
	HAL::getInstance()->setFrameRateCompensation(true);

	languageSelectorWheel.setAnimationEndedCallback(scrollWheelSelectedItemCallback);

	// Initialize the languageSelectorWheel
	switch (Texts::getLanguage())
	{
	case DK:
		languageSelectorWheel.animateToItem(0);
		break;
	case FR:
		languageSelectorWheel.animateToItem(1);
		break;
	case KR:
		languageSelectorWheel.animateToItem(2);
		break;
	case CN:
		languageSelectorWheel.animateToItem(3);
		break;
	case GB:
		languageSelectorWheel.animateToItem(4);
		break;
	case JP:
		languageSelectorWheel.animateToItem(5);
		break;
	case TN:
		languageSelectorWheel.animateToItem(6);
		break;
	default:
		break;
	}
}

void ListView::tearDownScreen()
{
    ListViewBase::tearDownScreen();
	HAL::getInstance()->setFrameRateCompensation(false);
}

void ListView::handleTickEvent()
{
	handleKeyEvent(presenter->GetButton());//°´¼ü¼ì²â
}

void ListView::handleKeyEvent(uint8_t key)
{
	if (languageSelectorWheel.isAnimating())
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
		languageSelectorWheel.animateToItem(languageSelectorWheel.getSelectedItem() + 1);
	}
	else if (key == 3)
	{
		// Down
		languageSelectorWheel.animateToItem(languageSelectorWheel.getSelectedItem() - 1);
	}
	else if (key == 2)
	{
		// Select
		application().gotoScreen1ScreenNoTransition();
	}
}

void ListView::languageSelectorWheelUpdateItem(languageSelectorElement& item, int16_t itemIndex)
{
	switch (itemIndex)
	{
	case 0:
		item.setupElement(BITMAP_DENMARK_FLAG_SMALL_ID, T_LANGUAGE0);
		break;
	case 1:
		item.setupElement(BITMAP_FRANCE_FLAG_SMALL_ID, T_LANGUAGE2);
		break;
	case 2:
		item.setupElement(BITMAP_SOUTH_KOREA_FLAG_SMALL_ID, T_LANGUAGE3);
		break;
	case 3:
		item.setupElement(BITMAP_CHINA_FLAG_SMALL_ID, T_LANGUAGE4);
		break;
	case 4:
		item.setupElement(BITMAP_UNITED_KINGDOM_FLAG_SMALL_ID, T_LANGUAGE5);
		break;
	case 5:
		item.setupElement(BITMAP_JAPAN_FLAG_SMALL_ID, T_LANGUAGE6);
		break;
	case 6:
		item.setupElement(BITMAP_TUNISIA_FLAG_SMALL_ID, T_LANGUAGE7);
		break;
	default:
		break;
	}
}

void ListView::languageSelectorWheelUpdateCenterItem(languageSelectorElementCenter& item, int16_t itemIndex)
{
	switch (itemIndex)
	{
	case 0:
		item.setupElement(BITMAP_DENMARK_FLAG_SMALL_ID, T_LANGUAGE0);
		break;
	case 1:
		item.setupElement(BITMAP_FRANCE_FLAG_SMALL_ID, T_LANGUAGE2);
		break;
	case 2:
		item.setupElement(BITMAP_SOUTH_KOREA_FLAG_SMALL_ID, T_LANGUAGE3);
		break;
	case 3:
		item.setupElement(BITMAP_CHINA_FLAG_SMALL_ID, T_LANGUAGE4);
		break;
	case 4:
		item.setupElement(BITMAP_UNITED_KINGDOM_FLAG_SMALL_ID, T_LANGUAGE5);
		break;
	case 5:
		item.setupElement(BITMAP_JAPAN_FLAG_SMALL_ID, T_LANGUAGE6);
		break;
	case 6:
		item.setupElement(BITMAP_TUNISIA_FLAG_SMALL_ID, T_LANGUAGE7);
		break;
	default:
		break;
	}
}

void ListView::scrollWheelSelectedItemHandler()
{
	switch (languageSelectorWheel.getSelectedItem())
	{
	case 0:
		Texts::setLanguage(DK);
		break;
	case 1:
		Texts::setLanguage(FR);
		break;
	case 2:
		Texts::setLanguage(KR);
		break;
	case 3:
		Texts::setLanguage(CN);
		break;
	case 4:
		Texts::setLanguage(GB);
		break;
	case 5:
		Texts::setLanguage(JP);
		break;
	case 6:
		Texts::setLanguage(TN);
		break;
	default:
		break;
	}
	
	headline.invalidate();
}
