/**
 * Author: Ziqian Zhong
 * Description: SIMD examples.
 */
#include "immintrin.h"
#include "emmintrin.h"
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast,no−stack−protector,−funroll−loops,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2,fma,sse4.1,sse4.2,sse4a,xsave,popcnt,abm,mmx,avx,tune=native")
#define __AVX__ 1
#define __AVX2__ 1
#define __SSE__ 1
#define __SSE2__ 1
#define __SSE2_MATH__ 1
#define __SSE3__ 1
#define __SSE4_1__ 1
#define __SSE4_2__ 1
#define __SSE_MATH__ 1
#define __SSSE3__ 1
__m256i
__m256i _mm256_abs_epi32 (__m256i a)
__m256i _mm256_add_epi32 (__m256i a, __m256i b)
__m256i _mm256_blend_epi32 (__m256i a, __m256i b, const int imm8) //get from a or b depending on the mask
__m256i _mm256_cmpeq_epi32 (__m256i a, __m256i b) //==
__m256i _mm256_cmpgt_epi32 (__m256i a, __m256i b) //>
__int32 _mm256_extract_epi32 (__m256i a, const int index)
__m256i _mm256_max_epi32 (__m256i a, __m256i b)
__m256i _mm256_min_epi32 (__m256i a, __m256i b)
__m256i _mm256_mul_epi32 (__m256i a, __m256i b) //64b mul low bits
__m256i _mm256_mullo_epi32 (__m256i a, __m256i b) //32b mul low bits, throw high bits
__m256i _mm256_set_epi32 (int e7, int e6, int e5, int e4, int e3, int e2, int e1, int e0)
__m256i _mm256_set1_epi32 (int a)
__m256i _mm256_setr_epi32 (int e7, int e6, int e5, int e4, int e3, int e2, int e1, int e0)
__m256i _mm256_sign_epi32 (__m256i a, __m256i b) //neg a by sign of b
__m256i _mm256_slli_epi32 (__m256i a, int imm8) //left shift
__m256i _mm256_sllv_epi32 (__m256i a, __m256i count) //left shift
__m256i _mm256_srai_epi32 (__m256i a, int imm8)
__m256i _mm256_srav_epi32 (__m256i a, __m256i count) //right shift, keep sign
__m256i _mm256_srli_epi32 (__m256i a, int imm8)
__m256i _mm256_srlv_epi32 (__m256i a, __m256i count) //right shift, do not keep sign
__m256i _mm256_sub_epi32 (__m256i a, __m256i b)
