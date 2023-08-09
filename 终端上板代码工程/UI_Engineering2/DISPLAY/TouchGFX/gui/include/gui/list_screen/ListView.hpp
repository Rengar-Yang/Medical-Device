#ifndef LISTVIEW_HPP
#define LISTVIEW_HPP

#include <gui_generated/list_screen/ListViewBase.hpp>
#include <gui/list_screen/ListPresenter.hpp>

class ListView : public ListViewBase
{
public:
    ListView();
    virtual ~ListView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

	void handleTickEvent();

	void handleKeyEvent(uint8_t key);

	virtual void languageSelectorWheelUpdateItem(languageSelectorElement& item, int16_t itemIndex);
	virtual void languageSelectorWheelUpdateCenterItem(languageSelectorElementCenter& item, int16_t itemIndex);
protected:

	Callback<ListView> scrollWheelSelectedItemCallback;
	void scrollWheelSelectedItemHandler();
};

#endif // LISTVIEW_HPP
