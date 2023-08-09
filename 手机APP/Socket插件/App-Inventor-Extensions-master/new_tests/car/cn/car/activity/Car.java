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

import gnu.math.DFloNum;
public class Car{
	public volatile float x,y;
	public volatile float r;
	public volatile float p_m = 0.002f;
	public volatile float vmax= 0.15f;
	public volatile float v= 0.01f;
	public volatile float vx,vy;
	public volatile boolean running = true;
	private FloatBuffer mVertexBuffer;
	private ByteBuffer mIndexBuffer;
	private float vertices[] = {
		1.0f, 0.0f, 0.0f,
		-1.0f, 1.0f,0.0f,
		-0.5f, 0.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
	};
	private byte indices[] = {
		0, 1, 2, 0, 2, 3,
	};
	public Car(Object[] f){
		this.x = getFloat(f[0]);
		this.y = getFloat(f[1]);
		this.r = getFloat(f[2]);

		ByteBuffer byteBuf = ByteBuffer.allocateDirect(vertices.length * 4);
		byteBuf.order(ByteOrder.nativeOrder());
		mVertexBuffer = byteBuf.asFloatBuffer();
		mVertexBuffer.put(vertices);
		mVertexBuffer.position(0);

		mIndexBuffer = ByteBuffer.allocateDirect(indices.length);
		mIndexBuffer.put(indices);
		mIndexBuffer.position(0);
	}
	public void updateLocation(){
		if(running){
			v += p_m*(1/v-1/vmax);
			vx=FloatMath.cos((float)Math.toRadians(r))*v;
			vy=FloatMath.sin((float)Math.toRadians(r))*v;
			x+=vx;
			y+=vy;
		}
	}
	public void setRunning(boolean b){
		running = b;
	}
	public void draw(GL10 gl){
		gl.glFrontFace(GL10.GL_CW);
		gl.glTranslatef(x, y ,0);
			gl.glVertexPointer(3, GL10.GL_FLOAT, 0, mVertexBuffer);
			gl.glColor4f(0.5f,0.5f,0.5f,1f);
			gl.glEnableClientState(GL10.GL_VERTEX_ARRAY);
			gl.glRotatef(-r,0f,0f,-1f);
			gl.glDrawArrays(GL10.GL_TRIANGLE_FAN,0, 4);
			gl.glRotatef(r,0f,0f,-1f);
			gl.glDisableClientState(GL10.GL_VERTEX_ARRAY);
		gl.glTranslatef(-x, -y ,0);
	}
	public void move(GL10 gl){
		gl.glTranslatef(-x*.9f, -y*.9f ,0);
	}
	public void catching(float f){//f为圆心到车的角度
		f+=90f;
		v *= FloatMath.cos((float)Math.toRadians(f-r));
		r = f;
		if(v<0){
			v = -v;
			r+=180;
		}
	}
	public float getFloat(Object o){
		return (float)((DFloNum)o).doubleValue();
	}
}