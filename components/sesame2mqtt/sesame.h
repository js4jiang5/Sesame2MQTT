#ifndef __SESAME_H__
#define __SESAME_H__

#include "blecent.h"
#include "mqtt_section.h"
#include "nvs_flash.h"
#include "ssm_cmd.h"
#include "wifi_section.h"
#include <cstdlib>
#include <esp_log.h>
#include <string>
#include "esphome.h"
#include "esphome/core/component.h"

using std::string;

namespace esphome {
namespace sesame2mqtt {

class Sesame : public Component {
    private:
    public:
        Sesame(){}; // constructor
        void loop(void);
        void init(string mqtt_broker_url, string wifi_ssid, string wifi_password);
        void init(string mqtt_broker_url, string wifi_ssid, string wifi_password, int number_devices);
        void pass_to_libsesame2mqtt(string mqtt_broker_url, string wifi_ssid, string wifi_password, int number_devices);
        ~Sesame(); // destructor
    };
} // namespace sesame2mqtt
} // namespace esphome

#endif // __SESAME_H__