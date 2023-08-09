#include <gui/containers/Notification.hpp>

Notification::Notification()
{

}

void Notification::initialize()
{
    NotificationBase::initialize();
}

void Notification::OKButtonClicked()
{
    setVisible(0);
    invalidate();
}