package cn.car.activity;

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

class Map {
	public volatile Car car;
	public volatile Ground ground;
	public volatile Tas tas;
	public volatile boolean catching = false;
	YailList yl;
	YCavas y;
	int t;
	boolean b = true;
	public Map(YailList car,YailList map,YailList tas,YCavas y) {
		this.yl = yl;
		this.car = new Car(car.toArray());
		this.ground = new Ground(map.toArray());
		this.tas = new Tas(tas.toArray());
		this.y = y;
		t= 0;
	}
	public void draw(GL10 gl) {
		car.move(gl);
		ground.draw(gl);
		car.updateLocation();
		tas.draw(gl,car);
		car.draw(gl);
		t++;
		car.setRunning(!ground.out(car));
		if(ground.out(car)){
			if(b){
				y.stop(t);
				b = false;
			}
		}
	}
	void startCatch(){
		catching =  true;
		tas.startCatch(car);
	}
	void endCatch(){
		catching =  false;
		tas.endCatch();
	}
}