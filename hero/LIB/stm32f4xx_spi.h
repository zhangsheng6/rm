FGR_BTEM HIS_CEC_BIT_TIMING_ERROR_MODE(MODE) (((MODE) == CEC_BitTimingStdMode) || ((MODE) == CEC_BitTimingErrFreeMode)) QCEC_BitPeriodStdMode ((uint16_t)0x00) RCEC_BitPeriodFlexibleMode CEC_CFGR_BPEM TIS_CEC_BIT_PERIOD_ERROR_MODE(MODE) (((MODE) == CEC_BitPeriodStdMode) || ((MODE) == CEC_BitPeriodFlexibleMode)) ^CEC_IT_TERR CEC_CSR_TERR _CEC_IT_TBTRF CEC_CSR_TBTRF `CEC_IT_RERR CEC_CSR_RERR aCEC_IT_RBTF CEC_CSR_RBTF bIS_CEC_GET_IT(IT) (((IT) == CEC_IT_TERR) || ((IT) == CEC_IT_TBTRF) || ((IT) == CEC_IT_RERR) || ((IT) == CEC_IT_RBTF)) lIS_CEC_ADDRESS(ADDRESS) ((ADDRESS) < 0x10) tIS_CEC_PRESCALER(PRESCALER) ((PRESCALER) <= 0x3FFF) �CEC_FLAG_BTE ((uint32_t)0x10010000) �CEC_FLAG_BPE ((uint32_t)0x10020000) �CEC_FLAG_RBTFE ((uint32_t)0x10040000) �CEC_FLAG_SBE ((uint32_t)0x10080000) �CEC_FLAG_ACKE ((uint32_t)0x10100000) �CEC_FLAG_LINE ((uint32_t)0x10200000) �CEC_FLAG_TBTFE ((uint32_t)0x10400000) �CEC_FLAG_TEOM ((uint32_t)0x00000002) �CEC_FLAG_TERR ((uint32_t)0x00000004) �CEC_FLAG_TBTRF ((uint32_t)0x00000008) �CEC_FLAG_RSOM ((uint32_t)0x00000010) �CEC_FLAG_REOM ((uint32_t)0x00000020) �CEC_FLAG_RERR ((uint32_t)0x00000040) �CEC_FLAG_RBTF ((uint32_t)0x00000080) �IS_CEC_CLEAR_FLAG(FLAG) ((((FLAG) & (uint32_t)0xFFFFFF03) == 0x00) && ((FLAG) != 0x00)) �IS_CEC_GET_FLAG(FLAG) (((FLAG) == CEC_FLAG_BTE) || ((FLAG) == CEC_FLAG_BPE) || ((FLAG) == CEC_FLAG_RBTFE) || ((FLAG)== CEC_FLAG_SBE) || ((FLAG) == CEC_FLAG_ACKE) || ((FLAG) == CEC_FLAG_LINE) || ((FLAG) == CEC_FLAG_TBTFE) || ((FLAG) == CEC_FLAG_TEOM) || ((FLAG) == CEC_FLAG_TERR) || ((FLAG) == CEC_FLAG_TBTRF) || ((FLAG) == CEC_FLAG_RSOM) || ((FLAG) == CEC_FLAG_REOM) || ((FLAG) == CEC_FLAG_RERR) || ((FLAG) == CEC_FLAG_RBTF))      1   0   /   �        
..\..\Libraries\FWlib\inc\stm32f10x_crc.h Component: ARM Compiler 5.06 update 6 (build 750) Tool: ArmCC [4d3637]  I:\2018电子设计大赛（自主设计）\2018(非RTX版)\Project\RVMDK（uv4）           p    g            ..\..\Libraries\FWlib\inc\ ..\..\Libraries\CMSIS\  stm32f10x_crc.h   stm32f10x.h      __STM32F10x_CRC_H         5   4   3   l       
..\..\Libraries\FWlib\inc\stm32f10x_dac.h Component: ARM Compiler 5.06 update 6 (build 750) Tool: ArmCC [4d3637]  I:\2018电子设计大赛（自主设计）\2018(非RTX版)\Project\RVMDK（uv4）         *�DAC_Trigger W  # DAC_WaveGeneration W  #DAC_LFSRUnmask_TriangleAmplitude W  #DAC_OutputBuffer W  # PDAC_InitTypeDef � A     p    g            ..\..\Libraries\FWlib\inc\ ..\..\Libraries\CMSIS\  stm32f10x_dac.h   stm32f10x.h      __STM32F10x_DAC_H   ODAC_Trigger_None ((uint32_t)0x00000000) QDAC_Trigger_T6_TRGO ((uint32_t)0x00000004) RDAC_Trigger_T8_TRGO ((uint32_t)0x0000000C) TDAC_Trigger_T3_TRGO ((uint32_t)0x0000000C) VDAC_Trigger_T7_TRGO ((uint32_t)0x00000014) WDAC_Trigger_T5_TRGO ((uint32_t)0x0000001C) XDAC_Trigger_T15_TRGO ((uint32_t)0x0000001C) ZDAC_Trigger_T2_TRGO ((uint32_t)0x00000024) [DAC_Trigger_T4_TRGO ((uint32_t)0x0000002C) \DAC_Trigger_Ext_IT9 ((uint32_t)0x00000034) ]DAC_Trigger_Software ((uint32_t)0x0000003C) _IS_DAC_TRIGGER(TRIGGER) (((TRIGGER) == DAC_Trigger_None) || ((TRIGGER) == DAC_Trigger_T6_TRGO) || ((TRIGGER) == DAC_Trigger_T8_TRGO) || ((TRIGGER) == DAC_Trigger_T7_TRGO) || ((TRIGGER) == DAC_Trigger_T5_TRGO) || ((TRIGGER) == DAC_Trigger_T2_TRGO) || ((TRIGGER) == DAC_Trigger_T4_TRGO) || ((TRIGGER) == DAC_Trigger_Ext_IT9) || ((TRIGGER) == DAC_Trigger_Software)) qDAC_WaveGeneration_None ((uint32_t)0x00000000) rDAC_WaveGeneration_Noise ((uint32_t)0x00000040) sDAC_WaveGeneration_Triangle ((uint32_t)0x00000080) tIS_DAC_GENERATE_WAVE(WAVE) (((WAVE) == DAC_WaveGeneration_None) || ((WAVE) == DAC_WaveGeneration_Noise) || ((WAVE) == DAC_WaveGeneration_Triangle)) DAC_LFSRUnmask_Bit0 ((uint32_t)0x00000000) �DAC_LFSRUnmask_Bits1_0 ((uint32_t)0x00000100) �DAC_LFSRUnmask_Bits2_0 ((uint32_t)0x00000200) �DAC_LFSRUnmask_Bits3_0 ((uint32_t)0x00000300) �DAC_LFSRUnmask_Bits4_0 ((uint32_t)0x00000400) �DAC_LFSRUnmask_Bits5_0 ((uint32_t)0x00000500) �DAC_LFSRUnmask_Bits6_0 ((uint32_t)0x00000600) �DAC_LFSRUnmask_Bits7_0 ((uint32_t)0x00000700) �DAC_LFSRUnmask_Bits8_0 ((uint32_t)0x00000800) �DAC_LFSRUnmask_Bits9_0 ((uint32_t)0x00000900) �DAC_LFSRUnmask_Bits10_0 ((uint32_t)0x00000A00) �DAC_LFSRUnmask_Bits11_0 ((uint32_t)0x00000B00) �DAC_TriangleAmplitude_1 ((uint32_t)0x00000000) �DAC_TriangleAmplitude_3 ((uint32_t)0x00000100) �DAC_TriangleAmplitude_7 ((uint32_t)0x00000200) �DAC_TriangleAmplitude_15 ((uint32_t)0x00000300) �DAC_TriangleAmplitude_31 ((uint32_t)0x00000400) �DAC_TriangleAmplitude_63 ((uint32_t)0x00000500) �DAC_TriangleAmplitude_127 ((uint32_t)0x00000600) �DAC_TriangleAmplitude_255 ((uint32_t)0x00000700) �DAC_TriangleAmplitude_511 ((uint32_t)0x00000800) �DAC_TriangleAmplitude_1023 ((uint32_t)0x00000900) �DAC_TriangleAmplitude_2047 ((uint32_t)0x00000A00) �DAC_TriangleAmplitude_4095 ((uint32_t)0x00000B00) �IS_DAC_LFSR_UNMASK_TRIANGLE_AMPLITUDE(VALUE) (((VALUE) == DAC_LFSRUnmask_Bit0) || ((VALUE) == DAC_LFSRUnmask_Bits1_0) || ((VALUE) == DAC_LFSRUnmask_Bits2_0) || ((VALUE) == DAC_LFSRUnmask_Bits3_0) || ((VALUE) == DAC_LFSRUnmask_Bits4_0) || ((VALUE) == DAC_LFSRUnmask_Bits5_0) || ((VALUE) == DAC_LFSRUnmask_Bits6_0) || ((VALUE) == DAC_LFSRUnmask_Bits7_0) || ((VALUE) == DAC_LFSRUnmask_Bits8_0) || ((VALUE) == DAC_LFSRUnmask_Bits9_0) || ((VALUE) == DAC_LFSRUnmask_Bits10_0) || ((VALUE) == DAC_LFSRUnmask_Bits11_0) || ((VALUE) == DAC_TriangleAmplitude_1) || ((VALUE) == DAC_TriangleAmplitude_3) || ((VALUE) == DAC_TriangleAmplitude_7) || ((VALUE) == DAC_TriangleAmplitude_15) || ((VALUE) == DAC_TriangleAmplitude_31) || ((VALUE) == DAC_TriangleAmplitude_63) || ((VALUE) == DAC_TriangleAmplitude_127) || ((VALUE) == DAC_TriangleAmplitude_255) || ((VALUE) == DAC_TriangleAmplitude_511) || ((VALUE) == DAC_TriangleAmplitude_1023) || ((VALUE) == DAC_TriangleAmplitude_2047) || ((VALUE) == DAC_TriangleAmplitude_4095)) �DAC_OutputBuffer_Enable ((uint32_t)0x00000000) �DAC_OutputBuffer_Disable ((uint32_t)0x00000002) �IS_DAC_OUTPUT_BUFFER_STATE(STATE) (((STATE) == DAC_OutputBuffer_Enable) || ((STATE) == DAC_OutputBuffer_Disable)) �DAC_Channel_1 ((uint32_t)0x00000000) �DAC_Channel_2 ((uint32_t)0x00000010) �IS_DAC_CHANNEL(CHANNEL) (((CHANNEL) == DAC_Channel_1) || ((CHANNEL) == DAC_Channel_2)) �DAC_Align_12b_R ((uint32_t)0x00000000) �DAC_Align_12b_L ((uint32_t)0x00000004) �DAC_Align_8b_R ((uint32_t)0x00000008) �IS_DAC_ALIGN(ALIGN) (((ALIGN) == DAC_Align_12b_R) || ((ALIGN) == DAC_Align_12b_L) || ((ALIGN) == DAC_Align_8b_R)) �DAC_Wave_Noise ((uint32_t)0x00000040) �DAC_Wave_Triangle ((uint32_t)0x00000080) �IS_DAC_WAVE(WAVE) (((WAVE) == DAC_Wave_Noise) || ((WAVE) == DAC_Wave_Triangle)) �IS_DAC_DATA(DATA) ((DATA) <= 0xFFF0)        9   8   7   �        
..\..\Libraries\FWlib\inc\stm32f10x_dbgmcu.h Component: ARM Compiler 5.06 update 6 (build 750) Tool: ArmCC [4d3637]  I:\2018电子设计大赛（自主设计）\2018(非RTX版)\Project\RVMDK（uv4）            t    j            ..\..\Libraries\FWlib\inc\ ..\..\Libraries\CMSIS\  stm32f10x_dbgmcu.h   stm32f10x.h      __STM32F10x_DBGMCU_H   6DBGMCU_SLEEP ((uint32_t)0x00000001) 7DBGMCU_STOP ((uint32_t)0x00000002) 8DBGMCU_STANDBY ((uint32_t)0x00000004) 9DBGMCU_IWDG_STOP ((uint32_t)0x00000100) :DBGMCU_WWDG_STOP ((uint32_t)0x00000200) ;DBGMCU_TIM1_STOP ((uint32_t)0x00000400) <DBGMCU_TIM2_STOP ((uint32_t)0x00000800) =DBGMCU_TIM3_STOP ((uint32_t)0x00001000) >DBGMCU_TIM4_STOP ((uint32_t)0x00002000) ?DBGMCU_CAN1_STOP ((uint32_t)0x00004000) @DBGMCU_I2C1_SMBUS_TIMEOUT ((uint32_t)0x00008000) ADBGMCU_I2C2_SMBUS_TIMEOUT ((uint32_t)0x00010000) BDBGMCU_TIM8_STOP ((uint32_t)0x00020000) CDBGMCU_TIM5_STOP ((uint32_t)0x00040000) DDBGMCU_TIM6_STOP ((uint32_t)0x00080000) EDBGMCU_TIM7_STOP ((uint32_t)0x00100000) FDBGMCU_CAN2_STOP ((uint32_t)0x00200000) GDBGMCU_TIM15_STOP ((uint32_t)0x00400000) HDBGMCU_TIM16_STOP ((uint32_t)0x00800000) IDBGMCU_TIM17_STOP ((uint32_t)0x01000000) JDBGMCU_TIM12_STOP ((uint32_t)0x02000000) KDBGMCU_TIM13_STOP ((uint32_t)0x04000000) LDBGMCU_TIM14_STOP ((uint32_t)0x08000000) MDBGMCU_TIM9_STOP ((uint32_t)0x10000000) NDBGMCU_TIM10_STOP ((uint32_t)0x20000000) ODBGMCU_TIM11_STOP ((uint32_t)0x40000000) QIS_DBGMCU_PERIPH(PERIPH) ((((PERIPH) & 0x800000F8) == 0x00) && ((PERIPH) != 0x00))        =   <   ;           
..\..\Libraries\FWlib\inc\stm32f10x_dma.h Component: ARM Compiler 5.06 update 6 (build 750) Tool: ArmCC [4d3637]  I:\2018电子设计大赛（自主设计）\2018(非RTX版)\Project\RVMDK（uv4）         *�,DMA_PeripheralBaseAddr W  # DMA_MemoryBaseAddr W  #DMA_DIR W  #DMA_BufferSize W  #DMA_PeripheralInc W  #DMA_MemoryInc W  #DMA_PeripheralDataSize W  #DMA_MemoryDataSize W  #DMA_Mode W  # DMA_Priority W  #$DMA_M2M W  #( PDMA_InitTypeDef � U  p    g            ..\..\Libraries\FWlib\inc\ ..\..\Libraries\CMSIS\  stm32f10x_dma.h   stm32f10x.h      __STM32F10x_DMA_H   _IS_DMA_ALL_PERIPH(PERIPH) (((PERIPH) == DMA1_Channel1) || ((PERIPH) == DMA1_Channel2) || ((PERIPH) == DMA1_Channel3) || ((PERIPH) == DMA1_Channel4) || ((PERIPH) == DMA1_Channel5) || ((PERIPH) == DMA1_Channel6) || ((PERIPH) == DMA1_Channel7) || ((PERIPH) == DMA2_Channel1) || ((PERIPH) == DMA2_Channel2) || ((PERIPH) == DMA2_Channel3) || ((PERIPH) == DMA2_Channel4) || ((PERIPH) == DMA2_Channel5)) pDMA_DIR_PeripheralDST ((uint32_t)0x00000010) qDMA_DIR_PeripheralSRC ((uint32_t)0x00000000) rIS_DMA_DIR(DIR) (((DIR) == DMA_DIR_PeripheralDST) || ((DIR) == DMA_DIR_PeripheralSRC)) |DMA_PeripheralInc_Enable ((uint32_t)0x00000040) }DMA_PeripheralInc_Disable ((uint32_t)0x00000000) ~IS_DMA_PERIPHERAL_INC_STATE(STATE) (((STATE) == DMA_PeripheralInc_Enable) || ((STATE) == DMA_PeripheralInc_Disable)) �DMA_MemoryInc_Enable ((uint32_t)0x00000080) �DMA_MemoryInc_Disable ((uint32_t)0x00000000) �IS_DMA_MEMORY_INC_STATE(STATE) (((STATE) == DMA_MemoryInc_Enable) || ((STATE) == DMA_MemoryInc_Disable)) �DMA_PeripheralDataSize_Byte ((uint32_t)0x00000000) �DMA_PeripheralDataSize_HalfWord ((uint32_t)0x00000100) �DMA_PeripheralDataSize_Word ((uint32_t)0x00000200) �IS_DMA_PERIPHERAL_DATA_SIZE(SIZE) (((SIZE) == DMA_PeripheralDataSize_Byte) || ((SIZE) == DMA_PeripheralDataSize_HalfWord) || ((SIZE) == DMA_PeripheralDataSize_Word)) �DMA_MemoryDataSize_Byte ((uint32_t)0x00000000) �DMA_MemoryDataSize_HalfWord ((uint32_t)0x00000400) �DMA_MemoryDataSize_Word ((uint32_t)0x00000800) �IS_DMA_MEMORY_DATA_SIZE(SIZE) (((SIZE) == DMA_MemoryDataSize_Byte) || ((SIZE) == DMA_MemoryDataSize_HalfWord) || ((SIZE) == DMA_MemoryDataSize_Word)) �DMA_Mode_Circular ((uint32_t)0x00000020) �DMA_Mode_Normal ((uint32_t)0x00000000) �IS_DMA_MODE(MODE) (((MODE) == DMA_Mode_Circular) || ((MODE) == DMA_Mode_Normal)) �DMA_Priority_VeryHigh ((uint32_t)0x00003000) �DMA_Priority_High ((uint32_t)0x00002000) �DMA_Priority_Medium ((uint32_t)0x00001000) �DMA_Priority_Low ((uint32_t)0x00000000) �IS_DMA_PRIORITY(PRIORITY) (((PRIORITY) == DMA_Priority_VeryHigh) || ((PRIORITY) == DMA_Priority_High) || ((PRIORITY) == DMA_Priority_Medium) || ((PRIORITY) == DMA_Priority_Low)) �DMA_M2M_Enable ((uint32_t)0x00004000) �DMA_M2M_Disable ((uint32_t)0x00000000) �IS_DMA_M2M_STATE(STATE) (((STATE) == DMA_M2M_Enable) || ((STATE) == DMA_M2M_Disable)) �DMA_IT_TC ((uint32_t)0x00000002) �DMA_IT_HT ((uint32_t)0x00000004) �DMA_IT_TE ((uint32_t)0x00000008) �IS_DMA_CONFIG_IT(IT) ((((IT) & 0xFFFFFFF1) == 0x00) && ((IT) != 0x00)) �DMA1_IT_GL1 ((uint32_t)0x00000001) �DMA1_IT_TC1 ((uint32_t)0x00000002) �DMA1_IT_HT1 ((uint32_t)0x00000004) �DMA1_IT_TE1 ((uint32_t)0x00000008) �DMA1_IT_GL2 ((uint32_t)0x00000010) �DMA1_IT_TC2 ((uint32_t)0x00000020) �DMA1_IT_HT2 ((uint32_t)0x00000040) �DMA1_IT_TE2 ((uint32_t)0x00000080) �DMA1_IT_GL3 ((uint32_t)0x00000100) �DMA1_IT_TC3 ((uint32_t)0x00000200) �DMA1_IT_HT3 ((uint32_t)0x00000400) �DMA1_IT_TE3 ((uint32_t)0x00000800) �DMA1_IT_GL4 ((uint32_t)0x00001000) �DMA1_IT_TC4 ((uint32_t)0x00002000) �DMA1_IT_HT4 ((uint32_t)0x00004000) �DMA1_IT_TE4 ((uint32_t)0x00008000) �DMA1_IT_GL5 ((uint32_t)0x00010000) �DMA1_IT_TC5 ((uint32_t)0x00020000) �DMA1_IT_HT5 ((uint32_t)0x00040000) �DMA1_IT_TE5 ((uint32_t)0x00080000) �DMA1_IT_GL6 ((uint32_t)0x00100000) �DMA1_IT_TC6 ((uint32_t)0x00200000) �DMA1_IT_HT6 ((uint32_t)0x00400000) �DMA1_IT_TE6 ((uint32_t)0x00800000) �DMA1_IT_GL7 ((uint32_t)0x01000000) �DMA1_IT_TC7 ((uint32_t)0x02000000) �DMA1_IT_HT7 ((uint32_t)0x04000000) �DMA1_IT_TE7 ((uint32_t)0x08000000) �DMA2_IT_GL1 ((uint32_t)0x10000001) �DMA2_IT_TC1 ((uint32_t)0x10000002) �DMA2_IT_HT1 ((uint32_t)0x10000004) �DMA2_IT_TE1 ((uint32_t)0x10000008) �DMA2_IT_GL2 ((uint32_t)0x10000010) �DMA2_IT_TC2 ((uint32_t)0x10000020) �DMA2_IT_HT2 ((uint32_t)0x10000040) �DMA2_IT_TE2 ((uint32_t)0x10000080) �DMA2_IT_GL3 ((uint32_t)0x10000100) �DMA2_IT_TC3 ((uint32_t)0x10000200) �DMA2_IT_HT3 ((uint32_t)0x10000400) �DMA2_IT_TE3 ((uint32_t)0x10000800) �DMA2_IT_GL4 ((uint32_t)0x10001000) �DMA2_IT_TC4 ((uint32_t)0x10002000) �DMA2_IT_HT4 ((uint32_t)0x10004000) �DMA2_IT_TE4 ((uint32_t)0x10008000) �DMA2_IT_GL5 ((uint32_t)0x10010000) �DMA2_IT_TC5 ((uint32_t)0x10020000) �DMA2_IT_HT5 ((uint32_t)0x10040000) �DMA2_IT_TE5 ((uint32_t)0x10080000) �IS_DMA_CLEAR_IT(IT) (((((IT) & 0xF0000000) == 0x00) || (((IT) & 0xEFF00000) == 0x00)) && ((IT) != 0x00)) �IS_DMA_GET_IT(IT) (((IT) == DMA1_IT_GL1) || ((IT) == DMA1_IT_TC1) || ((IT) == DMA1_IT_HT1) || ((IT) == DMA1_IT_TE1) || ((IT) == DMA1_IT_GL2) || ((IT) == DMA1_IT_TC2) || ((IT) == DMA1_IT_HT2) || ((IT) == DMA1_IT_TE2) || ((IT) == DMA1_IT_GL3) || ((IT) == DMA1_IT_TC3) || ((IT) == DMA1_IT_HT3) || ((IT) == DMA1_IT_TE3) || ((IT) == DMA1_IT_GL4) || ((IT) == DMA1_IT_TC4) || ((IT) == DMA1_IT_HT4) || ((IT) == DMA1_IT_TE4) || ((IT) == DMA1_IT_GL5) || ((IT) == DMA1_IT_TC5) || ((IT) == DMA1_IT_HT5) || ((IT) == DMA1_IT_TE5) || ((IT) == DMA1_IT_GL6) || ((IT) == DMA1_IT_TC6) || ((IT) == DMA1_IT_HT6) || ((IT) == DMA1_IT_TE6) || ((IT) == DMA1_IT_GL7) || ((IT) == DMA1_IT_TC7) || ((IT) == DMA1_IT_HT7) || ((IT) == DMA1_IT_TE7) || ((IT) == DMA2_IT_GL1) || ((IT) == DMA2_IT_TC1) || ((IT) == DMA2_IT_HT1) || ((IT) == DMA2_IT_TE1) || ((IT) == DMA2_IT_GL2) || ((IT) == DMA2_IT_TC2) || ((IT) == DMA2_IT_HT2) || ((IT) == DMA2_IT_TE2) || ((IT) == DMA2_IT_GL3) || ((IT) == DMA2_IT_TC3) || ((IT) == DMA2_IT_HT3) || ((IT) == DMA2_IT_TE3) || ((IT) == DMA2_IT_GL4) || ((IT) == DMA2_IT_TC4) || ((IT) == DMA2_IT_HT4) || ((IT) == DMA2_IT_TE4) || ((IT) == DMA2_IT_GL5) || ((IT) == DMA2_IT_TC5) || ((IT) == DMA2_IT_HT5) || ((IT) == DMA2_IT_TE5)) �DMA1_FLAG_GL1 ((uint32_t)0x00000001) �DMA1_FLAG_TC1 ((uint32_t)0x00000002) �DMA1_FLAG_HT1 ((uint32_t)0x00000004) �DMA1_FLAG_TE1 ((uint32_t)0x00000008) �DMA1_FLAG_GL2 ((uint32_t)0x00000010) �DMA1_FLAG_TC2 ((uint32_t)0x00000020) �DMA1_FLAG_HT2 ((uint32_t)0x00000040) �DMA1_FLAG_TE2 ((uint32_t)0x00000080) �DMA1_FLAG_GL3 ((uint32_t)0x00000100) �DMA1_FLAG_TC3 ((uint32_t)0x00000200) �DMA1_FLAG_HT3 ((uint32_t)0x00000400) �DMA1_FLAG_TE3 ((uint32_t)0x00000800) �DMA1_FLAG_GL4 ((uint32_t)0x00001000) �DMA1_FLAG_TC4 ((uint32_t)0x00002000) �DMA1_FLAG_HT4 ((uint32_t)0x00004000) �DMA1_FLAG_TE4 ((uint32_t)0x00008000) �DMA1_FLAG_GL5 ((uint32_t)0x00010000) �DMA1_FLAG_TC5 ((uint32_t)0x00020000) �DMA1_FLAG_HT5 ((uint32_t)0x00040000) �DMA1_FLAG_TE5 ((uint32_t)0x00080000) �DMA1_FLAG_GL6 ((uint32_t)0x00100000) �DMA1_FLAG_TC6 ((uint32_t)0x00200000) �DMA1_FLAG_HT6 ((uint32_t)0x00400000) �DMA1_FLAG_TE6 ((uint32_t)0x00800000) �DMA1_FLAG_GL7 ((uint32_t)0x01000000) �DMA1_FLAG_TC7 ((uint32_t)0x02000000) �DMA1_FLAG_HT7 ((uint32_t)0x04000000) �DMA1_FLAG_TE7 ((uint32_t)0x08000000) �DMA2_FLAG_GL1 ((uint32_t)0x10000001) �DMA2_FLAG_TC1 ((uint32_t)0x10000002) �DMA2_FLAG_HT1 ((uint32_t)0x10000004) �DMA2_FLAG_TE1 ((uint32_t)0x10000008) �DMA2_FLAG_GL2 ((uint32_t)0x10000010) �DMA2_FLAG_TC2 ((uint32_t)0x10000020) �DMA2_FLAG_HT2 ((uint32_t)0x10000040) �DMA2_FLAG_TE2 ((uint32_t)0x10000080) �DMA2_FLAG_GL3 ((uint32_t)0x10000100) �DMA2_FLAG_TC3 ((uint32_t)0x10000200) �DMA2_FLAG_HT3 ((uint32_t)0x10000400) �DMA2_FLAG_TE3 ((uint32_t)0x10000800) �DMA2_FLAG_GL4 ((uint32_t)0x10001000) �DMA2_FLAG_TC4 ((uint32_t)0x10002000) �DMA2_FLAG_HT4 ((uint32_t)0x10004000) �DMA2_FLAG_TE4 ((uint32_t)0x10008000) �DMA2_FLAG_GL5 ((uint32_t)0x10010000) �DMA2_FLAG_TC5 ((uint32_t)0x10020000) �DMA2_FLAG_HT5 ((uint32_t)0x10040000) �DMA2_FLAG_TE5 ((uint32_t)0x10080000) �IS_DMA_CLEAR_FLAG(FLAG) (((((FLAG) & 0xF0000000) == 0x00) || (((FLAG) & 0xEFF00000) == 0x00)) && ((FLAG) != 0x00)) �IS_DMA_GET_FLAG(FLAG) (((FLAG) == DMA1_FLAG_GL1) || ((FLAG) == DMA1_FLAG_TC1) || ((FLAG) == DMA1_FLAG_HT1) || ((FLAG) == DMA1_FLAG_TE1) || ((FLAG) == DMA1_FLAG_GL2) || ((FLAG) == DMA1_FLAG_TC2) || ((FLAG) == DMA1_FLAG_HT2) || ((FLAG) == DMA1_FLAG_TE2) || ((FLAG) == DMA1_FLAG_GL3) || ((FLAG) == DMA1_FLAG_TC3) || ((FLAG) == DMA1_FLAG_HT3) || ((FLAG) == DMA1_FLAG_TE3) || ((FLAG) == DMA1_FLAG_GL4) || ((FLAG) == DMA1_FLAG_TC4) || ((FLAG) == DMA1_FLAG_HT4) || ((FLAG) == DMA1_FLAG_TE4) || ((FLAG) == DMA1_FLAG_GL5) || ((FLAG) == DMA1_FLAG_TC5) || ((FLAG) == DMA1_FLAG_HT5) || ((FLAG) == DMA1_FLAG_TE5) || ((FLAG) == DMA1_FLAG_GL6) || ((FLAG) == DMA1_FLAG_TC6) || ((FLAG) == DMA1_FLAG_HT6) || ((FLAG) == DMA1_FLAG_TE6) || ((FLAG) == DMA1_FLAG_GL7) || ((FLAG) == DMA1_FLAG_TC7) || ((FLAG) == DMA1_FLAG_HT7) || ((FLAG) == DMA1_FLAG_TE7) || ((FLAG) == DMA2_FLAG_GL1) || ((FLAG) == DMA2_FLAG_TC1) || ((FLAG) == DMA2_FLAG_HT1) || ((FLAG) == DMA2_FLAG_TE1) || ((FLAG) == DMA2_FLAG_GL2) || ((FLAG) == DMA2_FLAG_TC2) || ((FLAG) == DMA2_FLAG_HT2) || ((FLAG) == DMA2_FLAG_TE2) || ((FLAG) == DMA2_FLAG_GL3) || ((FLAG) == DMA2_FLAG_TC3) || ((FLAG) == DMA2_FLAG_HT3) || ((FLAG) == DMA2_FLAG_TE3) || ((FLAG) == DMA2_FLAG_GL4) || ((FLAG) == DMA2_FLAG_TC4) || ((FLAG) == DMA2_FLAG_HT4) || ((FLAG) == DMA2_FLAG_TE4) || ((FLAG) == DMA2_FLAG_GL5) || ((FLAG) == DMA2_FLAG_TC5) || ((FLAG) == DMA2_FLAG_HT5) || ((FLAG) == DMA2_FLAG_TE5)) �IS_DMA_BUFFER_SIZE(SIZE) (((SIZE) >= 0x1) && ((SIZE) < 0x10000))        A   @   ?   �       
..\..\Libraries\FWlib\inc\stm32f10x_exti.h Component: ARM Compiler 5.06 update 6 (build 750) Tool: ArmCC [4d3637]  I:\2018电子设计大赛（自主设计）\2018(非RTX版)\Project\RVMDK（uv4）         �EXTI_Mode_Interrupt  EXTI_Mode_Event  PEXTIMode_TypeDef � 6�EXTI_Trigger_Rising EXTI_Trigger_Falling EXTI_Trigger_Rising_Falling  PEXTITrigger_TypeDef "C*�EXTI_Line W  # EXTI_Mode 
#EXTI_Trigger u#EXTI_LineCmd   # PEXTI_InitTypeDef �Y     t    h            ..\..\Libraries\FWlib\inc\ ..\..\Libraries\CMSIS\  stm32f10x_exti.h   stm32f10x.h      __STM32F10x_EXTI_H   8IS_EXTI_MODE(MODE) (((MODE) == EXTI_Mode_Interrupt) || ((MODE) == EXTI_Mode_Event)) EIS_EXTI_TRIGGER(TRIGGER) (((TRIGGER) == EXTI_Trigger_Rising) || ((TRIGGER) == EXTI_Trigger_Falling) || ((TRIGGER) == EXTI_Trigger_Rising_Falling)) gEXTI_Line0 ((uint32_t)0x00001) hEXTI_Line1 ((uint32_t)0x00002) iEXTI_Line2 ((uint32_t)0x00004) jEXTI_Line3 ((uint32_t)0x00008) kEXTI_Line4 ((uint32_t)0x00010) lEXTI_Line5 ((uint32_t)0x00020) mEXTI_Line6 ((uint32_t)0x00040) nEXTI_Line7 ((uint32_t)0x00080) oEXTI_Line8 ((uint32_t)0x00100) pEXTI_Line9 ((uint32_t)0x00200) qEXTI_Line10 ((uint32_t)0x00400) rEXTI_Line11 ((uint32_t)0x00800) sEXTI_Line12 ((uint32_t)0x01000) tEXTI_Line13 ((uint32_t)0x02000) uEXTI_Line14 ((uint32_t)0x04000) vEXTI_Line15 ((uint32_t)0x08000) wEXTI_Line16 ((uint32_t)0x10000) xEXTI_Line17 ((uint32_t)0x20000) yEXTI_Line18 ((uint32_t)0x40000) {EXTI_Line19 ((uint32_t)0x80000) }IS_EXTI_LINE(LINE) ((((LINE) & (uint32_t)0xFFF00000) == 0x00) && ((LINE) != (uint16_t)0x00)) ~IS_GET_EXTI_LINE(LINE) (((LINE) == EXTI_Line0) || ((LINE) == EXTI_Line1) || ((LINE) == EXTI_Line2) || ((LINE) == EXTI_Line3) || ((LINE) == EXTI_Line4) || ((LINE) == EXTI_Line5) || ((LINE) == EXTI_Line6) || ((LINE) == EXTI_Line7) || ((LINE) == EXTI_Line8) || ((LINE) == EXTI_Line9) || ((LINE) == EXTI_Line10) || ((LINE) == EXTI_Line11) || ((LINE) == EXTI_Line12) || ((LINE) == EXTI_Line13) || ((LINE) == EXTI_Line14) || ((LINE) == EXTI_Line15) || ((LINE) == EXTI_Line16) || ((LINE) == EXTI_Line17) || ((LINE) == EXTI_Line18) || ((LINE) == EXTI_Line19))        E   D   C   L       
..\..\Libraries\FWlib\inc\stm32f10x_flash.h Component: ARM Compiler 5.06 update 6 (build 750) Tool: ArmCC [4d3637]  I:\2018电子设计大赛（自主设计）\2018(非RTX版)\P