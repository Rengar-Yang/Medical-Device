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

class CubeUtil {
	public Cube cube = new Cube();
	public SimpleCube sc[] = new SimpleCube[5];

	public CubeUtil() {
		sc[0] = new SimpleCube(0.1f,0.1f,0.1f,0f,0f);
		sc[1] = new SimpleCube(0.7f,0.3f,0.5f,20f,20f);
		sc[2] = new SimpleCube(0.3f,0.5f,0.7f,70f,-30f);
		sc[3] = new SimpleCube(0.5f,0.2f,0.2f,-30f,-30f);
		sc[4] = new SimpleCube(0.0f,0.19f,0.9f,99f,-99f);
	}
	public void draw(GL10 gl) {
        cube.draw(gl, sc[0]);
        cube.draw(gl, sc[1]);
        cube.draw(gl, sc[2]);
        cube.draw(gl, sc[3]);
        cube.draw(gl, sc[4]);

	}
	public void setLocation(int index, float x, float y) {
        sc[index].x = x;
        sc[index].y = y;
    }

	public void setHeadr(int index,float y,float x){
		sc[index].headr = (float) Math.toDegrees(Math.atan2(y,x));
	}
	public void setBodyr(int index,float y,float x){
		sc[index].bodyr = (float) Math.toDegrees(Math.atan2(y,x));
	}
	public void setHeadr(int index,float d){
		sc[index].headr = d;
	}
	public void setBodyr(int index,float d){
		sc[index].bodyr = d;
	}
}