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
import android.widget.EditText;
import android.view.ViewGroup;
import android.view.View;
import android.widget.RelativeLayout;
import android.text.method.HideReturnsTransformationMethod;
import android.text.method.PasswordTransformationMethod;

@DesignerComponent(version = EditTextUtil.VERSION,
    description = "由Roger young创作，可以做工具",
    category = ComponentCategory.EXTENSION,
    nonVisible = true,
    iconName = "images/extension.png")

@SimpleObject(external = true)

public class EditTextUtil extends TextViewUtil{
    public static final int VERSION = 1;
    private static final String LOG_TAG = "EditTextUtil";
    private ComponentContainer container;
    private Context context;
	
    public EditTextUtil(ComponentContainer container) {
        super(container.$form());
        this.container = container;
        context = (Context) container.$context();
    }
    public ViewGroup findViewGroupById(int id) {
        return (ViewGroup)container.$form().findViewById(id);
    }
    private EditText findEditTextById(int id) {
        return (EditText)container.$form().findViewById(id);
    }
    @SimpleFunction(description = "start")
    public void NEW(int id,int parent,int width,int height) {
        EditText editText = new EditText(context);
        editText.setId(id);
        editText.setLayoutParams(new RelativeLayout.LayoutParams(width,height));
        findViewGroupById(parent).addView(editText);
        this.id = id;
    }
    @SimpleFunction(description = "start")
    public void selectAll() {
        findEditTextById(id).selectAll();
    }
    @SimpleFunction(description = "start")
    public void setSelectionAt(int index) {
        findEditTextById(id).setSelection(index);
    }
    @SimpleFunction(description = "start")
    public void setSelection(int start, int stop) {
        findEditTextById(id).setSelection(start,stop);
    }
    @SimpleFunction(description = "start")
    public void setPassword(boolean password) {
        if(password)
            findEditTextById(id).setTransformationMethod(HideReturnsTransformationMethod.getInstance());
        else
            findEditTextById(id).setTransformationMethod(PasswordTransformationMethod.getInstance());
        findEditTextById(id).setSelection(findEditTextById(id).getText().length());
    }
}
