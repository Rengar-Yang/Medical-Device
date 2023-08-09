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
    private Cube c1 = new Cube(-3.0f, -3.0f, -5.0f, 0.5f, 0.5f, 0.5f);
    private Cube c2 = new Cube(3.0f, 3.0f, -5.0f, 0.5f, 0.0f, 1.0f);
    public volatile float rox;
    public volatile float roy;
    int t = 0;

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
		gl.glClear(16640);
        gl.glLoadIdentity();
        gl.glRotatef(this.roy, 1.0f, 0.0f, 0.0f);
        gl.glRotatef(this.rox, 0.0f, 1.0f, 0.0f);
        c1.draw(gl);
        c2.draw(gl);
        gl.glLoadIdentity();
        t++;

	}
	public int getT(){
		return t;
	}
}