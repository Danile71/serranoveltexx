/*
 * =================================================================
 *
 *
 *	Description:  samsung display panel file
 *
 *	Author: jb09.kim
 *	Company:  Samsung Electronics
 *
 * ================================================================
 */
/*
<one line to give the program's name and a brief idea of what it does.>
Copyright (C) 2012, Samsung Electronics. All rights reserved.

*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
*/
#ifndef _SAMSUNG_DSI_SMART_DIMMING_S6E88A0_SDC_AMS427AP24_H_
#define _SAMSUNG_DSI_SMART_DIMMING_S6E88A0_SDC_AMS427AP24_H_

#include "../ss_dsi_panel_common.h"
#include "../ss_dsi_smart_dimming_common.h"

/*
*	From 4.8 inch model use AID function
*	CASE#1 is used for now.
*/
#define AID_OPERATION

enum {
	GAMMA_CURVE_1P95 = 0,
	GAMMA_CURVE_2P0,
	GAMMA_CURVE_2P05,
	GAMMA_CURVE_2P1,
	GAMMA_CURVE_2P12,
	GAMMA_CURVE_2P2,
};

#define REV_A	0x00
#define REV_C	0x01

#define LUMINANCE_MAX 62
#define GAMMA_SET_MAX 33
#define BIT_SHIFT 22
/*
	it means BIT_SHIFT is 22.  pow(2,BIT_SHIFT) is 4194304.
	BIT_SHIFT is used for right bit shfit
*/
#define BIT_SHFIT_MUL 4194304

#define GRAY_SCALE_MAX 256

/* 6.1 * 4194304 */
#define VREG0_REF_6P1 25585254

/*V0,V3,V11,V23,V35,V51,V87,V151,V203,V255*/
#define ARRAY_MAX 11

/* PANEL DEPENDENT THINGS */
#define MIN_CANDELA	20

/*
*	ID 0x20
*/
#define V255_300CD_R_MSB_20 0x01
#define V255_300CD_R_LSB_20 0x00

#define V255_300CD_G_MSB_20 0x01
#define V255_300CD_G_LSB_20 0x00

#define V255_300CD_B_MSB_20 0x01
#define V255_300CD_B_LSB_20 0x00

#define V203_300CD_R_20 0x80
#define V203_300CD_G_20 0x80
#define V203_300CD_B_20 0x80

#define V151_300CD_R_20 0x80
#define V151_300CD_G_20 0x80
#define V151_300CD_B_20 0x80

#define V87_300CD_R_20 0x80
#define V87_300CD_G_20 0x80
#define V87_300CD_B_20 0x80

#define V51_300CD_R_20 0x80
#define V51_300CD_G_20 0x80
#define V51_300CD_B_20 0x80

#define V35_300CD_R_20 0x80
#define V35_300CD_G_20 0x80
#define V35_300CD_B_20 0x80

#define V23_300CD_R_20 0x80
#define V23_300CD_G_20 0x80
#define V23_300CD_B_20 0x80

#define V11_300CD_R_20 0x80
#define V11_300CD_G_20 0x80
#define V11_300CD_B_20 0x80

#define V3_300CD_R_20 0x80
#define V3_300CD_G_20 0x80
#define V3_300CD_B_20 0x80

#define VT_300CD_R_20 0x00
#define VT_300CD_G_20 0x00
#define VT_300CD_B_20 0x00

/* PANEL DEPENDENT THINGS END*/

enum {
	V1_INDEX = 0,
	V3_INDEX = 1,
	V11_INDEX = 2,
	V23_INDEX = 3,
	V35_INDEX = 4,
	V51_INDEX = 5,
	V87_INDEX = 6,
	V151_INDEX = 7,
	V203_INDEX = 8,
	V255_INDEX = 9,
};

struct GAMMA_LEVEL {
	int level_0;
	int level_1;
	int level_3;
	int level_11;
	int level_23;
	int level_35;
	int level_51;
	int level_87;
	int level_151;
	int level_203;
	int level_255;
} __packed;

struct RGB_OUTPUT_VOLTARE {
	struct GAMMA_LEVEL R_VOLTAGE;
	struct GAMMA_LEVEL G_VOLTAGE;
	struct GAMMA_LEVEL B_VOLTAGE;
} __packed;

struct GRAY_VOLTAGE {
	/*
		This voltage value use 14bit right shit
		it means voltage is divied by 16384.
	*/
	int R_Gray;
	int G_Gray;
	int B_Gray;
} __packed;

