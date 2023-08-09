package cn.roger.opengl;

import com.google.appinventor.components.annotations.*;
import com.google.appinventor.components.common.ComponentCategory;
import com.google.appinventor.components.runtime.*;
import com.google.appinventor.components.runtime.util.*;
import com.google.appinventor.components.runtime.errors.YailRuntimeError;
import android.opengl.GLSurfaceView;

import android.content.Context;
import android.view.ViewGroup;
import android.view.MotionEvent;
import android.view.ViewGroup.LayoutParams;
import android.graphics.PixelFormat;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.opengl.GLU;
import java.nio.FloatBuffer;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import android.util.FloatMath;

public class SimpleCube{
	public volatile float r,g,b;
	public volatile float x,y;
	public volatile float headr=0,bodyr=0;
	public volatile float v = 0.2f;
	public volatile float vx,vy;
	public volatile boolean running = false;
	public SimpleCube(float r,float g,float b,float x,float y){
		this.r = r;
		this.g = g;
		this.b = b;
		this.x = x;
		this.y = y;
	}
	public void setBodyr(float y,float x){
		bodyr = headr+(float) Math.toDegrees(Math.atan2(y,x));
		vx=FloatMath.cos((float)Math.toRadians(bodyr))*v;
		vy=FloatMath.sin((float)Math.toRadians(bodyr))*v;
	}
	public void updateLocation(){
		if(running){
			x+=vx;
			y+=vy;
			if(x>200f)x=200f;
			if(y>200f)y=200f;
			if(x<-200f)x=-200f;
			if(y<-200f)y=-200f;
		}
	}
	public void setHeadr(float d){
		headr = d;
	}
	public void setRunning(boolean b){
		running = b;
	}
}