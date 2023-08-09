#include <gui/screen1_screen/Screen1View.hpp>
#include <BitmapDatabase.hpp>
#include <touchgfx/EasingEquations.hpp>
#include <texts/TextKeysAndLanguages.hpp>

Screen1View::Screen1View():imgClickCallback(this,&Screen1View::imgClickHandler)
{
	animationState = ANIMATION_READY;
	menuAnimationState = MENU_ANIMATION_READY;

	animationTickCounter = 0;
	menuAnimationTickCounter = 0;
	selectedMenuItem = 0;
	itemIndex = 0;
	//// Start animation
	animationState = ANIMATION_STEP_0;
}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
		menuIcon0.setClickAction(imgClickCallback);
		animationState = ANIMATION_STEP_0;
	/*	presenter->CancleHealthDiagnose();
		presenter->CancelPostData();
		presenter->CancelNetDebug();*/
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

uint8_t t_alpha = 0;

void Screen1View::handleTickEvent()
{
	if (presenter->IfStarted() == 1)//返回主界面动画
	{
		logoText.setVisible(0);
		if (animationState > ANIMATION_READY)
		{
			animationTickCounter++;
			if (animationState == ANIMATION_STEP_0)
			{
				if (animationTickCounter < ANIMATION_STEP4_DURATION)
				{
					int16_t deltaXforLogoX = EasingEquations::cubicEaseInOut(animationTickCounter, 0, ((280 - logoX.getWidth()) / 2), ANIMATION_STEP0_DURATION);
					int16_t deltaYforLogoY = EasingEquations::cubicEaseInOut(animationTickCounter, 0, 180 - logoX.getY(), ANIMATION_STEP3_DURATION);
					logoX.moveTo(((340 - logoX.getWidth()) / 2) + deltaXforLogoX, logoX.getY() + deltaYforLogoY);

					int16_t deltaX = EasingEquations::cubicEaseInOut(animationTickCounter, 0, seperatorLine.getWidth(), ANIMATION_STEP4_DURATION);
					seperatorLine.moveTo(-seperatorLine.getWidth() + deltaX, seperatorLine.getY());

					uint8_t deltaAlpha = (uint8_t)EasingEquations::cubicEaseInOut(animationTickCounter, 0, 255, 30);
					subtitle.setAlpha(deltaAlpha);
					subtitle.invalidate();
					subtitleStartPositionX = subtitle.getX();
					subtitleStartPositionY = subtitle.getY();
					int16_t deltaXforSubtitleX = EasingEquations::cubicEaseInOut(animationTickCounter, 0, 22 - subtitleStartPositionX, ANIMATION_STEP3_DURATION);
					int16_t deltaYforSubtitleY = EasingEquations::cubicEaseInOut(animationTickCounter, 0, 202 - subtitleStartPositionY, ANIMATION_STEP3_DURATION);
					subtitle.moveTo(subtitleStartPositionX + deltaXforSubtitleX - 10, subtitleStartPositionY + deltaYforSubtitleY);
					subtitle.invalidate();
				}
				else
				{
					animationState = ANIMATION_STEP_1;
					animationTickCounter = 0;
				}
			}
			else if (animationState == ANIMATION_STEP_1)
			{
				digitalClock1.setVisible(1);//开启显示时间
				if (animationTickCounter < ANIMATION_STEP5_DURATION)
				{
					uint8_t deltaAlpha = (uint8_t)EasingEquations::cubicEaseInOut(animationTickCounter, 0, 255, ANIMATION_STEP5_DURATION);
					menuIcon0.setAlpha(deltaAlpha);
					menuLeftButton.setAlpha(deltaAlpha);
					menuRightButton.setAlpha(deltaAlpha);
					headline.setAlpha(deltaAlpha);
					digitalClock1.setAlpha(deltaAlpha);

					menuIcon0.invalidate();
					menuLeftButton.invalidate();
					menuRightButton.invalidate();
					headline.invalidate();
					digitalClock1.invalidate();
				}
				else
				{
					animationState = ANIMATION_READY;
					animationTickCounter = 0;
				}
			}
			//	if (animationState == ANIMATION_STEP_0)
			//	{

			//		if (animationTickCounter < ANIMATION_STEP0_DURATION)
			//		{
			//			int16_t deltaXforLogoX = EasingEquations::cubicEaseInOut(animationTickCounter, 0, ((280 - logoX.getWidth()) / 2), ANIMATION_STEP0_DURATION);
			//			logoX.moveTo(((320 - logoX.getWidth()) / 2) + deltaXforLogoX, logoX.getY());

			//			int16_t deltaXforLogoText = EasingEquations::cubicEaseInOut(animationTickCounter, 0, (280 / 2), ANIMATION_STEP0_DURATION);

			//			logoTextContainer.moveTo(320 / 2 - deltaXforLogoText, logoTextContainer.getY());

			//			int16_t newWidth = logoX.getX() - logoTextContainer.getX();
			//			logoTextContainer.setWidth((newWidth > 0) ? newWidth : 0);
			//			logoTextContainer.invalidate();
			//		}
			//		else
			//		{
			//			animationState = ANIMATION_STEP_1;
			//			animationTickCounter = 0;
			//		}
			//	}
			//	else if (animationState == ANIMATION_STEP_1)
			//	{
			//		if (animationTickCounter < ANIMATION_STEP1_DURATION)
			//		{
			//			uint8_t deltaAlpha = (uint8_t)EasingEquations::cubicEaseInOut(animationTickCounter, 0, 255, ANIMATION_STEP1_DURATION);
			//			subtitle.setAlpha(deltaAlpha);
			//			subtitle.invalidate();
			//		}
			//		else
			//		{
			//			animationState = ANIMATION_STEP_2;
			//			animationTickCounter = 0;
			//		}
			//	}
			//	else if (animationState == ANIMATION_STEP_2)
			//	{
			//		if (animationTickCounter < ANIMATION_STEP2_DURATION)
			//		{
			//			// Pause
			//		}
			//		else
			//		{
			//			animationState = ANIMATION_STEP_3;
			//			animationTickCounter = 0;

			//			subtitleStartPositionX = -1; // Reset
			//		}
			//	}
			//	else if (animationState == ANIMATION_STEP_3)
			//	{
			//		if (subtitleStartPositionX == -1)
			//		{
			//			subtitleStartPositionX = subtitle.getX();
			//			subtitleStartPositionY = subtitle.getY();
			//			logoXStartPositionX = logoX.getX();
			//			logoXStartPositionY = logoX.getY();
			//		}

			//		if (animationTickCounter < ANIMATION_STEP3_DURATION)
			//		{
			//			int16_t deltaXforLogoX = EasingEquations::cubicEaseInOut(animationTickCounter, 0, 266 - logoXStartPositionX, ANIMATION_STEP3_DURATION);
			//			int16_t deltaYforLogoY = EasingEquations::cubicEaseInOut(animationTickCounter, 0, 180 - logoXStartPositionY, ANIMATION_STEP3_DURATION);
			//			//       lcd_set_window(logoXStartPositionX + deltaXforLogoX, logoXStartPositionY + deltaYforLogoY, logoX.getWidth() , logoX.getHeight());
			//			logoX.moveTo(logoXStartPositionX + deltaXforLogoX, logoXStartPositionY + deltaYforLogoY);
			//			//       animationTickCounter = 40;
			//			//      logoX.invalidate();
			//			//       logoX.setAlpha(t_alpha);
			//			//       logoX.invalidate();

			//			int16_t deltaXforSubtitleX = EasingEquations::cubicEaseInOut(animationTickCounter, 0, 22 - subtitleStartPositionX, ANIMATION_STEP3_DURATION);
			//			int16_t deltaYforSubtitleY = EasingEquations::cubicEaseInOut(animationTickCounter, 0, 202 - subtitleStartPositionY, ANIMATION_STEP3_DURATION);
			//			subtitle.moveTo(subtitleStartPositionX + deltaXforSubtitleX - 10, subtitleStartPositionY + deltaYforSubtitleY);
			//		}
			//		else
			//		{
			//			animationState = ANIMATION_STEP_4;
			//			animationTickCounter = 0;
			//		}
			//	}
			//	else if (animationState == ANIMATION_STEP_4)
			//	{
			//		if (animationTickCounter < ANIMATION_STEP4_DURATION)
			//		{
			//			int16_t deltaX = EasingEquations::cubicEaseInOut(animationTickCounter, 0, seperatorLine.getWidth(), ANIMATION_STEP4_DURATION);
			//			seperatorLine.moveTo(-seperatorLine.getWidth() + deltaX, seperatorLine.getY());

			//			int16_t deltaYText = EasingEquations::cubicEaseInOut(animationTickCounter, 0, logoTextContainer.getHeight(), ANIMATION_STEP4_DURATION);
			//			logoText.moveTo(logoText.getX(), deltaYText);
			//		}
			//		else
			//		{
			//			animationState = ANIMATION_STEP_5;
			//			animationTickCounter = 0;
			//		}
			//	}
			//	else if (animationState == ANIMATION_STEP_5)
			//	{
			//		if (animationTickCounter < ANIMATION_STEP5_DURATION)
			//		{
			//			uint8_t deltaAlpha = (uint8_t)EasingEquations::cubicEaseInOut(animationTickCounter, 0, 255, ANIMATION_STEP5_DURATION);
			//			menuIcon0.setAlpha(deltaAlpha);
			//			menuLeftButton.setAlpha(deltaAlpha);
			//			menuRightButton.setAlpha(deltaAlpha);
			//			headline.setAlpha(deltaAlpha);

			//			menuIcon0.invalidate();
			//			menuLeftButton.invalidate();
			//			menuRightButton.invalidate();
			//			headline.invalidate();
			//		}
			//		else
			//		{
			//			animationState = ANIMATION_READY;
			//			animationTickCounter = 0;
			//		}
			//	}
		}
	}
	else
	{
		if (animationState > ANIMATION_READY)
		{
			animationTickCounter++;
			if (animationState == ANIMATION_STEP_0)
			{

				if (animationTickCounter < ANIMATION_STEP0_DURATION)
				{
					int16_t deltaXforLogoX = EasingEquations::cubicEaseInOut(animationTickCounter, 0, ((280 - logoX.getWidth()) / 2), ANIMATION_STEP0_DURATION);
					logoX.moveTo(((320 - logoX.getWidth()) / 2) + deltaXforLogoX, logoX.getY());

					int16_t deltaXforLogoText = EasingEquations::cubicEaseInOut(animationTickCounter, 0, (280 / 2), ANIMATION_STEP0_DURATION);

					logoTextContainer.moveTo(320 / 2 - deltaXforLogoText, logoTextContainer.getY());

					int16_t newWidth = logoX.getX() - logoTextContainer.getX();
					logoTextContainer.setWidth((newWidth > 0) ? newWidth : 0);
					logoTextContainer.invalidate();
				}
				else
				{
					animationState = ANIMATION_STEP_1;
					animationTickCounter = 0;
				}
			}
			else if (animationState == ANIMATION_STEP_1)
			{
				if (animationTickCounter < ANIMATION_STEP1_DURATION)
				{
					uint8_t deltaAlpha = (uint8_t)EasingEquations::cubicEaseInOut(animationTickCounter, 0, 255, ANIMATION_STEP1_DURATION);
					subtitle.setAlpha(deltaAlpha);
					subtitle.invalidate();
				}
				else
				{
					animationState = ANIMATION_STEP_2;
					animationTickCounter = 0;
				}
			}
			else if (animationState == ANIMATION_STEP_2)
			{
				if (animationTickCounter < ANIMATION_STEP2_DURATION)
				{
					// Pause
				}
				else
				{
					animationState = ANIMATION_STEP_3;
					animationTickCounter = 0;

					subtitleStartPositionX = -1; // Reset
				}
			}
			else if (animationState == ANIMATION_STEP_3)
			{
				if (subtitleStartPositionX == -1)
				{
					subtitleStartPositionX = subtitle.getX();
					subtitleStartPositionY = subtitle.getY();
					logoXStartPositionX = logoX.getX();
					logoXStartPositionY = logoX.getY();
				}

				if (animationTickCounter < ANIMATION_STEP3_DURATION)
				{
					int16_t deltaXforLogoX = EasingEquations::cubicEaseInOut(animationTickCounter, 0, 266 - logoXStartPositionX, ANIMATION_STEP3_DURATION);
					int16_t deltaYforLogoY = EasingEquations::cubicEaseInOut(animationTickCounter, 0, 180 - logoXStartPositionY, ANIMATION_STEP3_DURATION);
					//       lcd_set_window(logoXStartPositionX + deltaXforLogoX, logoXStartPositionY + deltaYforLogoY, logoX.getWidth() , logoX.getHeight());
					logoX.moveTo(logoXStartPositionX + deltaXforLogoX, logoXStartPositionY + deltaYforLogoY);
					//       animationTickCounter = 40;
					//      logoX.invalidate();
					//       logoX.setAlpha(t_alpha);
					//       logoX.invalidate();

					int16_t deltaXforSubtitleX = EasingEquations::cubicEaseInOut(animationTickCounter, 0, 22 - subtitleStartPositionX, ANIMATION_STEP3_DURATION);
					int16_t deltaYforSubtitleY = EasingEquations::cubicEaseInOut(animationTickCounter, 0, 202 - subtitleStartPositionY, ANIMATION_STEP3_DURATION);
					subtitle.moveTo(subtitleStartPositionX + deltaXforSubtitleX - 10, subtitleStartPositionY + deltaYforSubtitleY);
				}
				else
				{
					animationState = ANIMATION_STEP_4;
					animationTickCounter = 0;
				}
			}
			else if (animationState == ANIMATION_STEP_4)
			{
				if (animationTickCounter < ANIMATION_STEP4_DURATION)
				{
					int16_t deltaX = EasingEquations::cubicEaseInOut(animationTickCounter, 0, seperatorLine.getWidth(), ANIMATION_STEP4_DURATION);
					seperatorLine.moveTo(-seperatorLine.getWidth() + deltaX, seperatorLine.getY());

					int16_t deltaYText = EasingEquations::cubicEaseInOut(animationTickCounter, 0, logoTextContainer.getHeight(), ANIMATION_STEP4_DURATION);
					logoText.moveTo(logoText.getX(), deltaYText);
				}
				else
				{
					animationState = ANIMATION_STEP_5;
					animationTickCounter = 0;
				}
			}
			else if (animationState == ANIMATION_STEP_5)
			{
				digitalClock1.setVisible(1);//开启显示时间
				if (animationTickCounter < ANIMATION_STEP5_DURATION)
				{
					uint8_t deltaAlpha = (uint8_t)EasingEquations::cubicEaseInOut(animationTickCounter, 0, 255, ANIMATION_STEP5_DURATION);
					menuIcon0.setAlpha(deltaAlpha);
					menuLeftButton.setAlpha(deltaAlpha);
					menuRightButton.setAlpha(deltaAlpha);
					headline.setAlpha(deltaAlpha);
					digitalClock1.setAlpha(deltaAlpha);

					menuIcon0.invalidate();
					menuLeftButton.invalidate();
					menuRightButton.invalidate();
					headline.invalidate();
					digitalClock1.invalidate();
				}
				else
				{
					animationState = ANIMATION_READY;
					animationTickCounter = 0;
				}
			}
		}
	}

		if (menuAnimationState > MENU_ANIMATION_READY)//菜单切换动画
		{
			menuAnimationTickCounter++;

			if (menuAnimationState == MENU_ANIMATION_STEP_0)
			{
				if (menuAnimationTickCounter < MENU_ANIMATION_STEP0_DURATION)
				{
					uint8_t deltaAlpha = (uint8_t)EasingEquations::cubicEaseInOut(menuAnimationTickCounter, 0, 255, MENU_ANIMATION_STEP0_DURATION);
					menuIcon0.setAlpha(255 - deltaAlpha);
					menuIcon0.invalidate();
					headline.setAlpha(255 - deltaAlpha);
					headline.invalidate();

					int16_t centerPositionOfMenuIcon = (320 - menuIcon0.getWidth()) / 2;
					int16_t centerPositionOfTitleIcon = (320 - headline.getWidth()) / 2;
					int16_t directionModifier = (menuAnimationDirectionLeft) ? -1 : 1;

					int16_t deltaX = directionModifier * EasingEquations::cubicEaseInOut(menuAnimationTickCounter, 0, MENU_ANIMATION_MOVE_X_SIZE, MENU_ANIMATION_STEP0_DURATION);
					menuIcon0.moveTo(centerPositionOfMenuIcon + deltaX, menuIcon0.getY());
					/*headline.moveTo(centerPositionOfTitleIcon + deltaX, headline.getY());*/
				}
				else
				{
					menuAnimationState = MENU_ANIMATION_STEP_1;
					menuAnimationTickCounter = 0;

					setSelectedMenuItem();
				}
			}
			else if (menuAnimationState == MENU_ANIMATION_STEP_1)
			{
				if (menuAnimationTickCounter < MENU_ANIMATION_STEP1_DURATION)
				{
					uint8_t deltaAlpha = (uint8_t)EasingEquations::cubicEaseInOut(menuAnimationTickCounter, 0, 255, MENU_ANIMATION_STEP1_DURATION);
					menuIcon0.setAlpha(deltaAlpha);
					menuIcon0.invalidate();
					headline.setAlpha(deltaAlpha);
					headline.invalidate();

					int16_t centerPositionOfMenuIcon = (320 - menuIcon0.getWidth()) / 2;
					int16_t centerPositionOfTitleIcon = (320 - headline.getWidth()) / 2;
					int16_t directionModifier = (menuAnimationDirectionLeft) ? -1 : 1;

					int16_t deltaX = directionModifier * EasingEquations::cubicEaseInOut(menuAnimationTickCounter, 0, MENU_ANIMATION_MOVE_X_SIZE, MENU_ANIMATION_STEP0_DURATION);
					menuIcon0.moveTo(centerPositionOfMenuIcon - (directionModifier * MENU_ANIMATION_MOVE_X_SIZE) + deltaX, menuIcon0.getY());
					/*headline.moveTo(centerPositionOfTitleIcon - (directionModifier * MENU_ANIMATION_MOVE_X_SIZE) + deltaX, headline.getY());*/
				}
				else
				{
					menuAnimationState = MENU_ANIMATION_READY;
					menuAnimationTickCounter = 0;
				}
			}
		}
	
	handleKeyEvent(presenter->GetButton());//按键检测

	digitalClock1.setTime24Hour(presenter->GetHour(), presenter->GetMinute(), presenter->GetSecond());//时间更新
	digitalClock1.invalidate();
}


