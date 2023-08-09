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

import android.support.v4.view.ViewPager;
import android.support.v4.view.PagerAdapter;
import java.util.ArrayList;
import java.util.List;

@DesignerComponent(version = GuanKaActivity.VERSION,
    description = "by Roger Young3",
    category = ComponentCategory.EXTENSION,
    nonVisible = true,
    iconName = "images/extension.png")

@SimpleObject(external = true)

public class GuanKaActivity extends AndroidNonvisibleComponent {
    public static final int VERSION = 1;
    private static final String LOG_TAG = "GuanKaActivity";
    ComponentContainer container;
    Context context;
    ViewGroup viewGroup;
    private ChooseView chooseView;
    public GuanKaActivity(ComponentContainer container) {
        super(container.$form());
        this.container = container;
        context = (Context) container.$context();
        chooseView = new ChooseView(this);
    }
    @SimpleFunction(description = "init")
    public void init(HVArrangement h){
        viewGroup = (ViewGroup)(h.getView());
        viewGroup.addView(chooseView);
    }
    @SimpleEvent
    public void play(int i){
        EventDispatcher.dispatchEvent(this, "play", i);
    }
    @SimpleEvent
    public void number(){
        EventDispatcher.dispatchEvent(this, "number");
    }
    public Context getContext(){
        return context;
    }
}
class ChooseView extends RelativeLayout{
    private Context context;
    private GuanKaActivity guanKaActivity;
    ViewPager viewPager;
    PagerAdapter pagerAdapter;
    List<View> viewList;
    RelativeLayout.LayoutParams lp;
    GuanKaView guanKaView[] = new GuanKaView[3];
    public ChooseView(GuanKaActivity ga){
        super(ga.getContext());
            setBackgroundColor(0xff101520);
            context = ga.getContext();
            guanKaActivity = ga;
        viewPager = new ViewPager(context);
        guanKaView[0] = new GuanKaView(this,"关卡一",1);
        guanKaView[1] = new GuanKaView(this,"关卡二",2);
        guanKaView[2] = new GuanKaView(this,"关于",3);
        viewList = new ArrayList<View>();
        viewList.add(guanKaView[0]);
        viewList.add(guanKaView[1]);
        viewList.add(guanKaView[2]);
        pagerAdapter = new PagerAdapter() {
            public boolean isViewFromObject(View arg0, Object arg1) {
                return arg0 == arg1;  
            }
            public int getCount() {  
                return viewList.size();  
            }  
            public void destroyItem(ViewGroup container, int position,Object object) {  
                container.removeView(viewList.get(position));  
            }  
            public Object instantiateItem(ViewGroup container, int position) {  
                container.addView(viewList.get(position));
                return viewList.get(position);  
            }  
        };
        viewPager.setAdapter(pagerAdapter);
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
        addView(viewPager,lp);
    }
    @SimpleEvent
    public void play(int i){
        guanKaActivity.play(i);
    }
    public int dp(float dp) {
        final float scale = context.getResources().getDisplayMetrics().density;
        return (int) (dp * scale + 0.5f);
    }
}

class GuanKaView extends RelativeLayout{
    private TextView title;
    private Button button;
    private ValueAnimator valueAnimator1;
    private Context context;
    private ChooseView chooseView;

    RelativeLayout.LayoutParams lp;
    int rtn_i;
    public GuanKaView(ChooseView cv,String s,int i){
        super(cv.getContext());
            setBackgroundColor(0xff101520);
            context = cv.getContext();
            chooseView = cv;
            rtn_i = i;

        GradientDrawable gd = new GradientDrawable();
            gd.setCornerRadius(dp(999));
            gd.setColor(0xffff1744);
        title = new TextView(context);
            title.setTextColor(0xffffffff);
            title.setTextSize(40f);
            title.setText(s);
            title.setId(201);
            title.setTranslationY(dp(-30));
        button = new Button(context);
            button.setText("开始游戏");
            button.setTextColor(0xffffffff);
            button.setTextSize(30f);
            button.setBackground(new RippleDrawable(ColorStateList.valueOf(0xffffffff),gd,gd));
            button.setTranslationY(dp(-10));
            button.setPadding(dp(10),dp(10),dp(10),dp(10));
        
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
        title.setOnClickListener(new View.OnClickListener(){
            public void onClick(View v) {
                valueAnimator1.start();
            }
        });
        button.setOnClickListener(new View.OnClickListener(){
            public void onClick(View v) {
                chooseView.play(rtn_i);
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
        addView(button,lp);
    }
    public int dp(float dp) {
        final float scale = context.getResources().getDisplayMetrics().density;
        return (int) (dp * scale + 0.5f);
    }
}