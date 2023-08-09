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

class Cube {
    float r,b,g;
    float x,y,z;
	private FloatBuffer mVertexBuffer1;
	private FloatBuffer mVertexBuffer2;
	private ByteBuffer mIndexBuffer;
	private float vertices1[] = {
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f
	};
	private float vertices2[] = {
		-0.5f, 1.0f, -0.5f,
		0.5f, 1.0f, -0.5f,
		0.5f, 2.0f, -0.5f,
		-0.5f, 2.0f, -0.5f,
		-0.5f, 1.0f, 0.5f,
		0.5f, 1.0f, 0.5f,
		0.5f, 2.0f, 0.5f,
		-0.5f, 2.0f, 0.5f,
	};
	private byte indices[] = {
		0, 4, 1,    5, 4, 1,
		1, 5, 6,    1, 6, 2,
		2, 6, 7,    2, 7, 3,
		3, 7, 4,    4, 0, 3,
		4, 7, 6,    0, 3, 1,
		5, 4, 6,    3, 1, 2
	};
	private byte indices2[] = {
		0, 1, 1, 2,
		2, 3, 3, 0,
		4, 5, 5, 6,
		6, 7, 7, 4,
		3, 7, 2, 6,
		1, 5, 0, 4,
	};
	public Cube(float fx, float fy, float fz, float fr, float fg, float fb) {
		this.x = fx;
        this.y = fy;
        this.z = fy;
        this.r = fr;
        this.b = fg;//原来就错的。。。
        this.b = fb;

		ByteBuffer byteBuf = ByteBuffer.allocateDirect(vertices1.length * 4);
		byteBuf.order(ByteOrder.nativeOrder());
		mVertexBuffer = byteBuf.asFloatBuffer();
		mVertexBuffer.put(vertices1);
		mVertexBuffer.position(0);
		
		mIndexBuffer = ByteBuffer.allocateDirect(indices.length);
		mIndexBuffer.put(indices);
		mIndexBuffer.position(0);
		
		mIndexBuffer2 = ByteBuffer.allocateDirect(indices2.length);
		mIndexBuffer2.put(indices2);
		mIndexBuffer2.position(0);
	}
	public void draw(GL10 gl,SimpleCube sc) {
		gl.glFrontFace(GL10.GL_CW);
		//gl.glShadeModel(GL10.GL_FLAT);
        gl.glTranslatef(-x, -y, -z);

		gl.glVertexPointer(3, GL10.GL_FLOAT, 0, mVertexBuffer1);
		gl.glColor4f(r,g,b,1f);
		gl.glLineWidth(3.5f);
		gl.glEnableClientState(GL10.GL_VERTEX_ARRAY);
		gl.glDrawElements(GL10.GL_TRIANGLES, 36, GL10.GL_UNSIGNED_BYTE,mIndexBuffer);
		gl.glColor4f(1f,1f,1f,1f);
		gl.glLineWidth(5f);
		gl.glDrawElements(GL10.GL_LINES, 24, GL10.GL_UNSIGNED_BYTE,mIndexBuffer2);
		gl.glDisableClientState(GL10.GL_VERTEX_ARRAY);
        gl.glTranslatef(x, y, z);
	}
}