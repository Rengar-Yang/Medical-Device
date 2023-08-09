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
    public volatile float b;
    public volatile float bodyr;
    public volatile float g;
    public volatile float headr;
    public volatile float r;
    public volatile float x;
    public volatile float y;

    public SimpleCube(float r, float g, float b, float x, float y) {
        this.r = r;
        this.g = g;
        this.b = b;
        this.x = x;
        this.y = y;
    }

}