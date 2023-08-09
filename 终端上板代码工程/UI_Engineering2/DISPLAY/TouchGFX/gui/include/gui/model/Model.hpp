#ifndef MODEL_HPP
#define MODEL_HPP

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();
		
		//接收数据
		int GetHumidity();
		int GetTemperature();
		int GetHeartRate();
		int GetSPO2();
		int GetHeartRateValid();
		int GetSPO2Valid();
		int GetHeartSignal();
		int GetButton();
		int GetHour();
		int GetMinute();
		int GetSecond();
		int GetECG();
		int Model::GetDebugResult();
			
		int IfStarted();
		
		//发送指令
		void HealthDiagnose();
		void StateDetect();
		void NetTime();
		void PostData();
		void NetDebug();
		void ConnectWIFI();
		
		void CancelHealthDiagnose();
		void CancelStateDetect();
		void CancelNetTime();
		void CancelPostData();
		void CancelNetDebug();
		void CancelConnectWIFI();
		
protected:
    ModelListener* modelListener;
};

#endif /* MODEL_HPP */
