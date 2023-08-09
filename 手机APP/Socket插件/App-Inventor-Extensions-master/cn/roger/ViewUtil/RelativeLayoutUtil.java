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

@DesignerComponent(version = RelativeLayoutUtil.VERSION,
    description = "由Roger young创作，可以做工具",
    category = ComponentCategory.EXTENSION,
    nonVisible = true,
    iconName = "images/extension.png")

@SimpleObject(external = true)

public class RelativeLayoutUtil extends ViewGroupUtil{
    public static final int VERSION = 1;
    private static final String LOG_TAG = "RelativeLayoutUtil";
    private ComponentContainer container;
    private Context context;
	
    public RelativeLayoutUtil(ComponentContainer container) {
        super(container.$form());
        this.container = container;
        context = (Context) container.$context();
    }
    public ViewGroup findViewGroupById(int id) {
        return (ViewGroup)container.$form().findViewById(id);
    }
    @SimpleFunction(description = "start")
    public void NEW(int id,int parent,int width,int height) {
        RelativeLayout relativeLayout = new RelativeLayout(context);
        relativeLayout.setId(id);
        relativeLayout.setLayoutParams(new RelativeLayout.LayoutParams(width,height));
        if(parent == -1)
            container.$form().setContentView(relativeLayout);
        else
            findViewGroupById(parent).addView(relativeLayout);
        this.id = id;
    }
    @SimpleFunction(description = "start")
    public void addRule(int verb,int anchor) {
        ((RelativeLayout.LayoutParams)findViewById(id).getLayoutParams()).addRule(verb,anchor);
    }
}
