#define _CRT_SECURE_NO_WARNINGS
#include <gui/debugwindow_screen/DebugWindowView.hpp>
#include <texts/TextKeysAndLanguages.hpp>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"
DebugWindowView::DebugWindowView()
{

}

void DebugWindowView::setupScreen()
{
    DebugWindowViewBase::setupScreen();
    //this->bufSize = 4096;
    //this->textBuf = (uint8_t*)malloc(this->bufSize);
    //this->textBuf[this->bufSize];
    presenter->NetDebug();
    if (textBuf != NULL)
    {
        memset(textBuf, 0, this->bufSize);
    }
   /* presenter->NetTime();*/
}

void DebugWindowView::tearDownScreen()
{
    DebugWindowViewBase::tearDownScreen();
    presenter->CancelNetDebug();
    /*presenter->CancelNetTime();*/
}

void DebugWindowView::handleTickEvent()
{
    uint8_t str[128];
   
    static uint16_t textCount = 0;
    if (presenter->GetDebugResult() == 1)
    {
        tickCounter++;
        sprintf((char*)str, "Config %d: Config successfully. Reply:OK \n", tickCounter);
        this->TextAreaAddStr(str, sizeof(str));
    }
    scrollableContainer1.invalidate();
    scrollableContainer1.setScrollDurationSpeedup(7);
    handleKeyEvent(presenter->GetButton());
}

void DebugWindowView::TextAreaAddStr(uint8_t* str, uint32_t len)
{
    int16_t textHeight = 0, nowTextHeight = 0;
    static int16_t addHeigth = 0, addHeightsum = 0, scrollHeight = 0;
    nowTextHeight = textArea1.getTextHeight();
    textHeight = textArea1.getHeight();
    scrollHeight = scrollableContainer1.getHeight();
    /* buf is ready */
    if (textBuf == NULL || textArea1Buffer == NULL || len == 0)
        return;
    /* buf is full text is  on the bottom of scroll*/
    if (nowTextHeight > textHeight)
    {
        memset(textBuf, 0, this->bufSize);
        scrollableContainer1.doScroll(0, addHeightsum);
        addHeigth = 0;
        addHeightsum = 0;
        nowTextHeight = 0;
    }
    /* scroll the text */
    if (nowTextHeight > scrollHeight + addHeightsum)
    {
        addHeigth = scrollHeight + addHeightsum - nowTextHeight;
        addHeightsum = addHeightsum - addHeigth;
        scrollableContainer1.doScroll(0, addHeigth);
    }
    uint32_t lens = strlen((char*)textBuf);
    memcpy(textBuf + lens,str, len);
    //Unicode::snprintf(textArea1Buffer, lens + len, textBuf);
    Unicode::fromUTF8(textBuf, textArea1Buffer, lens + len);
    textArea1.setWideTextAction(WIDE_TEXT_CHARWRAP);
    textArea1.invalidate();

 /*   Unicode::fromUTF8(str, textArea1Buffer, len);
    textArea1.invalidate();*/
}

void DebugWindowView::handleKeyEvent(uint8_t key)
{
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
        scrollableContainer1.doScroll(0, -30);
    }
    else if (key == 3)
    {
        // Down
        scrollableContainer1.doScroll(0, 30);
    }
    else if (key == 2)
    {
        // Select
        application().gotoScreen1ScreenNoTransition();
    }
}