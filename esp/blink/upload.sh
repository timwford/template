arduino-cli compile --fqbn esp32:esp32:esp32 blink.ino
arduino-cli upload -p /dev/cu.usbserial-0001 --fqbn esp32:esp32:esp32 blink
