package com.ysm0622.live;

import android.os.Bundle;
import android.os.CountDownTimer;
import android.support.v7.app.AppCompatActivity;
import android.view.MotionEvent;
import android.view.View;
import android.view.Window;

public class SplashActivity extends AppCompatActivity implements View.OnTouchListener {

    private static final String TAG = SplashActivity.class.getName();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        supportRequestWindowFeature(Window.FEATURE_NO_TITLE);
        setContentView(R.layout.activity_splash);

        new CountDownTimer(1000, 1000) {
            public void onTick(long millisUntilFinished) {
            }

            public void onFinish() {
                finish();
            }
        }.start();
    }

    @Override
    public boolean onTouch(View v, MotionEvent event) {
        finish();
        return false;
    }
}
