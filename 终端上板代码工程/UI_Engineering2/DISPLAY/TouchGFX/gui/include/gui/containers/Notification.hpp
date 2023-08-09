#ifndef NOTIFICATION_HPP
#define NOTIFICATION_HPP

#include <gui_generated/containers/NotificationBase.hpp>

class Notification : public NotificationBase
{
public:
    Notification();
    virtual ~Notification() {}

    virtual void initialize();
    virtual void OKButtonClicked();
protected:
};

#endif // NOTIFICATION_HPP
