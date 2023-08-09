package cn.roger.Socket;

import com.google.appinventor.components.annotations.*;
import com.google.appinventor.components.common.ComponentCategory;
import com.google.appinventor.components.runtime.*;
import com.google.appinventor.components.runtime.util.*;
import com.google.appinventor.components.runtime.errors.YailRuntimeError;
import android.graphics.drawable.GradientDrawable;
import android.graphics.Color;
import android.content.res.ColorStateList;
import android.view.View;
import android.graphics.drawable.RippleDrawable;
import android.graphics.drawable.Drawable;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.app.Activity;
import android.content.Context;
import android.view.Menu;
import android.widget.TextView;

import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.ServerSocket;
import java.net.SocketException;
import java.util.Enumeration;


@DesignerComponent(version = SocketUtil.VERSION,
    description = "by Roger Young",
    category = ComponentCategory.EXTENSION,
    nonVisible = true,
    iconName = "images/extension.png")

@SimpleObject(external = true)

public class SocketUtil extends AndroidNonvisibleComponent {
    public static final int VERSION = 1;
    private static final String LOG_TAG = "SocketUtil";
    private ComponentContainer container;
    private Context context;
    String ip;
    int port;

    private ServerSocket serverSocket = null;
    StringBuffer stringBuffer = new StringBuffer();

    private InputStream inputStream;

    public Handler handler = new Handler(){

        @Override
        public void handleMessage(Message msg) {
        	GetMessage(msg.obj.toString());

        }
    };
	
    public SocketUtil(ComponentContainer container) {
        super(container.$form());
        this.container = container;
        context = (Context) container.$context();
    }
    public void getLocalIpAddress(ServerSocket serverSocket){

      try {
         for (Enumeration<NetworkInterface> en = NetworkInterface.getNetworkInterfaces(); en.hasMoreElements();){
                NetworkInterface intf = en.nextElement();
                for (Enumeration<InetAddress> enumIpAddr = intf.getInetAddresses();    enumIpAddr.hasMoreElements();){
                    InetAddress inetAddress = enumIpAddr.nextElement();
                    String mIP = inetAddress.getHostAddress().substring(0, 3);
                    if(mIP.equals("192")){
                        ip = inetAddress.getHostAddress();    //获取本地IP
                        port = serverSocket.getLocalPort();
                    }
                }
            }
      } catch (SocketException e) {
         e.printStackTrace();
      }
   }

    @SimpleEvent
    public void GetMessage(String s){
        EventDispatcher.dispatchEvent(this, "GetMessage", "\n"+s);
    }
    @SimpleFunction(description = "start")
    public void receiveData(){

        Thread thread = new Thread(){
            @Override
            public void run() {
                super.run();
                /*指明服务器端的端口号*/
                try {
                    serverSocket = new ServerSocket(8000);
                } catch (IOException e) {
                    e.printStackTrace();
                }
                
                getLocalIpAddress(serverSocket);

                Message message_1 = handler.obtainMessage();
                message_1.obj = "IP:" + ip + " PORT: " + port;
                handler.sendMessage(message_1);

                while (true){
                    Socket socket = null;
                    try {
                        socket = serverSocket.accept();
                        Message message_2 = handler.obtainMessage();
                        message_2.obj = "有兄弟连上了！"+socket.getInetAddress().getHostAddress();
                        handler.sendMessage(message_2);
                    } catch (IOException e) {
                    }

                    new ServerThread(socket).start();

                }
            }
        };
        thread.start();

    }

	class ServerThread extends Thread{

	    Socket socket;
        Message message_2;


	    public ServerThread(Socket socket){
	        this.socket = socket;
	    }

	    @Override
	    public void run() {
            try {
                BufferedReader br = null;
                br = new BufferedReader(new InputStreamReader(socket.getInputStream()));
                while(true){
                    String msg = null;
                    msg = br.readLine();
                    if(msg != null){
                        message_2 = handler.obtainMessage();
                        message_2.obj = socket.getInetAddress().getHostAddress()+":"+msg;
                        handler.sendMessage(message_2);
                    }
                }
	        } catch (IOException e) {
                message_2 = handler.obtainMessage();
                message_2.obj = "他好像不见了";
                handler.sendMessage(message_2);
                try{socket.close();}catch(Exception e1){}
	        }
        }
	}

}