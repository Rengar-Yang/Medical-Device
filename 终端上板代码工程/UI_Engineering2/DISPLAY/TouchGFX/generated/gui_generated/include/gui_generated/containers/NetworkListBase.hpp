/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef NETWORKLISTBASE_HPP
#define NETWORKLISTBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextArea.hpp>

class NetworkListBase : public touchgfx::Container
{
public:
    NetworkListBase();
    virtual ~NetworkListBase() {}
    virtual void initialize();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box background;
    touchgfx::Image FunctionLogo;
    touchgfx::TextArea FunctionName;
    touchgfx::Box box1;
    touchgfx::Box box2;

private:

};

#endif // NETWORKLISTBASE_HPP
