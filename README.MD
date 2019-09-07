# Hyperion uses framegrabber on Kodi
* Drives **WS2812B** Led stripes
* **45 LEDS** activated 170 incative to be activated
* **xbmcVideoChecker** is **activated** to communicate to **Kodi**
  64 * 64 Pixel @ 60 Hz
* **Smoothing** Linear 96ms @ Update Freq 48k

## USB Arduino
Folder *USB-ArduinoUno*

* Sketch for **Arduino Uno R3 & Nano**
* uses **FastLED** lib
* set to **45 LED**
* Speaks SPI on Digital **Pin 6**
* Baudrate is set to **500k baud**
* Type **adalight**
* Output to **USB Port** /ttyUSB0 
* Colororder **grb**

### Install
* copy the hyperion.config.json to your /storage/.config folder
* Install the ino on your Arduino


## UDP / Network ESP8266
 Folder *UDP-ESP8266*
 * Type **udp**

### Install
* copy the hyperion.config.json to your /storage/.config folder

* Install Aircoookie WLED on your ESP8266

  to get here: 
  * https://github.com/Aircoookie/WLED/releases

  wiki here: 
  * https://github.com/Aircoookie/WLED/wiki

## Directly via GPIO
 Folder *PI-GPIO*
 * Type **ws281x**
 * set to **45 LED**
 * Speaks PWM 0 on **GPIO12 (PIN 32)**
 * Colororder **grb**

### Install
* copy the hyperion.config.json to your /storage/.config folder

* SD Folder 
 * copy the file or at least the last lines directly to your SD Card while it's not running in the pi
* etc Folder
 * copy the file while your pi is running in the / of your Pi
 * after reboot check with `aplay -l`if you still se a soundcard, then you might want to sudo vi /etc/modprobe.d/alsa-blacklist.conf and add (i) `blacklist snd_bcm2835` and save (:x) the file, then reboot and check again
