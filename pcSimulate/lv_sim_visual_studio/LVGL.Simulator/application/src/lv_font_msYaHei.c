﻿#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

/*******************************************************************************
 * Tool: MCU_Font V2.0
 * Time: 2022-05-23 04:30:26
 * Bpp: 2
 * LineHeight: 19 px
 * BaseLine: 4
 * 
 * FontCount: 1
 * FontSize_1: 8px  FontFamily_1: 微软雅黑  
 ******************************************************************************/

#ifndef LV_FONT_MSYAHEI
#define LV_FONT_MSYAHEI 1
#endif

#if LV_FONT_MSYAHEI

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t gylph_bitmap[] = {

    /* U+20 " " */
    0x0, 

    /* U+23 "#" */
    0x3, 0x14, 0x2, 0x24, 0x3f, 0xfe, 0x9, 0x20, 
    0x8, 0x60, 0xbf, 0xfd, 0x8, 0x90, 0x18, 0x80, 
    0x14, 0xc0, 

    /* U+25 "%" */
    0x7e, 0x1, 0x82, 0x8, 0x8, 0x8, 0x24, 0x80, 
    0x30, 0xc5, 0x0, 0x7d, 0x20, 0x0, 0x2, 0x1f, 
    0x80, 0x14, 0xc3, 0x40, 0x86, 0x5, 0x8, 0xc, 
    0x34, 0x90, 0x1f, 0x10, 

    /* U+2a "*" */
    0x5, 0x0, 0x50, 0x79, 0xd0, 0xf0, 0x1a, 0x42, 
    0x8, 

    /* U+2c "," */
    0x36, 0x24, 

    /* U+2d "-" */
    0xff, 

    /* U+2e "." */
    0xdd, 

    /* U+2f "/" */
    0x0, 0x70, 0xd, 0x0, 0xc0, 0x28, 0x3, 0x0, 
    0x70, 0xd, 0x1, 0xc0, 0x24, 0x3, 0x0, 0x60, 
    0xd, 0x0, 

    /* U+30 "0" */
    0x2f, 0xcb, 0xe, 0xc0, 0x3c, 0x3, 0xc0, 0x3c, 
    0x3, 0xc0, 0x3c, 0x3, 0xa0, 0xd3, 0xf8, 

    /* U+31 "1" */
    0x3, 0x1f, 0xa3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 

    /* U+32 "2" */
    0x3f, 0xc8, 0xe, 0x0, 0x70, 0x7, 0x0, 0xd0, 
    0x74, 0x2c, 0xb, 0x0, 0xc0, 0xf, 0xff, 

    /* U+33 "3" */
    0x3f, 0xa0, 0x30, 0x8, 0x3, 0x3f, 0x0, 0x30, 
    0x4, 0x1, 0x80, 0xdf, 0x34, 

    /* U+34 "4" */
    0x0, 0x70, 0x3, 0xc0, 0x2f, 0x0, 0xdc, 0xd, 
    0x30, 0xa0, 0xc7, 0x3, 0x3f, 0xff, 0x0, 0x30, 
    0x0, 0x30, 

    /* U+35 "5" */
    0x7f, 0xd7, 0x0, 0x60, 0x6, 0x0, 0xbf, 0x80, 
    0xe, 0x0, 0x70, 0x7, 0x40, 0xd7, 0xf4, 

    /* U+37 "7" */
    0x7f, 0xfc, 0x0, 0x70, 0x3, 0x0, 0x18, 0x0, 
    0xc0, 0xa, 0x0, 0x30, 0x1, 0xc0, 0xd, 0x0, 
    0x34, 0x0, 

    /* U+38 "8" */
    0x2f, 0xcb, 0xb, 0xd0, 0x37, 0xa, 0x1f, 0x8a, 
    0x7, 0xc0, 0x3c, 0x3, 0xd0, 0x73, 0xfc, 

    /* U+39 "9" */
    0x3f, 0x8d, 0xd, 0xc0, 0x3c, 0x3, 0xd0, 0xb3, 
    0xf7, 0x0, 0x30, 0x6, 0x1, 0xcf, 0xf0, 

    /* U+3a ":" */
    0xcc, 0x0, 0xc, 0x30, 

    /* U+3c "<" */
    0x0, 0x20, 0x3c, 0x3c, 0xe, 0x0, 0x3d, 0x0, 
    0x3c, 0x0, 0x8, 

    /* U+41 "A" */
    0x1, 0xd0, 0x0, 0xb8, 0x0, 0x37, 0x0, 0x18, 
    0xd0, 0xd, 0x1c, 0x3, 0x3, 0x2, 0xff, 0xd0, 
    0xd0, 0x1c, 0x70, 0x3, 0x68, 0x0, 0x28, 

    /* U+42 "B" */
    0xff, 0xf4, 0x2d, 0x7, 0x43, 0xff, 0xb4, 0x1d, 
    0x3, 0x40, 0xd0, 0x7f, 0x3c, 

    /* U+43 "C" */
    0x7, 0xf4, 0xf0, 0x1a, 0x0, 0x30, 0x0, 0xc0, 
    0x3, 0x0, 0xc, 0x0, 0x34, 0x0, 0x38, 0x8, 
    0x3f, 0x34, 

    /* U+45 "E" */
    0xff, 0xf4, 0xd, 0x3, 0x40, 0xff, 0xf4, 0xd, 
    0x3, 0x40, 0xd0, 0x3f, 0x3c, 

    /* U+46 "F" */
    0xbf, 0xe4, 0x9, 0x2, 0x40, 0xbf, 0xe4, 0x9, 
    0x2, 0x40, 0x90, 0x24, 0x0, 

    /* U+47 "G" */
    0x7, 0xfc, 0x3c, 0x6, 0xa0, 0x0, 0xc0, 0x0, 
    0xc0, 0x0, 0xc0, 0xbf, 0xc0, 0x7, 0xd0, 0x7, 
    0x38, 0x7, 0xf, 0xfd, 

    /* U+4f "O" */
    0xf, 0xfc, 0xe, 0x1, 0xce, 0x0, 0x2f, 0x0, 
    0x3, 0xc0, 0x0, 0xf0, 0x0, 0x3c, 0x0, 0xf, 
    0x40, 0xa, 0x34, 0xb, 0x3, 0xfe, 0x0, 

    /* U+50 "P" */
    0xbf, 0xc9, 0x7, 0x90, 0x39, 0x3, 0x90, 0x7b, 
    0xfc, 0x90, 0x9, 0x0, 0x90, 0x9, 0x0, 

    /* U+51 "Q" */
    0xf, 0xfc, 0x3, 0x80, 0x70, 0xe0, 0x2, 0xcc, 
    0x0, 0xc, 0xc0, 0x0, 0xdc, 0x0, 0xc, 0xc0, 
    0x0, 0xcd, 0x0, 0x28, 0x34, 0xb, 0x0, 0xff, 
    0xf0, 0x0, 0x3, 0x3c, 

    /* U+52 "R" */
    0xff, 0xc3, 0x43, 0x8d, 0x7, 0x34, 0x1c, 0xd0, 
    0xd3, 0xfc, 0xd, 0x2c, 0x34, 0x34, 0xd0, 0x73, 
    0x40, 0x3c, 

    /* U+55 "U" */
    0xd0, 0x7, 0x40, 0x1d, 0x0, 0x74, 0x1, 0xd0, 
    0x7, 0x40, 0x19, 0x0, 0x68, 0x2, 0x34, 0x1c, 
    0x3f, 0x30, 

    /* U+56 "V" */
    0xa0, 0x2, 0x9c, 0x0, 0xd3, 0x40, 0x70, 0xa0, 
    0x28, 0xc, 0xc, 0x3, 0x47, 0x0, 0x72, 0x40, 
    0xd, 0xc0, 0x3, 0xf0, 0x0, 0x74, 0x0, 

    /* U+57 "W" */
    0xb0, 0xd, 0x2, 0x9c, 0x7, 0x80, 0xd3, 0x42, 
    0xf0, 0x30, 0xd0, 0xec, 0x1c, 0x1c, 0x33, 0x4a, 
    0x7, 0x18, 0xa3, 0x40, 0xd9, 0x1d, 0xc0, 0x2b, 
    0x3, 0xb0, 0x7, 0xc0, 0xf4, 0x0, 0xe0, 0x1d, 
    0x0, 

    /* U+58 "X" */
    0x74, 0xd, 0x2c, 0x1c, 0xd, 0x34, 0xb, 0xb0, 
    0x3, 0xc0, 0x3, 0xd0, 0xa, 0xb0, 0x1c, 0x34, 
    0x34, 0x2c, 0xb0, 0xe, 

    /* U+5a "Z" */
    0x7f, 0xfd, 0x0, 0x1c, 0x0, 0x34, 0x0, 0xe0, 
    0x1, 0xc0, 0x3, 0x40, 0xa, 0x0, 0x1c, 0x0, 
    0x34, 0x0, 0xbf, 0xfd, 

    /* U+5c "\" */
    0xc0, 0x24, 0x3, 0x0, 0xd0, 0x18, 0x3, 0x0, 
    0x90, 0x1c, 0x3, 0x40, 0x60, 0x6, 

    /* U+5e "^" */
    0x5, 0x0, 0xf0, 0x2a, 0x43, 0xc, 0x90, 0x6c, 
    0x3, 

    /* U+5f "_" */
    0xff, 0x3c, 

    /* U+61 "a" */
    0x3f, 0x50, 0x70, 0xf, 0xff, 0xc0, 0xf0, 0xbf, 
    0x76, 

    /* U+62 "b" */
    0xd0, 0xd, 0x0, 0xd0, 0xd, 0xfd, 0xf0, 0x7d, 
    0x3, 0xd0, 0x3d, 0x3, 0xf0, 0x7e, 0xfc, 

    /* U+63 "c" */
    0x1f, 0xec, 0xc, 0x3, 0x0, 0xc0, 0x3c, 0x2, 
    0x7e, 

    /* U+64 "d" */
    0x0, 0x70, 0x7, 0x0, 0x73, 0xfb, 0xd0, 0xfc, 
    0x7, 0xc0, 0x7c, 0x7, 0xd0, 0xf3, 0xf7, 

    /* U+65 "e" */
    0x3f, 0x74, 0x3c, 0xf, 0xff, 0xc0, 0x34, 0x23, 
    0x7a, 

    /* U+66 "f" */
    0x1f, 0x30, 0x70, 0xfe, 0x70, 0x70, 0x70, 0x70, 
    0x70, 0x70, 

    /* U+67 "g" */
    0x3f, 0xbd, 0xf, 0xc0, 0x7c, 0x7, 0xc0, 0x7d, 
    0xf, 0x3f, 0x70, 0x7, 0x80, 0xd3, 0xf4, 

    /* U+68 "h" */
    0xd0, 0xd, 0x0, 0xd0, 0xd, 0xfd, 0xf0, 0xbd, 
    0x3, 0xd0, 0x3d, 0x3, 0xd0, 0x3d, 0x3, 

    /* U+69 "i" */
    0xcc, 0xc, 0xcc, 0xcc, 0xcc, 

    /* U+6b "k" */
    0xd0, 0xd, 0x0, 0xd0, 0xd, 0x1d, 0xd3, 0x4d, 
    0xd0, 0xfc, 0xd, 0xe0, 0xd3, 0x8d, 0xf, 

    /* U+6c "l" */
    0xff, 0xff, 0x3c, 

    /* U+6d "m" */
    0xdf, 0xcb, 0xdf, 0xf, 0x47, 0xd0, 0x70, 0x3d, 
    0x6, 0x3, 0xd0, 0x60, 0x3d, 0x6, 0x3, 0xd0, 
    0x60, 0xc, 

    /* U+6e "n" */
    0xdf, 0xcf, 0xb, 0xd0, 0x3d, 0x3, 0xd0, 0x3d, 
    0x3, 0xd0, 0xc, 

    /* U+6f "o" */
    0x3f, 0xce, 0x7, 0xc0, 0x3c, 0x3, 0xc0, 0x3e, 
    0x7, 0x3f, 0x30, 

    /* U+70 "p" */
    0xdf, 0xdf, 0x7, 0xd0, 0x3d, 0x3, 0xd0, 0x3f, 
    0x7, 0xef, 0xcd, 0x0, 0xd0, 0xd, 0x0, 

    /* U+71 "q" */
    0x3f, 0xfd, 0xf, 0xc0, 0x7c, 0x7, 0xc0, 0x7d, 
    0xf, 0x3f, 0x70, 0x7, 0x0, 0x70, 0x7, 

    /* U+72 "r" */
    0xdf, 0xf0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 

    /* U+73 "s" */
    0x7e, 0xc1, 0xd0, 0x7d, 0x3, 0x43, 0xfe, 

    /* U+74 "t" */
    0x70, 0x70, 0xfe, 0x70, 0x70, 0x70, 0x70, 0x70, 
    0x3e, 

    /* U+75 "u" */
    0xd0, 0x7d, 0x7, 0xd0, 0x7d, 0x7, 0xd0, 0x7e, 
    0xf, 0x3f, 0x2c, 

    /* U+76 "v" */
    0xa0, 0x1d, 0xc0, 0xd3, 0x47, 0x6, 0x24, 0xc, 
    0xc0, 0x3a, 0x0, 0x74, 0x0, 

    /* U+77 "w" */
    0xa0, 0x70, 0x67, 0xb, 0x9, 0x30, 0x94, 0xc3, 
    0x55, 0x88, 0x1a, 0xa, 0x80, 0xe0, 0xb4, 0xe, 
    0x7, 0x0, 

    /* U+78 "x" */
    0x70, 0x38, 0xa1, 0xc0, 0xec, 0x0, 0xd0, 0xe, 
    0xc0, 0xa2, 0x8b, 0x3, 0x10, 

    /* U+79 "y" */
    0xe0, 0x1d, 0xc0, 0xd3, 0x47, 0x6, 0x24, 0xd, 
    0xc0, 0x2e, 0x0, 0x70, 0x1, 0xc0, 0xd, 0x2, 
    0xd0, 0x0, 

    /* U+7a "z" */
    0x7f, 0xe0, 0x1c, 0x3, 0x40, 0xa0, 0x1c, 0x3, 
    0x40, 0xbf, 0x38, 

    /* U+4e00 "一" */
    0xff, 0xff, 0xff, 0x18, 

    /* U+4e09 "三" */
    0x3f, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
    0x7, 0xff, 0xff, 0x40, 0x0, 0x0, 0x0, 0x0, 
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
    0xb, 0xff, 0xff, 0x7c, 

    /* U+4e8c "二" */
    0x2f, 0xff, 0xfe, 0x0, 0x0, 0x0, 0x0, 0x0, 
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
    0x0, 0x0, 0xbf, 0xff, 0xff, 0x8, 

    /* U+4e94 "五" */
    0xbf, 0xff, 0xff, 0x0, 0x14, 0x0, 0x0, 0x9, 
    0x0, 0x0, 0x2, 0x0, 0x0, 0x7f, 0xff, 0xf4, 
    0x0, 0x20, 0x5, 0x0, 0x18, 0x1, 0x40, 0x5, 
    0x0, 0x50, 0x2, 0x40, 0x14, 0x0, 0x80, 0x5, 
    0x0, 0x30, 0x1, 0x43, 0xff, 0xff, 0xfe, 

    /* U+4f5c "作" */
    0x3, 0x8, 0x0, 0x1, 0x42, 0x0, 0x0, 0x82, 
    0xff, 0xfc, 0x30, 0x88, 0x0, 0x1c, 0xd2, 0x0, 
    0xf, 0x60, 0xff, 0xd6, 0xc0, 0x20, 0x2, 0x30, 
    0x8, 0x0, 0xc, 0x2, 0x0, 0x3, 0x0, 0xff, 
    0xd0, 0xc0, 0x20, 0x0, 0x30, 0x8, 0x0, 

    /* U+5149 "光" */
    0x0, 0x8, 0x0, 0x9, 0x2, 0x1, 0x40, 0xd0, 
    0x82, 0x80, 0x8, 0x21, 0x40, 0x0, 0x8, 0x0, 
    0x2f, 0xff, 0xff, 0xd0, 0xc, 0x14, 0x0, 0x2, 
    0x5, 0x0, 0x1, 0x81, 0x40, 0x0, 0xc0, 0x50, 
    0x20, 0xd0, 0x14, 0x1a, 0xc0, 0x3, 0xfd, 

    /* U+516d "六" */
    0x0, 0x24, 0x0, 0x0, 0x3, 0x0, 0x0, 0x0, 
    0x50, 0x1, 0xff, 0xff, 0xff, 0x0, 0x0, 0x0, 
    0x0, 0x0, 0x0, 0x0, 0x8, 0x8, 0x0, 0x5, 
    0x1, 0xc0, 0x2, 0x0, 0x28, 0x3, 0x0, 0x3, 
    0x43, 0x40, 0x0, 0x31, 0x40, 0x0, 0x5, 

    /* U+529f "功" */
    0x0, 0x2, 0x0, 0xbf, 0xd2, 0x0, 0x8, 0x2, 
    0x0, 0x8, 0x3f, 0xff, 0x8, 0x3, 0x3, 0x8, 
    0x3, 0x3, 0x8, 0x2, 0x3, 0x8, 0x6, 0x3, 
    0xf, 0xdd, 0x3, 0xbc, 0x2c, 0x3, 0x0, 0x70, 
    0x7, 0x2, 0xc1, 0xfd, 

    /* U+538b "压" */
    0x7f, 0xff, 0xfe, 0x60, 0x0, 0x0, 0x60, 0x8, 
    0x0, 0x60, 0x8, 0x0, 0x60, 0x8, 0x0, 0x67, 
    0xff, 0xfc, 0x50, 0x8, 0x0, 0x50, 0x8, 0x50, 
    0x90, 0x8, 0x20, 0x80, 0x8, 0x8, 0xc0, 0x8, 
    0x0, 0x5f, 0xff, 0xfe, 

    /* U+53c2 "参" */
    0x0, 0xd0, 0x0, 0xb, 0x3, 0x0, 0x3f, 0xff, 
    0xd0, 0x0, 0xc0, 0x20, 0xff, 0xff, 0xfd, 0xa, 
    0x1a, 0x40, 0x35, 0xe0, 0xb0, 0xde, 0xf, 0x4e, 
    0x3, 0xf4, 0x60, 0x2e, 0x7, 0x80, 0x0, 0xf8, 
    0x0, 0x3f, 0x0, 0x0, 

    /* U+54c1 "品" */
    0x3f, 0xff, 0xf0, 0x80, 0x0, 0x82, 0x0, 0x2, 
    0xf, 0xff, 0xfc, 0x20, 0x0, 0x20, 0x0, 0x0, 
    0xf, 0xf8, 0xbf, 0xe0, 0x62, 0x42, 0x81, 0x89, 
    0xa, 0x6, 0x24, 0x2f, 0xf8, 0xbf, 0xe0, 0x62, 
    0x42, 

    /* U+56db "四" */
    0xff, 0xff, 0xfe, 0x6, 0x14, 0x38, 0x18, 0x50, 
    0xe0, 0x51, 0x43, 0x81, 0x45, 0xe, 0x8, 0x14, 
    0x38, 0xa0, 0x3f, 0xeb, 0x0, 0x3, 0x80, 0x0, 
    0xe, 0x0, 0x0, 0x3f, 0xff, 0xff, 0xe0, 0x0, 
    0x3, 

    /* U+5ea6 "度" */
    0x0, 0x28, 0x0, 0x7f, 0xff, 0xfe, 0x51, 0x80, 
    0x80, 0x7f, 0xff, 0xfd, 0x51, 0x80, 0x80, 0x51, 
    0xff, 0xc0, 0x50, 0x0, 0x0, 0x9f, 0xff, 0xf0, 
    0x82, 0x40, 0xd0, 0xc0, 0xa3, 0x40, 0x80, 0xbf, 
    0x0, 0x7f, 0x40, 0xfe, 

    /* U+65e5 "日" */
    0xff, 0xff, 0xf0, 0x0, 0x2c, 0x0, 0xb, 0x0, 
    0x2, 0xc0, 0x0, 0xbf, 0xff, 0xfc, 0x0, 0xb, 
    0x0, 0x2, 0xc0, 0x0, 0xb0, 0x0, 0x2f, 0xff, 
    0xff, 0x0, 0x2, 

    /* U+661f "星" */
    0xf, 0xff, 0xfd, 0x8, 0x0, 0x5, 0xf, 0xff, 
    0xfd, 0x8, 0x0, 0x5, 0xf, 0xff, 0xfd, 0x0, 
    0x0, 0x5, 0x5, 0x9, 0x0, 0xf, 0xff, 0xff, 
    0x34, 0x9, 0x0, 0x6f, 0xff, 0xff, 0x0, 0x9, 
    0x0, 0x7f, 0xff, 0xff, 

    /* U+671f "期" */
    0x14, 0x31, 0xff, 0xbf, 0xfd, 0x82, 0x14, 0x31, 
    0x82, 0x1f, 0xf1, 0xff, 0x14, 0x31, 0x82, 0x1f, 
    0xf1, 0x82, 0x14, 0x31, 0x82, 0x14, 0x31, 0xff, 
    0xff, 0xfe, 0x42, 0x8, 0xd2, 0x2, 0x34, 0x3b, 
    0x2, 0x90, 0x8, 0x3f, 

    /* U+6d41 "流" */
    0xc0, 0xd, 0x0, 0x3b, 0xff, 0xfd, 0x0, 0x34, 
    0x0, 0x80, 0xa0, 0x50, 0x72, 0x80, 0x20, 0x3, 
    0xff, 0xfc, 0x0, 0x0, 0x5, 0x21, 0x88, 0x50, 
    0x61, 0x48, 0x50, 0x92, 0x48, 0x53, 0xc7, 0x8, 
    0x52, 0xec, 0x8, 0x7d, 

    /* U+6de6 "淦" */
    0xc0, 0xb, 0x0, 0x70, 0x1e, 0x40, 0x18, 0x70, 
    0xd0, 0x42, 0xc0, 0x2c, 0xca, 0xbf, 0xf7, 0x60, 
    0x5, 0x0, 0x0, 0x5, 0x0, 0x27, 0xff, 0xfc, 
    0x50, 0x5, 0x0, 0x92, 0x5, 0x18, 0xc0, 0xc5, 
    0x60, 0x8f, 0xff, 0xfe, 

    /* U+6e29 "温" */
    0xc1, 0xff, 0xf4, 0x35, 0x40, 0x14, 0x1, 0xff, 
    0xf4, 0x81, 0x40, 0x14, 0x71, 0xff, 0xf4, 0x1, 
    0x40, 0x14, 0x20, 0x0, 0x0, 0x63, 0xff, 0xfc, 
    0x93, 0x25, 0x48, 0x83, 0x25, 0x48, 0xc3, 0x25, 
    0x48, 0xdf, 0xff, 0xff, 

    /* U+6e7f "湿" */
    0x30, 0x7f, 0xff, 0x3, 0x14, 0x0, 0xc0, 0x7, 
    0xff, 0xf2, 0xc1, 0x40, 0xc, 0x1c, 0x7f, 0xff, 
    0x0, 0x14, 0x0, 0xc0, 0x80, 0x93, 0x8, 0x56, 
    0x24, 0xc8, 0x24, 0xd9, 0x36, 0x8, 0x1e, 0x4f, 
    0x43, 0x0, 0x93, 0x1, 0x8b, 0xff, 0xff, 

    /* U+7387 "率" */
    0x0, 0x30, 0x0, 0xff, 0xff, 0xfd, 0x0, 0x70, 
    0x0, 0x82, 0x47, 0xc, 0x27, 0xfc, 0x30, 0x18, 
    0x25, 0x60, 0xf2, 0xc2, 0x2c, 0x87, 0xfe, 0x85, 
    0x0, 0x20, 0x0, 0xff, 0xff, 0xff, 0x0, 0x20, 
    0x0, 0x0, 0x20, 0x0, 

    /* U+7535 "电" */
    0x0, 0x50, 0x0, 0x0, 0x50, 0x0, 0xff, 0xff, 
    0xf0, 0x80, 0x50, 0x20, 0x80, 0x50, 0x20, 0xff, 
    0xff, 0xf0, 0x80, 0x50, 0x20, 0x80, 0x50, 0x20, 
    0xff, 0xff, 0xf0, 0x80, 0x50, 0x6, 0x0, 0x50, 
    0x9, 0x0, 0x3f, 0xfc, 

    /* U+7684 "的" */
    0x24, 0x2, 0x0, 0xc0, 0x24, 0xf, 0xf4, 0xff, 
    0xe0, 0x55, 0x2, 0x81, 0xa0, 0xa, 0x5, 0x30, 
    0x2f, 0xf4, 0x30, 0xa0, 0x50, 0x22, 0x81, 0x40, 
    0xa, 0x5, 0x0, 0x3f, 0xf4, 0x0, 0xe0, 0x51, 
    0xfd, 

    /* U+8005 "者" */
    0x0, 0x24, 0x0, 0x0, 0x9, 0x1, 0x81, 0xff, 
    0xff, 0xc0, 0x0, 0x93, 0x80, 0xbf, 0xff, 0xff, 
    0xc0, 0xb, 0x0, 0x0, 0x7f, 0xff, 0xc3, 0xf8, 
    0x0, 0x20, 0x3, 0xff, 0xfc, 0x0, 0x80, 0x2, 
    0x0, 0x3f, 0xff, 0xc0, 0x8, 0x0, 0x20, 

    /* U+8d5b "赛" */
    0x0, 0x1c, 0x0, 0x1f, 0xff, 0xff, 0xd6, 0x9, 
    0x8, 0x24, 0x3f, 0xff, 0xf0, 0x0, 0x90, 0x80, 
    0x1f, 0xff, 0xff, 0xd0, 0x18, 0x5, 0x0, 0x3f, 
    0xff, 0xf0, 0xb3, 0x8, 0x27, 0x80, 0xc2, 0x8, 
    0x0, 0x7, 0x7f, 0x40, 0xbe, 0x0, 0x2c, 

    /* U+8ffd "追" */
    0x10, 0x2, 0x0, 0x8, 0x1, 0x40, 0x0, 0x87, 
    0xff, 0xd0, 0x21, 0x40, 0x14, 0x0, 0x7f, 0xfd, 
    0x2e, 0x14, 0x0, 0x1, 0x87, 0xff, 0xe0, 0x61, 
    0x40, 0x18, 0x18, 0x50, 0x6, 0x6, 0x1f, 0xff, 
    0x83, 0xd5, 0x0, 0x62, 0xb, 0xff, 0xfe, 

    /* U+963b "阻" */
    0xfd, 0x7f, 0xf4, 0x89, 0x50, 0x14, 0x8c, 0x50, 
    0x14, 0x94, 0x50, 0x14, 0xa0, 0x7f, 0xf4, 0x98, 
    0x50, 0x14, 0x88, 0x50, 0x14, 0x89, 0x7f, 0xf4, 
    0x89, 0x50, 0x14, 0xfc, 0x50, 0x14, 0x80, 0x50, 
    0x14, 0x83, 0xff, 0xff, 

    /* U+9e7f "鹿" */
    0x0, 0xd, 0x0, 0x7, 0xff, 0xff, 0xe1, 0x82, 
    0x8, 0x0, 0x7f, 0xff, 0xfc, 0x18, 0x20, 0x82, 
    0x6, 0x8, 0x20, 0x81, 0xff, 0xff, 0xf0, 0x66, 
    0x2, 0x8, 0x15, 0xfd, 0x87, 0xd, 0x60, 0x3e, 
    0x7, 0x19, 0xd8, 0xa, 0x47, 0x43, 0xfd, 

    /* U+9e8b "麋" */
    0x0, 0x6, 0x0, 0xb, 0xff, 0xff, 0xe2, 0x46, 
    0x8, 0x20, 0xbf, 0xff, 0xfc, 0x25, 0x41, 0x80, 
    0x9, 0x57, 0xb0, 0x62, 0x7d, 0xf, 0xf4, 0x8b, 
    0x18, 0x34, 0x20, 0x76, 0x34, 0xf, 0xff, 0xff, 
    0xe5, 0x3, 0xad, 0x2, 0x7f, 0x18, 0x7f, 
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
/* id = 0 reserved */  {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
/* U+20 " " */  {.bitmap_index = 0, .adv_w = 56, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = -1},
/* U+23 "#" */  {.bitmap_index = 1, .adv_w = 120, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
/* U+25 "%" */  {.bitmap_index = 19, .adv_w = 184, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
/* U+2a "*" */  {.bitmap_index = 47, .adv_w = 88, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 4},
/* U+2c "," */  {.bitmap_index = 56, .adv_w = 40, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = -2},
/* U+2d "-" */  {.bitmap_index = 58, .adv_w = 88, .box_w = 4, .box_h = 1, .ofs_x = 1, .ofs_y = 3},
/* U+2e "." */  {.bitmap_index = 59, .adv_w = 40, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
/* U+2f "/" */  {.bitmap_index = 60, .adv_w = 88, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
/* U+30 "0" */  {.bitmap_index = 78, .adv_w = 120, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
/* U+31 "1" */  {.bitmap_index = 93, .adv_w = 120, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
/* U+32 "2" */  {.bitmap_index = 103, .adv_w = 120, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
/* U+33 "3" */  {.bitmap_index = 118, .adv_w = 120, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
/* U+34 "4" */  {.bitmap_index = 131, .adv_w = 120, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
/* U+35 "5" */  {.bitmap_index = 149, .adv_w = 120, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
/* U+37 "7" */  {.bitmap_index = 164, .adv_w = 120, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
/* U+38 "8" */  {.bitmap_index = 182, .adv_w = 120, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
/* U+39 "9" */  {.bitmap_index = 197, .adv_w = 120, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
/* U+3a ":" */  {.bitmap_index = 212, .adv_w = 40, .box_w = 2, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
/* U+3c "<" */  {.bitmap_index = 216, .adv_w = 152, .box_w = 6, .box_h = 7, .ofs_x = 2, .ofs_y = 1},
/* U+41 "A" */  {.bitmap_index = 227, .adv_w = 136, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
/* U+42 "B" */  {.bitmap_index = 250, .adv_w = 120, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
/* U+43 "C" */  {.bitmap_index = 263, .adv_w = 136, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
/* U+45 "E" */  {.bitmap_index = 281, .adv_w = 104, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
/* U+46 "F" */  {.bitmap_index = 294, .adv_w = 104, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
/* U+47 "G" */  {.bitmap_index = 307, .adv_w = 152, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
/* U+4f "O" */  {.bitmap_index = 327, .adv_w = 168, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
/* U+50 "P" */  {.bitmap_index = 350, .adv_w = 120, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
/* U+51 "Q" */  {.bitmap_index = 365, .adv_w = 168, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
/* U+52 "R" */  {.bitmap_index = 393, .adv_w = 120, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
/* U+55 "U" */  {.bitmap_index = 411, .adv_w = 152, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
/* U+56 "V" */  {.bitmap_index = 429, .adv_w = 136, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
/* U+57 "W" */  {.bitmap_index = 452, .adv_w = 200, .box_w = 13, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
/* U+58 "X" */  {.bitmap_index = 485, .adv_w = 120, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
/* U+5a "Z" */  {.bitmap_index = 505, .adv_w = 120, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
/* U+5c "\" */  {.bitmap_index = 525, .adv_w = 72, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
/* U+5e "^" */  {.bitmap_index = 539, .adv_w = 152, .box_w = 6, .box_h = 6, .ofs_x = 2, .ofs_y = 4},
/* U+5f "_" */  {.bitmap_index = 548, .adv_w = 88, .box_w = 6, .box_h = 1, .ofs_x = 0, .ofs_y = -3},
/* U+61 "a" */  {.bitmap_index = 550, .adv_w = 104, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
/* U+62 "b" */  {.bitmap_index = 559, .adv_w = 120, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
/* U+63 "c" */  {.bitmap_index = 574, .adv_w = 104, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
/* U+64 "d" */  {.bitmap_index = 583, .adv_w = 120, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
/* U+65 "e" */  {.bitmap_index = 598, .adv_w = 104, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
/* U+66 "f" */  {.bitmap_index = 607, .adv_w = 72, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
/* U+67 "g" */  {.bitmap_index = 617, .adv_w = 120, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
/* U+68 "h" */  {.bitmap_index = 632, .adv_w = 120, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
/* U+69 "i" */  {.bitmap_index = 647, .adv_w = 40, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
/* U+6b "k" */  {.bitmap_index = 652, .adv_w = 104, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
/* U+6c "l" */  {.bitmap_index = 667, .adv_w = 40, .box_w = 1, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
/* U+6d "m" */  {.bitmap_index = 670, .adv_w = 184, .box_w = 10, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
/* U+6e "n" */  {.bitmap_index = 688, .adv_w = 120, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
/* U+6f "o" */  {.bitmap_index = 699, .adv_w = 120, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
/* U+70 "p" */  {.bitmap_index = 710, .adv_w = 120, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
/* U+71 "q" */  {.bitmap_index = 725, .adv_w = 120, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
/* U+72 "r" */  {.bitmap_index = 740, .adv_w = 72, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
/* U+73 "s" */  {.bitmap_index = 747, .adv_w = 88, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
/* U+74 "t" */  {.bitmap_index = 754, .adv_w = 72, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
/* U+75 "u" */  {.bitmap_index = 763, .adv_w = 120, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
/* U+76 "v" */  {.bitmap_index = 774, .adv_w = 104, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
/* U+77 "w" */  {.bitmap_index = 787, .adv_w = 152, .box_w = 10, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
/* U+78 "x" */  {.bitmap_index = 805, .adv_w = 104, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
/* U+79 "y" */  {.bitmap_index = 818, .adv_w = 104, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
/* U+7a "z" */  {.bitmap_index = 836, .adv_w = 88, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
/* U+4e00 "一" */  {.bitmap_index = 847, .adv_w = 200, .box_w = 13, .box_h = 1, .ofs_x = 0, .ofs_y = 4},
/* U+4e09 "三" */  {.bitmap_index = 851, .adv_w = 200, .box_w = 13, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
/* U+4e8c "二" */  {.bitmap_index = 887, .adv_w = 200, .box_w = 13, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
/* U+4e94 "五" */  {.bitmap_index = 917, .adv_w = 200, .box_w = 13, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
/* U+4f5c "作" */  {.bitmap_index = 956, .adv_w = 200, .box_w = 13, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
/* U+5149 "光" */  {.bitmap_index = 995, .adv_w = 200, .box_w = 13, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
/* U+516d "六" */  {.bitmap_index = 1034, .adv_w = 200, .box_w = 13, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
/* U+529f "功" */  {.bitmap_index = 1073, .adv_w = 200, .box_w = 12, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
/* U+538b "压" */  {.bitmap_index = 1109, .adv_w = 200, .box_w = 12, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
/* U+53c2 "参" */  {.bitmap_index = 1145, .adv_w = 200, .box_w = 12, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
/* U+54c1 "品" */  {.bitmap_index = 1181, .adv_w = 200, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
/* U+56db "四" */  {.bitmap_index = 1214, .adv_w = 200, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
/* U+5ea6 "度" */  {.bitmap_index = 1247, .adv_w = 200, .box_w = 12, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
/* U+65e5 "日" */  {.bitmap_index = 1283, .adv_w = 200, .box_w = 9, .box_h = 12, .ofs_x = 2, .ofs_y = -1},
/* U+661f "星" */  {.bitmap_index = 1310, .adv_w = 200, .box_w = 12, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
/* U+671f "期" */  {.bitmap_index = 1346, .adv_w = 200, .box_w = 12, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
/* U+6d41 "流" */  {.bitmap_index = 1382, .adv_w = 200, .box_w = 12, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
/* U+6de6 "淦" */  {.bitmap_index = 1418, .adv_w = 200, .box_w = 12, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
/* U+6e29 "温" */  {.bitmap_index = 1454, .adv_w = 200, .box_w = 12, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
/* U+6e7f "湿" */  {.bitmap_index = 1490, .adv_w = 200, .box_w = 13, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
/* U+7387 "率" */  {.bitmap_index = 1529, .adv_w = 200, .box_w = 12, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
/* U+7535 "电" */  {.bitmap_index = 1565, .adv_w = 200, .box_w = 12, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
/* U+7684 "的" */  {.bitmap_index = 1601, .adv_w = 200, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
/* U+8005 "者" */  {.bitmap_index = 1634, .adv_w = 200, .box_w = 13, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
/* U+8d5b "赛" */  {.bitmap_index = 1673, .adv_w = 200, .box_w = 13, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
/* U+8ffd "追" */  {.bitmap_index = 1712, .adv_w = 200, .box_w = 13, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
/* U+963b "阻" */  {.bitmap_index = 1751, .adv_w = 200, .box_w = 12, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
/* U+9e7f "鹿" */  {.bitmap_index = 1787, .adv_w = 200, .box_w = 13, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
/* U+9e8b "麋" */  {.bitmap_index = 1826, .adv_w = 200, .box_w = 13, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_1[] = {

    0x20, 0x23, 0x25, 0x2a, 0x2c, 0x2d, 0x2e, 0x2f, 
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x37, 0x38, 
    0x39, 0x3a, 0x3c, 0x41, 0x42, 0x43, 0x45, 0x46, 
    0x47, 0x4f, 0x50, 0x51, 0x52, 0x55, 0x56, 0x57, 
    0x58, 0x5a, 0x5c, 0x5e, 0x5f, 0x61, 0x62, 0x63, 
    0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6b, 0x6c, 
    0x6d, 0x6e, 0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 
    0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x4e00, 0x4e09, 
    0x4e8c, 0x4e94, 0x4f5c, 0x5149, 0x516d, 0x529f, 0x538b, 0x53c2, 
    0x54c1, 0x56db, 0x5ea6, 0x65e5, 0x661f, 0x671f, 0x6d41, 0x6de6, 
    0x6e29, 0x6e7f, 0x7387, 0x7535, 0x7684, 0x8005, 0x8d5b, 0x8ffd, 
    0x963b, 0x9e7f, 0x9e8b, 
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 0, .range_length = 40587, .glyph_id_start = 1,
        .unicode_list = unicode_list_1, .glyph_id_ofs_list = NULL, .list_length = 91, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/
/*Store all the custom data of the font*/
static lv_font_fmt_txt_dsc_t font_dsc = {
    .glyph_bitmap = gylph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 2,
    .kern_classes = 0,
    .bitmap_format = 0
};

/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
lv_font_t lv_font_msYaHei = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 19,          /*The maximum line height required by the font*/
    .base_line = 4,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};
#endif /*#if LV_FONT_MSYAHEI*/
