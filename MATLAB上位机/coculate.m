load('signal.mat');%导入日志文件
t=0:1:499;
mag = HeartSignal;
magNoG = mag - mean(mag)*0;%滤除直流分量
low = magNoG;
fs=250;   %采集系统的采样频率
low = lowpass(low,0.4,fs);          %以0.4为频率上限，做lowpass

% N=8192;  
% n=0:N-1;
% x1=magNoG(1,:);
% y1=fft(x1,N);%进行fft变换
% mag1=abs(y1);%求幅值
% f=(0:N-1)'*fs/N;%进行对应的频率转换
% subplot(311);
% plot(f,mag1);%做频谱图
% xlabel('频率(Hz)'); ylabel('幅值');
% title('标量心电频域图');grid; 
% figure

%---------------------------------------------------%
%-------------------频域信号计算---------------------%
%---------------------------------------------------%
FFT_Data = abs(fft(magNoG));
m = FFT_Data(1:length(FFT_Data)/2);
n = length(magNoG);
f = (1:n/2)*(fs/n);
plot(f,m);
xlabel('频率(Hz)'); ylabel('幅值');
title('标量心电频域图');grid; 
figure

magNoG = magNoG-low;%归一化幅值
magNoG1 = lowpass(magNoG,50,fs);          %以2为频率上限，做lowpass

%-----------------------------------------------%
%-------------------滤波处理---------------------%
%-----------------------------------------------%
% minPeakHeight = 0*std(magNoG); %求标准差，调整此参数以调整极点判断阈值
% [pks,locs] = findpeaks(magNoG,'MINPEAKHEIGHT',minPeakHeight);%求极值
% numSteps = numel(pks);%统计心率
% 
% hold on;
% plot(t,mag);
% plot(t,low);
% title('调制信号计算');
% hold off;
% 
% figure
% subplot(2,1,1);
% hold on;
% plot(t,magNoG);
% plot(t(locs), pks, 'r', 'Marker', 'v', 'LineStyle', 'none');%极点可视化
% title('滤波前，心率为',numSteps);
% xlabel('时间 (s)');
% ylabel('心电强度');
% hold off;

minPeakHeight1 = 0*std(magNoG); %求标准差，调整此参数以调整极点判断阈值
[pks,locs1] = findpeaks(magNoG1,'MINPEAKHEIGHT',minPeakHeight1);%求极值
numSteps1 = numel(pks);%统计心率

hold on;
plot(t,magNoG1);
plot(t(locs1), pks, 'r', 'Marker', 'v', 'LineStyle', 'none');%极点可视化
title('滤波后，心率为',numSteps1);
xlabel('时间 (s)');
ylabel('心电强度');
hold off;

%---------------------------------------------------%
%-------------------幅值归一化处理---------------------%
%---------------------------------------------------%
% figure
% subplot(3,1,1)
% plot(t,mag);
% title('原始信号');
% subplot(3,1,2)
% plot(t,low)
% title('调制信号');
% subplot(3,1,3)
% plot(t,magNoG)
% title('幅度归一化信号');