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


@DesignerComponent(version = IDUtil.VERSION,
    description = "由Roger young创作，可以做工具",
    category = ComponentCategory.EXTENSION,
    nonVisible = true,
    iconName = "images/extension.png")

@SimpleObject(external = false)

public abstract class IDUtil extends AndroidNonvisibleComponent{
    public static final int VERSION = 1;
    private static final String LOG_TAG = "IDUtil";
    private ComponentContainer container;
    private Context context;
    public static int id;
	
    public View findViewById(int id) {
        return container.$form().findViewById(id);
    }
    public IDUtil(ComponentContainer container) {
        super(container.$form());
        this.container = container;
        context = (Context) container.$context();
    }
    @SimpleFunction(description = "start")
    public void id(int id) {
        this.id = id;
    }
}
