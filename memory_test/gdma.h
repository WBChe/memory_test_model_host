#include "zcu102_sender_global.h"
#ifndef GDMA_H
#define GDMA_H
#ifdef __cplusplus
extern "C" {
#endif
void Gdma_RegConfig(uint8_t index,
		uint32_t st_rd_addr_lsb, uint32_t st_rd_addr_msb,
		uint32_t rd_length,  //byte length-1;
		uint32_t st_wr_addr_lsb, uint32_t st_wr_addr_msb,
		uint32_t wr_length,uint32_t rd_wr_flag);

void RouterSetup(uint32_t chip_num);
void gtp_fifo_rst();
void gtp_speed_set();
void Gdma_StepSim(uint32_t step, uint8_t parallel_num, int16_t rev_num);
#ifdef __cplusplus
}
#endif
#endif






