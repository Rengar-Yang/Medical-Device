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
import android.widget.RelativeLayout;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.opengl.GLU;
import java.nio.FloatBuffer;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

@DesignerComponent(version = YCavas.VERSION,
    description = "by Roger Young3",
    category = ComponentCategory.EXTENSION,
    nonVisible = true,
    iconName = "images/extension.png")

@SimpleObject(external = true)

public class YCavas extends AndroidNonvisibleComponent {
    public static final int VERSION = 1;
    private static final String LOG_TAG = "YCavas";
	private YGLSurfaceView glSurfaceView;
	private ComponentContainer container;
    private Context context;
	
    public YCavas(ComponentContainer container) {
        super(container.$form());
        this.container = container;
        context = (Context) container.$context();
    }
	
    @SimpleFunction(description = "init")
    public void init2(Object o) {
        ViewGroup vg = (ViewGroup) ((HVArrangement) o).getView();
        glSurfaceView = new YGLSurfaceView(((HVArrangement) o).$context());
        glSurfaceView.setZOrderOnTop(true);
        glSurfaceView.setZOrderMediaOverlay(true);
        glSurfaceView.setZ(-100.0f);
        vg.addView(glSurfaceView);
        glSurfaceView.setZOrderOnTop(true);
        glSurfaceView.setZOrderMediaOverlay(true);
        glSurfaceView.setZ(-100.0f);
    }

    @SimpleFunction(description = "init")
    public void init1() {
        glSurfaceView = new YGLSurfaceView(context);
        container.$form().addContentView(glSurfaceView, new LayoutParams(-1, -1));
        glSurfaceView.setZ(-1.0f);
    }


    @SimpleFunction(description = "init")
    public int getT(){
        return glSurfaceView.getT();
    }
}