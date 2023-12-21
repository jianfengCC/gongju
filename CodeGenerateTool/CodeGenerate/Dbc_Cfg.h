/**
 * Copyright (c) 2012-2018
 * All Rights Reserved by APPSYS and its affiliates.
 * You may not use, copy, distribute, modify, transmit in any form this file
 * except in compliance with APPSYS in writing by applicable law.
 */
/**
 * @file    Dbc_Cfg.h
 * @brief   brief function description.
 * @details detailed function description.
 * @version 1.0
 * @author  wenzc
 * @date    2023-05-21
 *
 * Edit History
 * ----------------------------------------------------------------------------
 * DATE                     NAME               DESCRIPTION
 * 2023-05-21               wenzc             Create it.
 */

#ifndef DBC_CFG_H
#define DBC_CFG_H
#define CAN_AS_LOG_UNIT_CNT            2U
#define PDUR_MAX_ROUTE_COUNT       181
#define CANIF_AS_MAX_NUM_LPDU_TX_BUF   60u
#define CANIF_AS_MAX_NOF_TX_BUFFERS   60u
#define CANIF_PDU_ID_CANNMTX        59
#define CANIF_PDU_ID_CANNMRX        0
extern unsigned short canif_max_num_tx_buf;
extern unsigned short canif_max_nof_tx_buf;

#endif

