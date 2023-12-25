/**
 * Copyright (c) 2012-2018
 * All Rights Reserved by APPSYS and its affiliates.
 * You may not use, copy, distribute, modify, transmit in any form this file
 * except in compliance with APPSYS in writing by applicable law.
 */
/**
 * @file    CanIf_PBCfg.c
 * @brief   brief function description.
 * @details detailed function description.
 * @version 1.0
 * @author  appsys
 * @date    2019-05-21
 *
 * Edit History
 * ----------------------------------------------------------------------------
 * DATE                     NAME               DESCRIPTION
 * 2019-05-21               appsys             Create it.
 */

#ifndef CANIF_PBCFG_H_
#define CANIF_PBCFG_H_


#define CANIF_NUM_TX_LPDU  60

#define CANIF_NUM_RX_LPDU  122

#define CANIF_PDU_ID_DIAGPHYSICALTX 0
#define CANIF_PDU_ID_0x4F3_INFO   1
#define CANIF_PDU_ID_0x408_INFO   2
#define CANIF_PDU_ID_0x376_INFO   3
#define CANIF_PDU_ID_0x096_INFO   4
#define CANIF_PDU_ID_0x075_INFO   5
#define CANIF_PDU_ID_0x095_INFO   6
#define CANIF_PDU_ID_0x0A5_INFO   7
#define CANIF_PDU_ID_0x1D5_INFO   8
#define CANIF_PDU_ID_0x065_INFO   9
#define CANIF_PDU_ID_0x066_INFO   10
#define CANIF_PDU_ID_0x067_INFO   11
#define CANIF_PDU_ID_0x069_INFO   12
#define CANIF_PDU_ID_0x068_INFO   13
#define CANIF_PDU_ID_0x06A_INFO   14
#define CANIF_PDU_ID_0x06B_INFO   15
#define CANIF_PDU_ID_0x105_INFO   16
#define CANIF_PDU_ID_0x098_INFO   17
#define CANIF_PDU_ID_0x093_INFO   18
#define CANIF_PDU_ID_0x0C5_INFO   19
#define CANIF_PDU_ID_0x0C6_INFO   20
#define CANIF_PDU_ID_0x3D2_INFO   21
#define CANIF_PDU_ID_0x0F5_INFO   22
#define CANIF_PDU_ID_0x31C_INFO   23
#define CANIF_PDU_ID_0x31D_INFO   24
#define CANIF_PDU_ID_0x325_INFO   25
#define CANIF_PDU_ID_0x328_INFO   26
#define CANIF_PDU_ID_0x33A_INFO   27
#define CANIF_PDU_ID_0x33B_INFO   28
#define CANIF_PDU_ID_0x34A_INFO   29
#define CANIF_PDU_ID_0x34B_INFO   30
#define CANIF_PDU_ID_0x33D_INFO   31
#define CANIF_PDU_ID_0x33E_INFO   32
#define CANIF_PDU_ID_0x052_INFO   33
#define CANIF_PDU_ID_0x5FD_INFO   34
#define CANIF_PDU_ID_0x3F2_INFO   35
#define CANIF_PDU_ID_0x3F8_INFO   36
#define CANIF_PDU_ID_0x4F4_INFO   37
#define CANIF_PDU_ID_0x571_INFO   38
#define CANIF_PDU_ID_0x570_INFO   39
#define CANIF_PDU_ID_0x2F2_INFO   40
#define CANIF_PDU_ID_0x3F7_INFO   41
#define CANIF_PDU_ID_0x482_INFO   42
#define CANIF_PDU_ID_0x491_INFO   43
#define CANIF_PDU_ID_0x492_INFO   44
#define CANIF_PDU_ID_0x493_INFO   45
#define CANIF_PDU_ID_0x494_INFO   46
#define CANIF_PDU_ID_0x495_INFO   47
#define CANIF_PDU_ID_0x496_INFO   48
#define CANIF_PDU_ID_0x5F0_INFO   49
#define CANIF_PDU_ID_0x4A2_INFO   50
#define CANIF_PDU_ID_0x3B5_INFO   51
#define CANIF_PDU_ID_0x485_INFO   52
#define CANIF_PDU_ID_0x486_INFO   53
#define CANIF_PDU_ID_0x395_INFO   54
#define CANIF_PDU_ID_0x3C5_INFO   55
#define CANIF_PDU_ID_0x3A5_INFO   56
#define CANIF_PDU_ID_0x3E1_INFO   57
#define CANIF_PDU_ID_0x500_INFO   58


