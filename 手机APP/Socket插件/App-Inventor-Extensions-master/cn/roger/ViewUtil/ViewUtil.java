package cn.roger.ViewUtil;

import com.google.appinventor.components.annotations.*;
import com.google.appinventor.components.common.ComponentCategory;
import com.google.appinventor.components.runtime.*;
import com.google.appinventor.components.runtime.util.*;
import com.google.appinventor.components.runtime.errors.YailRuntimeError;
import android.content.Context;
import android.view.ViewGroup;
import android.view.View;
import android.widget.RelativeLayout;
import android.graphics.drawable.Drawable;
import android.graphics.Color;


@DesignerComponent(version = ViewUtil.VERSION,
    description = "由Roger young创作，可以做工具",
    category = ComponentCategory.EXTENSION,
    nonVisible = true,
    iconName = "images/extension.png")

@SimpleObject(external = false)

public abstract class ViewUtil extends IDUtil{
    public static final int VERSION = 1;
    private static final String LOG_TAG = "ViewUtil";
    private ComponentContainer container;
    private Context context;

    public static final int VISIBLE = 0x00000000;
    public static final int INVISIBLE = 0x00000004;
    public static final int GONE = 0x00000008;
	
    public ViewUtil(ComponentContainer container) {
        super(container.$form());
        this.container = container;
        context = (Context) container.$context();
    }
    public abstract void NEW(int id,int parent,int width,int height);
    
    @SimpleFunction(description = "start")
    public void bringToFront() {
        findViewById(id).bringToFront();
    }
    @SimpleFunction(description = "start")
    public void clearAnimation() {
        findViewById(id).clearAnimation();
    }
    @SimpleFunction(description = "start")
    public int getVisibility() {
        return findViewById(id).getVisibility();
    }
    @SimpleFunction(description = "start")
    public void invalidate() {
        findViewById(id).invalidate();
    }
    @SimpleFunction(description = "start")
    public void setBackgroundColor(String color) {
        findViewById(id).setBackgroundColor(Color.parseColor(color));
    }
    @SimpleFunction(description = "start")
    public void setElevation(float elevation) {
        findViewById(id).setElevation(elevation);
    }
    @SimpleFunction(description = "start")
    public void setKeepScreenOn(boolean keepScreenOn) {
        findViewById(id).setKeepScreenOn(keepScreenOn);
    }
    @SimpleFunction(description = "start")
    public void setMargins(int left, int top, int right, int bottom) {
        ((ViewGroup.MarginLayoutParams)findViewById(id).getLayoutParams()).setMargins(left,top,right,bottom);
    }
    @SimpleFunction(description = "start")
    public void setPadding(int left, int top, int right, int bottom) {
        findViewById(id).setPadding(left,top,right,bottom);
    }
    @SimpleFunction(description = "start")
    public void setRotation(float rotation) {
        findViewById(id).setRotation(rotation);
    }
    @SimpleFunction(description = "start")
    public void setRotationX(float rotationX) {
        findViewById(id).setRotationX(rotationX);
    }
    @SimpleFunction(description = "start")
    public void setRotationY(float rotationY) {
        findViewById(id).setRotationY(rotationY);
    }
    @SimpleFunction(description = "start")
    public void setTag(Object tag) {
        findViewById(id).setTag(tag);
    }
    @SimpleFunction(description = "start")
    public void setTextAlignment(int textAlignment) {
        findViewById(id).setTextAlignment(textAlignment);
    }
    @SimpleFunction(description = "start")
    public void setVisibility(int visibility) {
        findViewById(id).setVisibility(visibility);
    }
    @SimpleFunction(description = "start")
    public void setX(float x) {
        findViewById(id).setX(x);
    }
    @SimpleFunction(description = "start")
    public void setY(float y) {
        findViewById(id).setY(y);
    }
    @SimpleFunction(description = "start")
    public void setZ(float z) {
        findViewById(id).setZ(z);
    }
}
