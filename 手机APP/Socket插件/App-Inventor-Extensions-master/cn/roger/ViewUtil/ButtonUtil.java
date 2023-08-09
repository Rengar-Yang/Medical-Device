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
import android.widget.Button;

@DesignerComponent(version = ButtonUtil.VERSION,
    description = "由Roger young创作，可以做工具",
    category = ComponentCategory.EXTENSION,
    nonVisible = true,
    iconName = "images/extension.png")

@SimpleObject(external = true)

public class ButtonUtil extends TextViewUtil{
    public static final int VERSION = 1;
    private static final String LOG_TAG = "ButtonUtil";
    private ComponentContainer container;
    private Context context;
	
    public ButtonUtil(ComponentContainer container) {
        super(container.$form());
        this.container = container;
        context = (Context) container.$context();
    }
    public ViewGroup findViewGroupById(int id) {
        return (ViewGroup)container.$form().findViewById(id);
    }
    @SimpleFunction(description = "start")
    public void NEW(int id,int parent,int width,int height) {
        Button button = new Button(context);
        button.setId(id);
        button.setLayoutParams(new ViewGroup.LayoutParams(width,height));
        findViewGroupById(parent).addView(button);
        this.id = id;
    }
}
