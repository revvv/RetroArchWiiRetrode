### RetroArchWiiRetrode
RetroArch for Wii with Retrode 2 support!

* The [Retrode 2](http://www.retrode.org) cartridge reader offers USB mass storage access for your SNES cartridges. This works out of the box on the Wii!
* With my driver you can also use your SNES gamepad on your Wii!
* Support for 1 player only! (Port 1) (_more to come!_)
* Tested with two games: Super Mario World and Sonic
* Contains two cores: snes9x2010 and genesis\_plus\_gx (_more to come!_)
* I also maintain the [Snes9x GX Retrode](https://github.com/revvv/snes9xgx-retrode) fork, which supports 4 players.

#### Download
* [RetroArchWiiRetrode-0.1.zip](https://github.com/revvv/RetroArchWiiRetrode/releases/download/0.1/RetroArchWiiRetrode-0.1.zip) includes Snes9x2010 core.
* [genesis_plus_gx_libretro_wii-0.1.zip](https://github.com/revvv/RetroArchWiiRetrode/releases/download/0.1/genesis_plus_gx_libretro_wii-0.1.zip) optional Genesis core

### Notes
* RetroArch will find two Retrode devices. Usually #1 is the SNES mouse (not supported) and #2 is the SNES gamepad in port 1.
* `retroarch.cfg` has already #2 configured for user 1. If your gamepad does not react, change settings value `input_player1_joypad_index` from 1 to 0 **or**
* If you have another USB gamepad that is supported by RetroArch you can delete the config file and configure the Retrode gamepad manually.
* If you want to use an addtional USB gamepad, please note: RetroArch Wii only supports certain USB gamepads: VIDs/PIDs are hardcoded and an autoconfig file has to exist. I'm not sure if this is a bug or feature ;-) **My distribution contains the autoconfig file for the Retrode.**
* Logging is enabled.

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
