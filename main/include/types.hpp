// types.hpp
// Common datastructures.
// Matt Rossouw (omeh-a)
// 05/2023

#ifndef TYPES_H
#define TYPES_H

#include <vector>
#include <stdint.h>

typedef struct {
    uint16_t acc_x;
    uint16_t acc_y;
    uint16_t acc_z;
} accel_reading;

typedef struct {
    uint16_t acc_x;
    uint16_t acc_y;
    uint16_t acc_z;
    uint16_t gyr_x;
    uint16_t gyr_y;
    uint16_t gyr_z;
    uint16_t mag_x;
    uint16_t mag_y;
    uint16_t mag_z;
    uint8_t temp;
} imu_reading;

typedef uint32_t rtc_reading;

typedef struct {
    uint16_t humidity;
    uint16_t temp;
    uint16_t pressure;
} env_reading;

#endif