
#include "pcie_fun.h"
#include "zcu102_sender_global.h"
#include "gdma.h"
#define SERDES_ON
#define FILES_DEBUG_PRINT
#define DOWNLOAD_DEBUG_PRINT
#define UPLOAD_DEBUG_PRINT
#define PARALLEL 1
//#define chip_num 256
//#define change_num chip_num/4
extern unsigned int gtp_state;


//Type
#define spike 0
#define raw 1
#define read 2
#define write 3

//req
#define request 0
#define response 1



/********** board: 1, chip_max: 9, row_max: 3, column_max: 3 **********/
const char *chip_num_table9[1][9] = {
	{
	 "_0.bin", "_1.bin", "_2.bin", 
	 "_3.bin", "_4.bin", "_5.bin", 
	 "_6.bin", "_7.bin", "_8.bin"
	 }
};
const unsigned int chip_row_table9[1][9] = {
	{
	 1, 1, 1, 2, 2, 2, 
	 3, 3, 3
	 }
};
const unsigned int chip_column_table9[1][9] = {
	{
	 1, 2, 3, 1, 2, 3, 
	 1, 2, 3
	 }
};

/********** board: 2, chip_max: 18, row_max: 6, column_max: 3 **********/
const char *chip_num_table18[1][18] = {
        {
         "_0.bin", "_1.bin", "_2.bin",
         "_3.bin", "_4.bin", "_5.bin",
         "_6.bin", "_7.bin", "_8.bin",
         "_9.bin", "_10.bin", "_11.bin",
         "_12.bin", "_13.bin", "_14.bin",
         "_15.bin", "_16.bin", "_17.bin"
         }
};
const unsigned int chip_row_table18[1][18] = {
        {
         1, 1, 1, 2, 2, 2,
         3, 3, 3, 4, 4, 4,
         5, 5, 5, 6, 6, 6
         }
};
const unsigned int chip_column_table18[1][18] = {
        {
         1, 2, 3, 1, 2, 3,
         1, 2, 3, 1, 2, 3,
         1, 2, 3, 1, 2, 3
         }
};

///********** board: 2, chip_max: 18, row_max: 3, column_max: 6 **********/
//const char *chip_num_table18[1][18] = {
//        {
//         "_0.bin", "_1.bin", "_2.bin", "_3.bin", "_4.bin", "_5.bin",
//         "_6.bin", "_7.bin", "_8.bin", "_9.bin", "_10.bin", "_11.bin",
//         "_12.bin", "_13.bin", "_14.bin", "_15.bin", "_16.bin", "_17.bin"
//         }
//};
//const unsigned int chip_row_table18[1][18] = {
//        {
//         1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2,
//         3, 3, 3, 3, 3, 3
//         }
//};
//const unsigned int chip_column_table18[1][18] = {
//        {
//         1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6,
//         1, 2, 3, 4, 5, 6
//         }
//};

/********** board: 1, chip_max: 32, row_max: 4, column_max: 8 **********/
const char *chip_num_table32[4][8] = {
	{
		"_0.bin", "_1.bin", "_2.bin", "_3.bin", "_4.bin", "_5.bin", "_6.bin", "_7.bin"
	},
	{
		"_8.bin", "_9.bin", "_10.bin", "_11.bin", "_12.bin", "_13.bin", "_14.bin", "_15.bin"
	},
	{
		"_16.bin", "_17.bin", "_18.bin", "_19.bin", "_20.bin", "_21.bin", "_22.bin", "_23.bin"
	},
	{
		"_24.bin", "_25.bin", "_26.bin", "_27.bin", "_28.bin", "_29.bin", "_30.bin", "_31.bin"
	}
};
const unsigned int chip_row_table32[4][8] = {
	{
		1, 1, 1, 1, 1, 1, 1, 1
	},
	{
		2, 2, 2, 2, 2, 2, 2, 2
	},
	{
		3, 3, 3, 3, 3, 3, 3, 3
	},
	{
		4, 4, 4, 4, 4, 4, 4, 4
	}
};
const unsigned int chip_column_table32[4][8] = {
	{
		1, 2, 3, 4, 5, 6, 7, 8
	},
	{
		1, 2, 3, 4, 5, 6, 7, 8
	},
	{
		1, 2, 3, 4, 5, 6, 7, 8
	},
	{
		1, 2, 3, 4, 5, 6, 7, 8
	}
};



/********** board: 4, chip_max: 36, row_max: 6, column_max: 6 **********/
const char *chip_num_table36[1][64] = {
	{
	 "_0.bin",  "_1.bin",  "_2.bin",  "_3.bin",  "_4.bin",  "_5.bin",  "_6.bin",  "_7.bin", 
	 "_8.bin",  "_9.bin",  "_10.bin", "_11.bin", "_12.bin", "_13.bin", "_14.bin", "_15.bin", 
	 "_16.bin", "_17.bin", "_18.bin", "_19.bin", "_20.bin", "_21.bin", "_22.bin", "_23.bin", 
	 "_24.bin", "_25.bin", "_26.bin", "_27.bin", "_28.bin", "_29.bin", "_30.bin", "_31.bin", 
	 "_32.bin", "_33.bin", "_34.bin", "_35.bin", "_36.bin", "_37.bin", "_38.bin", "_39.bin", 
	 "_40.bin", "_41.bin", "_42.bin", "_43.bin", "_44.bin", "_45.bin", "_46.bin", "_47.bin", 
	 "_48.bin", "_49.bin", "_50.bin", "_51.bin", "_52.bin", "_53.bin", "_54.bin", "_55.bin", 
	 "_56.bin", "_57.bin", "_58.bin", "_59.bin", "_60.bin", "_61.bin", "_62.bin", "_63.bin"
	 }
};
const unsigned int chip_row_table36[1][64] = {
	{
	 0, 1, 2, 3, 4, 5, 6, 7, 
	 0, 1, 2, 3, 4, 5, 6, 7, 
	 0, 1, 2, 3, 4, 5, 6, 7, 
	 0, 1, 2, 3, 4, 5, 6, 7, 
	 0, 1, 2, 3, 4, 5, 6, 7, 
	 0, 1, 2, 3, 4, 5, 6, 7,
	 0, 1, 2, 3, 4, 5, 6, 7,
	 0, 1, 2, 3, 4, 5, 6, 7
	 }
};
const unsigned int chip_column_table36[1][64] = {
	{
	 0, 0, 0, 0, 0, 0, 0, 0, 
	 1, 1, 1, 1, 1, 1, 1, 1, 
	 2, 2, 2, 2, 2, 2, 2, 2, 
	 3, 3, 3, 3, 3, 3, 3, 3,
	 4, 4, 4, 4, 4, 4, 4, 4, 
	 5, 5, 5, 5, 5, 5, 5, 5, 
	 6, 6, 6, 6, 6, 6, 6, 6, 
	 7, 7, 7, 7, 7, 7, 7, 7
	 }
}; 

