#ifndef ZCU102_SENDER_GLOBAL_H
#define ZCU102_SENDER_GLOBAL_H
//#define OS_WIN

#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "string.h"
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <string>
#include <chrono>
//#include <Python.h>
//#include <dlfcn.h>
//#include <ffi.h>

#ifdef OS_WIN
#include <io.h>
#include <direct.h>
#endif



using namespace std;
typedef long clock_t;

#pragma pack(1)
typedef struct {
	unsigned int dCBWSignature;
	unsigned int dCBWTag;
	unsigned int dCBWDataTransferLength;
	unsigned int CBWCB[4];
	unsigned char bmCBWFlags;
	unsigned char cCBWLUN;
	unsigned char bCBWCBLength;
	unsigned char user;
} USB_CBW;

typedef struct {
	unsigned int dCSWSignature;
	unsigned int dCSWTag;
	unsigned int dCSWDataResidue;
	unsigned char bCSWStatus;
} USB_CSW;
#pragma pack()

#define PRINT_INFO

//customized usb internal cmd;
#define USB_CC_CMD		0x20
#define USB_CC_WRITE	0x2A
#define USB_CC_READ		0x28
//
#define PC_BLANK			0xFF
#define PC_DOWNLOAD 		0x00
#define PC_UPLOAD 	 		0x01
#define PC_CHECKBUSY		0x02
#define PC_STEPSIM			0x03
#define PC_DOWNLOAD_ONE 	0x04
#define PC_UPLOAD_ONE 		0x05
#define PC_DOWNLOAD_EXTERN 	0x06
#define PC_UPLOAD_EXTERN 	0x07
#define PC_SET_CHIP 		0x10
//
#define USB_EP1_OUT 0x01
#define USB_EP1_IN	0x81
//
#define GDMA_BASE_ADDR		0x800000000
#define GDMA0_BASE_ADDR 	0x0
#define GDMA1_BASE_ADDR		0x20000000
#define GDMA2_BASE_ADDR		0x40000000
#define GDMA3_BASE_ADDR		0x60000000
#define GDMA_ADDR_LIMIT		0x20000000

#define USB_TRANSFER_LIMIT 0x800000
#define OneWriteFileSize   0x800000
//CELL
//#define CELL_PROPERTY_BASE 0x00
//#define CELL_ROUTE_INFO_BASE 0x00
//#define CELL_WEIGHT_BASE 0x80000000


#define GDMA_CTRL_REG	  	0x10000

#define GDMA_SPEED_DIVIDER  0x10000 + 4*25
#define GPIO_OREG	  		0x10000 + 4*26
#define GPIO_IREG	  		0x10000 + 4*28
#define HOST_FLAG	  		0x10000 + 4*30
#define LAST_CTRL	  		0x10000 + 4*31

// #define GPIO_OREG	  	    0x12000
// #define GPIO_IREG	  	    0x14000
// #define BRAM    	  	    0x15000

#define GDMA_OP_OFFSET		0x60
#define GDMA0_RD_BIT		0x01
#define GDMA0_WR_BIT		0x02
#define GDMA1_RD_BIT		0x04
#define GDMA1_WR_BIT		0x08
#define GDMA2_RD_BIT		0x10
#define GDMA2_WR_BIT		0x20
#define GDMA3_RD_BIT		0x40
#define GDMA3_WR_BIT		0x80
//CMD
#define ROUTER_SETUP		0x4D420100
#define ROUTER_REMOTE		0x4D420101
#define EXTERN_SPIKE_OUT		0x10

//flag
#define RD_FLAG		0X02
#define WR_FLAG		0X01
#define RD_WR_FLAG	0X03


#define SRAM        0x2000C000
// #define SRAM        0x20000000
#define LUT         0x4000C000
#define APB_SMU     0x10400000

//BPU NPU
#define NPU0_CSR				0x30000000
#define NPU0_CSR_MODEL_CFG0		NPU0_CSR
#define NPU0_CSR_MODEL_CFG1		NPU0_CSR + 8
#define NPU0_CSR_MODEL_CFG2		NPU0_CSR + 16
#define NPU0_CSR_MODEL_CFG3		NPU0_CSR + 24
#define NPU0_CSR_MODEL_CFG4		NPU0_CSR + 32
#define NPU0_CSR_HW_CFG0		NPU0_CSR + 40
#define NPU0_CSR_MAT_CFG		NPU0_CSR + 48
#define NPU0_CSR_RUN			NPU0_CSR + 56 
#define NPU0_CSR_TEST_CFG0		NPU0_CSR + 64
#define NPU0_CSR_NPU_STATUS		NPU0_CSR + 72

#define NPU0_SMT		0x30100000
#define NPU0_SPIKE		0x30200000
#define NPU0_NCU		0x30208000
#define NPU0_INDEX		0x305E0000
#define NPU0_WEIGHT 	0x30600000

//Type
#define packet_spike 0
#define packet_raw 1
#define packet_read 2
#define packet_write 3

////usb functions;
//libusb_device_handle *USB_Init();
//void USB_Exit(libusb_device_handle *dev_handle);
//void USB_SendCmd(libusb_device_handle *dev_handle, unsigned char pc_cmd, unsigned int *usb_cmd);
//void USB_ReadWrite(libusb_device_handle *dev_handle, unsigned char endpoint, unsigned char *data, unsigned int start_addr,
//				   unsigned int transfer_length);
//unsigned char USB_RecvCSW(libusb_device_handle *dev_handle);
//
////gdma functions;
//void Gdma_ParallelDownload(libusb_device_handle *dev_handle, unsigned int *usb_cmd);
//void Gdma_ParallelUpload(libusb_device_handle *dev_handle, unsigned int *usb_cmd);
//void Gdma_DumpFile(libusb_device_handle *dev_handle, char *path_prefix,
//					unsigned char gdma_index, unsigned int gdma_addroffset, unsigned int byte_length);

//file functions;
unsigned int Files_LoadMem_Download(FILE *fp, unsigned char gdma_index, unsigned int file_index,
									long file_size, unsigned int gdma_addroffset, unsigned int cell_start_addr, unsigned int chip_num, bool extern_spike, unsigned int packet_type);
void Files_ReadMem_Upload(char *path_prefix, unsigned int file_index_start,
						   unsigned int block_num, unsigned int *aligned_file_size, unsigned char gdma_index, unsigned int chip_num,unsigned int t);
void Files_LoadMem_Upload( unsigned int file_index, unsigned int cell_start_addr,
							unsigned int aligned_file_size, unsigned char gdma_index, unsigned int gdma_addroffset, unsigned int chip_num,unsigned int hw_type);
void Files_ParallelDownload_All(char *path_prefix, unsigned int cell_start_addr, 
				unsigned char parallel_num, unsigned int chip_num, unsigned int chip_sel, bool extern_spike, unsigned int packet_type);
void Files_ParallelUpload_ALL(char *path_prefix, unsigned int cell_start_addr, unsigned int byte_length, 
								unsigned char parallel_num, unsigned int chip_num, unsigned int chip_sel, bool extern_spike, unsigned int hw_type,unsigned int t);

//void Serdes_Init(libusb_device_handle *dev_handle, unsigned int parallel_num, unsigned int chip_num);
//void Serdes_StepSim(libusb_device_handle *dev_handle,unsigned int step);
/* void Files_ParallelDownload_One(char *path_prefix, unsigned int cell_start_addr, unsigned int chip_num);
void Files_ParallelUpload_One(char *path_prefix, 
							  unsigned int cell_start_addr, unsigned int byte_length, unsigned int chip_num); */

#endif
