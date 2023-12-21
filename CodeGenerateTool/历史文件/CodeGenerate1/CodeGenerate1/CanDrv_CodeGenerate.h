/**
 * Copyright (c) 2012-2018
 * All Rights Reserved by APPSYS and its affiliates.
 * You may not use, copy, distribute, modify, transmit in any form this file
 * except in compliance with APPSYS in writing by applicable law.
 */
/**
 * @file    CanDrv_CodeGenerate.h
 * @brief   brief function description.
 * @details detailed function description.
 * @version 1.0
 * @author  wenzc
 * @date    2023-05-21
 *
 * Edit History
 * ----------------------------------------------------------------------------
 * DATE                     NAME               DESCRIPTION
 * 2023-05-21               appsys             Create it.
 */

#ifndef _CanDrv_CodeGenerate_H_
#define _CanDrv_CodeGenerate_H_

#include "r_typedefs.h"

typedef struct {
    volatile uint32_t e_dw_ID;
    volatile uint32_t e_dw_MK;
    volatile uint32_t e_dw_P0;
    volatile uint32_t e_dw_P1;
} stCanDrv_RxRuleSfr;
/* RCFDCnCFDGAFLCFG0 and RCFDCnCFDGAFLCFG1 Set channel < 128 */
#define     CANDRV_RNC0                   ( 120U )
#define     CANDRV_RNC1                   ( 0U )
#define     CANDRV_RNC2                   ( 0U )
#define     CANDRV_RNC3                   ( 0U )
#define     CANDRV_RNC4                   ( 0U )
#define     CANDRV_RNC5                   ( 0U )

#define     CANDRV_CFG_RN   ( CANDRV_RNC0 + CANDRV_RNC1 + CANDRV_RNC2 + CANDRV_RNC3 + CANDRV_RNC4 + CANDRV_RNC5 )
extern const stCanDrv_RxRuleSfr CaCanDrv_h_RxRule[CANDRV_CFG_RN];
extern uint8_t candrv_cfg_rn;
#define     CANDRV_ENABLE           1U
#define     CANDRV_DISABLE          0U
#define     CANDRV_NULL             0U
typedef enum
{
    E_CH_0 = 0U,
    E_CH_1,
    E_CH_2,
    E_CH_3,
    E_CH_4,
    E_CH_5,
    E_CH_MAX
} eCanDrv_Channel;
#endif