struct GRAY_SCALE {
	struct GRAY_VOLTAGE TABLE[GRAY_SCALE_MAX];
	struct GRAY_VOLTAGE VT_TABLE;
} __packed;

/*V0,V1,V3,V11,V23,V35,V51,V87,V151,V203,V255*/

struct MTP_SET {
	char OFFSET_255_MSB;
	char OFFSET_255_LSB;
	char OFFSET_203;
	char OFFSET_151;
	char OFFSET_87;
	char OFFSET_51;
	char OFFSET_35;
	char OFFSET_23;
	char OFFSET_11;
	char OFFSET_3;
	char OFFSET_1;
} __packed;

struct MTP_OFFSET {
	struct MTP_SET R_OFFSET;
	struct MTP_SET G_OFFSET;
	struct MTP_SET B_OFFSET;
} __packed;

struct illuminance_table {
	int lux;
	char gamma_setting[GAMMA_SET_MAX];
} __packed;

struct SMART_DIM {
	struct MTP_OFFSET MTP_ORIGN;

	struct MTP_OFFSET MTP;
	struct RGB_OUTPUT_VOLTARE RGB_OUTPUT;
	struct GRAY_SCALE GRAY;

	/* Because of AID funtion, below members are added*/
	int lux_table_max;
	int *plux_table;
	struct illuminance_table gen_table[LUMINANCE_MAX];

	int brightness_level;
	int ldi_revision;
	int vregout_voltage;
} __packed;

#define AOR_DIM_BASE_CD	110

#define CANDELA_MAX_TABLE 53
#define RGB_COMPENSATION 24

static int candela_table[][2] = {
	{10, 0},
	{11, 1},
	{12, 2},
	{13, 3},
	{14, 4},
	{15, 5},
	{16, 6},
	{17, 7},
	{19, 8},
	{20, 9},
	{21, 10},
	{22, 11},
	{24, 12},
	{25, 13},
	{27, 14},
	{29, 15},
	{30, 16},
	{32, 17},
	{34, 18},
	{37, 19},
	{39, 20},
	{41, 21},
	{44, 22},
	{47, 23},
	{50, 24},
	{53, 25},
	{56, 26},
	{60, 27},
	{64, 28},
	{68, 29},
	{72, 30},
	{77, 31},
	{82, 32},
	{87, 33},
	{93, 34},
	{98, 35},
	{105, 36},
	{111, 37},
	{119, 38},
	{126, 39},
	{134, 40},
	{143, 41},
	{152, 42},
	{162, 43},
	{172, 44},
	{183, 45},
	{195, 46},
	{207, 47},
	{220, 48},
	{234, 49},
	{249, 50},
	{265, 51},
	{282, 52},
	{300, 53},
};
static int base_luminance_revA[][2] = {
	{10, 110},
	{11, 110},
	{12, 110},
	{13, 110},
	{14, 110},
	{15, 110},
	{16, 110},
	{17, 110},
	{19, 110},
	{20, 110},
	{21, 110},
	{22, 110},
	{24, 110},
	{25, 110},
	{27, 110},
	{29, 110},
	{30, 110},
	{32, 110},
	{34, 110},
	{37, 110},
	{39, 110},
	{41, 110},
	{44, 110},
	{47, 110},
	{50, 110},
	{53, 110},
	{56, 110},
	{60, 110},
	{64, 110},
	{68, 110},
	{72, 110},
	{77, 110},
	{82, 110},
	{87, 110},
	{93, 110},
	{98, 110},
	{105, 110},
	{111, 179},
	{119, 191},
	{126, 201},
	{134, 213},
	{143, 226},
	{152, 239},
	{162, 254},
	{172, 269},
	{183, 183},
	{195, 195},
	{207, 207},
	{220, 220},
	{234, 234},
	{249, 249},
	{265, 265},
	{282, 282},
	{300, 300},
};

