// Define vector unit width here
#define VECTOR_WIDTH 4

#ifndef CS149INTRIN_H_
#define CS149INTRIN_H_

#include <cstdlib>
#include <cmath>
#include "logger.h"

//*******************
//* Type Definition *
//*******************

extern Logger CS149Logger;

template <typename T>
struct __cs149_vec {
  T value[VECTOR_WIDTH];
};

// Declare a mask with __cs149_mask
struct __cs149_mask : __cs149_vec<bool> {};

// Declare a floating point vector register with __cs149_vec_float
#define __cs149_vec_float __cs149_vec<float>

// Declare an integer vector register with __cs149_vec_int
#define __cs149_vec_int   __cs149_vec<int>

//***********************
//* Function Definition *
//***********************

// Return a mask initialized to 1 in the first N lanes and 0 in the others
__cs149_mask _cs149_init_ones(int first = VECTOR_WIDTH);

// Return the inverse of maska
__cs149_mask _cs149_mask_not(__cs149_mask &maska);

// Return (maska | maskb)
__cs149_mask _cs149_mask_or(__cs149_mask &maska, __cs149_mask &maskb);

// Return (maska & maskb)
__cs149_mask _cs149_mask_and(__cs149_mask &maska, __cs149_mask &maskb);

// Count the number of 1s in maska
int _cs149_cntbits(__cs149_mask &maska);

// Set register to value if vector lane is active
//  otherwise keep the old value
void _cs149_vset_float(__cs149_vec_float &vecResult, float value, __cs149_mask &mask);
void _cs149_vset_int(__cs149_vec_int &vecResult, int value, __cs149_mask &mask);
// For user's convenience, returns a vector register with all lanes initialized to value
__cs149_vec_float _cs149_vset_float(float value);
__cs149_vec_int _cs149_vset_int(int value);

// Copy values from vector register src to vector register dest if vector lane active
// otherwise keep the old value
void _cs149_vmove_float(__cs149_vec_float &dest, __cs149_vec_float &src, __cs149_mask &mask);
void _cs149_vmove_int(__cs149_vec_int &dest, __cs149_vec_int &src, __cs149_mask &mask);

// Load values from array src to vector register dest if vector lane active
//  otherwise keep the old value
void _cs149_vload_float(__cs149_vec_float &dest, float* src, __cs149_mask &mask);
void _cs149_vload_int(__cs149_vec_int &dest, int* src, __cs149_mask &mask);

// Store values from vector register src to array dest if vector lane active
//  otherwise keep the old value
void _cs149_vstore_float(float* dest, __cs149_vec_float &src, __cs149_mask &mask);
void _cs149_vstore_int(int* dest, __cs149_vec_int &src, __cs149_mask &mask);

// Return calculation of (veca + vecb) if vector lane active
//  otherwise keep the old value
void _cs149_vadd_float(__cs149_vec_float &vecResult, __cs149_vec_float &veca, __cs149_vec_float &vecb, __cs149_mask &mask);
void _cs149_vadd_int(__cs149_vec_int &vecResult, __cs149_vec_int &veca, __cs149_vec_int &vecb, __cs149_mask &mask);

// Return calculation of (veca - vecb) if vector lane active
//  otherwise keep the old value
void _cs149_vsub_float(__cs149_vec_float &vecResult, __cs149_vec_float &veca, __cs149_vec_float &vecb, __cs149_mask &mask);
void _cs149_vsub_int(__cs149_vec_int &vecResult, __cs149_vec_int &veca, __cs149_vec_int &vecb, __cs149_mask &mask);

// Return calculation of (veca * vecb) if vector lane active
//  otherwise keep the old value
void _cs149_vmult_float(__cs149_vec_float &vecResult, __cs149_vec_float &veca, __cs149_vec_float &vecb, __cs149_mask &mask);
void _cs149_vmult_int(__cs149_vec_int &vecResult, __cs149_vec_int &veca, __cs149_vec_int &vecb, __cs149_mask &mask);

// Return calculation of (veca / vecb) if vector lane active
//  otherwise keep the old value
void _cs149_vdiv_float(__cs149_vec_float &vecResult, __cs149_vec_float &veca, __cs149_vec_float &vecb, __cs149_mask &mask);
void _cs149_vdiv_int(__cs149_vec_int &vecResult, __cs149_vec_int &veca, __cs149_vec_int &vecb, __cs149_mask &mask);


