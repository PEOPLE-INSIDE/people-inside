package com.ysm0622.live;

import java.util.ArrayList;

public class Cafeteria {

    private static final String TAG = Cafeteria.class.getName();

    public String name;
    public int people_max;
    public int people_now;
    public ArrayList<Menu> menus;

    public Cafeteria(String name, int people_max, int people_now, ArrayList<Menu> menus) {
        this.name = name;
        this.people_max = people_max;
        this.people_now = people_now;
        this.menus = menus;
    }
}