static int gradation_offset_revA[][9] = {
/*	V255 V203 V151 V87 V51 V35 V23 V11 V3 */
	{0, 1, 2, 3, 3, 2, 0, -3, -3},
	{0, 1, 2, 3, 3, 2, 0, -3, -3},
	{0, 1, 1, 3, 3, 2, 0, -3, -2},
	{0, 1, 1, 3, 3, 2, 0, -3, -2},
	{0, 0, 1, 3, 2, 1, -1, -3, -2},
	{0, 1, 1, 2, 1, 1, -1, -3, -2},
	{0, 1, 2, 3, 3, 2, 0, -3, -2},
	{0, 1, 1, 3, 3, 2, 0, -2, -1},
	{0, 1, 1, 3, 3, 2, 0, -2, -1},
	{0, 1, 1, 3, 2, 1, 0, -2, -1},
	{0, 1, 1, 3, 2, 1, 0, -2, -1},
	{0, 1, 2, 2, 2, 1, 0, -2, -2},
	{0, 1, 2, 2, 2, 1, 0, -2, -2},
	{0, 1, 2, 4, 3, 3, 2, -1, -1},
	{0, 1, 2, 4, 3, 3, 2, -1, -1},
	{0, 1, 2, 4, 2, 3, 2, -1, -1},
	{0, 1, 2, 4, 2, 3, 2, -1, -1},
	{0, 1, 2, 4, 2, 3, 2, -1, -1},
	{0, 1, 2, 4, 2, 2, 1, -1, -1},
	{0, 0, 1, 3, 2, 2, 1, -1, -1},
	{0, 0, 1, 2, 1, 2, 1, -1, -1},
	{0, 1, 2, 3, 2, 2, 1, 0, 0},
	{0, 1, 2, 3, 2, 2, 1, 0, 0},
	{0, 1, 2, 3, 2, 2, 1, 0, 0},
	{0, 1, 2, 3, 2, 2, 1, 0, 0},
	{0, 1, 2, 3, 1, 2, 1, 0, 0},
	{0, 1, 1, 3, 1, 2, 1, 0, 0},
	{0, 1, 1, 3, 1, 2, 1, 0, 0},
	{0, 1, 1, 2, 1, 1, 1, 0, 0},
	{0, 1, 1, 2, 1, 1, 1, 0, 0},
	{0, 1, 1, 2, 1, 1, 1, 0, 0},
	{0, 1, 1, 1, 1, 1, 1, 0, 0},
	{0, 1, 1, 1, 1, 1, 1, 0, 0},
	{0, 1, 1, 1, 0, 0, 0, 0, 0},
	{0, 1, 1, 1, 0, 0, 0, 0, 0},
	{0, 1, 1, 1, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, -1, -1, -1, -1, 0},
	{0, 1, 2, 3, 2, 2, 1, 0, 0},
	{0, 1, 2, 2, 2, 2, 1, 0, 0},
	{0, 1, 2, 3, 2, 2, 1, 0, 0},
	{0, 1, 2, 3, 2, 2, 1, -1, 0},
	{0, 1, 2, 2, 2, 2, 1, -1, 0},
	{0, 1, 2, 3, 2, 2, 1, -1, 0},
	{0, 1, 2, 1, 1, 1, 1, -1, 0},
	{0, 1, 2, 1, 1, 1, 1, -2, 0},
	{0, 1, 2, 4, 2, 2, 2, 1, 1},
	{0, 1, 2, 3, 2, 2, 2, 1, 1},
	{0, 0, 1, 3, 2, 1, 2, 1, 1},
	{0, 1, 2, 2, 2, 2, 1, 0, 0},
	{0, 2, 3, 3, 2, 2, 1, 0, 0},
	{0, 0, 2, 3, 2, 2, 1, 0, 0},
	{0, 0, 2, 2, 1, 1, 0, 0, 0},
	{0, 1, 2, 1, 1, 1, 1, -1, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
};
static int rgb_offset_revA[][RGB_COMPENSATION] = {
/*	R255 G255 B255 R203 G203 B203 R151 G151 B151 R87 G87 B87 R51 G51 B51 R35 G35 B35  R23 G23 B23 R11 G11 B11*/
	{0, 0, 0, 1, 0, 0, -1, -1, 0, 0, -1, 1, 0, -2, 3, -3, -2, 6, -3, -9, 14, -12, -9, 15},
	{0, 0, 0, 1, 0, 0, -1, -1, 0, 0, -1, 1, 0, -2, 3, -3, -2, 6, -3, -9, 14, -12, -9, 15},
	{0, 0, 0, 1, 0, 0, -1, -1, 0, 0, -1, 1, 0, -2, 3, -2, -2, 5, -4, -9, 13, -12, -9, 15},
	{0, 0, 0, 1, 0, 0, -1, -1, 0, 0, -1, 1, 0, -2, 3, -2, -2, 5, -4, -9, 13, -11, -8, 15},
	{0, 0, 0, 1, 0, 0, -1, -1, 0, 0, -1, 1, 0, -1, 3, 0, -2, 5, -4, -9, 11, -11, -8, 15},
	{0, 0, 0, 1, 0, 0, 0, 0, 0, -1, -2, 0, -1, -2, 3, -1, -2, 5, -5, -8, 11, -10, -8, 15},
	{0, 0, 0, 1, 0, 0, 0, 0, 0, -1, -2, 0, 0, -1, 3, 0, -1, 5, -5, -8, 11, -10, -7, 15},
	{0, 0, 0, 1, 0, 0, 0, 0, 0, -1, -2, 0, 0, -1, 3, 0, -2, 4, -5, -7, 11, -10, -6, 15},
	{0, 0, 0, 1, 0, 0, 0, 0, 0, -1, -2, 0, 0, -1, 2, 0, -1, 4, -6, -8, 10, -9, -5, 15},
	{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, -2, 0, 0, -1, 2, -1, -2, 3, -6, -8, 9, -9, -5, 15},
	{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, -2, 0, 0, -1, 2, -1, -2, 3, -6, -7, 9, -9, -5, 15},
	{0, 0, 0, 1, 0, 0, 0, 0, 0, -1, -1, 0, 0, -1, 2, -1, -2, 3, -3, -6, 8, -9, -5, 15},
	{0, 0, 0, 1, 0, 0, 0, 0, 0, -1, -1, 0, 0, -1, 2, -1, -2, 3, -3, -5, 7, -8, -5, 15},
	{0, 0, 0, 1, 0, 0, 0, 0, 0, -1, -1, 0, 1, 0, 2, -1, -3, 2, -3, -5, 7, -8, -5, 15},
	{0, 0, 0, 1, 0, 0, 0, 0, 0, -1, -1, 0, 1, 0, 2, -1, -3, 2, -3, -5, 7, -8, -5, 15},
	{0, 0, 0, 1, 0, 0, 0, 0, 0, -1, -1, 0, 0, -1, 1, 0, -1, 2, -2, -4, 6, -9, -5, 15},
	{0, 0, 0, 1, 0, 0, 0, 0, 0, -1, -1, 0, 0, -1, 1, 0, -1, 2, -2, -4, 6, -9, -5, 15},
	{0, 0, 0, 1, 0, 0, 0, 0, 0, -1, -1, 0, 0, -1, 1, 0, -1, 2, -2, -4, 6, -9, -5, 15},
	{0, 0, 0, 1, 0, 0, 0, 0, 0, -1, -1, 0, 0, -1, 1, 0, -1, 2, -2, -4, 5, -10, -5, 15},
	{0, 0, 0, 1, 0, 0, 0, 0, 0, -1, -1, 0, 1, 0, 1, 0, -1, 2, -2, -4, 5, -10, -5, 14},
	{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, -1, -2, 0, -1, -1, 2, -1, -4, 4, -10, -5, 14},
	{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, -1, -2, 0, -1, -1, 2, -1, -3, 4, -10, -5, 14},
	{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, -1, -2, 0, -1, -1, 2, -1, -3, 4, -10, -5, 13},
	{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, 0, -1, -1, 2, -1, -3, 3, -9, -5, 12},
	{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, -1, 2, -1, -3, 3, -9, -5, 11},
	{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, -1, 2, -1, -3, 3, -8, -5, 10},
	{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, -1, 1, -1, -3, 2, -8, -4, 9},
	{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, -1, 1, -2, -3, 2, -7, -4, 8},
	{0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, -1, 1, -2, -3, 2, -7, -4, 7},
	{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, -1, -1, 0, 0, 0, 1, -1, -2, 1, -6, -3, 6},
	{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, -1, -2, 1, -6, -2, 5},
	{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 1, -1, -1, 0, -6, -2, 4},
	{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 1, -1, -1, 0, -5, -2, 3},
	{0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, -1, -1, 0, -1, 0, 1, -1, -2, 0, -5, -2, 2},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, -1, 0, 0, -1, 0, 0, -1, -2, 0, -5, -1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, -1, 0, 0, -1, -2, 0, -5, -1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, -1, 0, 0, -1, -1, 0, -5, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, -1, -1, 0, 0, -1, 2, -8, 0, 5},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, -1, -1, 0, 0, -2, 3, -8, 0, 5},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, -1, -1, 0, 0, -1, 2, -8, 0, 5},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, -1, 0, 0, -1, -1, 0, 0, -1, 2, -8, 0, 4},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, -1, 0, 0, 0, -1, 0, 0, -1, 2, -8, 0, 4},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, -1, -1, 0, 0, 0, 2, -8, 0, 4},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, -1, -1, 0, 0, -1, 2, -8, 0, 4},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, -1, -1, 0, 1, 0, 2, -8, 0, 4},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};
#endif