//
///********** board: 4, chip_max: 36, row_max: 12, column_max: 3 **********/
//const char *chip_num_table36[1][36] = {
//	{
//	 "_0.bin", "_1.bin", "_2.bin", 
//	 "_3.bin", "_4.bin", "_5.bin", 
//	 "_6.bin", "_7.bin", "_8.bin", 
//	 
//	 "_9.bin", "_10.bin", "_11.bin", 
//	 "_12.bin", "_13.bin", "_14.bin", 
//	 "_15.bin", "_16.bin", "_17.bin", 
//	 
//	 "_18.bin", "_19.bin", "_20.bin", 
//	 "_21.bin", "_22.bin", "_23.bin", 
//	 "_24.bin", "_25.bin", "_26.bin", 
//	 
//	 "_27.bin", "_28.bin", "_29.bin", 
//	 "_30.bin", "_31.bin", "_32.bin", 
//	 "_33.bin", "_34.bin", "_35.bin"
//	 }
//};
//const unsigned int chip_row_table36[1][36] = {
//	{
//	 1, 1, 1, 2, 2, 2, 
//	 3, 3, 3, 4, 4, 4, 
//	 5, 5, 5, 6, 6, 6, 
//	 7, 7, 7, 8, 8, 8, 
//	 9, 9, 9, 10, 10, 10, 
//	 11, 11, 11, 12, 12, 12
//	 }
//};
//const unsigned int chip_column_table36[1][36] = {
//	{
//	 1, 2, 3, 1, 2, 3, 
//	 1, 2, 3, 1, 2, 3, 
//	 1, 2, 3, 1, 2, 3, 
//	 1, 2, 3, 1, 2, 3, 
//	 1, 2, 3, 1, 2, 3, 
//	 1, 2, 3, 1, 2, 3
//	 }
//};

//
///********** board: 1, chip_max: 32, row_max: 4, column_max: 8 **********/
//const char *chip_num_table32[1][32] = {
//	{
//		"_0.bin", "_1.bin", "_2.bin", "_3.bin", "_4.bin", "_5.bin", "_6.bin", "_7.bin",
//		"_8.bin", "_9.bin", "_10.bin", "_11.bin", "_12.bin", "_13.bin", "_14.bin", "_15.bin",
//	"_16.bin", "_17.bin", "_18.bin", "_19.bin", "_20.bin", "_21.bin", "_22.bin", "_23.bin",
//	"_24.bin", "_25.bin", "_26.bin", "_27.bin", "_28.bin", "_29.bin", "_30.bin", "_31.bin"
//	}
//};
//const unsigned int chip_row_table32[1][32] = {
//	{
//		1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2,
//		3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4
//	}
//};
//const unsigned int chip_column_table32[1][32] = {
//	{
//		1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8,
//		1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8
//	}
//};



/********** board: 8, chip_max: 72, row_max: 6, column_max: 12 **********/
const char *chip_num_table72[1][72] = {
	{
	 "_0.bin", "_1.bin", "_2.bin", "_3.bin", "_4.bin", "_5.bin", "_6.bin", "_7.bin", "_8.bin", "_9.bin", "_10.bin", "_11.bin", 
	 "_12.bin", "_13.bin", "_14.bin", "_15.bin", "_16.bin", "_17.bin", "_18.bin", "_19.bin", "_20.bin", "_21.bin", "_22.bin", "_23.bin", 
	 "_24.bin", "_25.bin", "_26.bin", "_27.bin", "_28.bin", "_29.bin", "_30.bin", "_31.bin", "_32.bin", "_33.bin", "_34.bin", "_35.bin", 
	 "_36.bin", "_37.bin", "_38.bin", "_39.bin", "_40.bin", "_41.bin", "_42.bin", "_43.bin", "_44.bin", "_45.bin", "_46.bin", "_47.bin", 
	 "_48.bin", "_49.bin", "_50.bin", "_51.bin", "_52.bin", "_53.bin", "_54.bin", "_55.bin", "_56.bin", "_57.bin", "_58.bin", "_59.bin", 
	 "_60.bin", "_61.bin", "_62.bin", "_63.bin", "_64.bin", "_65.bin", "_66.bin", "_67.bin", "_68.bin", "_69.bin", "_70.bin", "_71.bin"
	 }
};
const unsigned int chip_row_table72[1][72] = {
	{
	 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 
	 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
	 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6
	 }
};
const unsigned int chip_column_table72[1][72] = {
	{
	 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 
	 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 
	 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12
	 }
};

