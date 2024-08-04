# BLEtarget 
BLEtarget is an optical electronic scoring target with bluetooth connectivity developed for air guns. 

The project consists of both Hardware and firmware. The source is found in hw and fw respectively. 

## HW
The HW is developed in KiCad 7.0. It consists of a sensor array with support electronics as well as an STM32 with BLE capabilites. 

### Known bugs
BOM error - U8-U10 MCP604 populated with MCP6044 with 14kHz bandwidth, should be MCP604 with 2.8Mhz bandwidth.
BOM error - c32 and corresponding 10u caps should be changed to 10000PF for a shorter signal pulse.
Schematic error - add a jumper to select master/slave. 
Schematic update - add a small memory, fram.


## FW
The firmware developed in CubeIDE.

## SW
The user interface is called Bullseye and developed in Qt using widgets.

### Dependencies
qt6-base-dev-tools
qt6-serialport-dev
cmake

### Raspberry pi Zero 2W with Hyperpixel 4.0 Square
#### Increase swap file:
Edit /etc/dphys-swapfile to change CONF_SWAPSIZE=100 to CONF_SWAPSIZE=2048. After making the change, restart the Pi.
#### Enable Hyperpixel
Add one line in /boot/firmware/config.txt:
dtoverlay=vc4-kms-dpi-hyperpixel4sq
#### Convenience
Enable one-click open of files: 
In Accessories select File Manager
In File Manage select Preference.
Select "Open Files with One Click"
#### Add desktop shortcut
Add desktop shortcut by draging the application to the desktop. Also drag the updateBullseye.sh script to the desktop.

#### Start at bootup
