/**
 * Copyright (c) 2012-2018
 * All Rights Reserved by APPSYS and its affiliates.
 * You may not use, copy, distribute, modify, transmit in any form this file
 * except in compliance with APPSYS in writing by applicable law.
 */
/**
 * @file    Com_PbCfg.c
 * @brief   brief function description.
 * @details detailed function description.
 * @version 1.0
 * @author  wenzc
 * @date    2019-05-21
 *
 * Edit History
 * ----------------------------------------------------------------------------
 * DATE                     NAME               DESCRIPTION
 * 2019-05-21               appsys             Create it.
 */

#ifndef COM_PBCFG_CODEGENERATE_H
#define COM_PBCFG_CODEGENERATE_H

#include "Com_Types.h"


#define      ComConf_ComIPdu_0x35F_INFO    0
#define      ComConf_ComIPdu_0x514_INFO    1
#define      ComConf_ComIPdu_0x574_INFO    2
#define      ComConf_ComIPdu_0x561_INFO    3
#define      ComConf_ComIPdu_0x351_INFO    4
#define      ComConf_ComIPdu_0x111_INFO    5
#define      ComConf_ComIPdu_0x387_INFO    6
#define      ComConf_ComIPdu_0x407_INFO    7
#define      ComConf_ComIPdu_0x38D_INFO    8
#define      ComConf_ComIPdu_0x309_INFO    9
#define      ComConf_ComIPdu_0x38A_INFO    10
#define      ComConf_ComIPdu_0x304_INFO    11
#define      ComConf_ComIPdu_0x331_INFO    12
#define      ComConf_ComIPdu_0x7DF_INFO    13
#define      ComConf_ComIPdu_0x301_INFO    14
#define      ComConf_ComIPdu_0x330_INFO    15
#define      ComConf_ComIPdu_0x3A4_INFO    16
#define      ComConf_ComIPdu_0x3A1_INFO    17
#define      ComConf_ComIPdu_0x124_INFO    18
#define      ComConf_ComIPdu_0x144_INFO    19
#define      ComConf_ComIPdu_0x142_INFO    20
#define      ComConf_ComIPdu_0x122_INFO    21
#define      ComConf_ComIPdu_0x212_INFO    22
#define      ComConf_ComIPdu_0x2A2_INFO    23
#define      ComConf_ComIPdu_0x252_INFO    24
#define      ComConf_ComIPdu_0x3FB_INFO    25
#define      ComConf_ComIPdu_0x272_INFO    26
#define      ComConf_ComIPdu_0x282_INFO    27
#define      ComConf_ComIPdu_0x2C2_INFO    28
#define      ComConf_ComIPdu_0x219_INFO    29
#define      ComConf_ComIPdu_0x239_INFO    30
#define      ComConf_ComIPdu_0x349_INFO    31
#define      ComConf_ComIPdu_0x369_INFO    32
#define      ComConf_ComIPdu_0x34E_INFO    33
#define      ComConf_ComIPdu_0x34F_INFO    34
#define      ComConf_ComIPdu_0x355_INFO    35
#define      ComConf_ComIPdu_0x356_INFO    36
#define      ComConf_ComIPdu_0x21A_INFO    37
#define      ComConf_ComIPdu_0x35A_INFO    38
#define      ComConf_ComIPdu_0x359_INFO    39
#define      ComConf_ComIPdu_0x35D_INFO    40
#define      ComConf_ComIPdu_0x22B_INFO    41
#define      ComConf_ComIPdu_0x380_INFO    42
#define      ComConf_ComIPdu_0x35B_INFO    43
#define      ComConf_ComIPdu_0x3B1_INFO    44
#define      ComConf_ComIPdu_0x347_INFO    45
#define      ComConf_ComIPdu_0x375_INFO    46
#define      ComConf_ComIPdu_0x360_INFO    47
#define      ComConf_ComIPdu_0x3B6_INFO    48
#define      ComConf_ComIPdu_0x386_INFO    49
#define      ComConf_ComIPdu_0x2A1_INFO    50
#define      ComConf_ComIPdu_0x3C1_INFO    51
#define      ComConf_ComIPdu_0x3C2_INFO    52
#define      ComConf_ComIPdu_0x305_INFO    53
#define      ComConf_ComIPdu_0x411_INFO    54
#define      ComConf_ComIPdu_0x421_INFO    55
#define      ComConf_ComIPdu_0x2C1_INFO    56
#define      ComConf_ComIPdu_0x3D1_INFO    57
#define      ComConf_ComIPdu_0x5C3_INFO    58
#define      ComConf_ComIPdu_0x32A_INFO    59
#define      ComConf_ComIPdu_0x394_INFO    60
#define      ComConf_ComIPdu_0x335_INFO    61
#define      ComConf_ComIPdu_0x3D5_INFO    62
#define      ComConf_ComIPdu_0x3D6_INFO    63
#define      ComConf_ComIPdu_0x3D4_INFO    64
#define      ComConf_ComIPdu_0x318_INFO    65
#define      ComConf_ComIPdu_0x31A_INFO    66
#define      ComConf_ComIPdu_0x0A8_INFO    67
#define      ComConf_ComIPdu_0x3C6_INFO    68
#define      ComConf_ComIPdu_0x3C7_INFO    69
#define      ComConf_ComIPdu_0x3C8_INFO    70
#define      ComConf_ComIPdu_0x3C9_INFO    71
#define      ComConf_ComIPdu_0x3CA_INFO    72
#define      ComConf_ComIPdu_0x3CB_INFO    73
#define      ComConf_ComIPdu_0x3CC_INFO    74
#define      ComConf_ComIPdu_0x3CD_INFO    75
#define      ComConf_ComIPdu_0x3DE_INFO    76
#define      ComConf_ComIPdu_0x31E_INFO    77
#define      ComConf_ComIPdu_0x3AE_INFO    78
#define      ComConf_ComIPdu_0x3BE_INFO    79
#define      ComConf_ComIPdu_0x37E_INFO    80
#define      ComConf_ComIPdu_0x223_INFO    81
#define      ComConf_ComIPdu_0x353_INFO    82
#define      ComConf_ComIPdu_0x24E_INFO    83
#define      ComConf_ComIPdu_0x3CE_INFO    84
#define      ComConf_ComIPdu_0x3AD_INFO    85
#define      ComConf_ComIPdu_0x484_INFO    86
#define      ComConf_ComIPdu_0x3FA_INFO    87
#define      ComConf_ComIPdu_0x0A9_INFO    88
#define      ComConf_ComIPdu_0x498_INFO    89
#define      ComConf_ComIPdu_0x4F5_INFO    90
#define      ComConf_ComIPdu_0x35E_INFO    91
#define      ComConf_ComIPdu_0x725_INFO    92
#define      ComConf_ComIPdu_0x400_INFO    93


