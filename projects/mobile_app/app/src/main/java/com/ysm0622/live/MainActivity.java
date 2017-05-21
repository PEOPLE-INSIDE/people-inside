package com.ysm0622.live;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.widget.ExpandableListAdapter;
import android.widget.ExpandableListView;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = MainActivity.class.getName();

    private ExpandableListView exListView;
    private ExpandableListAdapter exListAdapter;
    private ArrayList<Cafeteria> cafeList;
    private ArrayList<ArrayList<Menu>> menuList;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        cafeList = new ArrayList<>();
        Cafeteria test1 = new Cafeteria("비전타워", 100, 10, new ArrayList<Menu>());
        Cafeteria test2 = new Cafeteria("아름관", 100, 50, new ArrayList<Menu>());
        Cafeteria test3 = new Cafeteria("창조관", 100, 90, new ArrayList<Menu>());
        cafeList.add(test1);
        cafeList.add(test2);
        cafeList.add(test3);
        menuList = new ArrayList<>();
        exListView = (ExpandableListView) findViewById(R.id.exlistview);
        exListAdapter = new BaseExpandableAdapter(this, cafeList, menuList);
        exListView.setAdapter(exListAdapter);
    }
}
