package cn.car.activity;

import com.google.appinventor.components.annotations.*;
import com.google.appinventor.components.common.ComponentCategory;
import com.google.appinventor.components.runtime.*;
import com.google.appinventor.components.runtime.util.*;
import com.google.appinventor.components.runtime.errors.YailRuntimeError;

import android.content.Context;
import android.view.ViewGroup;
import android.view.View;
import android.view.Gravity;
import android.view.MotionEvent;
import android.view.ViewGroup.LayoutParams;
import android.view.MotionEvent;
import android.view.animation.AlphaAnimation;
import android.animation.ValueAnimator;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.EditText;
import android.widget.Button;
import android.util.FloatMath;
import android.graphics.drawable.GradientDrawable;
import android.graphics.drawable.RippleDrawable;
import android.content.res.ColorStateList;
import android.text.method.HideReturnsTransformationMethod;

@DesignerComponent(version = ScoreActivity.VERSION,
    description = "by Roger Young3",
    category = ComponentCategory.EXTENSION,
    nonVisible = true,
    iconName = "images/extension.png")

@SimpleObject(external = true)

public class ScoreActivity extends AndroidNonvisibleComponent {
    public static final int VERSION = 1;
    private static final String LOG_TAG = "ScoreActivity";
    ComponentContainer container;
    Context context;
    ViewGroup viewGroup;
    private ScoreView scoreView;
    public ScoreActivity(ComponentContainer container) {
        super(container.$form());
        this.container = container;
        context = (Context) container.$context();
    }
    @SimpleFunction(description = "init")
    public void init(HVArrangement h,int i){
        viewGroup = (ViewGroup)(h.getView());
        scoreView = new ScoreView(this,i);
        viewGroup.addView(scoreView);
    }
    @SimpleEvent
    public void back(){
        EventDispatcher.dispatchEvent(this, "back");
    }
    public Context getContext(){
        return context;
    }
}
class ScoreView extends RelativeLayout{
    private TextView title;
    private TextView text;
    private ValueAnimator valueAnimator1,color,valueAnimator2;
    private Context context;
    private ScoreActivity scoreActivity;
    RelativeLayout.LayoutParams lp;
    public ScoreView(ScoreActivity sa,int i){
        super(sa.getContext());
            setBackgroundColor(0xff101520);
            context = sa.getContext();
            scoreActivity = sa;
        title = new TextView(context);
            title.setTextColor(0xffffffff);
            title.setTextSize(70f);
            title.setText("0");
            title.setId(201);
            title.setTranslationY(dp(-20));
        text = new TextView(context);
            text.setTextColor(0xffffffff);
            text.setTextSize(25f);
            text.setText("点击屏幕重新开始");
            text.setId(202);
            text.setTranslationY(dp(-10));

        valueAnimator1 = ValueAnimator.ofFloat(0f,5f*3.1415926535f);
            valueAnimator1.setDuration(1000);
            valueAnimator1.addUpdateListener(new ValueAnimator.AnimatorUpdateListener() {
                final TextView text_final = title;
                float f;
                @Override
                public void onAnimationUpdate(ValueAnimator animation) {
                    f = (Float) animation.getAnimatedValue();
                    text_final.setTranslationX(dp(-20f*FloatMath.sin(f)));
                    text_final.requestLayout();
                }
            });
        valueAnimator2 = ValueAnimator.ofInt(0,i);
            valueAnimator2.setDuration(2000);
            valueAnimator2.addUpdateListener(new ValueAnimator.AnimatorUpdateListener() {
                final TextView text_final = title;
                int i;
                @Override
                public void onAnimationUpdate(ValueAnimator animation) {
                    i = (Integer) animation.getAnimatedValue();
                    text_final.setText(""+i);
                    text_final.requestLayout();
                }
            });
        color = ValueAnimator.ofFloat(0f,1f,0f);
            color.setDuration(2000);
            color.setRepeatCount(10000);
            color.addUpdateListener(new ValueAnimator.AnimatorUpdateListener() {
                final TextView text_final = text;
                float f;
                @Override
                public void onAnimationUpdate(ValueAnimator animation) {
                    f = (Float) animation.getAnimatedValue();
                    text_final.setAlpha(f);
                    text_final.requestLayout();
                }
            });
        setOnClickListener(new View.OnClickListener(){
            public void onClick(View v) {
                scoreActivity.back();
            }
        });
        title.setOnClickListener(new View.OnClickListener(){
            public void onClick(View v) {
                valueAnimator1.start();
            }
        });
        lp = new RelativeLayout.LayoutParams(
            RelativeLayout.LayoutParams.MATCH_PARENT,RelativeLayout.LayoutParams.MATCH_PARENT);
        setLayoutParams(lp);
        init();
    }
    public void init(){
        lp = new RelativeLayout.LayoutParams(
            RelativeLayout.LayoutParams.WRAP_CONTENT,RelativeLayout.LayoutParams.WRAP_CONTENT);
        lp.addRule(RelativeLayout.CENTER_HORIZONTAL,-1);
        lp.addRule(RelativeLayout.CENTER_VERTICAL,-1);
        addView(title,lp);

        lp = new RelativeLayout.LayoutParams(
            RelativeLayout.LayoutParams.WRAP_CONTENT,RelativeLayout.LayoutParams.WRAP_CONTENT);
        lp.addRule(RelativeLayout.CENTER_HORIZONTAL,-1);
        lp.addRule(RelativeLayout.BELOW,201);
        addView(text,lp);
        color.start();
        valueAnimator2.start();
    }
    public int dp(float dp) {
        final float scale = context.getResources().getDisplayMetrics().density;
        return (int) (dp * scale + 0.5f);
    }
}