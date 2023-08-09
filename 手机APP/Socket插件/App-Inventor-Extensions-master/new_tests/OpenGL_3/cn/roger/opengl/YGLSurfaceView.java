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
import javax.microedition.khronos.egl.EGL10;

import android.opengl.GLU;
import java.nio.FloatBuffer;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import android.util.FloatMath;

public class YGLSurfaceView extends GLSurfaceView {
	  public volatile float fx;
    public volatile float fy;
    float plx;
    float ply;
    float prx;
    float pry;
    YRenderer yr;

    public YGLSurfaceView(Context context) {
        super(context);
		yr = new YRenderer(context);
        setRenderer(yr);
    }

    public boolean onTouchEvent(MotionEvent e) {
        float x;
        float y;
        switch (e.getActionMasked()) {
			case MotionEvent.ACTION_DOWN:
			case MotionEvent.ACTION_POINTER_DOWN:
                x = e.getX(e.getActionIndex());
                y = e.getY(e.getActionIndex());
                if (x <= ((float) (yr.w / 2))) {
                    plx = x;
                    ply = y;
                    break;
                }
                prx = x;
                pry = y;
                break;
			case MotionEvent.ACTION_MOVE:
                for (int i = 0; i < e.getPointerCount(); i++) {
                    x = e.getX(i);
                    y = e.getY(i);
                    if (x > ((float) (yr.w / 2))) {
                        yr.rox += (x - prx) * 0.8f;
                        yr.roy -= (y - pry) * 0.8f;
                        if (yr.roy > 10.0f) {
                            yr.roy = 10.0f;
                        }
                        if (yr.roy < -80.0f) {
                            yr.roy = -80.0f;
                        }
                        prx = x;
                        pry = y;
                    } else {
                        fy = (FloatMath.sin((float) Math.toRadians((double) yr.rox)) * (x - plx)) * 0.002f;
                        fx = (FloatMath.sin((float) Math.toRadians((double) (-yr.rox))) * (y - ply)) * 0.002f;
                        fx += (FloatMath.cos((float) Math.toRadians((double) yr.rox)) * (x - plx)) * 0.002f;
                        fy += (FloatMath.cos((float) Math.toRadians((double) (-yr.rox))) * (y - ply)) * 0.002f;
                    }
                }
                break;
        }
        return true;
    }

    public int getT() {
        return yr.getT();
    }

    public float getRoate() {
        return yr.rox;
    }

}