void Screen1View::handleKeyEvent(uint8_t key)
{
	if (animationState != ANIMATION_READY ||
		menuAnimationState != MENU_ANIMATION_READY)
	{
		return;
	}

	if (key == 3)
	{
		// Right
		menuSelectRight();
	}
	else if (key == 1)
	{
		// Left
		menuSelectLeft();
	}
	else if (key == '8')
	{
		// Up
	}
	else if (key == '6')
	{
		// Down
	}
	else if (key == 2)
	{
		// Select

		switch (selectedMenuItem)
		{
		case 0:
			application().gotoDebugWindowScreenNoTransition();
			break;
		case 1:
			application().gotoListScreenNoTransition();
			break;
		case 2:
			application().gotoScreen2ScreenNoTransition();
			break;
		case 3:
			application().gotoNetworkMenuScreenNoTransition();
			break;
		default:
			break;
		}
	}


}

void Screen1View::leftButtonClicked()
{
	menuSelectRight();
}

void Screen1View::rightButtonClicked()
{
	menuSelectLeft();
}
void Screen1View::imgClickHandler(const touchgfx::Image & img,const touchgfx::ClickEvent & event)
{
	touchgfx::ClickEvent::ClickEventType type = event.getType();
	
	if(type==touchgfx::ClickEvent::PRESSED)
	{
		
		
	}else if(type==touchgfx::ClickEvent::RELEASED)
	{
		switch(itemIndex)
		{
		case 0:
			application().gotoDebugWindowScreenNoTransition();
			break;
		case 1:
			application().gotoListScreenNoTransition();
			break;
		case 2:
			application().gotoScreen2ScreenNoTransition();
			break;
		case 3:
			application().gotoNetworkMenuScreenNoTransition();
			break;
		default:
			break;
			
		}
	}else if(type==touchgfx::ClickEvent::CANCEL)
	{

	}
}
void Screen1View::menuSelectLeft()
{
	menuAnimationState = MENU_ANIMATION_STEP_0;
	menuAnimationTickCounter = 0;
	itemIndex--;
	if(itemIndex<0)
		itemIndex= NUMBER_OF_MENU_ITEMS - 1;
	menuAnimationDirectionLeft = true;
}