//the file is split into 8MB chunks to send;
unsigned int Files_LoadMem_Download(FILE *fp, unsigned char gdma_index, unsigned int file_index, 
					long file_size, unsigned int gdma_addroffset, unsigned int cell_start_addr, unsigned int chip_num, bool extern_spike,unsigned int packet_type) {
	unsigned int i;
	unsigned char *file_buffer=NULL;
	unsigned int transfer_round;
	unsigned int aligned_file_size;  //start from 1;
	unsigned int transfer_round_limit;
	unsigned int gdma_base[4] = { GDMA0_BASE_ADDR, GDMA1_BASE_ADDR, GDMA2_BASE_ADDR, GDMA3_BASE_ADDR };
	unsigned int chip_pos;
	unsigned int word_length;
	unsigned int cmd = 0x47545057; //GTPW
	unsigned int byte_length;
	unsigned int x_src=0 ,y_src=-1;
	//unsigned int buf1[2048];

	//for (i = 0; i<1024; i++)
	//{
	//	buf1[i] = i;
	//}
	if (file_size % 4 != 0)   //32bit address alignment tunning;
		aligned_file_size = ((file_size >> 2) + 1) << 2;
	else
		aligned_file_size = file_size;
	file_buffer = (unsigned char *)malloc(USB_TRANSFER_LIMIT*sizeof(unsigned char));

	//packet_type 
	if(packet_type != packet_spike) {//-----------------------------new 6.5
		switch (chip_num) {
			case 9:
				chip_pos = (chip_row_table9[gdma_index][file_index] ) | (chip_column_table9[gdma_index][file_index] << 14);
				break;
			
			case 18:
				chip_pos = (chip_row_table18[gdma_index][file_index] ) | (chip_column_table18[gdma_index][file_index] << 14);
				break;
			case 32:
				chip_pos = (chip_row_table32[gdma_index][file_index] ) | (chip_column_table32[gdma_index][file_index] << 14);
				break;

			case 36:
				chip_pos = (chip_row_table36[gdma_index][file_index] ) | (chip_column_table36[gdma_index][file_index] << 14);
				break;
				
			case 72:
				chip_pos = (chip_row_table72[gdma_index][file_index] ) | (chip_column_table72[gdma_index][file_index] << 14);
				break;
				
			default:
				chip_pos = (chip_row_table36[gdma_index][file_index] ) | (chip_column_table36[gdma_index][file_index] << 14);
				break;
		}
		//transfer header;
		byte_length = aligned_file_size >> 3; 
		*(unsigned int *)(file_buffer) = (x_src&0x3FFF)|((y_src& 0x3FFF) <<14)|(chip_pos<<28);
		*(unsigned int *)(file_buffer + 4) = (packet_type << 29)|(request << 28)|(chip_pos >> 4);
		*(unsigned int *)(file_buffer + 8) = byte_length;
		*(unsigned int *)(file_buffer + 12) = cell_start_addr;
	}
	else {
		cout << "transfer packet_spike type" << endl;
	}

	
if (!extern_spike) {
		//printf("chip_pos = %d\r\n", chip_pos);
		//printf("gdma_index = %d\r\n", gdma_index);
		//cout << "send normal cmd mode" << endl;
	//	USB_ReadWrite(dev_handle, USB_EP1_OUT, file_buffer, gdma_base[gdma_index] + gdma_addroffset, 20);
	

//		h2c_transfer(0, 1024 * 4, (unsigned char *)buf1);
		h2c_transfer(gdma_base[gdma_index] + gdma_addroffset, 4*4 , (unsigned char *)file_buffer);
	//	c2h_transfer(gdma_base[gdma_index] + gdma_addroffset, 20, (unsigned char *)buf1);
		gdma_addroffset += 16;

		
	}
	else {
		cout << "extern spike mode" << endl;
	}

//transfer file data;
	if (aligned_file_size % USB_TRANSFER_LIMIT == 0)
			transfer_round_limit = aligned_file_size / USB_TRANSFER_LIMIT;
		else
			transfer_round_limit = aligned_file_size / USB_TRANSFER_LIMIT + 1;
		for (transfer_round = 0; transfer_round < transfer_round_limit; transfer_round++) {
			if (transfer_round == transfer_round_limit - 1) {
				fread(file_buffer, sizeof(unsigned char), file_size - transfer_round*USB_TRANSFER_LIMIT,fp);
				for (i = 0; i < aligned_file_size - file_size; i++)
					file_buffer[i + file_size - transfer_round*USB_TRANSFER_LIMIT] = 0; //add 0 to remaining bytes;
				//USB_ReadWrite(dev_handle, USB_EP1_OUT, file_buffer, gdma_base[gdma_index] + gdma_addroffset, aligned_file_size - transfer_round*USB_TRANSFER_LIMIT);
				h2c_transfer(gdma_base[gdma_index] + gdma_addroffset, (aligned_file_size - transfer_round*USB_TRANSFER_LIMIT) * 4, (unsigned char *)file_buffer);
			}
			else {
				fread(file_buffer, sizeof(unsigned char), USB_TRANSFER_LIMIT, fp);
				//USB_ReadWrite(dev_handle, USB_EP1_OUT, file_buffer, gdma_base[gdma_index] + gdma_addroffset, USB_TRANSFER_LIMIT);
				h2c_transfer(gdma_base[gdma_index] + gdma_addroffset, (USB_TRANSFER_LIMIT) * 4, (unsigned char *)file_buffer);
				gdma_addroffset += USB_TRANSFER_LIMIT;
			}
		}

//	c2h_transfer(0, (2048)* 4, (unsigned char *)buf1);

	free(file_buffer);
	return aligned_file_size;
}