// Return calculation of absolute value abs(veca) if vector lane active
//  otherwise keep the old value
void _cs149_vabs_float(__cs149_vec_float &vecResult, __cs149_vec_float &veca, __cs149_mask &mask);
void _cs149_vabs_int(__cs149_vec_int &vecResult, __cs149_vec_int &veca, __cs149_mask &mask);

// Return a mask of (veca > vecb) if vector lane active
//  otherwise keep the old value
void _cs149_vgt_float(__cs149_mask &vecResult, __cs149_vec_float &veca, __cs149_vec_float &vecb, __cs149_mask &mask);
void _cs149_vgt_int(__cs149_mask &vecResult, __cs149_vec_int &veca, __cs149_vec_int &vecb, __cs149_mask &mask);

// Return a mask of (veca < vecb) if vector lane active
//  otherwise keep the old value
void _cs149_vlt_float(__cs149_mask &vecResult, __cs149_vec_float &veca, __cs149_vec_float &vecb, __cs149_mask &mask);
void _cs149_vlt_int(__cs149_mask &vecResult, __cs149_vec_int &veca, __cs149_vec_int &vecb, __cs149_mask &mask);

// Return a mask of (veca == vecb) if vector lane active
//  otherwise keep the old value
void _cs149_veq_float(__cs149_mask &vecResult, __cs149_vec_float &veca, __cs149_vec_float &vecb, __cs149_mask &mask);
void _cs149_veq_int(__cs149_mask &vecResult, __cs149_vec_int &veca, __cs149_vec_int &vecb, __cs149_mask &mask);

// Adds up adjacent pairs of elements, so
//  [0 1 2 3] -> [0+1 0+1 2+3 2+3]
void _cs149_hadd_float(__cs149_vec_float &vecResult, __cs149_vec_float &vec);

// Performs an even-odd interleaving where all even-indexed elements move to front half
//  of the array and odd-indexed to the back half, so
//  [0 1 2 3 4 5 6 7] -> [0 2 4 6 1 3 5 7]
void _cs149_interleave_float(__cs149_vec_float &vecResult, __cs149_vec_float &vec);

// Add a customized log to help debugging
void addUserLog(const char * logStr);

#endif



// 此文件实现 CS149 向量内在函数库，用于模拟 SIMD 操作。所有函数都使用掩码控制通道执行，以避免分支。以下按类别总结主要函数：

// 1. 掩码操作
// __cs149_mask _cs149_init_ones(int first): 创建掩码，前 first 个通道为 true，其余为 false。
// __cs149_mask _cs149_mask_not(__cs149_mask &maska): 对掩码取反。
// __cs149_mask _cs149_mask_or/and(__cs149_mask &maska, __cs149_mask &maskb): 掩码按位或/与操作。
// int _cs149_cntbits(__cs149_mask &maska): 计算掩码中 true 的位数。
// 2. 向量设置与移动
// void _cs149_vset(__cs149_vec<T> &vecResult, T value, __cs149_mask &mask): 将向量所有通道设置为 value，受掩码控制。
// void _cs149_vmove(__cs149_vec<T> &dest, __cs149_vec<T> &src, __cs149_mask &mask): 将 src 向量复制到 dest，受掩码控制。
// 3. 向量加载与存储
// void _cs149_vload(__cs149_vec<T> &dest, T* src, __cs149_mask &mask): 从内存加载数据到向量，受掩码控制。
// void _cs149_vstore(T* dest, __cs149_vec<T> &src, __cs149_mask &mask): 从向量存储数据到内存，受掩码控制。
// 4. 算术操作
// void _cs149_vadd/sub/mult/div(__cs149_vec<T> &vecResult, __cs149_vec<T> &veca, __cs149_vec<T> &vecb, __cs149_mask &mask): 向量加/减/乘/除，受掩码控制。
// void _cs149_vabs(__cs149_vec<T> &vecResult, __cs149_vec<T> &veca, __cs149_mask &mask): 向量绝对值，受掩码控制。
// 5. 比较操作
// void _cs149_vgt/lt/eq(__cs149_mask &maskResult, __cs149_vec<T> &veca, __cs149_vec<T> &vecb, __cs149_mask &mask): 向量大于/小于/等于比较，生成新掩码，受输入掩码控制。
// 6. 特殊操作
// void _cs149_hadd(__cs149_vec<T> &vecResult, __cs149_vec<T> &vec): 水平加法，将相邻元素相加并复制。
// void _cs149_interleave(__cs149_vec<T> &vecResult, __cs149_vec<T> &vec): 交织向量元素。
// 7. 日志与辅助
// void addUserLog(const char * logStr): 添加用户自定义日志。