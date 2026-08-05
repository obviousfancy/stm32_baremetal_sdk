/**
 * @file      ofl_rcc.h
 * @brief     
 *
 * @details   
 *
 * @author    obviousfancy
 * @date      Aug 4, 2026
 * @version   0.0.1
 *
 * @note      
 *
 * @copyright Copyright (c) 2026 ObviousFancy Lab
 *            Licensed under the MIT License
 */
#ifndef INC_OFL_RCC_H_
#define INC_OFL_RCC_H_

#include "main.h"
/**
 * @brief
 *
 * @param[in] port  Puntero al periférico GPIO (ej. GPIOA)
 * @param[in] pin   Número de pin (0-15)
 * @param[in] mode  Modo deseado
 *
 * @return    void
 *
 * @note      No verifica límites de pin; el llamador debe garantizar 0-15
 */
void ofl_rcc_hse_config(void);
#endif /* INC_OFL_RCC_H_ */
