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
import java.nio.ByteOrder;
import android.util.FloatMath;

public class ControlBar{
	public volatile float rox,roy;
	public volatile float prx,pry;
	public volatile float plx=-200,ply=-200;
	public volatile float v=0.8f;
	public volatile float max=80f,min=-10f;
	public volatile SimpleCube controler;
	public volatile float x,y;

	private FloatBuffer mVertexBuffer1;
	private FloatBuffer mVertexBuffer2;
	private ByteBuffer mIndexBuffer;
	private float vertices1[] = new float[30*3];
	private float vertices2[] = new float[30*3];
	private byte indices[] = new byte[30];
	public ControlBar(SimpleCube sc){
		rox = 0f;
		roy = 0f;
		controler = sc;
		vertices1[0] = 0;
		vertices1[1] = 0;
		vertices1[2] = 0;
		indices[0] = 0;
		for(int i = 1;i < 30;i++){
			vertices1[3*i] = FloatMath.cos((float)Math.toRadians((i-1)*(360.0f/28)))*200;
			vertices1[3*i+1] = FloatMath.sin((float)Math.toRadians((i-1)*(360.0f/28)))*200;
			vertices1[3*i+2] = 0;
			vertices2[3*i] = FloatMath.cos((float)Math.toRadians((i-1)*(360.0f/28)))*80;
			vertices2[3*i+1] = FloatMath.sin((float)Math.toRadians((i-1)*(360.0f/28)))*80;
			vertices2[3*i+2] = 0;
			indices[i] = (byte)i;
		}
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
	}
	public void setP(boolean b,float f1,float f2){
		if(b){
			prx = f1;
			pry = f2;
		}else{
			plx = f1;
			ply = f2;
			controler.setRunning(false);
		}
	}
	public void updateP(boolean b,float x,float y){
		if(b){
			rox += (x - prx)*v;
			roy -= (y - pry)*v;
			if(roy>-min)roy=-min;
			if(roy<-max)roy=-max;
			prx = x;
			pry = y;
			controler.setHeadr(rox);
		}else{
			controler.setBodyr(y-ply,x-plx);
			controler.setRunning(true);
			this.x = x;
			this.y = y;
		}
	}
	public void draw(GL10 gl) {
		gl.glVertexPointer(3, GL10.GL_FLOAT, 0, mVertexBuffer1);
		gl.glColor4f(1f,1f,1f,0.3f);
		gl.glEnableClientState(GL10.GL_VERTEX_ARRAY);
		gl.glTranslatef(plx, ply ,0);
		gl.glDrawElements(GL10.GL_TRIANGLE_FAN, 30, GL10.GL_UNSIGNED_BYTE,mIndexBuffer);
		gl.glTranslatef(-plx, -ply ,0);
		gl.glDisableClientState(GL10.GL_VERTEX_ARRAY);


		gl.glVertexPointer(3, GL10.GL_FLOAT, 0, mVertexBuffer2);
		gl.glColor4f(0.5f,0.5f,0.5f,0.8f);
		gl.glEnableClientState(GL10.GL_VERTEX_ARRAY);
		gl.glTranslatef(x, y ,0);
		gl.glDrawElements(GL10.GL_TRIANGLE_FAN, 30, GL10.GL_UNSIGNED_BYTE,mIndexBuffer);
		gl.glTranslatef(-x, -y ,0);
		gl.glDisableClientState(GL10.GL_VERTEX_ARRAY);
	}
}