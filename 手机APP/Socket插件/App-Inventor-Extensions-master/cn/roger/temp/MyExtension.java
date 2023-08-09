package cn.roger.temp;

import com.google.appinventor.components.annotations.*;
import com.google.appinventor.components.common.ComponentCategory;
import com.google.appinventor.components.runtime.*;
import com.google.appinventor.components.runtime.util.*;
import com.google.appinventor.components.runtime.errors.YailRuntimeError;

@DesignerComponent(version = MyExtension.VERSION,
    description = "by Roger Young",
    category = ComponentCategory.EXTENSION,
    nonVisible = true,
    iconName = "images/extension.png")

@SimpleObject(external = true)

public class MyExtension extends AndroidNonvisibleComponent {
    public static final int VERSION = 1;
    private static final String LOG_TAG = "MyExtension";

    public MyExtension(ComponentContainer container) {
        super(container.$form());
    }

    @SimpleFunction(description = "add up a and b")
    public String addab(int a,int b) {
        return ""+(a+b);
    }
}
