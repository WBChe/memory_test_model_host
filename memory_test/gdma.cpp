#include "zcu102_sender_global.h"
#include "pcie_fun.h"
#include "gdma.h"
#include <unistd.h>
const uint32_t Gdma_Rd_Bit[4] = { GDMA0_RD_BIT,GDMA1_RD_BIT,GDMA2_RD_BIT,GDMA3_RD_BIT };
const uint32_t Gdma_Wr_Bit[4] = { GDMA0_WR_BIT,GDMA1_WR_BIT,GDMA2_WR_BIT,GDMA3_WR_BIT };
extern unsigned int gtp_state;
void Gdma_RegConfig(uint8_t index,
	uint32_t st_rd_addr_lsb, uint32_t st_rd_addr_msb,
	uint32_t rd_length,  //byte length-1;
	uint32_t st_wr_addr_lsb, uint32_t st_wr_addr_msb,
	uint32_t wr_length,uint32_t rd_wr_flag) 
{
	uint32_t offset;
	uint32_t clear_bit = 0;
	uint32_t t=0;
	switch (index) {
	case 0:  offset = 0x0;  break;
	case 1:  offset = 0x18; break;
	case 2:  offset = 0x30; break;
	case 3:  offset = 0x48; break;
	default: offset = 0x0;  break;
	}

	user_write(GDMA_CTRL_REG + offset   , st_rd_addr_lsb);
	user_write(GDMA_CTRL_REG + offset +4, st_rd_addr_msb);
	user_write(GDMA_CTRL_REG + offset +8, rd_length);

	user_write(GDMA_CTRL_REG + offset +12, st_wr_addr_lsb);
	user_write(GDMA_CTRL_REG + offset +16, st_wr_addr_msb);
	user_write(GDMA_CTRL_REG + offset +20, wr_length);
	switch(rd_wr_flag)
	{
	case 0x01:t =  Gdma_Wr_Bit[index];
		break;
	case 0x02:t = Gdma_Rd_Bit[index];
		break;
	case 0x03:t = Gdma_Rd_Bit[index] | Gdma_Wr_Bit[index];
		break;
	default:t = Gdma_Rd_Bit[index];
		break;

	}
	// if(rd_wr_flag==1)
	// if (wr_length != 0)
	// {
	// 	t = Gdma_Rd_Bit[index] | Gdma_Wr_Bit[index];

	// }
	// else
	// 	t = Gdma_Rd_Bit[index];
	//if (wr_length != 0)
	//{
	//	user_write(GDMA_CTRL_REG + GDMA_OP_OFFSET, 4, (unsigned char *)&Gdma_Wr_Bit[index]);
	//	Sleep(1);
	//	user_write(GDMA_CTRL_REG + GDMA_OP_OFFSET, 4, (unsigned char *)&clear_bit);
	//}
	user_write(GDMA_CTRL_REG + GDMA_OP_OFFSET, t);
	usleep(1000);
	user_write(GDMA_CTRL_REG + GDMA_OP_OFFSET, clear_bit);

	return;
}

void RouterSetup(uint32_t chip_num) {
	uint32_t chip_row, chip_column;
	uint32_t row_max, column_max;
	unsigned char *buffer;
	unsigned char *buf1;
	chip_row = chip_column = 127;

	buffer = (unsigned char *)malloc(100*sizeof(unsigned char));
	buf1 = (unsigned char *)malloc(100*sizeof(unsigned char));
	*(unsigned int *)buffer = (chip_row << 8) | chip_column;
	*(unsigned int *)(buffer + 4) = 0;
	*(unsigned int *)(buffer + 8) = ROUTER_SETUP;
	*(unsigned int *)(buffer + 12) = (chip_row << 8) | chip_column;
	*(unsigned int *)(buffer + 16) = 0;
	switch (chip_num) {
	case 64:
		row_max = 16;	column_max = 16;
		break;
	case 128:
		row_max = 8;	column_max = 16;
		break;
	case 192:
		row_max = 8;	column_max = 24;
		break;
	case 256:
		row_max = 8;	column_max = 32;
		break;
	case 512:
		row_max = 8;	column_max = 64;
		break;
	case 960:
		row_max = 8;	column_max = 120;
		break;
	default:
		row_max = 12;	column_max = 12;
		break;
	}

	*(unsigned int *)(buffer + 20) = (row_max << 22) | (column_max << 15) | (1 << 14) | (1 << 7) | 1;
	h2c_transfer(0, 24 * 4, (unsigned char *)buffer);
	usleep(100);
	c2h_transfer(0, 24 * 4, (unsigned char *)buf1);
	Gdma_RegConfig(0, 0, 0, (6 - 1) << 2, 0, 0, 0,RD_FLAG);
	//user_read(GPIO_IREG, 4, (unsigned char *)&chip_column);
	printf("RouterSetup");

}

void gtp_fifo_rst(){

	uint32_t i1 = 0;
	uint32_t i2 = 1;

	//gtp rst
	// i2 = 2;
	user_write(GPIO_OREG,i2);
	usleep(2);
	user_write(GPIO_OREG,i1);
	usleep(2);
	 i2 = 2;
	user_write(GPIO_OREG,i2);
	usleep(2);
	user_write(GPIO_OREG,i1);
	printf("gtp_fifo_rst\n");
}

void gtp_speed_set() {
	uint32_t gdma_speed_divider = 16; //  8 error 
	user_write(GDMA_CTRL_REG + GDMA_OP_OFFSET + 0x04,gdma_speed_divider);
	printf("gdma_speed_divider = %d\n", gdma_speed_divider);
}



void Gdma_StepSim(uint32_t step, uint8_t parallel_num, int16_t rev_num) {

	//uint8_t gdma_busy = 0;
	uint8_t gdma_index = 0;
	unsigned int val=0;
	unsigned int func_out_val=0;
	static uint32_t step_count = 1;
	unsigned int gdma_base[4] = { GDMA0_BASE_ADDR, GDMA1_BASE_ADDR, GDMA2_BASE_ADDR, GDMA3_BASE_ADDR };
	//xil_printf("every gdma channel: %d\r\n",chip_num/8 -1);
	//xil_printf("StepSim step = %d\r\n",step);

	step_count++;
	//	gdma_base = (uint32_t *)(Gdma_Base[0]+GDMA_BASE_ADDR);
	//	chip_row = chip_column = 1;
	//	gdma_base[0] = (chip_row<<8) | chip_column;
	//	gdma_base[1] = 0;
	//	gdma_base[2] = ROUTER_STEPSTART;
	
	for (gdma_index = 0; gdma_index < parallel_num; gdma_index++) {
		Gdma_RegConfig(gdma_index, gdma_base[gdma_index], 0, 0, (uint32_t)(gdma_base[gdma_index] + 0x100), 0, (rev_num) << 2,WR_FLAG);
		//usleep(100000);
	}
	while (val!= gtp_state)
	{
		val=user_read(GPIO_IREG);
		// printf("val=%d\n",val);
		// printf("gtp_state=%d\n",gtp_state);
	}

	//trigger gdma0 read and write;
	//		//wait for all transmission done;
	//		while((Gdma_WR_Done_Flag[0]==0) ||
	//			  (Gdma_WR_Done_Flag[1]==0) ||
	//			  (Gdma_WR_Done_Flag[2]==0) ||
	//			  (Gdma_WR_Done_Flag[3]==0));
	//while(1);
	return;
}
