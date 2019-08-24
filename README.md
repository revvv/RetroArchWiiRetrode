### RetroArchWiiRetrode
RetroArch for Wii with Retrode 2 and XBOX360 controller support!

* The [Retrode 2](http://www.retrode.org) cartridge reader offers USB mass storage access for your SNES and Genesis/MegaDrive cartridges. This works out of the box on the Wii!
* With my driver you can also use your SNES and Genesis/MegaDrive gamepads on your Wii!
* Support for 4 players!
* Tested with various games: Super Mario World, Street Fighter 2, Super Bomberman, Sonic and Boulder Dash
* I also maintain the [Snes9x GX Retrode](https://github.com/revvv/snes9xgx-retrode) fork.

**XBOX360 controller** is now supported! (XBOX360 wired version: VID=0x045e, PID=0x028e)

_Maybe I should have chosen another project name ;-)_ 

**NEW**: I also fixed [caprice32's bad resolution bug](https://github.com/libretro/libretro-cap32/issues/65)

#### Download Retrode/XBOX360 Build
* [RetroArchWiiRetrode-0.4.zip](https://github.com/revvv/RetroArchWiiRetrode/releases/download/0.4/RetroArchWiiRetrode-0.4.zip)
* Contains three cores: **snes9x2010**, **genesis_plus_gx** and **caprice32**
* **WARNING!** Only the XBOX360 wired controller is supported: The wireless controller might crash.
* **WARNING!** This build does not support USB mass storage devices! This HACK was required to support XBOX360.
* **NOTE:** Plug in your USB controller before you launch RetroArch. Do not unplug while RetroArch is running.
* **NOTE:** This build _crashes_ sometimes after closing contents.

#### Download Retrode Build
* [RetroArchWiiRetrode-0.3.zip](https://github.com/revvv/RetroArchWiiRetrode/releases/download/0.3/RetroArchWiiRetrode-0.3.zip)
* Contains two cores: **snes9x2010** and **genesis_plus_gx**
* Works out of the box.

#### Download offical RetroArch Build with Retrode 2 support (XBOX360 support is not included!)
* My Retrode driver is now available in the official [RetroArch nightly builds](http://buildbot.libretro.com/nightly/nintendo/wii/)
* Contains **46 cores!**
* Add the autoconfig file [Retrode.cfg](https://github.com/revvv/RetroArchWiiRetrode/releases/download/0.3/Retrode.cfg) to `SD:/apps/retroarch-wii/autoconfig`
* Create directory `SD:/retroarch/config`
* Configure input joypad driver to `hid`, then restart.
* I usually add these values to the default config file `retroarch.cfg`. (Or use the RetroArch menu to configure.)

```
    input_joypad_driver = "hid"
    all_users_control_menu = "true"
    ;; open RetroArch menu with start+select (4) 
    input_menu_toggle_gamepad_combo = "4"
```

### Notes
* RetroArch will find four Retrode devices.
* If you want to use an additional USB gamepad, please note: RetroArch Wii only supports certain USB gamepads: VIDs/PIDs are [hardcoded](https://github.com/libretro/RetroArch/blob/master/input/connect/joypad_connection.h) and an autoconfig file has to exist. As described in the official [commit message](https://github.com/libretro/RetroArch/commit/bca4ccb155cdb088a38a3b00e23f9c1714412515).
* I also noticed that the autoconfig files for the Wii have a slightly different button layout. Just reconfigure if you have copied a file from another platform.
* Original SNES Mouse is not supported. (I don't have one, but if you give me the [RetrodeTest](https://github.com/revvv/snes9xgx-retrode/releases/download/0.1/RetrodeTest-0.1.zip) output I could add it...)

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
