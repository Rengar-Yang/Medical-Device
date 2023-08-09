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

class Ground {
	private FloatBuffer mVertexBuffer;
	private float vertices[];
	public Ground(Object[] f) {
		vertices = new float[f.length];
		for(int i = 0;i < f.length;i++){
			vertices[i] = getFloat(f[i]);
		}
		ByteBuffer byteBuf = ByteBuffer.allocateDirect(vertices.length * 4);
		byteBuf.order(ByteOrder.nativeOrder());
		mVertexBuffer = byteBuf.asFloatBuffer();
		mVertexBuffer.put(vertices);
		mVertexBuffer.position(0);
	}
	public void draw(GL10 gl) {
		gl.glFrontFace(GL10.GL_CW);
		//gl.glShadeModel(GL10.GL_FLAT);
		gl.glVertexPointer(3, GL10.GL_FLOAT, 0, mVertexBuffer);
		gl.glEnableClientState(GL10.GL_VERTEX_ARRAY);
		gl.glColor4f(1f,1f,1f,1f);
		gl.glDrawArrays(GL10.GL_TRIANGLE_STRIP,0, vertices.length/3);
		gl.glDisableClientState(GL10.GL_VERTEX_ARRAY);
	}
	public boolean out(Car car){
		boolean b = false;
		for(int i = 0;i < vertices.length-6;i += 6){
			float x1 = vertices[i]   - car.x;
			float y1 = vertices[i+1] - car.y;
			float x2 = vertices[i+3] - car.x;
			float y2 = vertices[i+4] - car.y;
			float x3 = vertices[i+6] - car.x;
			float y3 = vertices[i+7] - car.y;
			float x4 = vertices[i+9] - car.x;
			float y4 = vertices[i+10] - car.y;
			if(((x1*y2-x2*y1)*(x3*y4-x4*y3)<0 
				&& (x1*y3-x3*y1)*(x2*y4-x4*y2)<0))
				b = true;
		}
		return !b;
	}
	public float getFloat(Object o){
		return (float)((DFloNum)o).doubleValue();
	}
}