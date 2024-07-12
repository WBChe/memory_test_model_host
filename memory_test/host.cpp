 #include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
//#include <AtlBase.h>
#include "pcie_fun.h"
#include "zcu102_sender_global.h"
#include "gdma.h"
#include <unistd.h>
#pragma comment(lib, "setupapi.lib")
#pragma warning(disable:4996)
typedef unsigned char BYTE;
typedef unsigned long DWORD;
BYTE   start_en;
DWORD  user_irq_ack[1],readbuf[1];
unsigned int gtp_state;
//#define OS_WIN
#pragma pack(1)

struct run_parameter {
	unsigned int parallel_num;
	unsigned int chip_num;
	unsigned int chip_sel;


	char downloadPath_DOR[100];
	char uploadPath_DOR[100];

	unsigned int upload_sp_size;
	unsigned int upload_weight_size;
	bool extern_spike;
	unsigned char  mode;
	unsigned int hw_type;
	
	unsigned int CELL_REMOTE_BASE		;
	unsigned int CELL_PROPERTY_BASE	    ;
	unsigned int CELL_ROUTE_INFO_BASE	;
										
	unsigned int CELL_TILE_ID_BASE		;
	unsigned int CELL_NDMA_STADDR_BASE	;
	unsigned int CELL_NPU_CTRL_BASE	    ;
	unsigned int CELL_SP_SIZE_BASE		;
										
	unsigned int CELL_SMT_BRAM_BASE	    ;
	unsigned int CELL_SP_BRAM_BASE		;
	unsigned int CELL_SP_CNT_BRAM_BASE	;
	unsigned int CELL_WEIGHT_BRAM_BASE	;
	unsigned int READ_WEIGHT_ADDR		;
	
	unsigned int sample_num;
	unsigned int step_count;
	unsigned int neu_num;
};
#pragma pack()


void Data_Test(run_parameter parameter) {
	
	unsigned int index = 0;
        string download_DOR(parameter.downloadPath_DOR);
		string mscan_DOR                       = download_DOR + "/mscan/mscan";

        string interrupt_DOR                      = download_DOR + "/interrupt/interrupt";
        string property_DOR                     = download_DOR + "/property/property";
        string sram_DOR                       = download_DOR + "/sram/sram";
        string tile_id_DOR                      = download_DOR + "/tile_id/tile_id";
        string ndma_staddr_DOR             	= download_DOR + "/ndma_staddr/ndma_staddr";
        string smt_DOR                          = download_DOR + "/smt/smt";
        string route_info_DOR              	= download_DOR + "/route_info/route_info";
        string weight_DOR                       = download_DOR + "/weight/weight";	  
		string test_DOR                       = download_DOR + "/test/test";	

		string upload_DOR(parameter.uploadPath_DOR);
		string mscan_check_DOR 	        = upload_DOR + "/mscan_check/mscan_check";

        string weight_check_prefix_DOR 	        = upload_DOR + "/step" + to_string(index) + "/weight_check/weight_check";
        string smt_check_prefix_DOR 	        = upload_DOR + "/step" + to_string(index) + "/smt_check/smt_check";
        string sram_check_DOR 	        		= upload_DOR + "/step" + to_string(index) + "/sram_check/sram_check";
		
		

		unsigned value,value1,value2,value3;
		// test mscan 
		// Files_ParallelDownload_All((char*)MSCAN_DOR.data(),   NPU0_CSR_RUN,
		// 															parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 1, packet_spike);	

		// test
		// h2c_transfer file data to ddr -> read data from ddr -> write data to ddr
		// regconfig open read and write channel
		Files_ParallelDownload_All((char*)mscan_DOR.data(),   NPU0_CSR_RUN,
																	parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 1, packet_spike);
		// c2h_transfer ddr data to the file 
		Files_ParallelUpload_ALL( (char*)mscan_check_DOR.data(), NPU0_NCU,   	2*4*32*1024,
                                                                parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type,0);															

		/*********************************************************************test***********************************************************/

		cout << "compare ncu mem" << endl;
	
		cout << "sim done" << endl;

		while(1);

 
	return;
}

