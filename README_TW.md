# Sesame2MQTT
[Sesame2MQTT](https://github.com/js4jiang5/Sesame2MQTT) 專案的主要目的，是讓 Home Assistant 的使用者透過 ESP32 開發板便能輕鬆的將 Sesame 設備整合進 Home Assistant 之中。[Sesame2MQTT](https://github.com/js4jiang5/Sesame2MQTT) 的主要特色是它建立在 MQTT discovery 協議上, 能自動掃描、偵測、設定所有設備。因此，對於使用者來說，幾乎不需要做什麼複雜的設定便能完成。 目前支援的設備包括 Sesame 5/ 5 Pro/ Sesame Touch /Touch Pro。 本質上 [Sesame2MQTT](https://github.com/js4jiang5/Sesame2MQTT) 是一個以 ESP-IDF 為架構的 ESPHome 外部元件 (External Component), 其主要功能是以 [libsesame2mqtt](https://github.com/js4jiang5/libsesame2mqtt) 函式庫為基礎。此函式庫是 [SesameSDK_ESP32_with_DemoApp](https://github.com/CANDY-HOUSE/SesameSDK_ESP32_with_DemoApp) 的一個分支，但提供了更加完整的控制與監測功能，並且支援 WiFi 與 MQTT 協議。 

## 版本
- [[0.3.0](https://github.com/js4jiang5/Sesame2MQTT/tree/0.3.0)] (建議安裝，需使用 [最新版 sesame2mqtt.yaml](https://github.com/js4jiang5/Sesame2MQTT/blob/0.3.0/sesame2mqtt.yaml)) <br>
    - 增加 RSSI 顯示實體
    - 修改程式架構成純粹事件觸發，不再需要 loop() 即可達成永不間斷偵測新設備
    - 修正不間斷偵測設備因 Sesame 5 主動離線造成的問題

- [[0.2.0](https://github.com/js4jiang5/Sesame2MQTT/tree/0.2.0)] ([0.2.0 sesame2mqtt.yaml](https://github.com/js4jiang5/Sesame2MQTT/blob/0.2.0/sesame2mqtt.yaml)) <br>
    - 永不間斷偵測新 Sesame 設備，不需要重新插拔 ESP32 USB
    - 偵測與處理已有設備被人為重置的情況，不需要重新插拔 ESP32 USB

- [[0.1.1](https://github.com/js4jiang5/Sesame2MQTT/tree/0.1.1)] ([old sesame2mqtt.yaml](https://github.com/js4jiang5/Sesame2MQTT/blob/0.1.1/sesame2mqtt.yaml))<br>
    - 初版，一次性偵測所有 Sesame 設備，若有新增設備時必須重新插拔 ESP32 USB
    - 若已有設備被重置，需要重新插拔 ESP32 USB

## 多語言版本
- [English README](README.md)<br>
- [日文 README](README_JP.md)<br>

## 安裝前的準備工作
1. Home Assistant 平台必須安裝好兩個附加元件 (addons) 以及一個整合 (integration)。
    - Addons <br>
        - Mosquitto broker ([Installation Guide](https://github.com/home-assistant/addons/blob/master/mosquitto/DOCS.md))
        - ESPHome addon ([Installation Guide](https://github.com/esphome/home-assistant-addon/blob/main/esphome/DOCS.md))
    - Integration <br>
        - MQTT ([Installation Guide](https://www.home-assistant.io/integrations/mqtt/), [Add Integration](https://my.home-assistant.io/redirect/config_flow_start?domain=mqtt))。

2. 準備好一個 ESP32-C3-DevKtM-1 開發板。 盡量避免使用其他型號的 ESP32 開發板，除非你想給自己找麻煩。

## 安裝
安裝非常的簡單

1. 將檔案 [sesame2mqtt.yaml](sesame2mqtt.yaml) 複製到 Home Assistant /config/esphome/ 目錄下。
2. 編輯此檔案，輸入你真實的 wifi ssid/password 以及 mosquitto broker URL。 基本上只要這樣設定就夠了，不過如果你能額外設定真實的設備數量，可以大幅降低 ESP32 掃描設備所需要的時間，只要他已發現你所指定的設備數量，便會停止掃描。最多可以支援 8 個 Sesame 設備。
```yaml
sesame2mqtt:
  wifi_ssid: "wifi_ssid"
  wifi_password: "wifi_password"
  mqtt_broker_url: "username:password@address:1883" # MQTT Broker URL, for example "mqtt_user:mqtt_pass@192.168.1.69:1883"
  number_devices: 2 # Optional, but it will significantly improve device scan speed if you set it to the real number of your Sesame devices. Maximum is 8
```

3. 打開 ESPHome WEB UI 並點擊 "Sesame2MQTT" 專案右下角的 3 點，子選單就會跳出來，先點擊 Clean Build Files 確保已清除舊版本後，再點擊 Install，然後選擇 Manual download。 <br>
<img src="docs/Images/ESPHome - Sesame2MQTT Install.png" height="400" />
<img src="docs/Images/ESPHome - Manual Download.png" height="400" /><br> <br>

4. ESPHome 會開始編譯，大概需要幾分鐘才能完成。編譯完成後，選擇 "Modern format" 下載。 下載的映象檔檔名為 sesame2mqtt-factory.bin <br>
<img src="docs/Images/ESPHome Build.png" height="300" />
<img src="docs/Images/ESPHome - Download Format.png" height="300" /><br> <br>

5. 燒錄 (flash) ESP32 之前, 記得要用針重置所有的 Sesame 設備讓他們回復到未註冊狀態，距離 ESP32 開發板不要超過五公尺，這樣才能確保 Bluetooth 的訊號品質，這點很重要。

6. 透過 [ESPHome Web Dashboard](https://web.esphome.io/?dashboard_install) 將映象檔燒錄至你的 ESP32-C3-DevKitM-1。這是目前為止我認為最穩定的燒錄方法，只要連線，選擇正確的 USB port, 然後安裝就可以了。 <br>
(註記1: 目前 ESPHome Web 只支援 Chrome 以及 Edge 瀏覽器。)<br>
(註記2: 如果你是初次燒錄，要先下載並安裝好 USB to UART 的驅動程式。)<br>
<img src="docs/Images/ESPHome DashBoard - Main.png" height="300" />
<img src="docs/Images/ESPHome DashBoard - Connect.png" height="300" />
<img src="docs/Images/ESPHome DashBoard - Install.png" height="300" /><br> <br>

這樣就行了，接下來 ESP32-C3-DevKitM-1 會自動掃描你所有的 Sesame 設備。 先等一分鐘讓 ESP32 完成掃描，然後檢查一下你的 MQTT devices 應該就會發現新增的裝置。 最好點擊 "Reload" 刷新一下目前的實體。 如果有些設備沒掃描到，別擔心，把他們放靠近 ESP32一些，將 ESP32 的 USB 線斷開後再重連就會重啟掃描。 <br>
<img src="docs/Images/MQTT - Devices.png" width="600" /> <br> <br>

如果你的 MQTT 是在 ESP32 燒錄之後才安裝會看到以下的畫面，顯示新發現的設備。 <br>
<img src="docs/Images/MQTT - Discovery.png" width="600" /><br> <br>

Sesame 5 裝置的內容如下。 <br>
<img src="docs/Images/MQTT - Sesame 5.png" width="600" /><br> <br>

## 使用方法
1. 手機 Sesame APP 掃描 QR code 新增設備，這樣你不僅能用 Home Assistant 控制，也可以用手機控制，步驟如下。
- 按 "Gen QR Code Text" 按鈕便會在下方顯示產生的 QR code，其開頭為 "ssm://" <br>
<img src="docs/Images/MQTT - Gen Code.png" width="300" /><br> <br>

- 用 [QR Code Generator](https://www.qr-code-generator.com/solutions/text-qr-code/) 產生 QR code<br>
<img src="docs/Images/QR Code Generator.png" width="600" /><br> <br>

- 用手機 Sesame APP 掃描 QR code <br>
<img src="docs/Images/Sesame APP - Scan QR Code.png" width="300" /><br> <br>

2. 設定 Sesame 5/ 5 Pro<br>
    (1) 水平校正: 將 Sesame 5/ 5 Pro 旋鈕轉至水平位置，然後按 "Horizon Calibration" 按鈕，這個位置就是 0°。這個步驟也可以用手機 Sesame APP 來實現。<br>
    <img src="docs/Images/Sesame 5 - Horizon.png" width="300" /> <br><br>
    
    (2) 輸入上鎖與解鎖角度，設定好後鎖的狀態便會自動更新。如下圖所示我的上鎖是 160° 而解鎖是 20°。能夠直接輸入值來設定上鎖/解鎖角度非常方便，這樣即使你人在門外也能夠設定。或許有一天 Sesame 5 突然出問題而你被反鎖在門外時，這個功能可以救你一命。<br>
    <img src="docs/Images/Sesame 5 - Lock Unlock Position.png" width="300" /> <br>
    <img src="docs/Images/Sesame 5 - Lock 160 Unlock 20.png" width="400" /> <br><br>

3. 設定 Sesame Touch/ Touch Pro<br>
    (1) 與 Sesame 5/ 5 Pro 進行配對。假如你總共只有兩個設備，一台 Sesame 5 加上一台 Touch, ESP32 在掃描完後就會自動配對，不需要費心。但是如果你的設備超過兩台，便需自己手動進行配對，因為我無法得知配對哪一個才是正確的。<br>

    (2) Sesame Touch/ Touch Pro 是用 Sesame 5/ 5 Pro 的 MAC address 來配對的。你可以在裝置資訊的左上角看到 MAC address。<br>
    <img src="docs/Images/Sesame 5 - MAC address.png" width="300" /> <br> <br>

    (3) 只要將 Sesame 5/ 5 Pro 的 MAC address 複製貼上 "Enter MAC address - Add Sesame" 然後按 enter 便會開始配對。 ESP32 會檢查 MAC address，如果正確就會加入完成配對。當然，你也可以選擇用手機 Sesame APP 來進行配對。<br>
    <img src="docs/Images/Touch - Add Sesame.png" width="300" /> <br> <br>

## 3D 列印外盒
我也準備了 3D 列印外盒的 STL 檔案，包括 [上蓋](docs/3D%20case/esp32-c3-devkitm-1-lid.stl) 與 [底座](docs/3D%20case/esp32-c3-devkitm-1-base.stl)。 如下方所示，我故意在天線處做了一個開口，不僅是為了散熱，也是為了可以讓 RF 收訊品質更好。 <br>
<img src="docs/Images/3D Case - 1.png" height="300" />
<img src="docs/Images/3D Case - 2.png" height="300" /><br> <br>

我的 ESP32-C3-DevKitM-1 如下圖所示。在你做 3D 列印之前，先確認一下大小是否跟你的相同，如果不同你就得找其他適合的3D模型。 <br>
<img src="docs/Images/ESP32-C3-DevKitM-1 Dimension.jpeg" width="300" /><br> <br>

## 後記
雖然 [Sesame2MQTT](https://github.com/js4jiang5/Sesame2MQTT)「理論上」能支援最多 8 個設備, 但我從未測試過，畢竟我只有一個 Sesame 5 跟一個 Sesame Touch。因此，我無法保證超過兩個以上的設備能如預期般運行，當然我希望是可以。還有，這是我的第一個 ESPHome 計畫，所以設計可能不是很成熟。你相信嗎？兩個月前我連 ESPHome 跟 ESP-IDF 是什麼東東都還一無所知，而我現在已經變成業餘的開發者了。其實當初會開始進行這個計畫，純粹只是因為 CANDY HOUSE 的 WiFi2 模組已經缺貨很久了，不得已只好測試一下他們的 ESP32 展示版 SDK，看能不能藉此整合進 Home Assistant。雖然在 ESP-IDF 開發完成後達到了目的，但只有我能使用。為了讓更多人能使用，又開始接觸 ESPHome，一件接著一件，不知不覺就完成了這個計畫。人生真是無法預測啊。