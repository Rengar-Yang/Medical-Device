#include <gui/screen2_screen/Screen2View.hpp>
#include <touchgfx/Color.hpp>
int Graph=0;
int PostState1 = 0;
Screen2View::Screen2View()
{

}

void Screen2View::setupScreen()
{
    Screen2ViewBase::setupScreen();
    presenter->HealthDiagnose();
 //   presenter->PostData();
}

void Screen2View::tearDownScreen()
{
    Screen2ViewBase::tearDownScreen();
    presenter->CancleHealthDiagnose();
    presenter->CancelPostData();
}

void Screen2View::ShowData()
{
    Unicode::snprintf(textArea1Buffer, 10, "%d", presenter->GetHumidity());
    textArea1.resizeToCurrentText();
    textArea1.invalidate();

    Unicode::snprintf(textArea4Buffer, 10, "%d", presenter->GetTemperature());
    textArea4.resizeToCurrentText();
    textArea4.invalidate();

    Unicode::snprintf(textArea2Buffer, 10, "%d", presenter->GetHeartRate());
    textArea2.resizeToCurrentText();
    textArea2.invalidate();

    Unicode::snprintf(textArea3Buffer, 10, "%d", presenter->GetSPO2());
    textArea3.resizeToCurrentText();
    textArea3.invalidate();

    Unicode::snprintf(textArea5Buffer, 10, "%d", presenter->GetHeartRateValid());
    textArea5.resizeToCurrentText();
    textArea5.invalidate();

 /*   Unicode::snprintf(textArea6Buffer, 10, "%d", presenter->GetSPO2Valid());
    textArea6.resizeToCurrentText();
    textArea6.invalidate();*/
  
}

void Screen2View::handleTickEvent()
{
    /*int min = 2000, max = 2000;
    count++;
    if (count % 400 == 0)
        min = 2000, max = 2000;
    ShowData();
    if (min > presenter->GetECG())
        min = presenter->GetECG();
    if (max < presenter->GetECG())
        max = presenter->GetECG();*/
    //dynamicGraph1.addDataPoint(presenter->GetHeartSignal());
    handleKeyEvent(presenter->GetButton());//°´¼ü¼ì²â
    ShowData();
    if(Graph % 2 == 0)
        dynamicGraph1.addDataPoint(presenter->GetHeartSignal());
    if (Graph % 2 == 1)
        dynamicGraph1.addDataPoint(presenter->GetECG());
 /*   dynamicGraph1.setGraphRangeY(min-800, max+800);*/
    //dynamicGraph1.clear();

    dynamicGraph1.invalidate();
    /*Unicode::snprintf(textArea6Buffer, 10, "%d", count);
    textArea6.resizeToCurrentText();
    textArea6.invalidate();*/
}

void Screen2View::PostDataBegin()
{
    PostState1++;
    if (PostState1 % 2 == 1)
    {
        presenter->PostData();
        textArea7.setColor(0);
    }
    if (PostState1 % 2 == 0)
    {
        presenter->CancelPostData();
        textArea7.setColor(0);
    }
}

void Screen2View::GraphChanged()
{
    Graph++;
}

void Screen2View::handleKeyEvent(uint8_t key)
{
    if (key == 3)
    {
        // Right
        dynamicGraph1.moveRelative(10, 0);
    }
    else if (key == 1)
    {
        // Left
        dynamicGraph1.moveRelative(-10, 0);
    }
    else if (key == 2)
    {
        Graph++;
    }
}