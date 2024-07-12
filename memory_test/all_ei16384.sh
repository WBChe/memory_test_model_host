#!/bin/bash
#extern_sp  mode  hw_type sample_num step_count neu_chip
sh ../sender_rst.sh
./zcu102_sender 1 1 0 ~/work/data/ei_data_16384_asic /upload/ei_16384_asic 0 0 0 0 0 0 0 0  
./zcu102_sender 1 1 0 ~/work/data/ei_data_16384_asic /upload/ei_16384_asic 0 0 1 1 0 1 100 0 
