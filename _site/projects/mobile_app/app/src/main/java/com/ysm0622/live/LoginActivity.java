package com.ysm0622.live;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.view.Window;

public class LoginActivity extends AppCompatActivity {

    private static final String TAG = LoginActivity.class.getName();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        supportRequestWindowFeature(Window.FEATURE_NO_TITLE);
        setContentView(R.layout.activity_login);
        startActivity(new Intent(LoginActivity.this, SplashActivity.class));
    }

    public void onLoginClicked(View v){
        startActivity(new Intent(LoginActivity.this, MainActivity.class));
    }
}
