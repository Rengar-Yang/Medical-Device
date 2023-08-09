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

@DesignerComponent(version = TextViewUtil.VERSION,
    description = "由Roger young创作，可以做工具",
    category = ComponentCategory.EXTENSION,
    nonVisible = true,
    iconName = "images/extension.png")

@SimpleObject(external = true)

public class TextViewUtil extends ViewUtil{
    public static final int VERSION = 1;
    private static final String LOG_TAG = "TextViewUtil";
    private ComponentContainer container;
    private Context context;
	
    public TextViewUtil(ComponentContainer container) {
        super(container.$form());
        this.container = container;
        context = (Context) container.$context();
    }
    public TextView findTextViewById(int id) {
        return (TextView)container.$form().findViewById(id);
    }
    public ViewGroup findViewGroupById(int id) {
        return (ViewGroup)container.$form().findViewById(id);
    }
    @SimpleFunction(description = "start")
    public void NEW(int id,int parent,int width,int height) {
        TextView textView = new TextView(context);
        textView.setId(id);
        textView.setTextColor(0xffff0000);
        textView.setLayoutParams(new ViewGroup.LayoutParams(width,height));
        findViewGroupById(parent).addView(textView);
        this.id = id;
    }
    @SimpleFunction(description = "start")
    public String getText() {
        return findTextViewById(id).getText().toString();
    }
    @SimpleFunction(description = "start")
    public int getCurrentTextColor() {
        return findTextViewById(id).getCurrentTextColor();
    }
    @SimpleFunction(description = "start")
    public float getTextSize() {
        return findTextViewById(id).getTextSize();
    }
    @SimpleFunction(description = "start")
    public void setHint(String text) {
        findTextViewById(id).setHint(text);
    }
    @SimpleFunction(description = "start")
    public void setText(String text) {
        findTextViewById(id).setText(text);
    }
    @SimpleFunction(description = "start")
    public void setTextColor(int color) {
        findTextViewById(id).setTextColor(color);
    }
    @SimpleFunction(description = "start")
    public void setTextSize(float size) {
        findTextViewById(id).setTextSize(size);
    }
}
