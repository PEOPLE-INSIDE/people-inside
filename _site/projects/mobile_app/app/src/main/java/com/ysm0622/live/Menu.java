package com.ysm0622.live;

public class Menu {

    private static final String TAG = Menu.class.getName();

    private String name;
    private int price;
    private float rating;

    public Menu(String name, int price, float rating) {
        this.name = name;
        this.price = price;
        this.rating = rating;
    }
}
