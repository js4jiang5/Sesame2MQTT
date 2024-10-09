# Sesame2MQTT
[Sesame2MQTT](https://github.com/js4jiang5/Sesame2MQTT) プロジェクトの主な目的は、Home Assistantのユーザーが ESP32 開発ボードを通じて、Sesame デバイスを Home Assistant に簡単に統合できるようにすることです。 [Sesame2MQTT](https://github.com/js4jiang5/Sesame2MQTT) の主な特徴は、MQTT discoveryプロトコルに基づいて構築されており、すべてのデバイスを自動的にスキャン、検出、設定できることです。したがって、ユーザーはほとんど複雑な設定をする必要がありません。現在サポートされているデバイスには、Sesame 5/5 Pro/Sesame Touch/Touch Proが含まれます。本質的に、 [Sesame2MQTT](https://github.com/js4jiang5/Sesame2MQTT) はESP-IDFをベースにしたESPHomeの外部コンポーネント（External Component）であり、主な機能は [libsesame2mqtt](https://github.com/js4jiang5/libsesame2mqtt) ライブラリに基づいています。このライブラリは [SesameSDK_ESP32_with_DemoApp](https://github.com/CANDY-HOUSE/SesameSDK_ESP32_with_DemoApp) のフォークですが、より完全な制御と監視機能を提供し、WiFiとMQTTプロトコルをサポートしています。

## バージョン
- [[0.5.0](https://github.com/js4jiang5/Sesame2MQTT/tree/0.5.0)] ([最新版のsesame2mqtt.yaml](https://github.com/js4jiang5/Sesame2MQTT/blob/0.5.0/sesame2mqtt.yaml) を使用することを推奨) <br>
    - Sesame5またはSesame5 PROの予期しないログアウトの問題を解決するには、ESP32を再起動します。

- [[0.4.0](https://github.com/js4jiang5/Sesame2MQTT/tree/0.4.0)] ([0.4.0 sesame2mqtt.yaml](https://github.com/js4jiang5/Sesame2MQTT/blob/0.4.0/sesame2mqtt.yaml)) <br>
    - WiFi再接続失敗後の永続的なMQTTセッションとESP32の再起動により安定性を向上

- [[0.3.0](https://github.com/js4jiang5/Sesame2MQTT/tree/0.3.0)] ([0.3.0 sesame2mqtt.yaml](https://github.com/js4jiang5/Sesame2MQTT/blob/0.3.0/sesame2mqtt.yaml)) <br>
    - RSSI を表示するエンティティを追加する
    - イベントトリガーに基づいて無限検出を実現するためにプログラム構造を変更する。loop() 関数はもはや必要ありません
    - Sesame 5 によって開始された切断によって引き起こされる無限検出失敗のバグを修正する
    
- [[0.2.0](https://github.com/js4jiang5/Sesame2MQTT/tree/0.2.0)]  ([0.2.0 sesame2mqtt.yaml](https://github.com/js4jiang5/Sesame2MQTT/blob/0.2.0/sesame2mqtt.yaml)) <br>
    - 新しいSesameデバイスを途切れることなく検出し、ESP32 USBを再度挿入する必要はありません既存のデバイスが人為的にリセットされた場合の検出と処理を行い、ESP32 USBを再度挿入する必要はありません

- [[0.1.1](https://github.com/js4jiang5/Sesame2MQTT/tree/0.1.1)]  ([old sesame2mqtt.yaml](https://github.com/js4jiang5/Sesame2MQTT/blob/0.1.1/sesame2mqtt.yaml)) <br>
    -初期バージョンでは、すべてのSesameデバイスを一度に検出します。新しいデバイスが追加された場合は、ESP32 USBを再度挿入する必要があります既存のデバイスがリセットされた場合は、ESP32 USBを再度挿入する必要があります

## 多言語バージョン
- [正體中文 README](README_TW.md)<br>
- [英文 README](README.md)<br>

## インストール前の準備
1. Home Assistantプラットフォームには、2つのアドオン（addons）と1つの統合（integration）が必要です。
    - Addons <br>
        - Mosquitto broker ([Installation Guide](https://github.com/home-assistant/addons/blob/master/mosquitto/DOCS.md))
        - ESPHome addon ([Installation Guide](https://github.com/esphome/home-assistant-addon/blob/main/esphome/DOCS.md))
    - Integration <br>
        - MQTT ([Installation Guide](https://www.home-assistant.io/integrations/mqtt/), [Add Integration](https://my.home-assistant.io/redirect/config_flow_start?domain=mqtt))。

2. ESP32-C3-DevKtM-1 開発ボードを用意してください。他の型番の ESP32 開発ボードの使用は避けてください。それは自分自身に問題を引き起こすことになるかもしれません。

## インストール
インストールは非常に簡単です

1. ファイル [sesame2mqtt.yaml](sesame2mqtt.yaml) をHome Assistant /config/esphome/ディレクトリにコピーします。
2. このファイルを編集し、実際の wifi ssid/passwordおよび mosquitto broker URL を入力します。基本的にはこれだけの設定で十分ですが。最大8台の Sesame デバイスをサポートできます。
```yaml
sesame2mqtt:
  wifi_ssid: "wifi_ssid"
  wifi_password: "wifi_password"
  mqtt_broker_url: "username:password@address:1883" # MQTT Broker URL, for example "mqtt_user:mqtt_pass@192.168.1.69:1883"
```

3. ESPHome WEB UIを開き、"Sesame2MQTT"プロジェクトの右下にある3つの点をクリックします。サブメニューが表示されたら、まずClean Build Filesをクリックして古いバージョンがクリアされていることを確認し、次にInstallをクリックし、Manual downloadを選択します。 <br>
<img src="docs/Images/ESPHome - Sesame2MQTT Install.png" height="400" />
<img src="docs/Images/ESPHome - Manual Download.png" height="400" /><br> <br>

4. ESPHomeはコンパイルを開始し、完了するまでに数分かかります。コンパイルが完了したら、"Modern format"を選択してダウンロードします。ダウンロードされたイメージファイルの名前は sesame2mqtt-factory.bin です。 <br>
<img src="docs/Images/ESPHome Build.png" height="300" />
<img src="docs/Images/ESPHome - Download Format.png" height="300" /><br> <br>

5. ESP32をフラッシュ（flash）する前に、すべてのSesameデバイスをピンでリセットして未登録状態に戻すことを忘れないでください。ESP32 開発ボードから5メートル以内の距離を保ち、これにより Bluetooth の信号品質を確保することができます。これは非常に重要です。

6. [ESPHome Web Dashboard](https://web.esphome.io/?dashboard_install) を通じて、イメージファイルを ESP32-C3-DevKitM-1 にフラッシュ（flash）します。これは現時点で最も安定したフラッシュ方法と考えられており、接続して正しいUSBポートを選択し、インストールするだけです。<br>
(注記1: 現在、ESPHome Web は Chrome およびEdgeブラウザのみをサポートしています。)<br>
(注記2: 初めてフラッシュする場合は、USB to UART のドライバをダウンロードしてインストールする必要があります。)<br>
<img src="docs/Images/ESPHome DashBoard - Main.png" height="300" />
<img src="docs/Images/ESPHome DashBoard - Connect.png" height="300" />
<img src="docs/Images/ESPHome DashBoard - Install.png" height="300" /><br> <br>

これで完了です。次に、ESP32-C3-DevKitM-1 が自動的にすべての Sesame デバイスをスキャンします。ESP32 がスキャンを完了するのを1分間待ち、その後MQTT devices をチェックすると、新しいデバイスが見つかるはずです。現在のエンティティを更新するために "Reload" をクリックすることをお勧めします。もし一部のデバイスがスキャンされなかった場合は心配しないでください。それらを ESP32 に近づけ、ESP32 の USB ケーブルを抜いて再接続すると、スキャンが再開されます。<br>
<img src="docs/Images/MQTT - Devices.png" width="600" /> <br> <br>

もしMQTTが ESP32 にフラッシュ（flash）した後にインストールされた場合、以下のような画面が表示され、新しく発見されたデバイスが表示されます。 <br>
<img src="docs/Images/MQTT - Discovery.png" width="600" /><br> <br>

Sesame 5 デバイスの内容は以下の通りです。 <br>
<img src="docs/Images/MQTT - Sesame 5.png" width="600" /><br> <br>

## 使用方法
1. スマートフォンの Sesame APP でQRコードをスキャンしてデバイスを追加します。これにより、Home Assistant での制御だけでなく、スマートフォンでも制御が可能になります。手順は以下の通りです。
- "Gen QR Code Text"ボタンを押すと、下に生成された QR コードが表示されます。その先頭は "ssm://" となりますㄦ <br>
<img src="docs/Images/MQTT - Gen Code.png" width="300" /><br> <br>

- 使用 [QR Code Generator](https://www.qr-code-generator.com/solutions/text-qr-code/) 生成 QR コード<br>
<img src="docs/Images/QR Code Generator.png" width="600" /><br> <br>

- スマートフォンの Sesame APP を使用して QR コードをスキャンしてください。 <br>
<img src="docs/Images/Sesame APP - Scan QR Code.png" width="300" /><br> <br>

2. 設定 Sesame 5/ 5 Pro<br>
    (1) 水平校正：Sesame 5/5 Proのノブを水平位置に回し、"Horizon Calibration"ボタンを押します。この位置が 0° になります。この手順は、スマートフォンのSesame APPでも実行できます。<br>
    <img src="docs/Images/Sesame 5 - Horizon.png" width="300" /> <br><br>
    
    (2) 上鎖および解鎖の角度を入力し、設定が完了すると、鍵の状態が自動的に更新されます。以下の画像のように、私の上鎖は 160° で、解鎖は 20° です。直接値を入力して上鎖/解鎖の角度を設定することは非常に便利で、外出中でも設定が可能です。もしもある日 Sesame 5 に問題が発生し、外から鍵がかかってしまった場合、この機能が命を救うかもしれません。<br>
    <img src="docs/Images/Sesame 5 - Lock Unlock Position.png" width="300" /> <br>
    <img src="docs/Images/Sesame 5 - Lock 160 Unlock 20.png" width="400" /> <br><br>

3. 設定 Sesame Touch/ Touch Pro<br>
    (1) Sesame 5/5 Pro とのペアリングについては、以下の手順で行います。もしデバイスが合計2台だけの場合、Sesame 5 とTouch1台ずつであれば、ESP32 がスキャンを完了した後に自動的にペアリングされますので、特に手間はかかりません。しかし、デバイスが2台を超える場合は、どのデバイスが正しいペアリング対象かがわからないため、手動でペアリングを行う必要があります。<br>

    (2) Sesame Touch/Touch Pro は Sesame 5/5 Pro の MAC アドレスを使用してペアリングされます。デバイス情報の左上角に MAC アドレスが表示されています。<br>
    <img src="docs/Images/Sesame 5 - MAC address.png" width="300" /> <br> <br>

    (3) Sesame 5/5 Pro の MAC アドレスを "Enter MAC address - Add Sesame" にコピー＆ペーストし、Enter キーを押すとペアリングが開始されます。ESP32 はMACアドレスをチェックし、正しい場合はペアリングを完了します。もちろん、スマートフォンの Sesame APP を使用してペアリングを行うこともできます。<br>
    <img src="docs/Images/Touch - Add Sesame.png" width="300" /> <br> <br>

## 3Dプリントケース
私は3DプリントケースのSTLファイルも用意しました。これには [トップカバー](docs/3D%20case/esp32-c3-devkitm-1-lid.stl) と [ベース](docs/3D%20case/esp32-c3-devkitm-1-base.stl) が含まれます。以下に示すように、アンテナ部分には意図的に開口部を設けています。これは冷却のためだけでなく、RF受信品質を向上させるためでもあります。<br>
<img src="docs/Images/3D Case - 1.png" height="300" />
<img src="docs/Images/3D Case - 2.png" height="300" /><br> <br>

私の ESP32-C3-DevKitM-1 は以下の画像のようです。3D プリントを行う前に、サイズがあなたのものと同じであることを確認してください。異なる場合は、他の適切な3Dモデルを探す必要があります。 <br>
<img src="docs/Images/ESP32-C3-DevKitM-1 Dimension.jpeg" width="300" /><br> <br>

## あとがき
[Sesame2MQTT](https://github.com/js4jiang5/Sesame2MQTT) は「理論上」最大8台のデバイスをサポートできるとされていますが、私は実際にはテストしていません。なぜなら、私は Sesame 5 と Sesame Touch を1台ずつしか持っていないからです。したがって、2台以上のデバイスが期待通りに動作することを保証することはできませんが、もちろん動作することを願っています。また、これは私の初めてのESPHomeプロジェクトであるため、設計が完全に成熟しているとは言えません。信じられますか？2ヶ月前には、ESPHome や ESP-IDF が何であるかさえ知りませんでしたが、今ではアマチュアの開発者になっています。実は、このプロジェクトを始めたのは、CANDY HOUSEのWiFi2 モジュールが長い間在庫切れだったため、やむを得ず彼らの ESP32 デモ版SDKをテストして、Home Assistant に統合できるかどうかを見るためでした。ESP-IDF の開発が完了した後、目的は達成されましたが、それを使用できるのは私だけでした。より多くの人が使用できるようにするために、ESPHome に取り組み始め、一つ一つのステップを踏んで、気づけばこのプロジェクトを完成させていました。人生は本当に予測不可能ですね。