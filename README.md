# Sesame2MQTT
The objective of [Sesame2MQTT](https://github.com/js4jiang5/Sesame2MQTT) project is to let Home Assistant users to easily integrate Sesame devices into Home Assistant with an ESP32 board. The main feature of [Sesame2MQTT](https://github.com/js4jiang5/Sesame2MQTT) is that it is based on MQTT discovery protocol, which automatically scan, detect and configure all devices. Therefore, the users hardly need to do any complex setup. Currently supported devices include Sesame 5/ 5 Pro/ Sesame Touch /Touch Pro. Intrinsically [Sesame2MQTT](https://github.com/js4jiang5/Sesame2MQTT) is an ESPHome external component based on ESP-IDF framework, and the main functions are built on [libsesame2mqtt](https://github.com/js4jiang5/libsesame2mqtt), which is a fork of [SesameSDK_ESP32_with_DemoApp](https://github.com/CANDY-HOUSE/SesameSDK_ESP32_with_DemoApp) while provides more complete control and monitor functions along with WiFi and MQTT protocols. 

## Other languages
- [正體中文 README](README_TW.md)<br>
- [日文 README](README_JP.md)<br>

## Prerequisites
1. Home Assistant platform with two addons and one integration ready.
    - Addons <br>
        - Mosquitto broker ([Installation Guide](https://github.com/home-assistant/addons/blob/master/mosquitto/DOCS.md))
        - ESPHome addon ([Installation Guide](https://github.com/esphome/home-assistant-addon/blob/main/esphome/DOCS.md))
    - Integration <br>
        - MQTT ([Installation Guide](https://www.home-assistant.io/integrations/mqtt/), [Add Integration](https://my.home-assistant.io/redirect/config_flow_start?domain=mqtt)).

2. An ESP32-C3-DevKtM-1 development board. Avoid using other models to minimize problems. That would make your life easier.

## Installation
The installation is super easy.

1. Copy the file [sesame2mqtt.yaml](sesame2mqtt.yaml) into /config/esphome/ directory of your Home Assistant
2. Edit the file to enter your wifi ssid/password and mosquitto broker URL. Yes, that's all you need to setup. It would help if you also specify real number of devices to let ESP32 know how many devices it would search. Maximum number is 8.
```yaml
sesame2mqtt:
  wifi_ssid: "wifi_ssid"
  wifi_password: "wifi_password"
  mqtt_broker_url: "username:password@address:1883" # MQTT Broker URL, for example "mqtt_user:mqtt_pass@192.168.1.69:1883"
  number_devices: 2 # Optional, but it will significantly improve device scan speed if you set it to the real number of your Sesame devices. Maximum is 8
```

3. Open ESPHome WEB UI and click the 3 dots of "Sesame2MQTT" project. Sub-menu pop-up. Click Install. Then choose Manual download. <br>
<img src="docs/Images/ESPHome - Sesame2MQTT Install.png" height="400" />
<img src="docs/Images/ESPHome - Manual Download.png" height="400" /><br> <br>

4. ESPHome start to compile. It would take couple of minutes. After compilation is done, choose "Modern format" to download. The downloaded image file name is sesame2mqtt-factory.bin <br>
<img src="docs/Images/ESPHome Build.png" height="300" />
<img src="docs/Images/ESPHome - Download Format.png" height="300" /><br> <br>

5. Before flash ESP32, reset Sesame devices with a needle to enter unregistered state. Then put them within 5 meters range of ESP32. This is important to ensure good Bluetooth signal quality.

6. Flash the image into your ESP32-C3-DevKitM-1 with [ESPHome Web Dashboard](https://web.esphome.io/?dashboard_install), which is by far the most reliable way, just connect, select USB, and install. <br>
(Note 1: The browser must be Chrome or Edge. The other browsers are not supported by ESPHome Web.)<br>
(Note 2: If you never flash before, you need to download and install USB to UART driver first.)<br>
<img src="docs/Images/ESPHome DashBoard - Main.png" height="300" />
<img src="docs/Images/ESPHome DashBoard - Connect.png" height="300" />
<img src="docs/Images/ESPHome DashBoard - Install.png" height="300" /><br> <br>

That's all. The ESP32-C3-DevKitM-1 will automatically scan for all your Sesame devices. Wait one minute for ESP32 to finish the scan. Then check your MQTT devices. Click "Reload" to refresh all entities. If some devices are not shown in the device list, don't worry, just put them closer to ESP32, unplug USB of the ESP32 and plug again. Scan will resume immediately. <br>
<img src="docs/Images/MQTT - Devices.png" width="600" /> <br> <br>

If MQTT is installed after ESP32 flash, the discovered devices will pop-up like this <br>
<img src="docs/Images/MQTT - Discovery.png" width="600" /><br> <br>

Sesame 5 device looks like this. <br>
<img src="docs/Images/MQTT - Sesame 5.png" width="600" /><br> <br>

## Usage
1. Follow the steps below to add the devices to your Sesame APP by scanning QR code. After that you may control devices by both Home Assistant and your mobile phone.
- Generate QR code by pressing "Gen QR Code Text" button. The text leading with "ssm://" will be shown below. <br>
<img src="docs/Images/MQTT - Gen Code.png" width="300" /><br> <br>

- Generate QR code with any [QR Code Generator](https://www.qr-code-generator.com/solutions/text-qr-code/) <br>
<img src="docs/Images/QR Code Generator.png" width="600" /><br> <br>

- Scan the QR code with your Sesame APP.<br>
<img src="docs/Images/Sesame APP - Scan QR Code.png" width="300" /><br> <br>

2. Sesame 5/ 5 Pro setup<br>
    (1) Horizon calibration: move to the Sesame 5/ 5 Pro to horizon position. Then press "Horizon Calibration" button. This position is 0°. This step can also be done by Sesame APP.<br>
    <img src="docs/Images/Sesame 5 - Horizon.png" width="300" /> <br><br>
    
    (2) Enter Lock and Unlock Position. The Lock status will be updated automatically after the Lock/Unlock Position is setup. My Sesame 5 is 160° for lock and 20° for unlock as the pictures below. Entering the value directly to setup lock/unlock position is a very convenient approach because you can do it even if you are outside of the door. It might save you one day if Sesame 5 went wrong and you were locked outside. <br>
    <img src="docs/Images/Sesame 5 - Lock Unlock Position.png" width="300" /> <br>
    <img src="docs/Images/Sesame 5 - Lock 160.png" width="200" />
    <img src="docs/Images/Sesame 5 - UnLock 20.png" width="200" /><br> <br>

3. Sesame Touch/ Touch Pro setup<br>
    (1) Pair with Sesame 5/ 5 Pro. If you have only two devices (one Sesame 5 + one Touch), they are automatically paired after ESP32 device scan. If you have more than two devices, manual pairing is necessary since I have no idea which one goes with which.<br>
    
    (2) Sesame Touch/ Touch Pro can pair with Sesame 5/ 5 Pro with its MAC address, which can be found on top left corner of the Device Page.<br>
    <img src="docs/Images/Sesame 5 - MAC address.png" width="300" /> <br> <br>

    (3)To pair a Sesame 5/ 5 Pro with Touch, simply copy the MAC address of Sesame 5/ 5 Pro and paste it in "Enter MAC address - Add Sesame" and press enter. ESP32 will check the validity of the MAC address and add it if it is valid. Of course, you may also use Sesame APP for pairing.<br>
    <img src="docs/Images/Touch - Add Sesame.png" width="300" /> <br> <br>

## 3D-Print Case
I've also prepared two STL files for 3D-Print case, including [Top](docs/3D%20case/esp32-c3-devkitm-1-lid.stl) and [Base](docs/3D%20case/esp32-c3-devkitm-1-base.stl). As shown below, I deliberately made an outlet around RF antenna, not only for heat ventillation but also to expose the RF antenna for better signal quality. <br>
<img src="docs/Images/3D Case - 1.png" height="300" />
<img src="docs/Images/3D Case - 2.png" height="300" /><br> <br>

The dimension of my ESP32-C3-DevKitM-1 is shown below. Before 3D-printing you must check if the dimension is the same. If not, you'll have to find the 3D-Print model that fits yours. <br>
<img src="docs/Images/ESP32-C3-DevKitM-1 Dimension.jpeg" width="300" /><br> <br>

## Final Note
Although "theoretically" [Sesame2MQTT](https://github.com/js4jiang5/Sesame2MQTT) can support up to 8 devices, but I never tested it since I have only one Sesame 5 and one Sesame Touch. Therefore, it's not guaranteed for more than two devices to work as expected. I do hope it works fine, though. Also, this is my first ESPHome project, so the implementation might not be so mature. Could you belive that? Two months ago I didn't even know what ESPHome is, and now I'm kind of an amature developer. In fact, I started this project simply because the WiFi2 module of CAHDY HOUSE is sold out for a long time. I can't help but trying their ESP32 Demo SDK to see if it is possible to integrate into Home Assistant. I made it with ESP-IDF, but I am the only one who can use it. In order for more people to use it, I started learning ESPHome。One thing leads to another, this project is eventually finished. Life is really unexpectable.