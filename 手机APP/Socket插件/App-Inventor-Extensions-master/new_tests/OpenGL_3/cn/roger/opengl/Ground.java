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

class Ground {
	private FloatBuffer mVertexBuffer;
	private ByteBuffer mIndexBuffer;
	float max = 200f;
	float width = 0.1f;
	private float vertices[] = new float[21*12];
	private byte indices[] = {
		 0, 1, 2, 1, 2, 3,
		 4, 5, 6, 5, 6, 7,
		 8, 9,10, 9,10,11,
		12,13,14,13,14,15,
		16,17,18,17,18,19,
		20,21,22,21,22,23,
		24,25,26,25,26,27,
		28,29,30,29,30,31,
		32,33,34,33,34,35,
		36,37,38,37,38,39,
		40,41,42,41,42,43,
		44,45,46,45,46,47,
		48,49,50,49,50,51,
		52,53,54,53,54,55,
		56,57,58,57,58,59,
		60,61,62,61,62,63,
		64,65,66,65,66,67,
		68,69,70,69,70,71,
		72,73,74,73,74,75,
		76,77,78,77,78,79,
		80,81,82,81,82,83,

	};
	public Ground() {
		int tmp = 0;
		for(float f=-max;f<=max;f+=20f,tmp+=12){
			vertices[tmp] = f-width;
			vertices[tmp+1] = -2f;
			vertices[tmp+2] = -(max+width);

			vertices[tmp+3] = f+width;
			vertices[tmp+4] = -2f;
			vertices[tmp+5] = -(max+width);

			vertices[tmp+6] = f-width;
			vertices[tmp+7] = -2f;
			vertices[tmp+8] = (max+width);

			vertices[tmp+9] = f+width;
			vertices[tmp+10] = -2f;
			vertices[tmp+11] = (max+width);
		}
		ByteBuffer byteBuf = ByteBuffer.allocateDirect(vertices.length * 4);
		byteBuf.order(ByteOrder.nativeOrder());
		mVertexBuffer = byteBuf.asFloatBuffer();
		mVertexBuffer.put(vertices);
		mVertexBuffer.position(0);
		
		mIndexBuffer = ByteBuffer.allocateDirect(indices.length);
		mIndexBuffer.put(indices);
		mIndexBuffer.position(0);
	}
	public void draw(GL10 gl) {
		gl.glFrontFace(GL10.GL_CW);
		//gl.glShadeModel(GL10.GL_FLAT);
		gl.glVertexPointer(3, GL10.GL_FLOAT, 0, mVertexBuffer);
		gl.glEnableClientState(GL10.GL_VERTEX_ARRAY);
		gl.glColor4f(1f,0.5f,1f,1f);
		gl.glDrawElements(GL10.GL_TRIANGLES, 126, GL10.GL_UNSIGNED_BYTE,mIndexBuffer);
		gl.glRotatef(90,0f,1f,0f);
		gl.glDrawElements(GL10.GL_TRIANGLES, 126, GL10.GL_UNSIGNED_BYTE,mIndexBuffer);
		gl.glRotatef(-90,0f,1f,0f);
		gl.glDisableClientState(GL10.GL_VERTEX_ARRAY);
	}
}