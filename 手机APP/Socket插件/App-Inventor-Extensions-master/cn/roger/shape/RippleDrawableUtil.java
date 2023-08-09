package cn.roger.shape;

import com.google.appinventor.components.annotations.*;
import com.google.appinventor.components.common.ComponentCategory;
import com.google.appinventor.components.runtime.*;
import com.google.appinventor.components.runtime.util.*;
import com.google.appinventor.components.runtime.errors.YailRuntimeError;
import android.graphics.drawable.GradientDrawable;
import android.graphics.Color;
import android.content.res.ColorStateList;
import android.view.View;
import android.content.Context;
import android.graphics.drawable.RippleDrawable;
import android.graphics.drawable.Drawable;

import cn.roger.ViewUtil.IDUtil;


@DesignerComponent(version = RippleDrawableUtil.VERSION,
    description = "by Roger Young",
    category = ComponentCategory.EXTENSION,
    nonVisible = true,
    iconName = "images/extension.png")

@SimpleObject(external = true)

public class RippleDrawableUtil extends IDUtil {
    public static final int VERSION = 1;
    private static final String LOG_TAG = "RippleDrawableUtil";
    private ComponentContainer container;
    private Context context;
	
    public RippleDrawableUtil(ComponentContainer container) {
        super(container.$form());
        this.container = container;
        context = (Context) container.$context();
    }
	
    public Drawable findDrawableById(int id) {
        return (Drawable)container.$form().findViewById(id).getBackground();
    }
    
    @SimpleFunction(description = "newGradientDrawable")
    public void newRippleDrawable(String color) {
        findViewById(id).setBackground(new RippleDrawable(ColorStateList.valueOf(Color.parseColor(color)),findDrawableById(id),findDrawableById(id)));
    }
}