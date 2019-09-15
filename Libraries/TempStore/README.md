#TempStore Library
##Installation

1.  Download the Library
2.  Link the `TempStore` directory to your system's Arduino Library directory.
    - Windows:
        - Using windows explorer, open the directory where TempStore is located
        - Right click on the TempStore folder and select "make shortcut"
        - Cut the newly created shortcut
        - Past the shortcut in `C:\Users\<user>\Documents\Arduino\Libraries\`

    - Linux:
        - Run: `ln -s <path to TempStore> /home/<username>/arduino/libraries/`
 
    - Mac OS:
        - Run: `ln -s <path to TempStore> /Users/<username>/Documents/arduino/libraries/`
     
        
This library also requires that you use the full version of printf. To enable it do the following:

1.  Enable the AVR printf versino selection
    1. Open the File: `<Arduino Installation Directoy>/hardware/arduino/avr/platform.txt`
    2. Find the section of the board you are using (e.g. yun)
    3. Add the following lines, changing `yun` to your board name:
```
yun.printf=AVR printf Version
yun.menu.printf.default=Default printf
yun.menu.printf.default.compiler.c.elf.extra_flags=
yun.menu.printf.full=Full printf
yun.menu.printf.full.compiler.c.elf.extra_flags=-Wl,-u,vfprintf -lprintf_flt
yun.menu.printf.minimal=Minimal printf
yun.menu.printf.minimal.compiler.c.elf.extra_flags=-Wl,-u,vfprintf -
```