void Data_Init(run_parameter parameter) {
	 	unsigned int i;
	string download_DOR(parameter.downloadPath_DOR);
	string remote4_DOR		        = download_DOR + "/remote4/remote4";
	string property_DOR		        = download_DOR + "/property/property";
	string npu_on_DOR		        = download_DOR + "/npu_ctrl/npu_on";
	string tile_id_DOR		        = download_DOR + "/tile_id/tile_id";
	string ndma_staddr_DOR		    = download_DOR + "/ndma_staddr/ndma_staddr";
	string smt_DOR		        	= download_DOR + "/smt/smt";
	string route_info_DOR		    = download_DOR + "/route_info/route_info";
	string weight_DOR		        = download_DOR + "/weight/weight";
	//init reg
	if (parameter.hw_type==0) {
		//set remote reg
		cout << "Download remote reg, path: " << (char*)remote4_DOR.data() << endl;
		Files_ParallelDownload_All((char*)remote4_DOR.data(),	parameter.CELL_REMOTE_BASE, 
									parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type);			

		//set npu_ctrl reg
		cout << "Download npu_ctrl reg, path: " << (char*)npu_on_DOR.data() << endl;
		Files_ParallelDownload_All( (char*)npu_on_DOR.data(), parameter.CELL_NPU_CTRL_BASE, 
									parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type);		
		//set tile_id reg
		cout << "Download tile_id reg, path: " << (char*)tile_id_DOR.data() << endl;
		Files_ParallelDownload_All((char*)tile_id_DOR.data(), parameter.CELL_TILE_ID_BASE, 
									parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type);		    
		//set ndma_staddr reg
		cout << "Download ndma_staddr reg, path: " << (char*)ndma_staddr_DOR.data() << endl;
		Files_ParallelDownload_All( (char*)ndma_staddr_DOR.data(), parameter.CELL_NDMA_STADDR_BASE, 
									parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type);	    
		//router bram
		cout << "Download router bram, path: " << (char*)route_info_DOR.data() << endl;
		Files_ParallelDownload_All( (char*)route_info_DOR.data(), parameter.CELL_ROUTE_INFO_BASE, 
									parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type);
		
		//smt bram
		cout << "Download smt bram, path: " << (char*)smt_DOR.data() << endl;
		Files_ParallelDownload_All( (char*)smt_DOR.data(), parameter.CELL_SMT_BRAM_BASE, 
									parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type);
		
		//weight bram
		cout << "Download weight bram, path: " << (char*)weight_DOR.data() << endl;
		Files_ParallelDownload_All( (char*)weight_DOR.data(), parameter.CELL_WEIGHT_BRAM_BASE, 
									parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type);
	}
	else if (parameter.hw_type==1) {
		//set remote reg
		cout << "Download remote reg, path: " << (char*)remote4_DOR.data() << endl;
		Files_ParallelDownload_All( (char*)remote4_DOR.data(),	parameter.CELL_REMOTE_BASE, 
									parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type);			

		//set property reg
		cout << "Download property reg, path: " << (char*)property_DOR.data() << endl;
		Files_ParallelDownload_All( (char*)property_DOR.data(), parameter.CELL_PROPERTY_BASE, 
									parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type);		
									
		//router bram
		cout << "Download router bram, path: " << (char*)route_info_DOR.data() << endl;
		Files_ParallelDownload_All( (char*)route_info_DOR.data(), parameter.CELL_ROUTE_INFO_BASE, 
									parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type);
		
		//smt bram
		cout << "Download smt bram, path: " << (char*)smt_DOR.data() << endl;
		Files_ParallelDownload_All( (char*)smt_DOR.data(), parameter.CELL_SMT_BRAM_BASE, 
									parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type);
		
		//weight bram
		cout << "Download weight bram, path: " << (char*)weight_DOR.data() << endl;
		Files_ParallelDownload_All( (char*)weight_DOR.data(), parameter.CELL_WEIGHT_BRAM_BASE, 
									parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type);		
	}
		return;
	
}
void Data_Upload(unsigned int index, run_parameter parameter) {

	string upload_DOR(parameter.uploadPath_DOR);	
	string sp_check_prefix_DOR		= upload_DOR + "/step" + to_string(index) + "/spike_check/spike_check";
	string weight_check_prefix_DOR	= upload_DOR + "/step" + to_string(index) + "/weight_check/weight_check";
	
	unsigned int i;
	Files_ParallelUpload_ALL( (char*)sp_check_prefix_DOR.data(), parameter.CELL_SP_BRAM_BASE,		parameter.neu_num * 4, 
								parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type,0);
	//Files_ParallelUpload_ALL( (char*)weight_check_prefix_DOR.data(), parameter.CELL_WEIGHT_BRAM_BASE ,	parameter.neu_num * 32, 
	Files_ParallelUpload_ALL( (char*)weight_check_prefix_DOR.data(), parameter.CELL_WEIGHT_BRAM_BASE + 0x10000 * parameter.chip_num,	parameter.neu_num * 32, 
								parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type,0);
	return;
}


