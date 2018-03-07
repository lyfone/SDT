//
// Created by zzhfeng on 2018/3/5.
//

#ifndef SDT_AUTO_SDT_H
#define SDT_AUTO_SDT_H

#pragma once

struct Auto_SDT {
private:
    float start_point;  //起始点
    float end_point;    //终止点
    float max;          //最大值
    float min;          //最小值
    int counter;       //起点和终点的跨度

public:
    //构造函数
    Auto_SDT();

    //设置起点数值
    void set_start_point(float start_point);
    //获取起点数值
    float get_start_point();

    //设置终点数值
    void set_end_point(float end_point);
    //获取终点数值
    float get_end_point();

    //计数+1
    int inc();
    //获取总数值点的数量
    int get_counts();

    //设置最大值
    void set_max(float f);
    //更新最大值
    void update_max(float f);
    //获取最大值
    float get_max();

    //设置最小值
    void set_min(float f);
    //更新最小值
    void update_min(float f);
    //获取最小值
    float get_min();

    //重置数据
    void reset();
};

#endif //SDT_AUTO_SDT_H
