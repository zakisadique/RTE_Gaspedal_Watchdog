
/*
 * Filename: sp__common.h
 *
 * Author: Autogenerated by H-DA RTE Generator, (c) Prof. Fromm
 *
 * Description: all signals will be part of this common signal pool
 */

#ifndef _H_DEFINE_SP__COMMON
#define _H_DEFINE_SP__COMMON

#include "project.h"
#include "global.h"
#include "rte_types.h"

/* USER CODE START SP__COMMON_INCLUDES */

/* USER CODE END SP__COMMON_INCLUDES */







/*
 * Increments the age of the signals in this pool 
 */
void RTE_timertick_sp__common_tick(uint32_t tick);

/*
 * Reset all signals in this pool
 */
void RTE_reset_sp__common();

#endif