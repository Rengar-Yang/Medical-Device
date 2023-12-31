/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef NETSELECTORELEMENTBASE_HPP
#define NETSELECTORELEMENTBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextArea.hpp>

class NetSelectorElementBase : public touchgfx::Container
{
public:
    NetSelectorElementBase();
    virtual ~NetSelectorElementBase() {}
    virtual void initialize();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box background;
    touchgfx::Box verticalLine;
    touchgfx::Image FunctionLogo;
    touchgfx::TextArea FunctionName;

private:

};

#endif // NETSELECTORELEMENTBASE_HPP
