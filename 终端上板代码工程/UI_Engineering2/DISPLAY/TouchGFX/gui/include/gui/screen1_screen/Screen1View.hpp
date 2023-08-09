#ifndef SCREEN1_VIEW_HPP
#define SCREEN1_VIEW_HPP

#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>

class Screen1View : public Screen1ViewBase
{
public:
	enum AnimationState
	{
		ANIMATION_READY = 0,
		ANIMATION_STEP_0,
		ANIMATION_STEP_1,
		ANIMATION_STEP_2,
		ANIMATION_STEP_3,
		ANIMATION_STEP_4,
		ANIMATION_STEP_5,
		ANIMATION_DONE
	};

	static const int ANIMATION_STEP0_DURATION = 20;
	static const int ANIMATION_STEP1_DURATION = 20;
	static const int ANIMATION_STEP2_DURATION = 20;  // all 40
	static const int ANIMATION_STEP3_DURATION = 20;
	static const int ANIMATION_STEP4_DURATION = 20;
	static const int ANIMATION_STEP5_DURATION = 20;

	enum MenuAnimationState
	{
		MENU_ANIMATION_READY = 0,
		MENU_ANIMATION_STEP_0,
		MENU_ANIMATION_STEP_1,
		MENU_ANIMATION_DONE
	};

	static const int MENU_ANIMATION_MOVE_X_SIZE = 40;
	static const int MENU_ANIMATION_STEP0_DURATION = 20;//30
	static const int MENU_ANIMATION_STEP1_DURATION = 20;//30

	static const int NUMBER_OF_MENU_ITEMS = 4;//APPÊýÁ¿

	Screen1View();
    virtual ~Screen1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

	void handleTickEvent();

	void handleKeyEvent(uint8_t key);
	virtual void leftButtonClicked();
	virtual void rightButtonClicked();

protected:

	uint32_t animationTickCounter;
	AnimationState animationState;

	uint32_t menuAnimationTickCounter;
	uint32_t TitleAnimationTickCounter;
	bool menuAnimationDirectionLeft;
	MenuAnimationState menuAnimationState;

	int16_t subtitleStartPositionX;
	int16_t subtitleStartPositionY;
	int16_t logoXStartPositionX;
	int16_t logoXStartPositionY;

	uint8_t selectedMenuItem;

	void menuSelectLeft();
	void menuSelectRight();

	Callback<Screen1View,const touchgfx::Image &,const touchgfx::ClickEvent &> imgClickCallback;
	void imgClickHandler(const touchgfx::Image & img,const touchgfx::ClickEvent & event);

private:
	void setSelectedMenuItem();
	int itemIndex;
};

#endif // SCREEN1_VIEW_HPP
