
# Hyperion uses framegrabber on Kodi
* Drives **WS2812B** Led stripes
* **45 LEDS** activated 170 incative to be activated
* **xbmcVideoChecker** is **activated** to communicate to **Kodi**
  64 * 64 Pixel @ 60 Hz
* **Smoothing** Linear 96ms @ Update Freq 48k

---

# Get the code
```BASH 
git clone --recurse-submodules
git@github.com:NeedfulThings/hyperionconfigs.git
```

# Setup the dev environment
 
We are using direnv to get a clean environment that can have oher versions than the rest of your system. It's required to set it up first and configure well.

## Install direnv

### Linux
```BASH
curl -qfsSL https://github.com/direnv/direnv/releases/download/v2.19.0/direnv.linux-amd64 -o direnv
chmod +x direnv
sudo mv direnv /usr/local/bin
```

### macOS
```BASH
brew install dirvenv
```

## Hook it up in your shell
### BASH
*add the following line to your `~/.bashrc` file*
```BASH
eval "$(direnv hook bash)"
```
### ZSH
*add the following line to your `~/.zshrc` file*
```BASH
eval "$(direnv hook zsh)"
```
### Other shells

*Take a look [here](https://github.com/direnv/direnv/blob/master/docs/hook.md)*

## Setup the dev environment by just running
```BASH
./start.sh
```
in the Project root


---

# USB Arduino Uno
Folder *USB-ArduinoUno*

* Sketch for **Arduino Uno R3**
* uses **FastLED** lib
* set to **45 LED**
* Speaks SPI on Digital **Pin 6**
* Baudrate is set to **500k baud**
* Type **adalight**
* Output to **USB Port** /ttyUSB0 
* Colororder **grb**

## Install

### `hyperion.config.json`

copy the `L45_Config/hyperion.config.json` to your `/storage/.config` folder

### `hyperion_ws2812.ino`

Install the `hyperion_ws2812.ino` on your Arduino. You can use the Makefile inside the folder by just running ```make upload```

---

# USB Arduino Nano
Folder *USB-ArduinoNano*

* Sketch for **Arduino Nano**
* uses **FastLED** lib
* set to **128 LED**
* Uses Digital **Pin 11**
* Baudrate is set to **500k baud**
* Type **adalight**
* Output to **USB Port** /ttyUSB0 
* Colororder **grb**

<img src="USB-ArduinoNano/assets/completedBoard.jpg" align="left" height="200" width="231">

## Install

### `FS128_Config`

copy the `hyperion.config.json` to your `/storage/.config` folder

### `hyperion_ws2812.ino`

Install the `hyperion_ws2812.ino` on your Arduino. You can use the Makefile inside the folder by just running ```make upload```

### `Hardware`

Take a look into the USB-ArduinoNano.md file to get more informations

---

# UDP / Network ESP8266
 Folder *UDP-ESP8266*
 * Type **udp**
 * Protocol **0**
 * Port **19446**
 * set to **45 LED** supports up to 490 inn hyperion mode

<img src="UDP-ESP8266/assets/boardcompleted2.jpg" align="left" height="221" width="300">

## Install

### `hyperion.config.json`

Copy the `hyperion.config.json` to your `/storage/.config` folder

### `WLED`

Install from the submobule folder [Aircoookie](https://github.com/Aircoookie)'s [WLED](https://github.com/Aircoookie/WLED) 

If you want to get it as binary you can find the latest relases [here](https://github.com/Aircoookie/WLED/releases)

Further Infos can be found in the [Wiki](htpps://github.com/Aircoookie/WLED/wiki)

---

# Directly via GPIO

 Folder *PI-GPIO*
 * Type **ws281x**
 * set to **45 LED**
 * Speaks PWM 0 on **GPIO12 (PIN 32)**
 * Colororder **grb**

## Install

### `hyperion.config.json`

copy the `hyperion.config.json` to your `/storage/.config` folder

### `SD` 

copy the `config.txt` from `SD` or at least the last lines below the `End of default configuration Block` directly to your **SD Card** while it's **NOT** running in the pi

### `etc`

copy the file `snd-blacklist.conf` to your **running** pi `/etc/modprobe.d/` - The easiest way copy etc to your / 

Now **reboot** - When your pi is up again, check with `aplay -l`if you can still see a soundcard.

If yes you might want to `blacklist snd_bcm2835` as last line to `/etc/modprobe.d/alsa-blacklist.conf`, reboot and check again.