void Sim_Process( run_parameter parameter, int rev_num,unsigned int stop_pkg) {

	unsigned int step_limit = 1;
	clock_t start, end;
	double time = 0;
	double time_cnt = 0;
	unsigned int func_out_val=0;
	string download_DOR(parameter.downloadPath_DOR);	
	string npu_start_DOR		    = download_DOR + "/npu_ctrl/npu_after";
	string npu_stop_DOR		        = download_DOR + "/npu_ctrl/npu_all0";
	string npu_spike_DOR		        = download_DOR + "/npu_ctrl/npu_spike";
	string spike_in_DOR = download_DOR + "/spike_bin/sample" + to_string(parameter.sample_num) + "/spike";
		
	cout << '\n' << "Sim Step Loop : " << parameter.step_count << " ......" << endl;
	for (int step_i = 1; step_i < parameter.step_count + 1; step_i++) {
	#ifdef PRINT_INFO	
		cout << "\nstep--" << step_i << endl;
	#endif
		if (parameter.extern_spike) {
			if (step_i == 1) {
				spike_in_DOR = spike_in_DOR + to_string(step_i);
				Files_ParallelDownload_All((char*)npu_spike_DOR.data(), parameter.CELL_NPU_CTRL_BASE,
                                                        parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type); 
				Files_ParallelDownload_All((char*)spike_in_DOR.data(), parameter.CELL_NPU_CTRL_BASE,
                                                        1, 1, 0, 1, parameter.hw_type); 
			}
		}
//cout << '\n' << "rev_num :" << rev_num << endl;
	func_out_val=user_read(GPIO_OREG);
	//printf("func_out_val=%d\n",func_out_val);
	//printf("stop_pkg=%d\n",stop_pkg);
	user_write(GPIO_OREG,stop_pkg|func_out_val);
	//func_out_val=user_read(GPIO_OREG);
	//printf("func_out_val=%d\n",func_out_val);

// #ifdef OS_WIN
//                Sleep(500);
// #else
//                usleep(1000000);
// #endif
		Files_ParallelDownload_All( (char*)npu_start_DOR.data(), parameter.CELL_NPU_CTRL_BASE, 
							parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type);		//set sim start
		start = clock();						
	//	auto start = std::chrono::steady_clock::now();	
		Gdma_StepSim(step_i, parameter.parallel_num, rev_num);
	//	auto end = std::chrono::steady_clock::now();
	//	auto time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	//	time_cnt += time.count();
		
		end = clock();
		time_cnt += (double)(end - start) / CLOCKS_PER_SEC;
		Files_ParallelDownload_All((char*)npu_stop_DOR.data(), parameter.CELL_NPU_CTRL_BASE,
							parameter.parallel_num, parameter.chip_num, parameter.chip_sel, 0, parameter.hw_type);		//set sim stop

		user_write(GPIO_OREG,~stop_pkg&func_out_val);
		
// #ifdef OS_WIN
// 		Sleep(100);
// #else
// 		usleep(1000);
// #endif
		Data_Upload(step_i, parameter);

// #ifdef OS_WIN
// 		Sleep(100);
// #else
// 		usleep(1000);
// #endif


	}
	cout << "total time step: " << parameter.step_count << ", averaged step cost: "; 
	cout << setprecision(6) << double(time_cnt / parameter.step_count * 1000) <<  "ms, total step cost: ";
	cout << setprecision(6) << time_cnt << "s" << endl;
	return;
}

