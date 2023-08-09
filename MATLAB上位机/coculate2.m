%% Parameter Interface
Frequence0          = 60;        %单位：Hz    
Frequence1          = 1e3;       %单位：Hz
Frequence2          = 1.8e3;       %单位：Hz
SampleFre           = 4e3;       %单位：Hz
SampleLen           = SampleFre; %采样点数
%% Main
%-------------------产生三路信号
t = 0:1/SampleLen:1/SampleFre*(SampleLen-1);
SignalData0 = sin(2*pi*Frequence0*t);
SignalData1 = 2*sin(2*pi*Frequence1*t);
SignalData2 = 3*sin(2*pi*Frequence2*t);
SignalData3 = SignalData0+SignalData1+SignalData2;
figure;hold on

plot(t(1:150),SignalData0(1:150),'b')
plot(t(1:150),SignalData1(1:150),'r')
plot(t(1:150),SignalData2(1:150),'k')
title('输入信号成分')
hold off
figure;plot(t(1:150),SignalData3(1:150))
title('三路信号求和')
%-------------------输入信号频域图
FFT_Data = abs(fft(SignalData3));
m = FFT_Data(1:length(FFT_Data)/2);
n = length(SignalData3);
f = (1:n/2)*(SampleFre/n);

figure;
plot(f,m)
xlabel('Frequency')
ylabel('Power')
title('输入信号频谱')