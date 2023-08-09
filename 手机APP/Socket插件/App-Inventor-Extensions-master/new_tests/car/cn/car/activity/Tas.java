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
class Tas {
	public volatile boolean catching = false;
	public volatile float r2 = 0f;

	public volatile Ta tas[];
	public Tas(Object[] f) {
		tas = new Ta[f.length/3];
		for(int i = 0;i < tas.length;i++){
			tas[i] = new Ta(getFloat(f[3*i]),getFloat(f[3*i+1]),getFloat(f[3*i+2]));
		}
	}
	public void draw(GL10 gl,Car car) {
		for(int i = 0;i < tas.length;i++){
			tas[i].draw(gl,car);
		}
	}
	void startCatch(Car car){
		catching =  true;
		for(int i = 0;i < tas.length;i++){
			if(tas[i].in(car)){
				tas[i].startCatch(car);
				break;
			}
		}
	}
	void endCatch(){
		catching =  false;
		for(int i = 0;i < tas.length;i++){
			tas[i].catching = false;
		}
	}
	public float getFloat(Object o){
		return (float)((DFloNum)o).doubleValue();
	}
}
class Ta{
	public volatile float x,y;
	public volatile float r;
	public volatile float rotate = 0f;
	public volatile boolean catching = false;
	public volatile float r2 = 0f;
	private FloatBuffer mVertexBuffer,line;
	private float vertices[] = {
		0.5f,0.288675134594813f,-0.3f,
		-0.5f,0.288675134594813f,-0.3f,
		0f,-0.577350269189626f,-0.3f,
		0.5f,0.288675134594813f,-0.3f,
	};
	private float lines[] = {
		19f,-14f,-0.3f,
		-20f,-15f,-0.3f,
	};
	Ta(float x,float y,float r){
		this.x = x;
		this.y = y;
		this.r = r;
		lines[0] = x;
		lines[1] = y;
		ByteBuffer byteBuf = ByteBuffer.allocateDirect(vertices.length * 4);
		byteBuf.order(ByteOrder.nativeOrder());
		mVertexBuffer = byteBuf.asFloatBuffer();
		mVertexBuffer.put(vertices);
		mVertexBuffer.position(0);
		byteBuf = ByteBuffer.allocateDirect(lines.length * 4);
		byteBuf.order(ByteOrder.nativeOrder());
		line = byteBuf.asFloatBuffer();
		line.put(lines);
		line.position(0);
	}
	public void draw(GL10 gl,Car car) {
		gl.glColor4f(1f,1f,1f,1f);
		gl.glTranslatef(x, y ,0);
		gl.glRotatef(rotate,0f,0f,1f);
		gl.glVertexPointer(3, GL10.GL_FLOAT, 0, mVertexBuffer);
		gl.glEnableClientState(GL10.GL_VERTEX_ARRAY);
		gl.glDrawArrays(GL10.GL_LINE_STRIP,0, 4);
		gl.glRotatef(180,0f,0f,1f);
		gl.glDrawArrays(GL10.GL_LINE_STRIP,0, 4);
		gl.glRotatef(-180,0f,0f,1f);
		gl.glDisableClientState(GL10.GL_VERTEX_ARRAY);
		gl.glRotatef(-rotate,0f,0f,1f);
		gl.glTranslatef(-x, -y ,0);
		if(catching){
			line.put(3,car.x);
			line.put(4,car.y);
			line.position(0);
			gl.glLineWidth(3f);
			gl.glVertexPointer(3, GL10.GL_FLOAT, 0, line);
			gl.glEnableClientState(GL10.GL_VERTEX_ARRAY);
			if((car.x-x)*(car.x-x)+(car.y-y)*(car.y-y) > r2){
				gl.glColor4f(1f,0f,0f,1f);
				car.catching((float)Math.toDegrees(Math.atan2(y-car.y,x-car.x)));
			}else{
				r2 = (car.x-x)*(car.x-x)+(car.y-y)*(car.y-y);
				gl.glColor4f(0f,1f,0f,1f);
			}
			gl.glDrawArrays(GL10.GL_LINES,0, 2);
			gl.glDisableClientState(GL10.GL_VERTEX_ARRAY);
		}
		rotate += 2f;
	}
	public boolean in(Car car){
		if((car.x-x)*(car.x-x)+(car.y-y)*(car.y-y)<r*r)
			return true;
		return false;
	}
	void startCatch(Car car){
		catching =  true;
		r2 = (car.x-x)*(car.x-x)+(car.y-y)*(car.y-y);
	}
}