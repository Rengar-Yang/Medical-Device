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

@DesignerComponent(version = AnyEventUtil.VERSION,
    description = "由Roger young创作，可以做工具",
    category = ComponentCategory.EXTENSION,
    nonVisible = true,
    iconName = "images/extension.png")

@SimpleObject(external = true)

public class AnyEventUtil extends AndroidNonvisibleComponent implements View.OnClickListener{
    public static final int VERSION = 1;
    private static final String LOG_TAG = "AnyEventUtil";
    private ComponentContainer container;
    private Context context;
	
    public AnyEventUtil(ComponentContainer container) {
        super(container.$form());
        this.container = container;
        context = (Context) container.$context();
    }
    private View findViewById(int id) {
        return container.$form().findViewById(id);
    }

    @SimpleEvent
    public void Click(int id){
        EventDispatcher.dispatchEvent(this, "Click", id);
    }
    public void onClick(View v){
        Click(v.getId());
    }
    @SimpleFunction(description = "start")
    public void setOnClickListener(int id) {
        findViewById(id).setOnClickListener(this);
    }


    @SimpleFunction(description = "start")
    public boolean isClickable(int id) {
        return findViewById(id).isClickable();
    }
    @SimpleFunction(description = "start")
    public boolean isEnabled(int id) {
        return findViewById(id).isEnabled();
    }
    @SimpleFunction(description = "start")
    public boolean isLongClickable(int id) {
        return findViewById(id).isLongClickable();
    }
    @SimpleFunction(description = "start")
    public boolean isPressed(int id) {
        return findViewById(id).isPressed();
    }


    @SimpleFunction(description = "start")
    public void setLongClickable(int id,boolean longClickable) {
        findViewById(id).setLongClickable(longClickable);
    }
    @SimpleFunction(description = "start")
    public void setClickable(int id,boolean clickable) {
        findViewById(id).setClickable(clickable);
    }
    @SimpleFunction(description = "start")
    public void setEnabled(int id,boolean enabled) {
        findViewById(id).setEnabled(enabled);
    }
}
