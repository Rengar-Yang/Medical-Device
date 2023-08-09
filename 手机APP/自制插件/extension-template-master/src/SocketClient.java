package cn.roger.socket;

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
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.SocketTimeoutException;



@DesignerComponent(version = 1,
    description = "by Roger Young",
    category = ComponentCategory.EXTENSION,
    nonVisible = true,
    iconName = "images/extension.png")

@SimpleObject(external = true)

public class SocketClient extends AndroidNonvisibleComponent {
    Socket socket = null;
    OutputStream ou = null;
    String buffer = "";
    String geted1;
    MyThread mt;
    final int CONNECT = 100001;
    final int SENDMESSAGE = 100002;
    final int CLOSE = 100003;
    public SocketClient(ComponentContainer container) {
        super(container.$form());
    }
    public Handler myHandler = new Handler() {
        @Override
        public void handleMessage(Message msg) {
            GetMessage(msg.obj.toString());
        }
 
    };
    @SimpleFunction(description = "start")
    public void closeConnect(){
        if(socket != null){
            mt = new MyThread(CLOSE);
            mt.start();
        }else{
            GetMessage("连接未创建！");
        }
    }
    @SimpleFunction(description = "start")
    public void sendMessage(String s){
        if(socket != null){
            mt = new MyThread(SENDMESSAGE);
            mt.setText(s);
            mt.start();
        }else{
            GetMessage("连接未创建！");
        }
    }
    @SimpleFunction(description = "start")
    public void connect(String ip){
        if(socket == null){
            mt = new MyThread(CONNECT);
            mt.setIP(ip);
            mt.start();
        }else{
            GetMessage("连接已创建！");
        }
    }

    @SimpleEvent
    public void GetMessage(String s){
        EventDispatcher.dispatchEvent(this, "GetMessage", "\n"+s);
    }
    class MyThread extends Thread {
 
        public String txt1;
        public String IP;
        Message msg;
        public int flag;
        public MyThread(int flag) {
            this.flag = flag;
        }
        public void setText(String s){
            txt1 = s;
        }
        public void setIP(String ip){
            IP = ip;
        }
        @Override
        public void run() {
            switch(flag){
                case CONNECT:
                    try {
                        socket = new Socket();
                        msg = myHandler.obtainMessage();
                        msg.obj = "开始连接";
                        myHandler.sendMessage(msg);
                        socket.connect(new InetSocketAddress(IP, 3030), 1000);
                        ou = socket.getOutputStream();
                        msg = myHandler.obtainMessage();
                        msg.obj = "连接成功";
                        myHandler.sendMessage(msg);
                    } catch (SocketTimeoutException aa) {
                        msg = myHandler.obtainMessage();
                        msg.obj = "连接超时";
                        myHandler.sendMessage(msg);
                        socket = null;
                    } catch (IOException e) {
                        msg = myHandler.obtainMessage();
                        msg.obj = "未知错误";
                        myHandler.sendMessage(msg);
                        socket = null;
                    }
                break;
                case SENDMESSAGE:
                    try {
                        ou.write(txt1.getBytes("utf-8"));
                        ou.write("\n".getBytes("utf-8"));
                        ou.flush();
                        msg = myHandler.obtainMessage();
                        msg.obj = "发送完毕";
                        myHandler.sendMessage(msg);
                    }catch (IOException e) {
                        msg = myHandler.obtainMessage();
                        msg.obj = "未知错误";
                        myHandler.sendMessage(msg);
                    }
                break;
                case CLOSE:
                    try {
                        ou.close();
                        socket.close();
                        socket = null;
                        msg = myHandler.obtainMessage();
                        msg.obj = "关闭";
                        myHandler.sendMessage(msg);
                    }catch (IOException e) {
                        msg = myHandler.obtainMessage();
                        msg.obj = "未知错误";
                        myHandler.sendMessage(msg);
                    }
                break;
            }
        }
    }
}