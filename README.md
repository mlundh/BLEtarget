# BLEtarget 
BLEtarget is an optical electronic scoring target with bluetooth connectivity developed for air guns. 

The project consists of both Hardware and firmware. The source is found in hw and fw respectively. 

## HW
The HW is developed in KiCad 7.0. It consists of a sensor array with support electronics as well as an STM32 with BLE capabilites. 

### Known bugs
BOM error - U8-U10 MCP604 populated with MCP6044 with 14kHz bandwidth, should be MCP604 with 2.8Mhz bandwidth.



## FW
The firmware developed in CubeIDE.
