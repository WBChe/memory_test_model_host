#!/bin/bash
#extern_sp  test_mode  hw_type sample_num step_count neu_num
sh ../sender_rst.sh
./zcu102_sender 1 1 0 ~/work/data/ei_data_1000_asic /upload/ei_1000_asic 0 0 1 0 0 1 100 0 
