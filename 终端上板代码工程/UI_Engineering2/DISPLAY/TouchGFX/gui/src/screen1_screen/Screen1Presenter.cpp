#include <gui/screen1_screen/Screen1View.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>

Screen1Presenter::Screen1Presenter(Screen1View& v)
    : view(v)
{
}

void Screen1Presenter::activate()
{

}

void Screen1Presenter::deactivate()
{

}

int Screen1Presenter::GetButton()
{
    int released=1;
    if (model->GetButton() != 0)
    {
        if (released == 1)
        {
            return model->GetButton();
            released = 0;
        }
        else
            return 0;
    }
    else
    {
        released = 1;
        return 0;
    }
}

int Screen1Presenter::IfStarted()
{
    return model->IfStarted();
}
    
int Screen1Presenter::GetHour()
{
    return model->GetHour();
}
int Screen1Presenter::GetMinute()
{
    return model->GetMinute();
}
int Screen1Presenter::GetSecond()
{
    return model->GetSecond();
}

void Screen1Presenter::HealthDiagnose()
{
    model->HealthDiagnose();
}

void Screen1Presenter::CancleHealthDiagnose()
{
    model->CancelHealthDiagnose();
}

void Screen1Presenter::NetDebug()
{
    model->NetDebug();
}

void Screen1Presenter::CancelNetDebug()
{
    model->CancelNetDebug();
}

void Screen1Presenter::PostData()
{
    model->PostData();
}

void Screen1Presenter::CancelPostData()
{
    model->CancelPostData();
}