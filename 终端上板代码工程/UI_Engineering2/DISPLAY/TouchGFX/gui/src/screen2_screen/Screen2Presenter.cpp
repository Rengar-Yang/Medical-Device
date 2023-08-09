#include <gui/screen2_screen/Screen2View.hpp>
#include <gui/screen2_screen/Screen2Presenter.hpp>

Screen2Presenter::Screen2Presenter(Screen2View& v)
    : view(v)
{

}

void Screen2Presenter::activate()
{

}

void Screen2Presenter::deactivate()
{

}

int Screen2Presenter::GetHumidity()
{
    return model->GetHumidity();
}

int Screen2Presenter::GetTemperature()
{
    return model->GetTemperature();
}

int Screen2Presenter::GetHeartSignal()
{
    return model->GetHeartSignal();
}

int Screen2Presenter::GetHeartRate()
{
    if (model->GetHeartRate() < 10000)
        return model->GetHeartRate();
    else
        return 0;
}

int Screen2Presenter::GetHeartRateValid()
{
    return model->GetHeartRateValid();
}

int Screen2Presenter::GetSPO2()
{
    if (model->GetSPO2() < 10000)
        return model->GetSPO2();
    else
        return 0;
}

int Screen2Presenter::GetSPO2Valid()
{
    return model->GetSPO2Valid();
}

int Screen2Presenter::GetECG()
{
    return model->GetECG();
}

int Screen2Presenter::GetButton()
{
    int released = 1;
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

void Screen2Presenter::HealthDiagnose()
{
    model->HealthDiagnose();
}

void Screen2Presenter::CancleHealthDiagnose()
{
    model->CancelHealthDiagnose();
}

void Screen2Presenter::NetDebug()
{
    model->NetDebug();
}

void Screen2Presenter::CancelNetDebug()
{
    model->CancelNetDebug();
}

void Screen2Presenter::PostData()
{
    model->PostData();
}

void Screen2Presenter::CancelPostData()
{
    model->CancelPostData();
}