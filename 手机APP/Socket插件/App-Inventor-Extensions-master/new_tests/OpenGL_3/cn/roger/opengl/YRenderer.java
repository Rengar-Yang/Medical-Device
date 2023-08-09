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

class YRenderer implements GLSurfaceView.Renderer {
	public volatile CubeUtil cu = new CubeUtil();
    private Ground g = new Ground();
    public int h;
    public volatile float rox;
    public volatile float roy;
    int t = 0;
    public int w;
    public volatile float x = 0.0f;
    public volatile float y = 0.0f;
    volatile YGLSurfaceView ygv;

	public YRenderer(){
		ygv = y;
	}
	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
		gl.glClearColor(0f, 0f, 0f, 0.0f);
		gl.glClearDepthf(1.0f);
		gl.glEnable(GL10.GL_DEPTH_TEST);
		gl.glDepthFunc(GL10.GL_LEQUAL);
		gl.glEnable(GL10.GL_DEPTH_TEST);
	}
	public void onSurfaceChanged(GL10 gl, int width, int height) {
		// Set the OpenGL viewport to fill the entire surface.
		//gl.glViewport(0, 0, width, height);
		w=width;h=height;
		gl.glViewport(0, 0, width, height);
		gl.glMatrixMode(GL10.GL_PROJECTION);
		gl.glLoadIdentity();
		GLU.gluPerspective(gl, 45.0f, (float)width / (float)height, 0.1f, 100.0f);
		GLU.gluLookAt(gl,0.0f,0.0f,10.0f,  0.0f,0.0f,0.0f,  0.0f,1.0f,0.0f);
		gl.glViewport(0, 0, width, height);
		gl.glMatrixMode(GL10.GL_MODELVIEW);
		gl.glLoadIdentity();
	}
	public void onDrawFrame(GL10 gl) {
		gl.glClear(gl.GL_COLOR_BUFFER_BIT);
        x += ygv.fx;
        y += ygv.fy;
        if (x > 200.0f) {
            x = 200.0f;
        }
        if (y > 200.0f) {
            y = 200.0f;
        }
        if (x < -200.0f) {
            x = -200.0f;
        }
        if (y < -200.0f) {
            y = -200.0f;
        }
        gl.glLoadIdentity();
        gl.glRotatef(-roy, 1.0f, 0.0f, 0.0f);
        gl.glRotatef(rox, 0.0f, 1.0f, 0.0f);
        gl.glTranslatef(-x, 0.0f, -y);
        g.draw(gl);
        cu.setLocation(0, -x, -y);
        cu.setHeadr(0, rox);
        cu.setBodyr(0, ygv.fy, ygv.fx);
        cu.draw(gl);
        gl.glLoadIdentity();

		t++;
	}
	public int getT(){
		return t;
	}
}