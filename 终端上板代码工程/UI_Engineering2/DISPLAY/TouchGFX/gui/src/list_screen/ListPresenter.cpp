#include <gui/list_screen/ListView.hpp>
#include <gui/list_screen/ListPresenter.hpp>

ListPresenter::ListPresenter(ListView& v)
    : view(v)
{
}

void ListPresenter::activate()
{

}

void ListPresenter::deactivate()
{

}

int ListPresenter::GetButton()
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