//download files to all cell chips;
//the 4 gdma should send data in parallel;
//single file data size cannot exceed 512MB-20B since there is no slicing in gdma mem space;
//file transfer buffer array will set to 8MB;
void Files_ParallelDownload_All(char *path_prefix, unsigned int cell_start_addr, 
				unsigned char parallel_num, unsigned int chip_num, unsigned int chip_sel, bool extern_spike, unsigned int packet_type){
	unsigned int file_index = 0;
	unsigned int aligned_file_size = 0;
	unsigned char gdma_index = 0;
	unsigned char file_overflow_flag = 0, file_unsupport_flag = 0;
	unsigned int i = 0;
	unsigned int val=0;
	unsigned int gdma_base[4] = { GDMA0_BASE_ADDR, GDMA1_BASE_ADDR, GDMA2_BASE_ADDR, GDMA3_BASE_ADDR };
	FILE *fp = NULL;
	unsigned int prefix_len = 0, postfix_len = 0;
	long file_size;
	unsigned int gdma_addroffset[4] = { 0, 0, 0, 0 };
	unsigned int send_byte_length[4] = { 0xcccccccc, 0xcccccccc, 0xcccccccc, 0xcccccccc };  //start from 0;
	const unsigned int change_num = chip_num / parallel_num;

	//printf("Files_ParallelDownload_All\n");
	char *file_path = NULL;
	unsigned int func_out_val;
//copy path prefix;
	prefix_len = strlen((const char *)path_prefix);
	file_path = (char *)malloc((prefix_len + postfix_len + 100)*sizeof(char));
	for (i = 0; i < prefix_len; i++)
		file_path[i] = path_prefix[i];
//every gdma has 64 files to send;
	for (file_index = chip_sel; file_index < change_num; ) {

		//preprocess;
		for (gdma_index = 0; gdma_index < parallel_num; gdma_index++) { //open 4 files and check if all the 4 files can fit into gdma mem space;
			fp = NULL;
			switch (chip_num) {
				case 9:
					postfix_len = strlen(chip_num_table9[gdma_index][file_index]);
					for (i = 0; i < postfix_len + 1; i++)  //plus 1 include '\0';
							file_path[i + prefix_len] = chip_num_table9[gdma_index][file_index][i];
					break;	
				
				case 18:
					postfix_len = strlen(chip_num_table18[gdma_index][file_index]);
					for (i = 0; i < postfix_len + 1; i++)  //plus 1 include '\0';
									file_path[i + prefix_len] = chip_num_table18[gdma_index][file_index][i];
					break;

				case 32:
					postfix_len = strlen(chip_num_table32[gdma_index][file_index]);
					for (i = 0; i < postfix_len + 1; i++)  //plus 1 include '\0';
						file_path[i + prefix_len] = chip_num_table32[gdma_index][file_index][i];
					break;
				
				case 36:
					postfix_len = strlen(chip_num_table36[gdma_index][file_index]);
					for (i = 0; i < postfix_len + 1; i++)  //plus 1 include '\0';
						file_path[i + prefix_len] = chip_num_table36[gdma_index][file_index][i];
					break;
					
									
				case 72:
					postfix_len = strlen(chip_num_table72[gdma_index][file_index]);
					for (i = 0; i < postfix_len + 1; i++)  //plus 1 include '\0';
						file_path[i + prefix_len] = chip_num_table72[gdma_index][file_index][i];
					break;
					
				default:
					postfix_len = strlen(chip_num_table36[gdma_index][file_index]);
					for (i = 0; i < postfix_len + 1; i++)  //plus 1 include '\0';
						file_path[i + prefix_len] = chip_num_table36[gdma_index][file_index][i];
					break;
			}	
			//printf("open file: %s\n", file_path);
#ifdef PRINT_INFO
			//if (file_index == 0 && gdma_index ==0) {	
				cout << "open file: " << file_path << endl; 
			//}
#endif
#ifdef OS_WIN
			//fopen_s(&fp, file_path, "rb");
			fp = fopen(file_path, "rb");
#else
			fp = fopen(file_path, "rb");
#endif	
	        if (fp == NULL) {
				//printf("Files_ParallelDownload_All: fopen_s failed, no such file\r\n");
				cout << "Files_ParallelDownload_All: fopen_s failed, no such file" << endl;
				file_unsupport_flag = 1;
				break;
			}
			fseek(fp, 0, SEEK_END);
			file_size = ftell(fp);
			fseek(fp, 0, SEEK_SET);
			//
			if (file_size > GDMA_ADDR_LIMIT - 16) { //single file exceed upper limit;
				//printf("Files_ParallelDownload_All: single file size exceed upper limit %ld\n", file_size);
				cout << "Files_ParallelDownload_All: single file size exceed upper limit " << file_size << endl;
				file_unsupport_flag = 1;
				break;
			}
			else if (file_size + gdma_addroffset[gdma_index] + 16 > GDMA_ADDR_LIMIT) { //file size overflow;
				//printf("Files_ParallelDownload_All: file total size overflow, prepare to send out\n");
				cout << "Files_ParallelDownload_All: file total size overflow, prepare to send out" << endl;
				file_overflow_flag = 1;
			}
			else {  //load file to zcu102 ddr;
				aligned_file_size = Files_LoadMem_Download(fp, gdma_index, file_index, file_size,
													       gdma_addroffset[gdma_index], cell_start_addr, chip_num, extern_spike,packet_type); //load mem with current file;

				gdma_addroffset[gdma_index] += (aligned_file_size + 16); //file size and additional 20byte head;

			}

			fclose(fp); //close current file;
		}
		//postprocess;
		if (file_unsupport_flag == 1) {  //close exit;
			return;
		}
		else if ((file_overflow_flag == 1) || (file_index == change_num-1)) { //the rest mem space cannot hold the next file, need to transfer first;
			for (gdma_index = 0; gdma_index < parallel_num; gdma_index++) {	//32bit address alignment tunning;
				if (gdma_addroffset[gdma_index] % 4 == 0)
					send_byte_length[gdma_index] = gdma_addroffset[gdma_index] - 4; //gdma discard lower 2 bits and add 1 to upper bit;
				else {
					//printf("Files_ParallelDownload_All: gdma_addroffset not aligned\n");
					cout << "Files_ParallelDownload_All: gdma_addroffset not aligned" << endl;
					return;
				}
			} 

#ifdef SERDES_ON
			// printf("Files_ParallelDownload_All: Trigger gdma send_byte_length[0]=%d,send_byte_length[1]=%d,send_byte_length[2]=%d,send_byte_length[3]=%d\n",
			// 	send_byte_length[0], send_byte_length[1], send_byte_length[2], send_byte_length[3]);
			//	gdma_index = 0;
				printf("Files_ParallelDownload_All: Trigger gdma send_byte_length[0]=%d,send_byte_length[1]=%d,send_byte_length[2]=%d,send_byte_length[3]=%d\n",
				send_byte_length[0], send_byte_length[1], send_byte_length[2], send_byte_length[3]);
			//	gdma_index = 0;
			for (gdma_index = 0; gdma_index < parallel_num; gdma_index++) {
				if (extern_spike)
					//USB_SendCmd(dev_handle, PC_DOWNLOAD_EXTERN, send_byte_length);  //trigger gdma to send data;
					//extern inject need to transfer spike stream data

					//Gdma_RegConfig(gdma_index, gdma_base[gdma_index], 0, send_byte_length[gdma_index] -16, 0, 0, 0,RD_FLAG);//-----------------------------new 6.5
					Gdma_RegConfig(gdma_index, gdma_base[gdma_index], 0, send_byte_length[gdma_index]-16, 0, 0, 131072*2-1, RD_WR_FLAG); //修改最后两个变量，65536-1为写回ddr的数据个数，rd wr flag为拉高rd wr start开始读写ddr
					//131072-1

					//file_index = 0;//
				else
					Gdma_RegConfig(gdma_index, gdma_base[gdma_index], 0, send_byte_length[gdma_index], 0, 0, 0,RD_FLAG);
					//Gdma_RegConfig(gdma_index, gdma_base[gdma_index], 0, send_byte_length[gdma_index], 0x10000, 0, send_byte_length[gdma_index], WR_FLAG);
	
			}
		while (val != gtp_state)
				{
					val=user_read(GPIO_IREG);
			
				}

			//USB_SendCmd(dev_handle, PC_DOWNLOAD, send_byte_length);  //trigger gdma to send data;
			//	USB_RecvCSW(dev_handle);  //wait for transmit done;
			//printf("Files_ParallelDownload_All: send out complete\n");
			cout << "Files_ParallelDownload_All: send out complete" << endl;
			val=0;
			//USB_SendCmd(dev_handle, PC_DOWNLOAD, send_byte_length);  //trigger gdma to send data;
			//	USB_RecvCSW(dev_handle);  //wait for transmit done;
			//cout << "Files_ParallelDownload_All: send out complete" << endl;
#else
			for (gdma_index = 0; gdma_index < parallel_num; gdma_index++) {
				printf("Files_ParallelDownload_All: send_byte_length[%d] = %d\n", gdma_index, send_byte_length[gdma_index]);
				//Gdma_DumpFile(dev_handle, path_prefix, gdma_index, 0, gdma_addroffset[gdma_index]);
			}
#endif

			for (gdma_index = 0; gdma_index < parallel_num; gdma_index++)
				gdma_addroffset[gdma_index] = 0;
			file_overflow_flag = 0;
			if ((file_index == change_num-1) && (file_overflow_flag != 1))
				file_index++;
				}
			else
				file_index++;


	}
	//free(file_path);
	return;
}