//void mem_rw_test () {
//	// 获取Python程序中一个列表对象的内存地址
//   	 PyObject* pyList = PyList_New(3);
//   	 PyList_SetItem(pyList, 0, PyLong_FromLong(1));
//   	 PyList_SetItem(pyList, 1, PyLong_FromLong(2));
//   	 PyList_SetItem(pyList, 2, PyLong_FromLong(3));
//   	 void* addr = (void*)pyList;
//
//   	 // 使用libffi库访问Python程序中的内存地址，并获取其中的数据
//   	 ffi_cif cif;
//   	 ffi_type* argTypes[] = {&ffi_type_pointer};
//   	 void* argValues[] = {&addr};
//   	 long value;
//   	 ffi_type* returnType = &ffi_type_slong;
//   	 ffi_prep_cif(&cif, FFI_DEFAULT_ABI, 1, returnType, argTypes);
//   	 void* funcAddr = dlopen("libpython3.7m.so", RTLD_LAZY);
//   	 ffi_call(&cif, FFI_FN(dlsym(funcAddr, "PyLong_AsLong")), &value, argValues);
//   	 std::cout << "Value at address " << addr << " is " << value << std::endl;
//   	 dlclose(funcAddr);
//
//   	 // 释放Python对象
//   	 Py_DECREF(pyList);
//
//   	 return;
//}




