#include <gui/debugwindow_screen/DebugWindowView.hpp>
#include <gui/debugwindow_screen/DebugWindowPresenter.hpp>

DebugWindowPresenter::DebugWindowPresenter(DebugWindowView& v)
    : view(v)
{

}

void DebugWindowPresenter::activate()
{

}

void DebugWindowPresenter::deactivate()
{

}

void DebugWindowPresenter::NetDebug()
{
    model->NetDebug();
}

void DebugWindowPresenter::CancelNetDebug()
{
    model->CancelNetDebug();
}
void DebugWindowPresenter::NetTime()
{
    model->NetTime();
}

void DebugWindowPresenter::CancelNetTime()
{
    model->CancelNetTime();
}

void DebugWindowPresenter::PostData()
{
    model->PostData();
}

void DebugWindowPresenter::CancelPostData()
{
    model->CancelPostData();
}

int DebugWindowPresenter::GetButton()
{
    return model->GetButton();
}

int DebugWindowPresenter::GetHumidity()
{
    return model->GetHumidity();
}

int DebugWindowPresenter::GetTemperature()
{
    return model->GetTemperature();
}

int DebugWindowPresenter::GetHeartRate()
{
    if (model->GetHeartRate() < 10000)
        return model->GetHeartRate();
    else
        return 0;
}

int DebugWindowPresenter::GetSPO2()
{
    if (model->GetSPO2() < 10000)
        return model->GetSPO2();
    else
        return 0;
}

int DebugWindowPresenter::GetDebugResult()
{
    return model->GetDebugResult();
}