#include "zcu102_sender_global.h"
#ifdef __cplusplus
 extern "C" {
 #endif
#include <assert.h>
#include <fcntl.h>
#include <getopt.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdarg.h>
#include <syslog.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
/* ltoh: little to host */
/* htol: little to host */
#if __BYTE_ORDER == __LITTLE_ENDIAN
#  define ltohl(x)       (x)
#  define ltohs(x)       (x)
#  define htoll(x)       (x)
#  define htols(x)       (x)
#elif __BYTE_ORDER == __BIG_ENDIAN
#  define ltohl(x)     __bswap_32(x)
#  define ltohs(x)     __bswap_16(x)
#  define htoll(x)     __bswap_32(x)
#  define htols(x)     __bswap_16(x)
#endif

#define MAP_SIZE (1024*1024UL)
#define MAP_MASK (MAP_SIZE - 1)
#define FPGA_DDR_START_ADDR 0x00000000
#define MAX_BYTES_PER_TRANSFER 0x800000

static void *user_base;
static int h_c2h0;
static int h_h2c0;
static int h_user;
//static int h_event0;
//static int h_event1;
//static int h_event2;
//static int h_event3;

//static unsigned int  user_irq_ack;
unsigned int user_read(unsigned int address)
{
    unsigned int read_result = *((unsigned int *)(user_base+address));
   
    read_result = ltohl(read_result);
    
    return read_result;
 
}

void *event0_process(void *)
{
	int val;
	int h_event0;
	u_int32_t value,value1,value2,value3;
    	h_event0 = open("/dev/xdma0_events_0", O_RDWR | O_SYNC);
    	if(h_event0 < 0) 
	{ 
		printf("open event0 error\n");
	}
	else
	{
	printf("open event0\n");
	while (1)
		{
			
			read(h_event0,&val,4);
			if (val == 1){
				printf("event_0 done!\n");
				value =user_read(0x15000);
				value1 =user_read(0x15000+4);
				value2 =user_read(0x15000+8);
				value3 =user_read(0x15000+12);

			}

			else
				printf("event_0 timeout!\n");
			
			usleep(1);
		}
	//close(h_event0);
	}
}

void *event1_process(void *)
{
	int val;
	int h_event1;
    	h_event1 = open("/dev/xdma0_events_1", O_RDWR | O_SYNC);
    	if(h_event1 < 0) 
	{ 
		printf("open event1 error\n");
	}
	else
	{
	printf("open event1\n");
	while (1)
		{
			
			read(h_event1,&val,4);
			if (val == 1)
				printf("event_1 done!\n");
			else
				printf("event_1 timeout!\n");
			
			usleep(1);
		}
	close(h_event1);
	}
}

void *event2_process(void *)
{
	int val;
	int h_event2;
    	h_event2 = open("/dev/xdma0_events_2", O_RDWR | O_SYNC);
    	if(h_event2 < 0) 
	{ 
		printf("open event2 error\n");
	}
	else
	{
	printf("open event2\n");
	while (1)
		{
			
			read(h_event2,&val,4);
			if (val == 1)
				printf("event_2 done!\n");
			else
				printf("event_2 timeout!\n");
			
			usleep(1);
	}
	close(h_event2);
	}
}

void *event3_process(void *)
{
	int val;
	int h_event3;
    	h_event3 = open("/dev/xdma0_events_3", O_RDWR | O_SYNC);
    	if(h_event3 < 0) 
	{ 
		printf("open event3 error\n");
	}
	else
	{
	printf("open event3\n");
	while (1)
		{
			
			read(h_event3,&val,4);
			if (val == 1)
				printf("event_3 done!\n");
			else
				printf("event_3 timeout!\n");
			
			usleep(1);
		}
	close(h_event3);
	}
}

static void *mmap_control(int device,long mapsize)
{
    void *vir_addr;
    vir_addr = mmap(0, mapsize, PROT_READ | PROT_WRITE, MAP_SHARED, device, 0);
    return vir_addr;
}

void write_device(int device,unsigned int address,unsigned int len,unsigned char *buffer)
{
    lseek(device,address,SEEK_SET);
    write(device,buffer,len);
}

void read_device(int device,unsigned int address,unsigned int len,unsigned char *buffer)
{
    lseek(device,address,SEEK_SET);
    read(device,buffer,len);
}

void c2h_transfer(unsigned int address,unsigned int size,unsigned char *buffer)
 {
    read_device(h_c2h0,address,size,buffer);
 }

void h2c_transfer(unsigned int address,unsigned int size,unsigned char *buffer)
{
    write_device(h_h2c0,address,size,buffer);
}

void user_write(unsigned int address,unsigned int val )
{
    unsigned int writeval = htoll(val);
   
   *((unsigned int *)(user_base+address)) = writeval;

}



int pcie_init()
{
    char* user_name = (char*)"/dev/xdma0_user";
    char* c2h0_name = (char*)"/dev/xdma0_c2h_0";
    char* h2c0_name = (char*)"/dev/xdma0_h2c_0";
    // printf("pcie_init\n"); 
    pthread_t t_event0; 
    pthread_t t_event1;
    pthread_t t_event2;
    pthread_t t_event3;
    h_c2h0 = open(c2h0_name,O_RDWR | O_NONBLOCK);
    if(h_c2h0 < 0) { printf("open c2h0 error\n"); return -1; };

    h_h2c0 = open(h2c0_name,O_RDWR);
    if(h_h2c0 < 0) { printf("open h2c0 error\n"); return -2; };

    h_user = open(user_name, O_RDWR | O_SYNC);
    if(h_user < 0) { printf("open user error\n"); return -3; };

    user_base = mmap_control(h_user,MAP_SIZE);
         printf("pcie_init successed\n"); 
    

    pthread_create(&t_event0, NULL, event0_process, NULL);
	pthread_create(&t_event1, NULL, event1_process, NULL);
	pthread_create(&t_event2, NULL, event2_process, NULL);
	pthread_create(&t_event3, NULL, event3_process, NULL);

	user_write(HOST_FLAG, 0x00000000);
	usleep(2);
	user_write(HOST_FLAG, 0x00000001);
	

	usleep(100);
	user_write(LAST_CTRL, 0x00000000);//LAST_CTRL init
	usleep(100);

    // pthread_join(t_event0,NULL);
	// pthread_join(t_event1,NULL);
	// pthread_join(t_event2,NULL);
	// pthread_join(t_event3,NULL);
}

void pcie_deinit()
{
    //user_irq_ack = 0x00000000;
    //write_device(h_user, 0x04, 4, (unsigned char *)&user_irq_ack);//clear irq
    close(h_user);
    close(h_c2h0);
    close(h_h2c0);
}

#ifdef __cplusplus
}
#endif