#define      ComConf_ComIPdu_0x4F3_INFO    94
#define      ComConf_ComIPdu_0x408_INFO    95
#define      ComConf_ComIPdu_0x376_INFO    96
#define      ComConf_ComIPdu_0x096_INFO    97
#define      ComConf_ComIPdu_0x075_INFO    98
#define      ComConf_ComIPdu_0x095_INFO    99
#define      ComConf_ComIPdu_0x0A5_INFO    100
#define      ComConf_ComIPdu_0x1D5_INFO    101
#define      ComConf_ComIPdu_0x065_INFO    102
#define      ComConf_ComIPdu_0x105_INFO    103
#define      ComConf_ComIPdu_0x098_INFO    104
#define      ComConf_ComIPdu_0x093_INFO    105
#define      ComConf_ComIPdu_0x0C5_INFO    106
#define      ComConf_ComIPdu_0x3A0_INFO    107
#define      ComConf_ComIPdu_0x0C6_INFO    108
#define      ComConf_ComIPdu_0x3D2_INFO    109
#define      ComConf_ComIPdu_0x0F5_INFO    110
#define      ComConf_ComIPdu_0x31C_INFO    111
#define      ComConf_ComIPdu_0x31D_INFO    112
#define      ComConf_ComIPdu_0x325_INFO    113
#define      ComConf_ComIPdu_0x328_INFO    114
#define      ComConf_ComIPdu_0x33A_INFO    115
#define      ComConf_ComIPdu_0x33B_INFO    116
#define      ComConf_ComIPdu_0x34A_INFO    117
#define      ComConf_ComIPdu_0x34B_INFO    118
#define      ComConf_ComIPdu_0x33D_INFO    119
#define      ComConf_ComIPdu_0x33E_INFO    120
#define      ComConf_ComIPdu_0x052_INFO    121
#define      ComConf_ComIPdu_0x5FD_INFO    122
#define      ComConf_ComIPdu_0x3F2_INFO    123
#define      ComConf_ComIPdu_0x3F8_INFO    124
#define      ComConf_ComIPdu_0x4F4_INFO    125
#define      ComConf_ComIPdu_0x571_INFO    126
#define      ComConf_ComIPdu_0x570_INFO    127
#define      ComConf_ComIPdu_0x2F2_INFO    128
#define      ComConf_ComIPdu_0x3F7_INFO    129
#define      ComConf_ComIPdu_0x482_INFO    130
#define      ComConf_ComIPdu_0x491_INFO    131
#define      ComConf_ComIPdu_0x492_INFO    132
#define      ComConf_ComIPdu_0x493_INFO    133
#define      ComConf_ComIPdu_0x494_INFO    134
#define      ComConf_ComIPdu_0x495_INFO    135
#define      ComConf_ComIPdu_0x496_INFO    136
#define      ComConf_ComIPdu_0x5F0_INFO    137
#define      ComConf_ComIPdu_0x4A2_INFO    138
#define      ComConf_ComIPdu_0x3B5_INFO    139
#define      ComConf_ComIPdu_0x485_INFO    140
#define      ComConf_ComIPdu_0x486_INFO    141
#define      ComConf_ComIPdu_0x395_INFO    142
#define      ComConf_ComIPdu_0x3C5_INFO    143
#define      ComConf_ComIPdu_0x3A5_INFO    144
#define      ComConf_ComIPdu_0x7A5_INFO    145
#define      ComConf_ComIPdu_0x3E1_INFO    146
#define      ComConf_ComIPdu_0x500_INFO    147


#define ComRxPduNumber     94
#define ComTxPduNumber     54


extern uint16_t gComRxPduNumber ;
extern uint16_t gComTxPduNumber ;
extern const ComSignal_type ComSignal[];
extern const ComIPdu_type ComIPdu[];
extern const ComIPduGroup_type ComIpduGroupRefs_Ecu01[];


#endif

