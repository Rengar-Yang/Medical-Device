#include <gui/networkmenu_screen/NetworkMenuView.hpp>
#include <gui/networkmenu_screen/NetworkMenuPresenter.hpp>

NetworkMenuPresenter::NetworkMenuPresenter(NetworkMenuView& v)
    : view(v)
{

}

void NetworkMenuPresenter::activate()
{

}

void NetworkMenuPresenter::deactivate()
{

}

int NetworkMenuPresenter::GetButton()
{
    return model->GetButton();
}

void NetworkMenuPresenter::NetTime()
{
    model->NetTime();
}

void NetworkMenuPresenter::CancelNetTime()
{
    model->CancelNetTime();
}

void NetworkMenuPresenter::NetDebug()
{
    model->NetDebug();
}

void NetworkMenuPresenter::CancelNetDebug()
{
    model->CancelNetDebug();
}

void NetworkMenuPresenter::ConnectWIFI()
{
    model->ConnectWIFI();
}

void NetworkMenuPresenter::CancelConnectWIFI()
{
    model->CancelConnectWIFI();
}