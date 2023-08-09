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
    YRenderer yr = new YRenderer(context);

    public YGLSurfaceView(Context context) {
        super(context);
        setRenderer(yr);
		setZ(-1.0f);
    }

    public boolean onTouchEvent(MotionEvent e) {
        float x = e.getX();
        float y = e.getY();
        switch (e.getAction()) {
            case 2:
                yr.rox -= x - px;
                yr.roy -= y - py;
                if (yr.roy > 80.0f) {
                    yr.roy = 80.0f;
                }
                if (yr.roy < -80.0f) {
                    yr.roy = -80.0f;
                    break;
                }
                break;
        }
        px = x;
        py = y;
        return true;

    }


    public int getT() {
        return yr.getT();
    }


}