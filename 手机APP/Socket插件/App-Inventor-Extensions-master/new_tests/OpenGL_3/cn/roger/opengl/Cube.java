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
	private FloatBuffer mVertexBuffer1;
	private FloatBuffer mVertexBuffer2;
	private ByteBuffer mIndexBuffer;
	private ByteBuffer mIndexBuffer2;
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
		0, 4, 1, 5, 4, 1,
		1, 5, 6, 1, 6, 2,
		2, 6, 7, 2, 7, 3,
		3, 7, 4, 4, 0, 3,
		4, 7, 6, 0, 3, 1,
		5, 4, 6, 3, 1, 2
	};
	private byte indices2[] = {
		0, 1, 1, 2,
		2, 3, 3, 0,
		4, 5, 5, 6,
		6, 7, 7, 4,
		3, 7, 2, 6,
		1, 5, 0, 4,
	};
	public Cube() {
		ByteBuffer byteBuf = ByteBuffer.allocateDirect(vertices1.length * 4);
		byteBuf.order(ByteOrder.nativeOrder());
		mVertexBuffer1 = byteBuf.asFloatBuffer();
		mVertexBuffer1.put(vertices1);
		mVertexBuffer1.position(0);

		byteBuf = ByteBuffer.allocateDirect(vertices2.length * 4);
		byteBuf.order(ByteOrder.nativeOrder());
		mVertexBuffer2 = byteBuf.asFloatBuffer();
		mVertexBuffer2.put(vertices2);
		mVertexBuffer2.position(0);
		
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
		gl.glTranslatef(-sc.x, 0 ,-sc.y);
		gl.glVertexPointer(3, GL10.GL_FLOAT, 0, mVertexBuffer1);
		gl.glColor4f(sc.r,sc.g,sc.b,1f);
		gl.glEnableClientState(GL10.GL_VERTEX_ARRAY);
		gl.glRotatef(-sc.bodyr,0f,1f,0f);
		gl.glDrawElements(GL10.GL_TRIANGLES, 36, GL10.GL_UNSIGNED_BYTE,mIndexBuffer);
		gl.glColor4f(1f,1f,1f,1f);
		gl.glLineWidth(5f);
		gl.glDrawElements(GL10.GL_LINES, 24, GL10.GL_UNSIGNED_BYTE,mIndexBuffer2);
		gl.glRotatef(sc.bodyr,0f,1f,0f);
		gl.glDisableClientState(GL10.GL_VERTEX_ARRAY);


		gl.glVertexPointer(3, GL10.GL_FLOAT, 0, mVertexBuffer2);
		gl.glColor4f(sc.r,sc.g,sc.b,1f);
		gl.glEnableClientState(GL10.GL_VERTEX_ARRAY);
		gl.glRotatef(-sc.headr,0f,1f,0f);
		gl.glDrawElements(GL10.GL_TRIANGLES, 36, GL10.GL_UNSIGNED_BYTE,mIndexBuffer);
		gl.glColor4f(1f,1f,1f,1f);
		gl.glLineWidth(5f);
		gl.glDrawElements(GL10.GL_LINES, 24, GL10.GL_UNSIGNED_BYTE,mIndexBuffer2);
		gl.glRotatef(sc.headr,0f,1f,0f);
		gl.glDisableClientState(GL10.GL_VERTEX_ARRAY);
		gl.glTranslatef(sc.x,0,sc.y);
	}
}