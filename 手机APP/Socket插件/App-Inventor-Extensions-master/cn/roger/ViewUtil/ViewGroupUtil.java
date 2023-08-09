package cn.roger.ViewUtil;

import com.google.appinventor.components.annotations.*;
import com.google.appinventor.components.common.ComponentCategory;
import com.google.appinventor.components.runtime.*;
import com.google.appinventor.components.runtime.util.*;
import com.google.appinventor.components.runtime.errors.YailRuntimeError;
import android.view.ViewPropertyAnimator;
import android.animation.ValueAnimator;
import android.content.Context;
import android.widget.TextView;
import android.view.ViewGroup;
import android.view.View;
import android.widget.RelativeLayout;

@DesignerComponent(version = ViewGroupUtil.VERSION,
    description = "由Roger young创作，可以做工具",
    category = ComponentCategory.EXTENSION,
    nonVisible = true,
    iconName = "images/extension.png")

@SimpleObject(external = false)

public abstract class ViewGroupUtil extends ViewUtil{
    public static final int VERSION = 1;
    private static final String LOG_TAG = "ViewGroup";
    private ComponentContainer container;
    private Context context;
	
    public ViewGroupUtil(ComponentContainer container) {
        super(container.$form());
        this.container = container;
        context = (Context) container.$context();
    }
    public abstract void NEW(int id,int parent,int width,int height);
    public ViewGroup findViewGroupById(int id) {
        return (ViewGroup)container.$form().findViewById(id);
    }
    @SimpleFunction(description = "start")
    public void addView(int viewId) {
        findViewGroupById(id).addView(findViewById(viewId));
    }
    @SimpleFunction(description = "start")
    public void addViewAt(int viewId,int index) {
        findViewGroupById(id).addView(findViewById(viewId),index);
    }
    @SimpleFunction(description = "start")
    public int getChildAt(int index) {
        return findViewGroupById(id).getChildAt(index).getId();
    }
    @SimpleFunction(description = "start")
    public int getChildCount() {
        return findViewGroupById(id).getChildCount();
    }
    @SimpleFunction(description = "start")
    public void removeAllViews() {
        findViewGroupById(id).removeAllViews();
    }
    @SimpleFunction(description = "start")
    public void removeView(int viewId) {
        findViewGroupById(id).removeView(findViewById(viewId));
    }
    @SimpleFunction(description = "start")
    public void removeViewAt(int index) {
        findViewGroupById(id).removeViewAt(index);
    }
    @SimpleFunction(description = "start")
    public void removeViews(int start,int count) {
        findViewGroupById(id).removeViews(start,count);
    }
}