int main(int argc, char* argv[])
{

	//unsigned int buf1[1024];
	unsigned int buf2[1024] = {4,3,5,7,8,9};
	unsigned int i = 0;
	unsigned int val=0;
	unsigned int error_cnt = 0;

   	unsigned int  i2, t, stop_pkg = 1;
	struct run_parameter parameter;
	unsigned int step_limit = 1, step_count = 250;

	cout << "Input arguments count: " << argc << endl;

	//load_parameter(parameter, argv);
	if (!(argc == 14)) {
		cout << "Input arguments error!" << endl;
		return -1;
	}
	else {
		parameter.parallel_num = atoi(argv[1]);
		parameter.chip_num = atoi(argv[2]);
		parameter.chip_sel = atoi(argv[3]);
		strcpy( parameter.downloadPath_DOR      	 , argv[4] );  
		strcpy( parameter.uploadPath_DOR            	 , argv[5] ); 
		parameter.upload_sp_size = atoi(argv[6]);
		parameter.upload_weight_size = atoi(argv[7]);
		parameter.extern_spike = atoi(argv[8]);
		parameter.mode = atoi(argv[9]);
		parameter.hw_type = atoi(argv[10]);
		parameter.sample_num = atoi(argv[11]);
		parameter.step_count = atoi(argv[12]);
		parameter.neu_num = atoi(argv[13]);
	}



	if (parameter.hw_type==0) {  //asic 1k
		parameter.CELL_REMOTE_BASE		= 0x00000000  ;
		parameter.CELL_PROPERTY_BASE		= 0xC0000000  ;
		parameter.CELL_ROUTE_INFO_BASE	= 0x00008000  ;
								  ;
		parameter.CELL_TILE_ID_BASE		= 0x04040000  ;
		parameter.CELL_NDMA_STADDR_BASE	= 0x04040004  ;
		parameter.CELL_NPU_CTRL_BASE		= 0x04040008  ;
		parameter.CELL_SP_SIZE_BASE		= 0x04040034  ;
								  ;
		parameter.CELL_SMT_BRAM_BASE		= 0x04000000  ;
		parameter.CELL_SP_BRAM_BASE		= 0x05000000  ;
		parameter.CELL_SP_CNT_BRAM_BASE	= 0x05010000  ;
		parameter.CELL_WEIGHT_BRAM_BASE	= 0x06000000  ;

	}
	else if (parameter.hw_type==1) {
		parameter.CELL_REMOTE_BASE		= 0xC0000000  ;
		parameter.CELL_PROPERTY_BASE		= 0xC0011000  ;
		parameter.CELL_ROUTE_INFO_BASE	= 0xC0008000  ;
		parameter.CELL_NPU_CTRL_BASE		= 0xC0011008  ;
		parameter.CELL_SMT_BRAM_BASE		= 0xC0010000  ;
		parameter.CELL_SP_BRAM_BASE		= 0xC0020000  ;
		parameter.CELL_SP_CNT_BRAM_BASE	= 0x05010000  ;
		parameter.CELL_WEIGHT_BRAM_BASE	= 0x00000000  ;
	}   
	pcie_init();


	for(i=0;i<parameter.parallel_num;i++){
		stop_pkg = stop_pkg <<1;
		//printf("stop_pkg=%x\n",stop_pkg);
	}
	stop_pkg =(stop_pkg-1)<<8;

	printf("Serdes_Init End, parallel_num = %d, chip_num = %d, mode = %d, stop_pkg = %x,hw_type = %d, neu_num = %d\r\n", parameter.parallel_num, parameter.chip_num, parameter.mode, stop_pkg,parameter.hw_type, parameter.neu_num);
	int16_t rev_num = parameter.chip_num / (parameter.parallel_num ) - 1;
	if (rev_num < 0) 
		rev_num = 0;
	printf("every gdma channel: %d\r\n", rev_num);
	printf("*************System Init Complete*************\r\n");

	switch (parameter.parallel_num)
	{
	case 1:
		gtp_state = 0x0003;
		break;
	case 2:
		gtp_state = 0x000f;
		break;
	case 3:
		gtp_state = 0x003f;
		break;
	case 4:
		gtp_state = 0x00ff;
		break;
	default:
		gtp_state = 0x0003;
		break;
	}
	printf("gtp_state= %d\n",gtp_state);
    //printf("parameter.parallel_num=%d \r\n",parameter.parallel_num);
	//CreateintThread();
	/*h_event1 = CreateThread(NULL, 0, thread_event1, NULL, 0, NULL);
	h_event2 = CreateThread(NULL, 0, thread_event2, NULL, 0, NULL);
	h_event3 = CreateThread(NULL, 0, thread_event3, NULL, 0, NULL);*/
	//Serdes_Init(parameter.parallel_num, parameter.chip_num);
	//gtp rst
    // i2 = 2;
 
    // user_write(GPIO_OREG,i2);
  


    // printf("ready into gtp_fifo_rst");
	gtp_fifo_rst();
	gtp_speed_set();
	usleep(10000);

	Data_Test(parameter);

	if (parameter.mode == 0) {
		RouterSetup(64);
		while (val != gtp_state) {
			val = user_read(GPIO_IREG);
			printf("val=%d\n",val);
		}
		Data_Init(parameter);	
		cout << "Data_Init: Complete\r\n" << endl;
	}	
	else if (parameter.mode == 1) {
		
	//	Data_Upload(0, parameter);
	//	usleep(100000);
		Sim_Process( parameter,rev_num,stop_pkg);
	}
	else {
		RouterSetup(64);
                while (val != gtp_state) {
                	val = user_read(GPIO_IREG);
               		printf("val=%d\n",val);
                }
		
             	cout << '\n' << "Data_Test: Complete" << endl;
	}

}

