# AutoLight_BLE

AutoLight_BLE is a little project of mine allowing controlling your lights with your Bluetooth device. It is really simple : if an ESP32 detects your BLE device it turns on your lights, otherwise it turns them off.

---

## Requirements

* an ESP32
* a free IFTTT account
* a connected light
* ... an internet connection (WiFi)

## Tested on

* ESP32 reference board
* Yeelight ceiling lamp, but anything with an IFTTT action will do

---

## Installation & Usage

Go check out my tutorial on [my website](https://ndeybach.ovh/turning-on-my-lights-when-i-get-home-esp32-ifttt-and-ble)  : 

---

## Known limits

* you can easily be out of range from the ESP32 and not be detected. The program is best used in a single room or an apartment. Maybe this could be alleviated by putting multiple ESP32 in a mesh and syncing them. But it would require quite some more effort.

---

## To do

* add a daytime filter on IFTTT
  
* add a specified "turn off" trigger to make sure the light is off when user leave.

---

## Contributing

I do not think to maintain this project actively, but if you have some good ideas you are welcome to make a pull request.

---

## License
[MIT](https://choosealicense.com/licenses/mit/)
