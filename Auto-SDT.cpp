//
// Created by zzhfeng on 2018/3/5.
//

#include "Auto-SDT.h"

/**
 * 构造函数初始化
 */
Auto_SDT::Auto_SDT(){
    counter = 0;
    start_point = 0.0;
    end_point = 0.0;
    max = 0.0;
    min = 0.0;
}

/**
 * 设置起始点
 * @param point
 */
void Auto_SDT::set_start_point(float point) {
    start_point = point;
}

/**
 * 读取起始点
 * @return
 */
float Auto_SDT::get_start_point() {
    return start_point;
}

/**
 * 设置终止点
 * @param point
 */
void Auto_SDT::set_end_point(float point) {
    end_point = point;
}

/**
 * 读取终止点
 * @return
 */
float Auto_SDT::get_end_point() {
    return end_point;
}

/**
 * 计数器+1
 * @return
 */
int Auto_SDT::inc() {
    counter++;
}

/**
 * 读取计数器数值
 * @return
 */
int Auto_SDT::get_counts() {
    return counter;
}

/**
 * 设置最大值
 * @param f
 */
void Auto_SDT::set_max(float f) {
    max = f;
}

/**
 * 更新最大值
 * @param f
 */
void Auto_SDT::update_max(float f) {
    max = f > max ? f : max;
}

/**
 * 读取最大值
 * @return
 */
float Auto_SDT::get_max() {
    return max;
}

/**
 * 设置最小值
 * @param f
 */
void Auto_SDT::set_min(float f) {
    min = f;
}

/**
 * 更新最小值
 * @param f
 */
void Auto_SDT::update_min(float f) {
    min = f < min ? f : min;
}

/**
 * 读取最小值
 * @return
 */
float Auto_SDT::get_min() {
    return min;
}

/**
 * 重置数据
 */
void Auto_SDT::reset() {
    counter = 0;
    start_point = 0.0;
    end_point = 0.0;
    max = 0.0;
    min = 0.0;
}