void Screen1View::menuSelectRight()
{
	menuAnimationState = MENU_ANIMATION_STEP_0;
	menuAnimationTickCounter = 0;
	itemIndex++;
	if(itemIndex> NUMBER_OF_MENU_ITEMS - 1)
		itemIndex=0;
	menuAnimationDirectionLeft = false;
}

void Screen1View::setSelectedMenuItem()
{
	TitleAnimationTickCounter++;
	if (menuAnimationDirectionLeft)
	{
		selectedMenuItem = (selectedMenuItem == 0) ? NUMBER_OF_MENU_ITEMS - 1 : selectedMenuItem - 1;
	}
	else
	{
		selectedMenuItem = (selectedMenuItem == NUMBER_OF_MENU_ITEMS - 1) ? 0 : selectedMenuItem + 1;
	}

	switch (selectedMenuItem)
	{
	//case 0:
	//	menuIcon0.setBitmap(Bitmap(BITMAP_SUBDEMOICON_INFO_ID));
	//	break;
	case 0:
		menuIcon0.setBitmap(Bitmap(BITMAP_NETWORKDEBUG_ID));
		headline.setTypedText(TypedText(T_NETCONFIG));
		break;
	case 1:
		menuIcon0.setBitmap(Bitmap(BITMAP_SUBDEMOICON_LIST_ID));
		headline.setTypedText(TypedText(T_LANGUAGESELECT));
		break;
	case 2:
		menuIcon0.setBitmap(Bitmap(BITMAP_SUBDEMOICON_HEALTH_ID));
		headline.setTypedText(TypedText(T_HEALTHDIAGNOSE));
		break;
	case 3:
		menuIcon0.setBitmap(Bitmap(BITMAP_NETWORKTITLE_ID));
		headline.setTypedText(TypedText(T_NETFUNCTION));
		break;
	default:
		break;
	}
}
