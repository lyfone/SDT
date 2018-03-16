//
// Created by zzhfeng on 2018/3/6.
//

#ifndef SDT_AUTO_SDT_CODER_H
#define SDT_AUTO_SDT_CODER_H

#pragma once

#include "Auto-SDT.h"
#include <vector>
#include <math.h>

using std::vector;

class Auto_SDT_Coder {
private:
    vector<float> points;   //编码的点
    float max_de;           //门宽的最大值
    float min_de;           //门宽的最小值
    float step_de;          //门宽调整值
    float dt;               //控制参数
    float ds;               //期望偏差
    float de;               //初始门大小
    float up_k;             //上斜率
    float down_k;           //下斜率
    Auto_SDT auto_sdt;

    float compute_expectation();//计算期望
    bool update_k(float point, int step); //更新上下斜率k值

public:
    //构造函数
    Auto_SDT_Coder(float para_max_de, float para_min_de, int steps, float para_dt, float para_ds);

    //开始编码
    void start(float point);

    //根据每一个新来的数据点更新编码器
    bool update_door(float point);

    void reset();

    float get_de();

    //获取编码结果
    Auto_SDT get_Auto_SDT_result() {
        return auto_sdt;
    }

    //获取编码的数据点集合
    vector<float> get_points() {
        return points;
    }
};

/**
 *  构造函数
 * @param para_max_de
 * @param para_min_de
 * @param steps
 * @param para_dt
 * @param para_ds
 */
Auto_SDT_Coder::Auto_SDT_Coder(float para_max_de, float para_min_de, int steps, float para_dt, float para_ds) {
    max_de = para_max_de;
    min_de = para_min_de;
    step_de = (max_de - min_de) / steps;
    dt = para_dt;
    ds = para_ds;
    de = (max_de + min_de) / 2;
}

/**
 * 开始编码，初始化
 * @param point
 */
void Auto_SDT_Coder::start(float point) {
    points.clear();
    auto_sdt.set_start_point(point);
    auto_sdt.set_max(point);
    auto_sdt.set_min(point);
    up_k = -1.0;
    down_k = 1.0;
}

/**
 * 根据新数据点更新上下斜率，当上斜率大于等于下斜率数返回true(此时两个门的内角和大于180，本段压缩完成。)
 * @param point
 * @return
 */
bool Auto_SDT_Coder::update_k(float point, int step) {
    float new_up_k = (point - auto_sdt.get_start_point() - de) / step;
    up_k = up_k > new_up_k ? up_k : new_up_k;

    float new_down_k = (point - auto_sdt.get_start_point() + de) / step;
    down_k = down_k < new_down_k ? down_k : new_down_k;

    return up_k >= down_k;
}

/**
 * 计算方差
 * @return
 */
float Auto_SDT_Coder::compute_expectation() {
    float start = auto_sdt.get_start_point();
    float dy = (auto_sdt.get_end_point() - auto_sdt.get_end_point()) / (auto_sdt.get_step_dis() - 1);
    float sum = 0.0;
    int pos = 0;
    for (auto it = points.begin(); it != points.end(); it++) {
        float tmp = *it - (start + dy * pos);
        sum += tmp * tmp;
        pos++;
    }
    return sqrt(sum / auto_sdt.get_counts());
}

/**
 * 求较小值
 * @param a
 * @param b
 * @return
 */
float min(float a, float b) {
    if (a < b)
        return a;
    return b;
}

/**
 * 求较大值
 * @param a
 * @param b
 * @return
 */
float max(float a, float b) {
    if (a > b)
        return a;
    return b;
}

/**
 * 根据新到达的数据值更新旋转门相关数据，返回结果为本段是否完成
 * @param point
 */
bool Auto_SDT_Coder::update_door(float point) {
    if (!update_k(point,auto_sdt.get_counts())) {
        auto_sdt.set_end_point(point);
        auto_sdt.inc();
        points.push_back(point);
        auto_sdt.update_min(point);
        auto_sdt.update_max(point);
        return true;
    }
    float e = ds - compute_expectation();
    if (e >= ds * dt)
        de = min(max_de, de + (e * step_de) / (ds * dt));
    if (e <= -ds * dt)
        de = max(min_de, de - (e * step_de) / (ds * dt));
    if (abs(e) > 2 * ds * dt)
        //TODO 此处抛出异常，说明de的选择不合适，需要重新选择de
        ;
    return false;
}

/**
 * 读取门的大小
 * @return
 */
float Auto_SDT_Coder::get_de() {
    return de;
}


#endif //SDT_AUTO_SDT_CODER_H