#define CANIF_PDU_ID_DIAGFUNCTIONALRX       1
#define CANIF_PDU_ID_DIAGPHYSICALRX         0
#define CANIF_PDU_ID_0x35F_INFO   2
#define CANIF_PDU_ID_0x514_INFO   3
#define CANIF_PDU_ID_0x574_INFO   4
#define CANIF_PDU_ID_0x561_INFO   5
#define CANIF_PDU_ID_0x351_INFO   6
#define CANIF_PDU_ID_0x111_INFO   7
#define CANIF_PDU_ID_0x311_INFO   8
#define CANIF_PDU_ID_0x387_INFO   9
#define CANIF_PDU_ID_0x407_INFO   10
#define CANIF_PDU_ID_0x38D_INFO   11
#define CANIF_PDU_ID_0x309_INFO   12
#define CANIF_PDU_ID_0x38A_INFO   13
#define CANIF_PDU_ID_0x304_INFO   14
#define CANIF_PDU_ID_0x331_INFO   15
#define CANIF_PDU_ID_0x301_INFO   16
#define CANIF_PDU_ID_0x330_INFO   17
#define CANIF_PDU_ID_0x3A4_INFO   18
#define CANIF_PDU_ID_0x3A1_INFO   19
#define CANIF_PDU_ID_0x124_INFO   20
#define CANIF_PDU_ID_0x144_INFO   21
#define CANIF_PDU_ID_0x142_INFO   22
#define CANIF_PDU_ID_0x122_INFO   23
#define CANIF_PDU_ID_0x212_INFO   24
#define CANIF_PDU_ID_0x2A2_INFO   25
#define CANIF_PDU_ID_0x252_INFO   26
#define CANIF_PDU_ID_0x3FB_INFO   27
#define CANIF_PDU_ID_0x272_INFO   28
#define CANIF_PDU_ID_0x282_INFO   29
#define CANIF_PDU_ID_0x2C2_INFO   30
#define CANIF_PDU_ID_0x219_INFO   31
#define CANIF_PDU_ID_0x239_INFO   32
#define CANIF_PDU_ID_0x349_INFO   33
#define CANIF_PDU_ID_0x369_INFO   34
#define CANIF_PDU_ID_0x34E_INFO   35
#define CANIF_PDU_ID_0x34F_INFO   36
#define CANIF_PDU_ID_0x355_INFO   37
#define CANIF_PDU_ID_0x356_INFO   38
#define CANIF_PDU_ID_0x21A_INFO   39
#define CANIF_PDU_ID_0x35A_INFO   40
#define CANIF_PDU_ID_0x359_INFO   41
#define CANIF_PDU_ID_0x35D_INFO   42
#define CANIF_PDU_ID_0x22B_INFO   43
#define CANIF_PDU_ID_0x3AC_INFO   44
#define CANIF_PDU_ID_0x3A8_INFO   45
#define CANIF_PDU_ID_0x380_INFO   46
#define CANIF_PDU_ID_0x35B_INFO   47
#define CANIF_PDU_ID_0x345_INFO   48
#define CANIF_PDU_ID_0x2AA_INFO   49
#define CANIF_PDU_ID_0x2AB_INFO   50
#define CANIF_PDU_ID_0x2AD_INFO   51
#define CANIF_PDU_ID_0x2AF_INFO   52
#define CANIF_PDU_ID_0x2B2_INFO   53
#define CANIF_PDU_ID_0x2B3_INFO   54
#define CANIF_PDU_ID_0x2B5_INFO   55
#define CANIF_PDU_ID_0x2B6_INFO   56
#define CANIF_PDU_ID_0x2B7_INFO   57
#define CANIF_PDU_ID_0x2C6_INFO   58
#define CANIF_PDU_ID_0x30D_INFO   59
#define CANIF_PDU_ID_0x30E_INFO   60
#define CANIF_PDU_ID_0x308_INFO   61
#define CANIF_PDU_ID_0x307_INFO   62
#define CANIF_PDU_ID_0x31B_INFO   63
#define CANIF_PDU_ID_0x321_INFO   64
#define CANIF_PDU_ID_0x3B1_INFO   65
#define CANIF_PDU_ID_0x413_INFO   66
#define CANIF_PDU_ID_0x347_INFO   67
#define CANIF_PDU_ID_0x375_INFO   68
#define CANIF_PDU_ID_0x360_INFO   69
#define CANIF_PDU_ID_0x3B6_INFO   70
#define CANIF_PDU_ID_0x386_INFO   71
#define CANIF_PDU_ID_0x2A1_INFO   72
#define CANIF_PDU_ID_0x3C1_INFO   73
#define CANIF_PDU_ID_0x3C2_INFO   74
#define CANIF_PDU_ID_0x305_INFO   75
#define CANIF_PDU_ID_0x411_INFO   76
#define CANIF_PDU_ID_0x421_INFO   77
#define CANIF_PDU_ID_0x2C1_INFO   78
#define CANIF_PDU_ID_0x3D1_INFO   79
#define CANIF_PDU_ID_0x5C3_INFO   80
#define CANIF_PDU_ID_0x32A_INFO   81
#define CANIF_PDU_ID_0x394_INFO   82
#define CANIF_PDU_ID_0x335_INFO   83
#define CANIF_PDU_ID_0x3D5_INFO   84
#define CANIF_PDU_ID_0x3D6_INFO   85
#define CANIF_PDU_ID_0x3D4_INFO   86
#define CANIF_PDU_ID_0x318_INFO   87
#define CANIF_PDU_ID_0x31A_INFO   88
#define CANIF_PDU_ID_0x0A8_INFO   89
#define CANIF_PDU_ID_0x3A0_INFO   90
#define CANIF_PDU_ID_0x3C6_INFO   91
#define CANIF_PDU_ID_0x3C7_INFO   92
#define CANIF_PDU_ID_0x3C8_INFO   93
#define CANIF_PDU_ID_0x3C9_INFO   94
#define CANIF_PDU_ID_0x3CA_INFO   95
#define CANIF_PDU_ID_0x3CB_INFO   96
#define CANIF_PDU_ID_0x3CC_INFO   97
#define CANIF_PDU_ID_0x3CD_INFO   98
#define CANIF_PDU_ID_0x3DE_INFO   99
#define CANIF_PDU_ID_0x31E_INFO   100
#define CANIF_PDU_ID_0x3AE_INFO   101
#define CANIF_PDU_ID_0x3BE_INFO   102
#define CANIF_PDU_ID_0x37E_INFO   103
#define CANIF_PDU_ID_0x223_INFO   104
#define CANIF_PDU_ID_0x353_INFO   105
#define CANIF_PDU_ID_0x24E_INFO   106
#define CANIF_PDU_ID_0x3CE_INFO   107
#define CANIF_PDU_ID_0x3B7_INFO   108
#define CANIF_PDU_ID_0x3B8_INFO   109
#define CANIF_PDU_ID_0x3B9_INFO   110
#define CANIF_PDU_ID_0x3AD_INFO   111
#define CANIF_PDU_ID_0x484_INFO   112
#define CANIF_PDU_ID_0x3FA_INFO   113
#define CANIF_PDU_ID_0x0A9_INFO   114
#define CANIF_PDU_ID_0x498_INFO   115
#define CANIF_PDU_ID_0x21C_INFO   116
#define CANIF_PDU_ID_0x4F5_INFO   117
#define CANIF_PDU_ID_0x35E_INFO   118
#define CANIF_PDU_ID_0x515_INFO   119
#define CANIF_PDU_ID_0x400_INFO   120


extern uint16_t gcanif_num_rx_lpdu;
extern uint16_t gcanif_num_tx_lpdu;
#endif

