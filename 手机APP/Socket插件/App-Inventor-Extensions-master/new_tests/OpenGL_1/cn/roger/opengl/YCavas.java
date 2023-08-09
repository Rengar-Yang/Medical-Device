package cn.roger.opengl;

import com.google.appinventor.components.annotations.*;
import com.google.appinventor.components.common.ComponentCategory;
import com.google.appinventor.components.runtime.*;
import com.google.appinventor.components.runtime.util.*;
import com.google.appinventor.components.runtime.errors.YailRuntimeError;
import android.opengl.GLSurfaceView;

import android.content.Context;
import android.view.ViewGroup;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.opengl.GLU;
import java.nio.FloatBuffer;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

@DesignerComponent(version = YCavas.VERSION,
    description = "by Roger Young",
    category = ComponentCategory.EXTENSION,
    nonVisible = true,
    iconName = "images/extension.png")

@SimpleObject(external = true)

public class YCavas extends AndroidNonvisibleComponent {
    public static final int VERSION = 1;
    private static final String LOG_TAG = "YCavas";
    private GLSurfaceView glSurfaceView;
    private Context context;

    public YCavas(ComponentContainer container) {
        super(container.$form());
    }
    @SimpleFunction(description = "init")
    public void init(Object o){
        /*
			  水平布局和竖直布局的共同父类就是HVArrangement。它封装了ViewGroup，
			将之设计成在App Inventor中易于操作的样式。
			  我们可以getView()得到ViewGroup，进行更自由的处理。
			  如果对ViewGroup有什么疑问，可能需要了解"Android View体系"
		*/
		//获取ViewGroup，我们的控件将填充到它里面
        ViewGroup vg = (ViewGroup)((HVArrangement)o).getView();

        glSurfaceView = new GLSurfaceView(context);
		//设置渲染器为YRenderer，由它掌控图像绘制
        glSurfaceView.setRenderer(new YRenderer());
        //将View添加至ViewGroup中
        vg.addView(glSurfaceView);
        glSurfaceView.setZ(view);
    }

    private class YRenderer implements GLSurfaceView.Renderer {
        private Cube mCube = new Cube();
        private float mCubeRotation;
		
		//初始化，创建图形上下文
        public void onSurfaceCreated(GL10 gl, EGLConfig config) {
            //设置深度缓冲初始值
            gl.glClearDepthf(1.0f);
            //启用深度测试
            gl.glEnable(GL10.GL_DEPTH_TEST);
            //深度值小于或等于参考值则通过
            gl.glDepthFunc(GL10.GL_LEQUAL);
			//深度测试，用一句话说
        }
		
		//当大小被改变时
        public void onSurfaceChanged(GL10 gl, int width, int height) {
            gl.glViewport(0, 0, width, height);
            //将当前矩阵指定为投影矩阵
            gl.glMatrixMode(GL10.GL_PROJECTION);
            //复位变换
            gl.glLoadIdentity();
            //设置透视投影
            GLU.gluPerspective(gl, 45.0f, (float)width / (float)height, 0.1f, 100.0f);
            gl.glViewport(0, 0, width, height);
            //再设回模型矩阵
            gl.glMatrixMode(GL10.GL_MODELVIEW);
            gl.glLoadIdentity();
        }
		
		//画好每一帧
        public void onDrawFrame(GL10 gl) {
            gl.glClear(GL10.GL_COLOR_BUFFER_BIT | GL10.GL_DEPTH_BUFFER_BIT);
            gl.glLoadIdentity();
            //平移，我们的立方体的中心是(0,0,0)
			//绘制之前要把它移到我们想画的地方，不然就画在脸上了
            gl.glTranslatef(0.0f, 0.0f, -10f);
            //旋转
            gl.glRotatef(54.73561f, 1.0f, 0.0f, 1.0f);
            //再旋转
            gl.glRotatef(mCubeRotation, 1.0f, 1.0f, -1.0f);
            //画
            mCube.draw(gl);
            gl.glLoadIdentity();
            //每一次绘制都把旋转角度递减，造成旋转的样子
            mCubeRotation -= 0.5f;
        }
    }
    class Cube {
        //这几个都是用底层实现数组来加速访问
        private FloatBuffer mVertexBuffer;
        private FloatBuffer mColorBuffer;
        private ByteBuffer mIndexBuffer;
        //立方体的定点，一行一个点
        private float vertices[] = {
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,
            -1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f
        };
        //立方体的颜色索引，一行一个点
        private float colors[] = {
            0.0f, 1.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.5f, 0.0f, 1.0f,
            1.0f, 0.5f, 0.0f, 1.0f,
            1.0f, 0.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 1.0f
        };
        //立方体的定点绘制索引，每三个画一个三角形
        private byte indices[] = {
            0, 4, 5,    0, 5, 1,
            1, 5, 6,    1, 6, 2,
            2, 6, 7,    2, 7, 3,
            3, 7, 4,    3, 4, 0,
            4, 7, 6,    4, 6, 5,
            3, 0, 1,    3, 1, 2
        };
        public Cube() {
            //在构造函数中对各种Buffer们进行初始化
            ByteBuffer byteBuf = ByteBuffer.allocateDirect(vertices.length * 4);
            byteBuf.order(ByteOrder.nativeOrder());
            mVertexBuffer = byteBuf.asFloatBuffer();
            mVertexBuffer.put(vertices);
            mVertexBuffer.position(0);
            byteBuf = ByteBuffer.allocateDirect(colors.length * 4);
            byteBuf.order(ByteOrder.nativeOrder());
            mColorBuffer = byteBuf.asFloatBuffer();
            mColorBuffer.put(colors);
            mColorBuffer.position(0);
            mIndexBuffer = ByteBuffer.allocateDirect(indices.length);
            mIndexBuffer.put(indices);
            mIndexBuffer.position(0);
        }
        public void draw(GL10 gl) {
            //设置三角形的前面是逆时针形成的面
            //现在没什么用，如果正面反面不一样的话会用到
            gl.glFrontFace(GL10.GL_CW);
            //定点缓冲
            gl.glVertexPointer(3, GL10.GL_FLOAT, 0, mVertexBuffer);
            //颜色索引
            gl.glColorPointer(4, GL10.GL_FLOAT, 0, mColorBuffer);
            //启用，画画之前先通知
            gl.glEnableClientState(GL10.GL_VERTEX_ARRAY);
            gl.glEnableClientState(GL10.GL_COLOR_ARRAY);
            //画三角形，共36个点
            gl.glDrawElements(GL10.GL_TRIANGLES, 36, GL10.GL_UNSIGNED_BYTE,mIndexBuffer);
            //禁用，画完也要通知
            gl.glDisableClientState(GL10.GL_VERTEX_ARRAY);
            gl.glDisableClientState(GL10.GL_COLOR_ARRAY);
        }
    }
}