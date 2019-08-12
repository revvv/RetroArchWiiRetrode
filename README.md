### RetroArchWiiRetrode
RetroArch for Wii with Retrode 2 support!

* The [Retrode 2](http://www.retrode.org) cartridge reader offers USB mass storage access for your SNES and Genesis/MegaDrive cartridges. This works out of the box on the Wii!
* With my driver you can also use your SNES and Genesis/MegaDrive gamepads on your Wii!
* Support for 4 players!
* Tested with various games: Super Mario World, Street Fighter 2, Super Bomberman and Sonic
* Contains two cores: **snes9x2010** and **genesis_plus_gx** (_more to come!_)
* I also maintain the [Snes9x GX Retrode](https://github.com/revvv/snes9xgx-retrode) fork.

#### Download
[RetroArchWiiRetrode-0.3.zip](https://github.com/revvv/RetroArchWiiRetrode/releases/download/0.3/RetroArchWiiRetrode-0.3.zip)

### Notes
* RetroArch will find four Retrode devices.
* If RetroArch does not react, delete `retroarch.cfg` and check which devices were found. 
* **My distribution contains the Retrode autoconfig file.**
* If you want to use an addtional USB gamepad, please note: RetroArch Wii only supports certain USB gamepads: VIDs/PIDs are [hardcoded](https://github.com/libretro/RetroArch/blob/master/input/connect/joypad_connection.h) and an autoconfig file has to exist. As described in the official [commit message](https://github.com/libretro/RetroArch/commit/bca4ccb155cdb088a38a3b00e23f9c1714412515).
* I also noticed that the autoconfig files for the Wii have a slightly different button layout. Just reconfigure if you have copied a file from another platform.
* Logging is enabled.
* Original SNES Mouse not supported. (I don't have one, but if you give me the [RetrodeTest](https://github.com/revvv/snes9xgx-retrode/releases/download/0.1/RetrodeTest-0.1.zip) output I could add it...)

### Compile

Get devkitpro r29. Follow the offical [documentation](http://docs.libretro.com/development/retroarch/compilation/wii/) or read my summary:

Clone projects [RetroArchWiiRetrode](https://github.com/revvv/RetroArchWiiRetrode) and [libretro-super](https://github.com/libretro/libretro-super).

    RetroArchWiiRetrode> $ make -f Makefile.wii.salamander
    libretro-super> $ ./libretro-fetch.sh
    libretro-super> $ ./libretro-build-wii.sh snes9x2010
    libretro-super> $ cp dist/wii/snes9x2010_libretro_wii.a ../RetroArchWiiRetrode/libretro_wii.a
    RetroArchWiiRetrode> $ make -f Makefile.griffin platform=wii
    RetroArchWiiRetrode> $ cp retroarch_wii.dol /SDcard/apps/RetroArch/boot.dol

### Disclaimer
The author of the Retrode USB Wii driver is not afflicted with [Retrode.org](http://www.retrode.org) or [DragonBox Shop](https://www.dragonbox.de/en/accessories/cartridge-dumper/retrode-2-cartridge-dumper), but is a huge fan ;-)
This software comes without any warranty. I am not responsible for any damage to your devices.
