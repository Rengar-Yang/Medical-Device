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
import javax.microedition.khronos.egl.EGL10;

import android.opengl.GLU;
import java.nio.FloatBuffer;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import android.util.FloatMath;

public class YGLSurfaceView extends GLSurfaceView {
	float plx,ply;
	YRenderer yr;
    public YGLSurfaceView(Context context,YailList car,YailList map,YailList tas,YCavas y) {
        super(context);
		yr = new YRenderer(car,map,tas,y);
		setRenderer(yr);
		//setRenderMode(GLSurfaceView.RENDERMODE_WHEN_DIRTY);
    }
	@Override 
	public boolean onTouchEvent(MotionEvent e) {
		switch(e.getActionMasked()) {
			case MotionEvent.ACTION_UP:
				yr.map.endCatch();
			break;
			case MotionEvent.ACTION_DOWN:
				yr.map.startCatch();
			break;
		}
		//requestRender();
		return true;
	}
	public int getT(){
		return yr.getT();
	}
}