//read mem data and write to files;
//1 gdma every block correspond to 1 file;
void Files_ReadMem_Upload( char *path_prefix, unsigned int file_index_start,
						  unsigned int block_num, unsigned int *aligned_file_size, unsigned char gdma_index, unsigned int chip_num,unsigned int t) {
	unsigned int path_len = 0;
	unsigned int i = 0;
	unsigned int block_cnt;
	char *file_path = NULL; 
	unsigned int file_index = file_index_start;
	unsigned char *file_buffer;
	unsigned int transfer_round;
	unsigned int transfer_round_limit;
	unsigned int gdma_addroffset = 0;
	unsigned int gdma_base[4] = { GDMA0_BASE_ADDR, GDMA1_BASE_ADDR, GDMA2_BASE_ADDR, GDMA3_BASE_ADDR };
	unsigned int index = 0;
	FILE *fp = NULL;

//copy path prefix;
	path_len = strlen((const char *)path_prefix);
	file_path = (char *)malloc((path_len + 100)*sizeof(char));
	file_buffer = (unsigned char *)malloc(OneWriteFileSize * sizeof(unsigned char));
	for (i = 0; i < path_len; i++)
		file_path[i] = path_prefix[i];
	for (block_cnt = 0; block_cnt < block_num; block_cnt++) {
		switch (chip_num) {
			case 9:
				for (i = 0; i < 9; i++)
					file_path[i + path_len] = chip_num_table9[gdma_index][file_index][i];
				break;
			
			case 18:
				for (i = 0; i < 9; i++)
					file_path[i + path_len] = chip_num_table18[gdma_index][file_index][i];
				break;

			case 32:
				for (i = 0; i < 9; i++)
					file_path[i + path_len] = chip_num_table32[gdma_index][file_index][i];
				break;

			case 36:
				for (i = 0; i < 9; i++)
					file_path[i + path_len] = chip_num_table36[gdma_index][file_index][i];
				break;
				
			case 72:
				for (i = 0; i < 9; i++)
					file_path[i + path_len] = chip_num_table72[gdma_index][file_index][i];
				break;				
			default:
				for (i = 0; i < 9; i++)
					file_path[i + path_len] = chip_num_table36[gdma_index][file_index][i];
				break;
		}
#ifdef PRINT_INFO
		//if (file_index == 0 && gdma_index ==0) {
			cout << "upload: " << file_path << endl; 
		//}
#endif
		if(t==0){
			
			//remove(file_path);-------------------------------------------------------------------//stop romove data
			// if(remove(file_path)==0)
			// 	cout<<"delete suceesed:"<<file_path<<endl;
			// else
			// 	cout<<"delete failed:"<<file_path<<endl;
				
		}
			
		//else 
			
		//cout<<"writing..."<<endl;
			
		
#ifdef OS_WIN		
		//fopen_s(&fp, file_path, "wb+");

		fp = fopen(file_path,"ab+");
#else
	
		fp = fopen(file_path,"ab+");
#endif
		//printf("upload to file %s\n", file_path);
		if (fp == NULL)
			//printf("Files_ReadMem_Upload: fopen_s failed\n");
			cout << "Files_ReadMem_Upload: fopen_s failed" << endl;
		if (aligned_file_size[file_index] % OneWriteFileSize == 0)
			transfer_round_limit = aligned_file_size[file_index] / OneWriteFileSize;
		else
			transfer_round_limit = aligned_file_size[file_index] / OneWriteFileSize + 1;
		for (transfer_round = 0; transfer_round < transfer_round_limit; transfer_round++) {
			if (transfer_round == transfer_round_limit - 1) {
				/* USB_ReadWrite(dev_handle, USB_EP1_IN, file_buffer, gdma_base[gdma_index] + gdma_addroffset, 
							  aligned_file_size[file_index] - transfer_round*OneWriteFileSize); */
				c2h_transfer(gdma_base[gdma_index] + gdma_addroffset, (aligned_file_size[file_index] - transfer_round*OneWriteFileSize) , (unsigned char *)file_buffer);
				// for(i=0;i<50;i++)
				// {
				// 	printf("file_buffer=%x\n",(unsigned int)file_buffer[i]);
				// }
				fwrite(file_buffer, sizeof(unsigned char), aligned_file_size[file_index] - transfer_round*OneWriteFileSize, fp);
				//for (index = 4; index < aligned_file_size[file_index] - transfer_round * OneWriteFileSize + 1; index = index + 4) {
				//	/*if ((index+1) % 4 == 0) fprintf(fp, "%02x\n", *(file_buffer + index));
				//	else fprintf(fp, "%02x", *(file_buffer + index));*/
				//	fprintf(fp, "%02X", *(file_buffer + index - 1));
				//	fprintf(fp, "%02X", *(file_buffer + index - 2));
				//	fprintf(fp, "%02X", *(file_buffer + index - 3));
				//	fprintf(fp, "%02X\n", *(file_buffer + index - 4));
				//}
				gdma_addroffset += (aligned_file_size[file_index] - transfer_round*OneWriteFileSize);
			}
			else {
				//USB_ReadWrite(dev_handle, USB_EP1_IN, file_buffer, gdma_base[gdma_index] + gdma_addroffset, OneWriteFileSize);
				c2h_transfer(gdma_base[gdma_index] + gdma_addroffset, (OneWriteFileSize), (unsigned char *)file_buffer);
				fwrite(file_buffer, sizeof(unsigned char), OneWriteFileSize, fp);
				//for (index = 4; index < OneWriteFileSize + 1; index = index + 4) {
				//	/*if ((index+1) % 4 == 0) fprintf(fp, "%02x\n", *(file_buffer + index));
				//	else fprintf(fp, "%02x", *(file_buffer + index));*/
				//	fprintf(fp, "%02X", *(file_buffer + index - 1));
				//	fprintf(fp, "%02X", *(file_buffer + index - 2));
				//	fprintf(fp, "%02X", *(file_buffer + index - 3));
				//	fprintf(fp, "%02X\n", *(file_buffer + index - 4));
				//}
				gdma_addroffset += OneWriteFileSize;
			}
		}
		fclose(fp);
		file_index++;
	}
	free(file_path);
	free(file_buffer);
	return;
}

