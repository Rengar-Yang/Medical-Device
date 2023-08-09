package cn.roger.shape;

import com.google.appinventor.components.annotations.*;
import com.google.appinventor.components.common.ComponentCategory;
import com.google.appinventor.components.runtime.*;
import com.google.appinventor.components.runtime.util.*;
import com.google.appinventor.components.runtime.errors.YailRuntimeError;
import android.graphics.drawable.GradientDrawable;
import android.graphics.Color;
import android.view.View;
import com.google.appinventor.components.runtime.util.YailList;

import cn.roger.ViewUtil.IDUtil;


@DesignerComponent(version = GradientDrawableUtil.VERSION,
    description = "by Roger Young",
    category = ComponentCategory.EXTENSION,
    nonVisible = true,
    iconName = "images/extension.png")

@SimpleObject(external = true)

public class GradientDrawableUtil extends IDUtil {
    public static final int VERSION = 1;
    private static final String LOG_TAG = "GradientDrawableUtil";
	
    public GradientDrawableUtil(ComponentContainer container) {
        super(container.$form());
    }
	
    @SimpleFunction(description = "newGradientDrawable")
    public void NEW() {
        findViewById(id).setBackground(new GradientDrawable());
    }
	
    @SimpleFunction(description = "setCornerRadius")
    public void setCornerRadius(float radius) {
        ((GradientDrawable)findViewById(id).getBackground()).setCornerRadius(radius);
    }
    @SimpleFunction(description = "setStroke")
    public void setStroke(int width,String color) {
        ((GradientDrawable)findViewById(id).getBackground()).setStroke(width,Color.parseColor(color));
    }
    @SimpleFunction(description = "setColor")
    public void setColor(String color) {
        ((GradientDrawable)findViewById(id).getBackground()).setColor(Color.parseColor(color));
    }
    @SimpleFunction(description = "setColor")
    public void setColors(YailList colors) {
        String array[] = colors.toStringArray();
        int color[] = new int[array.length];
        for(int i = 0;i < array.length;i++){
            color[i] = Color.parseColor(array[i]);
        }
        ((GradientDrawable)findViewById(id).getBackground()).setColors(color);
    }
    @SimpleFunction(description = "setColor")
    public void setGradientType(int gradient) {
        ((GradientDrawable)findViewById(id).getBackground()).setGradientType(gradient);
    }
    @SimpleFunction(description = "setColor")
    public void setGradientRadius(float gradientRadius) {
        ((GradientDrawable)findViewById(id).getBackground()).setGradientRadius(gradientRadius);
    }
    @SimpleFunction(description = "setColor")
    public void setOrientation(int i) {
        GradientDrawable.Orientation orientation;
        switch (i) {
            case 0:
                orientation = GradientDrawable.Orientation.LEFT_RIGHT;
                break;
            case 1:
                orientation = GradientDrawable.Orientation.BL_TR;
                break;
            case 2:
                orientation = GradientDrawable.Orientation.BOTTOM_TOP;
                break;
            case 3:
                orientation = GradientDrawable.Orientation.BR_TL;
                break;
            case 4:
                orientation = GradientDrawable.Orientation.RIGHT_LEFT;
                break;
            case 5:
                orientation = GradientDrawable.Orientation.TR_BL;
                break;
            case 6:
                orientation = GradientDrawable.Orientation.TOP_BOTTOM;
                break;
            default:
                orientation = GradientDrawable.Orientation.TL_BR;
                break;
        }
        ((GradientDrawable)findViewById(id).getBackground()).setOrientation(orientation);
    }
}