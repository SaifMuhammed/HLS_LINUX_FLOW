connect
ta 2
rst
fpga -f Images/linux/design_1_wrapper.bit
source ../hls/components/plnx_workspace/device-tree-generation/ps7_init.tcl
ps7_post_config
ps7_init
dow Images/u-boot.elf
dow -data Images/image.ub 0x10000000
con
exit