//load mem with headers in upload;
void Files_LoadMem_Upload(unsigned int file_index, unsigned int cell_start_addr,
						  unsigned int aligned_file_size, unsigned char gdma_index, unsigned int gdma_addroffset, unsigned int chip_num,unsigned int hw_type) {
	unsigned int gdma_base[4] = { GDMA0_BASE_ADDR, GDMA1_BASE_ADDR, GDMA2_BASE_ADDR, GDMA3_BASE_ADDR };
	unsigned int *header_buffer;
	unsigned int chip_pos;
	unsigned int x_src = 0, y_src = -1;

//load header data;
	header_buffer = (unsigned int *)malloc(5 * sizeof(unsigned int));
		switch (chip_num) {
	case 9:
		chip_pos = (chip_row_table9[gdma_index][file_index]) | (chip_column_table9[gdma_index][file_index] << 14);
		break;

	case 18:
		chip_pos = (chip_row_table18[gdma_index][file_index]) | (chip_column_table18[gdma_index][file_index] << 14);
		break;
	case 32:
		chip_pos = (chip_row_table32[gdma_index][file_index]) | (chip_column_table32[gdma_index][file_index] << 14);
		break;

	case 36:
		chip_pos = (chip_row_table36[gdma_index][file_index]) | (chip_column_table36[gdma_index][file_index] << 14);
		break;

	case 72:
		chip_pos = (chip_row_table72[gdma_index][file_index]) | (chip_column_table72[gdma_index][file_index] << 14);
		break;

	default:
		chip_pos = (chip_row_table36[gdma_index][file_index]) | (chip_column_table36[gdma_index][file_index] << 14);
		break;
	}

	*(unsigned int *)(header_buffer) = (x_src & 0x3FFF) | ((y_src & 0x3FFF) << 14) | (chip_pos << 28);
	*(unsigned int *)(header_buffer +1) = (read << 29) | (request << 28) | (chip_pos >> 4);
	*(unsigned int *)(header_buffer +2) = aligned_file_size >> 3;
	*(unsigned int *)(header_buffer +3) = cell_start_addr;

	//USB_ReadWrite(dev_handle, USB_EP1_OUT, (unsigned char *)header_buffer, gdma_base[gdma_index] + gdma_addroffset, 20);
	h2c_transfer(gdma_base[gdma_index] + gdma_addroffset, 4*4, (unsigned char *)header_buffer);
	//cout << "Load read cmd header into DDR" << endl;
	free(header_buffer);
	return;
}

//all chip upload certain data;
//all chip have the same start_address and byte_length (it can vary in future versions);
//byte_length can not exceed 512MB;
//byte_length only include data part;  start from 1;
void Files_ParallelUpload_ALL(char *path_prefix, unsigned int cell_start_addr, unsigned int byte_length, 
								unsigned char parallel_num, unsigned int chip_num, unsigned int chip_sel, bool extern_spike,unsigned int hw_type,unsigned int t) {
	unsigned int gdma_base[4] = { GDMA0_BASE_ADDR, GDMA1_BASE_ADDR, GDMA2_BASE_ADDR, GDMA3_BASE_ADDR };
	unsigned char gdma_index = 0;
	unsigned int file_index = 0;
	unsigned int file_index_start = chip_sel;
	unsigned char file_overflow_flag = 0, file_unsupport_flag = 0;
	unsigned int gdma_addroffset[4] = { 0, 0, 0, 0 };
	unsigned int usb_cmd[4] = {0xcccccccc, 0xcccccccc, 0xcccccccc, 0xcccccccc};
	const unsigned int change_num = chip_num / parallel_num;
	unsigned int aligned_file_size[4][240];  //start from 1; max chip: 4*240 = 960 
	unsigned int block_num = 0; //the block number in zcu102 mem;
	unsigned int val=0;
	unsigned int x = 0;
	//printf("Files_ParallelUpload_ALL\r\n");
	// 
	//every gdma has 64 file
	for (file_index = chip_sel; file_index < change_num; ) {

		//printf("\r\nfile_index:  %d, byte_length:  %d\r\n", file_index, byte_length%4);
		//printf("usb_cmd[0]: %d  usb_cmd[1]: %d  usb_cmd[2]: %d  usb_cmd[3]: %d  \r\n", usb_cmd[0], usb_cmd[1], usb_cmd[2], usb_cmd[3]);
		//printf("usb_cmd[0]: %d  usb_cmd[1]: %d  usb_cmd[2]: %d  usb_cmd[3]: %d  \r\n", &usb_cmd[0], &usb_cmd[1], &usb_cmd[2], &usb_cmd[3]);

		//preprocess;
		for (gdma_index = 0; gdma_index < parallel_num; gdma_index++) { //read 4 gdma file size;
			//32bit address alignment tunning;
			if (byte_length % 4 != 0) {
				aligned_file_size[gdma_index][file_index] = ((byte_length >> 2) + 1) << 2;
			}
			else {
				aligned_file_size[gdma_index][file_index] = byte_length;
			}
				
			//judgement of file size fitness;
			if ((aligned_file_size[gdma_index][file_index] > GDMA_ADDR_LIMIT) || (aligned_file_size[gdma_index][file_index] < 20)) {
				#ifdef PRINT_INFO
				cout << "Files_ParallelUpload_ALL: unsupported byte_length" << endl;
				#endif
				file_unsupport_flag = 1;
			}
			else if (aligned_file_size[gdma_index][file_index] + gdma_addroffset[gdma_index] > GDMA_ADDR_LIMIT) {
				#ifdef PRINT_INFO
				cout << "Files_ParallelUpload_All: total size overflow, prepare to recv" << endl;
				#endif
				file_overflow_flag = 1;
			}
		}

		// //dont need to send instruction to read ddr
		// if (!file_unsupport_flag && !file_overflow_flag && !extern_spike) { //only under this condition data will be write to 4 gdma ddr;
		// 	for (gdma_index = 0; gdma_index < parallel_num; gdma_index++) {
		// 		// Files_LoadMem_Upload(file_index, cell_start_addr, aligned_file_size[gdma_index][file_index],
		// 		// 					gdma_index, gdma_addroffset[gdma_index], chip_num, hw_type); //load mem with header;
		// 		// 		printf("cell_start_addr=%d\n",cell_start_addr);																			//Õâ²¿·ÖÒªÅäºÏFPGA×öÏàÓ¦µÄÐÞ¸Ä
		// 		#ifdef SERDES_ON
		// 			cout << "trigger gdma to upload" << endl;
		// 						if (extern_spike)
		// 							cout << "extern_spike need to code" << endl;
		// 						else
		// 						{							
		// 							Gdma_RegConfig(gdma_index, gdma_base[gdma_index] + gdma_addroffset[gdma_index], 0, (4 - 1) << 2, 
		// 							gdma_base[gdma_index] + gdma_addroffset[gdma_index], 0, aligned_file_size[gdma_index][file_index] - 4,
		// 							RD_WR_FLAG);
		// 					/*		Gdma_RegConfig(gdma_index,
		// 								gdma_base[gdma_index] + gdma_addroffset[gdma_index], 0, (4 - 1) << 2,
		// 								gdma_base[gdma_index] + gdma_addroffset[gdma_index], 0, 0
		// 								);*/
		// 							//read_interrupt(0);
		// 						}

		// 						//stuck
 		// 						// while (val != gtp_state)	
		// 						// 	{
		// 						// 		val=user_read(GPIO_IREG);
								
		// 						// 	}
		// 							val = 0;

								
		// 		#endif  
		// 		gdma_addroffset[gdma_index] += aligned_file_size[gdma_index][file_index];
		// 		// gdma_addroffset[gdma_index] = 0;
		// 	}
		 	block_num++;
		// }

		//postprocess;
		if (file_unsupport_flag == 1) {  //exit;
			return;
		}
		else if ((file_overflow_flag == 1) || (file_index == change_num-1)) {   //the gdma mem space is full, or it is the last file, prepare to recv;
			usb_cmd[0] = block_num;
   			#ifdef PRINT_INFO
			cout << "Files_ReadMem_Upload: " << endl;
			#endif
			for (gdma_index = 0; gdma_index < parallel_num; gdma_index++) {
				Files_ReadMem_Upload(path_prefix, file_index_start, block_num,
									 aligned_file_size[gdma_index], gdma_index, chip_num,t);
				//printf("gdma_index2222: %d\r\n", gdma_index);
			}
			#ifdef PRINT_INFO
			cout << "Files_ParallelUpload_All: recv complete" << endl;
			#endif
			//param adjust;
			for (gdma_index = 0; gdma_index < parallel_num; gdma_index++)
				gdma_addroffset[gdma_index] = 0;
			file_index_start = file_index;
			file_overflow_flag = 0;
			block_num = 0;
			if ((file_index == change_num-1) && (file_overflow_flag != 1)) //the last file but not overflow;
				file_index++;
		}
		else
			file_index++;
	}
	return;
}


