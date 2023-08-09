package cn.roger.Util;

import com.google.appinventor.components.annotations.*;
import com.google.appinventor.components.common.ComponentCategory;
import com.google.appinventor.components.runtime.*;
import com.google.appinventor.components.runtime.util.*;
import com.google.appinventor.components.runtime.errors.YailRuntimeError;
import android.view.ViewPropertyAnimator;
import android.animation.ValueAnimator;
import android.content.Context;
import android.graphics.Color;
import android.view.View;
import android.graphics.drawable.Drawable;

@DesignerComponent(version = Util.VERSION,
    description = "由Roger young创作，可以做工具",
    category = ComponentCategory.EXTENSION,
    nonVisible = true,
    iconName = "images/extension.png")

@SimpleObject(external = true)

public class Util  extends AndroidNonvisibleComponent{
    public static final int VERSION = 1;
    private static final String LOG_TAG = "Util";
    private ComponentContainer container;
    private Context context;
	
    public Util(ComponentContainer container) {
        super(container.$form());
        this.container = container;
        context = (Context) container.$context();
    }
    @SimpleFunction(description = "start")
    public int dp2px(float dp) {
        final float scale = context.getResources().getDisplayMetrics().density;
        return (int) (dp * scale + 0.5f);
    }
    @SimpleFunction(description = "start")
    public int px2dp(float px) {
        final float scale = context.getResources().getDisplayMetrics().density;
        return (int) (px / scale + 0.5f);
    }
    @SimpleFunction(description = "start")
    public int px2sp(float px) {
        final float fontScale = context.getResources().getDisplayMetrics().scaledDensity;
        return (int) (px / fontScale + 0.5f);
    }
    @SimpleFunction(description = "start")
    public int sp2px(float sp) {
        final float fontScale = context.getResources().getDisplayMetrics().scaledDensity;
        return (int) (sp * fontScale + 0.5f);
    }

    @SimpleFunction(description = "start")
    public int string2color(String s) {
        return Color.parseColor(s);
    }
    @SimpleFunction(description = "start")
    public void setRootView(int id) {
        container.$form().setContentView((View)findViewById(id));
    }
    @SimpleFunction(description = "start")
    public void setTheme(int themeId) {
        container.$form().setTheme(themeId);
    }
    @SimpleFunction(description = "start")
    public Object NULL() {
        return null;
    }
}
