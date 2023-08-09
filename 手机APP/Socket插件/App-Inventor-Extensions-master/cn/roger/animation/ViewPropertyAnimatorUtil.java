package cn.roger.animation;

import com.google.appinventor.components.annotations.*;
import com.google.appinventor.components.common.ComponentCategory;
import com.google.appinventor.components.runtime.*;
import com.google.appinventor.components.runtime.util.*;
import com.google.appinventor.components.runtime.errors.YailRuntimeError;
import android.view.ViewPropertyAnimator;
import android.animation.ValueAnimator;
import android.view.View;
import android.content.Context;

import cn.roger.ViewUtil.IDUtil;

@DesignerComponent(version = ViewPropertyAnimatorUtil.VERSION,
    description = "由Roger young创作，可以执行动画",
    category = ComponentCategory.EXTENSION,
    nonVisible = true,
    iconName = "images/extension.png")

@SimpleObject(external = true)

public class ViewPropertyAnimatorUtil extends IDUtil {
    public static final int VERSION = 1;
    private static final String LOG_TAG = "ViewPropertyAnimatorUtil";
    private ComponentContainer container;
    private Context context;
	
    public ViewPropertyAnimatorUtil(ComponentContainer container) {
        super(container.$form());
        this.container = container;
        context = (Context) container.$context();
    }
    public ViewPropertyAnimator getAnimator(int id) {
        return findViewById(id).animate();
    }

    @SimpleFunction(description = "getAnimator")
    public void start(long duration,long startDelay) {
        getAnimator(id).setDuration(duration);;
        getAnimator(id).setStartDelay(startDelay);
        getAnimator(id).start();
    }
	
    @SimpleFunction(description = "scaleX")
    public void scaleX(float f,boolean b) {
		if(b) getAnimator(id).scaleXBy(f);
		else getAnimator(id).scaleX(f);
    }
    @SimpleFunction(description = "scaleY")
    public void scaleY(float f,boolean b) {
		if(b) getAnimator(id).scaleYBy(f);
		else getAnimator(id).scaleY(f);
    }
	
    @SimpleFunction(description = "alpha")
    public void alpha(float f,boolean b) {
		if(b) getAnimator(id).alphaBy(f);
		else getAnimator(id).alpha(f);
    }
	
    @SimpleFunction(description = "translationX")
    public void translationX(float f,boolean b) {
		if(b) getAnimator(id).translationXBy(f);
		else getAnimator(id).translationX(f);
    }
    @SimpleFunction(description = "translationY")
    public void translationY(float f,boolean b) {
		if(b) getAnimator(id).translationYBy(f);
		else getAnimator(id).translationY(f);
    }
    @SimpleFunction(description = "translationZ")
    public void translationZ(float f,boolean b) {
		if(b) getAnimator(id).translationZBy(f);
		else getAnimator(id).translationZ(f);
    }
	
    @SimpleFunction(description = "cancel")
    public void cancel() {
        getAnimator(id).cancel();
    }
	
    @SimpleFunction(description = "rotation")
    public void rotation(float f,boolean b) {
		if(b) getAnimator(id).rotationBy(f);
		else getAnimator(id).rotation(f);
    }
    @SimpleFunction(description = "rotationX")
    public void rotationX(float f,boolean b) {
		if(b) getAnimator(id).rotationXBy(f);
		else getAnimator(id).rotationX(f);
    }
    @SimpleFunction(description = "rotationY")
    public void rotationY(float f,boolean b) {
		if(b) getAnimator(id).rotationYBy(f);
		else getAnimator(id).rotationY(f);
    }
	
    @SimpleFunction(description = "withLayer")
    public void withLayer() {
        getAnimator(id).withLayer();
    }
	
    @SimpleFunction(description = "x")
    public void x(float f,boolean b) {
		if(b) getAnimator(id).xBy(f);
		else getAnimator(id).x(f);
    }
    @SimpleFunction(description = "y")
    public void y(float f,boolean b) {
		if(b) getAnimator(id).yBy(f);
		else getAnimator(id).y(f);
    }
    @SimpleFunction(description = "z")
    public void z(float f,boolean b) {
        if(b) getAnimator(id).zBy(f);
        else getAnimator(id).z(f);
    }

    @SimpleEvent
    public void WithStartAction(int id){
        EventDispatcher.dispatchEvent(this, "WithStartAction", id);
    }
    @SimpleFunction(description = "z")
    public void addStartActionEvent() {
        getAnimator(id).withStartAction(
            new Runnable(){
            int nowid = id;
            public void run(){
                WithStartAction(id);
            }
        });
    }

    @SimpleEvent
    public void WithEndAction(int id){
        EventDispatcher.dispatchEvent(this, "WithEndAction", id);
    }
    @SimpleFunction(description = "z")
    public void addEndActionEvent() {
        getAnimator(id).withEndAction(
            new Runnable(){
            int nowid = id;
            public void run(){
                WithEndAction(id);
            }
        });
    }
	
    @SimpleEvent
    public void Click(int id){
        EventDispatcher.dispatchEvent(this, "Click", id);
    }
}