/* 
//download files to one multicast chip;
//the 4 gdma should send data in parallel;
//single file data size cannot exceed 512MB-20B since there is no slicing in gdma mem space;
//file transfer buffer array will set to 8MB;
void Files_ParallelDownload_One(char *path_prefix, unsigned int cell_start_addr, unsigned int chip_num) {
	unsigned int file_index = 0;
	unsigned int aligned_file_size = 0;
	unsigned char gdma_index = 0;
	unsigned char file_overflow_flag = 0, file_unsupport_flag = 0;
	unsigned int i = 0;
	FILE *fp = NULL;
	unsigned int prefix_len = 0, postfix_len = 0;
	long file_size = 0;
	unsigned int gdma_addroffset[PARALLEL] = { 0};
	unsigned int send_byte_length[PARALLEL] = { 0};  //start from 0;
	const unsigned int change_num = 1;

	//printf("Files_ParallelDownload_All\n");
	char *file_path = NULL;
	if (dev_handle == NULL) {
		//printf("Files_ParallelDownload_All: device handle empty\n");
		cout << "Files_ParallelDownload_All: device handle empty" << endl;
		return;
	}
//copy path prefix;
	prefix_len = strlen((const char *)path_prefix);
	file_path = (char *)malloc((prefix_len + postfix_len + 100)*sizeof(char));
	for (i = 0; i < prefix_len; i++)
		file_path[i] = path_prefix[i];
//every gdma has 64 files to send;
	for (file_index = 0; file_index < change_num; ) {

		//preprocess;
		for (gdma_index = 0; gdma_index < PARALLEL; gdma_index++) { //open PARALLEL files and check if all the PARALLEL files can fit into gdma mem space;
			fp = NULL;
			switch (chip_num) {
				case 9:
					postfix_len = strlen(chip_num_table9[gdma_index][file_index]);
					for (i = 0; i < postfix_len + 1; i++)  //plus 1 include '\0';
						file_path[i + prefix_len] = chip_num_table9[gdma_index][file_index][i];
					break;
				case 18:
                                        postfix_len = strlen(chip_num_table18[gdma_index][file_index]);
                                        for (i = 0; i < postfix_len + 1; i++)  //plus 1 include '\0';
                                                file_path[i + prefix_len] = chip_num_table18[gdma_index][file_index][i];
                                        break;
				case 36:
					postfix_len = strlen(chip_num_table36[gdma_index][file_index]);
					for (i = 0; i < postfix_len + 1; i++)  //plus 1 include '\0';
						file_path[i + prefix_len] = chip_num_table36[gdma_index][file_index][i];
					break;
					
				case 72:
					postfix_len = strlen(chip_num_table72[gdma_index][file_index]);
					for (i = 0; i < postfix_len + 1; i++)  //plus 1 include '\0';
						file_path[i + prefix_len] = chip_num_table72[gdma_index][file_index][i];
					break;					
				default:
					postfix_len = strlen(chip_num_table36[gdma_index][file_index]);
					for (i = 0; i < postfix_len + 1; i++)  //plus 1 include '\0';
						file_path[i + prefix_len] = chip_num_table36[gdma_index][file_index][i];
					break;
			}	
			//printf("open file: %s\n", file_path);
#ifdef DOWNLOAD_DEBUG_PRINT
			if (file_index == 0 && gdma_index ==0) {
				cout << "open file: " << file_path << endl; 
			}
#endif
#ifdef OS_WIN
			//fopen_s(&fp, file_path, "rb");
			fp = fopen(file_path, "rb");
#else
			fp = fopen(file_path, "rb");
#endif
			if (fp == NULL) {
				//printf("Files_ParallelDownload_All: fopen_s failed, no such file\r\n");
				cout << "Files_ParallelDownload_All: fopen_s failed, no such file" << endl;
				file_unsupport_flag = 1;
				break;
			}
			fseek(fp, 0, SEEK_END);
			file_size = ftell(fp);
			fseek(fp, 0, SEEK_SET);
			//
			if (file_size > GDMA_ADDR_LIMIT - 20) { //single file exceed upper limit;
				//printf("Files_ParallelDownload_All: single file size exceed upper limit %ld\n", file_size);
				cout << "Files_ParallelDownload_All: single file size exceed upper limit " << file_size << endl;
				file_unsupport_flag = 1;
				break;
			}
			else if (file_size + gdma_addroffset[gdma_index] + 20 > GDMA_ADDR_LIMIT) { //file size overflow;
				//printf("Files_ParallelDownload_All: file total size overflow, prepare to send out\n");
				cout << "Files_ParallelDownload_All: file total size overflow, prepare to send out" << endl;
				file_overflow_flag = 1;
			}
			else {  //load file to zcu102 ddr;
				aligned_file_size = Files_LoadMem_Download(fp, gdma_index, file_index, file_size,
													       gdma_addroffset[gdma_index], cell_start_addr, chip_num, 1); //load mem with current file;
				gdma_addroffset[gdma_index] += (aligned_file_size + 20); //file size and additional 20byte head;
			}
			fclose(fp); //close current file;
		}
		//postprocess;
		if (file_unsupport_flag == 1) {  //close exit;
			return;
		}
		else if ((file_overflow_flag == 1) || (file_index == change_num-1)) { //the rest mem space cannot hold the next file, need to transfer first;
			for (gdma_index = 0; gdma_index < PARALLEL; gdma_index++) {	//32bit address alignment tunning;
				if (gdma_addroffset[gdma_index] % 4 == 0)
					send_byte_length[gdma_index] = gdma_addroffset[gdma_index] - 4; //gdma discard lower 2 bits and add 1 to upper bit;
				else {
					//printf("Files_ParallelDownload_All: gdma_addroffset not aligned\n");
					cout << "Files_ParallelDownload_All: gdma_addroffset not aligned" << endl;
					return;
				}
			}
#ifdef SERDES_ON
			//printf("Files_ParallelDownload_All: Trigger gdma send_byte_length[0]=%d,send_byte_length[1]=%d,send_byte_length[2]=%d,send_byte_length[3]=%d\n", 
			//		send_byte_length[0], send_byte_length[1], send_byte_length[2], send_byte_length[3]);
			USB_SendCmd(dev_handle, PC_DOWNLOAD_ONE, send_byte_length);  //trigger gdma to send data;
			USB_RecvCSW(dev_handle);  //wait for transmit done;
			//printf("Files_ParallelDownload_All: send out complete\n");
			cout << "Files_ParallelDownload_All: send out complete" << endl;
#else
			for (gdma_index = 0; gdma_index < PARALLEL; gdma_index++) {
				printf("Files_ParallelDownload_All: send_byte_length[%d] = %d\n", gdma_index, send_byte_length[gdma_index]);
				Gdma_DumpFile(dev_handle, path_prefix, gdma_index, 0, gdma_addroffset[gdma_index]);
			}
#endif
			for (gdma_index = 0; gdma_index < PARALLEL; gdma_index++)
				gdma_addroffset[gdma_index] = 0;
			file_overflow_flag = 0;
			if ((file_index == change_num-1) && (file_overflow_flag != 1))
				file_index++;
		}
		else
			file_index++;
	}
	//free(file_path);
	return;
}



//One chip upload certain data;
//One chip have the same start_address and byte_length (it can vary in future versions);
//byte_length can not exceed 512MB;
//byte_length only include data part;  start from 1;
void Files_ParallelUpload_One(libusb_device_handle *dev_handle, char *path_prefix, 
							  unsigned int cell_start_addr, unsigned int byte_length, unsigned int chip_num) {
	unsigned char gdma_index;
	unsigned int file_index;
	unsigned int file_index_start = 0;
	unsigned char file_overflow_flag = 0, file_unsupport_flag = 0;
	unsigned int gdma_addroffset[PARALLEL] = { 0};
	unsigned int usb_cmd[4] = {0xcccccccc, 0xcccccccc, 0xcccccccc, 0xcccccccc};
	const unsigned int change_num = 1;
	unsigned int aligned_file_size[4][240];  //start from 1; max chip: 4*240 = 960 
	unsigned int block_num = 0; //the block number in zcu102 mem;
	//printf("Files_ParallelUpload_ALL\r\n");
	// 
	//every gdma has 64 file
	for (file_index = 0; file_index < change_num; ) {

		//printf("\r\nfile_index:  %d, byte_length:  %d\r\n", file_index, byte_length%4);
		//printf("usb_cmd[0]: %d  usb_cmd[1]: %d  usb_cmd[2]: %d  usb_cmd[3]: %d  \r\n", usb_cmd[0], usb_cmd[1], usb_cmd[2], usb_cmd[3]);
		//printf("usb_cmd[0]: %d  usb_cmd[1]: %d  usb_cmd[2]: %d  usb_cmd[3]: %d  \r\n", &usb_cmd[0], &usb_cmd[1], &usb_cmd[2], &usb_cmd[3]);

		//preprocess;
		for (gdma_index = 0; gdma_index < PARALLEL; gdma_index++) { //read 4 gdma file size;
			//32bit address alignment tunning;
			if (byte_length % 4 != 0) {
				aligned_file_size[gdma_index][file_index] = ((byte_length >> 2) + 1) << 2;
			}
			else {
				aligned_file_size[gdma_index][file_index] = byte_length;
			}
				
			//judgement of file size fitness;
			if ((aligned_file_size[gdma_index][file_index] > GDMA_ADDR_LIMIT) || (aligned_file_size[gdma_index][file_index] < 20)) {
				cout << "Files_ParallelUpload_ALL: unsupported byte_length" << endl;
				file_unsupport_flag = 1;
			}
			else if (aligned_file_size[gdma_index][file_index] + gdma_addroffset[gdma_index] > GDMA_ADDR_LIMIT) {
				cout << "Files_ParallelUpload_All: total size overflow, prepare to recv" << endl;
				file_overflow_flag = 1;
			}
		}

		if (!file_unsupport_flag && !file_overflow_flag) { //only under this condition data will be write to 4 gdma ddr;
			for (gdma_index = 0; gdma_index < PARALLEL; gdma_index++) {
				Files_LoadMem_Upload(dev_handle, file_index, cell_start_addr, aligned_file_size[gdma_index][file_index],
									gdma_index, gdma_addroffset[gdma_index], chip_num); //load mem with header;
				gdma_addroffset[gdma_index] += aligned_file_size[gdma_index][file_index];
			}
			block_num++;
		}
		//postprocess;
		if (file_unsupport_flag == 1) {  //exit;
			return;
		}
		else if ((file_overflow_flag == 1) || (file_index == change_num-1)) {   //the gdma mem space is full, or it is the last file, prepare to recv;
			usb_cmd[0] = block_num;
#ifdef SERDES_ON
			cout << "trigger gdma to upload" << endl;
			USB_SendCmd(dev_handle, PC_UPLOAD_ONE, usb_cmd);  //trigger gdma to upload;
			cout << "wait for gdma" << endl;
			USB_RecvCSW(dev_handle); //wait for gdma;
#endif
			cout << "Files_ReadMem_Upload: " << endl;
			for (gdma_index = 0; gdma_index < PARALLEL; gdma_index++) {
				Files_ReadMem_Upload(dev_handle, path_prefix, file_index_start, block_num,
									 aligned_file_size[gdma_index], gdma_index, chip_num,0);
				//printf("gdma_index2222: %d\r\n", gdma_index);
			}
			cout << "Files_ParallelUpload_All: recv complete" << endl;
			//param adjust;
			for (gdma_index = 0; gdma_index < PARALLEL; gdma_index++)
				gdma_addroffset[gdma_index] = 0;
			file_index_start = file_index;
			file_overflow_flag = 0;
			block_num = 0;
			if ((file_index == change_num-1) && (file_overflow_flag != 1)) //the last file but not overflow;
				file_index++;
		}
		else
			file_index++;
	}
	return;
}
 */


