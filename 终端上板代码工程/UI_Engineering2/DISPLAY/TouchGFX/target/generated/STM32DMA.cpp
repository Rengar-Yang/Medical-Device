/**
  ******************************************************************************
  * File Name          : STM32DMA.cpp
  ******************************************************************************
  * This file is generated by TouchGFX Generator 4.18.1. Please, do not edit!
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

#include <STM32DMA.hpp>
#include <assert.h>

STM32DMA::STM32DMA()
    : DMA_Interface(q), q(&b, 1)
{
}

touchgfx::BlitOperations STM32DMA::getBlitCaps()
{
    return static_cast<touchgfx::BlitOperations>(0);
}

void STM32DMA::setupDataCopy(const touchgfx::BlitOp& blitOp)
{
    assert(0 && "DMA operation not supported");
}

void STM32DMA::setupDataFill(const touchgfx::BlitOp& blitOp)
{
    assert(0 && "DMA operation not supported");
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
