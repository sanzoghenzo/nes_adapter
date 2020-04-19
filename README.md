# NES controller USB adapter

[LUFA](http://www.fourwalledcubicle.com/LUFA.php)-based USB adapter for up to 4 NES (Nintendo Entertainment System) controllers.
Works great with LAKKA/RetroArch (see below for configuration).

Once connected to your pc, it will be detected as 4 generic joysticks with 4 buttons each.

Tested with Minimus AVR (atmega32u2) and cheap NES controller replicas (famiclone joysticks the previous renter left in my house).

## Index <!-- omit in toc -->

- [Connections](#connections)
  - [NES connector pinout](#nes-connector-pinout)
  - [Pin map](#pin-map)
- [How To Flash the ROM](#how-to-flash-the-rom)
  - [Windows instructions](#windows-instructions)
- [LAKKA pad configuration](#lakka-pad-configuration)
- [Credits](#credits)
- [Loose ends](#loose-ends)

## Connections

### NES connector pinout

```asciiart
           ____
          /  O |  GND
    VCC  | O O |  CLOCK
    NC   | O O |  LATCH
    NC   | O O |  DATA
         -------
```

### Pin map

| Minimus | NES    |
| ------- | ------ |
| PD0     | DATA 1 |
| PD1     | DATA 2 |
| PD2     | LATCH  |
| PD3     | CLOCK  |
| PD4     | DATA 3 |
| PD5     | DATA 4 |
| GND     | GND    |
| VCC     | VCC    |

## How To Flash the ROM

The following instructions will work on Ubuntu based linux distros:

- install dependencies

  ```sh
  sudo apt install -y avr-libc dfu-programmer
  ```

- clone LUFA and NesAdapter in the same directory

  ```sh
  git clone https://github.com/abcminiuser/lufa.git
  git clone https://github.com/sanzoghenzo/nes_adapter
  ```

- move to nes_adapter directory
  
  ```sh
  cd nes_adapter
  ```

- build the ROM
  
  ```sh
  make all
  ```

- If everything went fine, set the Minimus AVR in programming mode:
  - Hold the HWB button
  - Press and release the RST button
  - Release HWB

- Flash the ROM:

  ```sh
  make dfu
  ```

- Enjoy!

### Windows instructions

You can use WSL (Windows Subsystem on Linux) to build the ROM in the same way as on Ubuntu.

The only thing that don't work is the actual ROM flashing, for which you need [QMK Toolbox](https://github.com/qmk/qmk_toolbox/releases) instead of `dfu-programmer`.

The commands to type become:

```sh
sudo apt install -y avr-libc
git clone https://github.com/abcminiuser/lufa.git
git clone https://github.com/sanzoghenzo/nes_adapter
cd nes_adapter
make all
```

Then use QMK Toolbox to flash the ROM.

## LAKKA pad configuration

Simply place the [joypad configuration file](retroarch/NesAdapter.cfg) in `/storage/joypads/udev` folder.
See [here for details](http://www.lakka.tv/doc/Accessing-Lakka-filesystem/) on how to access LAKKA filesystem on a remote machine.

## Credits

Heavily based on [Nintendo Four Score USB Joystick Adapter by Simon Inns](https://www.waitingforfriday.com/?p=93).

Since I have a Minimus AVR and no Four Score, I removed Fire and Player buttons from his code.

## Loose ends

This code could be easily modified to use a SNES (Super Nintendo) controller.
In fact, I started to set it up, but then I realized most of the 8 buttons in my joysticks were fake... Damn you famiclones!
You can find some trace of "SNES" parts in the code.
Since I haven't tested them, I left them commented.
