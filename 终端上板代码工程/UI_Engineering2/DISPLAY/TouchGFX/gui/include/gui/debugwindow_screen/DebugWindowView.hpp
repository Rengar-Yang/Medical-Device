#ifndef DEBUGWINDOWVIEW_HPP
#define DEBUGWINDOWVIEW_HPP

#include <gui_generated/debugwindow_screen/DebugWindowViewBase.hpp>
#include <gui/debugwindow_screen/DebugWindowPresenter.hpp>


class DebugWindowView : public DebugWindowViewBase
{
public:
    DebugWindowView();
    virtual ~DebugWindowView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void TextAreaAddStr(uint8_t* str, uint32_t len);
    virtual void handleTickEvent();
    virtual void handleKeyEvent(uint8_t key);
    int  tickCounter;
    /*uint8_t* textBuf;*/
    static const uint16_t bufSize = 4096;
    uint8_t textBuf[bufSize];
protected:
};

#endif // DEBUGWINDOWVIEW_HPP
