package com.ysm0622.live;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseExpandableListAdapter;
import android.widget.ProgressBar;
import android.widget.TextView;

import java.util.ArrayList;

public class BaseExpandableAdapter extends BaseExpandableListAdapter {

    private Context context;
    private ArrayList<Cafeteria> cafeList = null;
    private ArrayList<ArrayList<Menu>> menuList = null;

    public BaseExpandableAdapter(Context context, ArrayList<Cafeteria> cafeList, ArrayList<ArrayList<Menu>> menuList) {
        this.context = context;
        this.cafeList = cafeList;
        this.menuList = menuList;
    }

    @Override
    public int getGroupCount() {
        return cafeList.size();
    }

    @Override
    public int getChildrenCount(int groupPosition) {
        return menuList.get(groupPosition).size();
    }

    @Override
    public Object getGroup(int groupPosition) {
        return cafeList.get(groupPosition);
    }

    @Override
    public Object getChild(int groupPosition, int childPosition) {
        return menuList.get(groupPosition).get(childPosition);
    }

    @Override
    public long getGroupId(int groupPosition) {
        return 0;
    }

    @Override
    public long getChildId(int groupPosition, int childPosition) {
        return 0;
    }

    @Override
    public boolean hasStableIds() {
        return false;
    }

    @Override
    public View getGroupView(int groupPosition, boolean isExpanded, View convertView, ViewGroup parent) {
        String listTitle = cafeList.get(groupPosition).name;
        if (convertView == null) {
            LayoutInflater layoutInflater = (LayoutInflater) this.context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
            convertView = layoutInflater.inflate(R.layout.cafeteria_item, null);
        }
        TextView textView1 = (TextView) convertView.findViewById(R.id.textView1);
        textView1.setText(listTitle);
        ProgressBar progressBar = (ProgressBar) convertView.findViewById(R.id.progressbar);
        progressBar.setProgress(cafeList.get(groupPosition).people_now);
        TextView textView2 = (TextView) convertView.findViewById(R.id.textView2);
        if(progressBar.getProgress()<33){
            textView2.setText("원활");
            progressBar.setProgressTintList(context.getResources().getColorStateList(R.color.colorGreen));
        }
        else if(progressBar.getProgress()<66) textView2.setText("보통");
        else {
            textView2.setText("혼잡");
            progressBar.setProgressTintList(context.getResources().getColorStateList(R.color.colorRed));
        }
        return convertView;
    }

    @Override
    public View getChildView(int groupPosition, int childPosition, boolean isLastChild, View convertView, ViewGroup parent) {
        return null;
    }

    @Override
    public boolean isChildSelectable(int groupPosition, int childPosition) {
        return true;
    }
}
