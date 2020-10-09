############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2018 Xilinx, Inc. All Rights Reserved.
############################################################

set hls_dir [lindex $argv 2]
set scale [lindex $argv 3]
set part [lindex $argv 4]

open_project HLS_PROJ
set_top DoCompute
add_files ${hls_dir}/top.h
add_files ${hls_dir}/top.cpp
add_files -tb ${hls_dir}/tb.cpp -cflags "-Wno-unknown-pragmas"
open_solution ${scale}
set_part ${part} -tool vivado
create_clock -period 5 -name default
config_compile -no_signed_zeros=0 -unsafe_math_optimizations=0
config_export -format ip_catalog -rtl verilog -vivado_phys_opt place -vivado_report_level 0
config_sdx -optimization_level none -target none
config_bind -effort medium
config_schedule -effort medium -relax_ii_for_timing=0
set_clock_uncertainty 12.5%
#source "./read_data/small/directives.tcl"
csim_design
csynth_design
#cosim_design
export_design -rtl verilog -format ip_catalog

exit
