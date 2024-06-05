#include "sesame.h"
#include "esp_task_wdt.h"

static const char * TAG = "sesame.cpp";

using namespace std;
using namespace esphome;

static void ssm_action_handle(sesame * ssm) {
	ESP_LOGI(TAG, "[%s_action_handle][ssm status: %s]", SSM_PRODUCT_TYPE_STR(ssm->product_type), SSM_STATUS_STR(ssm->device_status));

	// mqtt
	if (ssm->mqtt_discovery_done) {
		ESP_LOGI(TAG, "[%s_action_handle][ssm status: %s]", SSM_PRODUCT_TYPE_STR(ssm->product_type), SSM_STATUS_STR(ssm->device_status));
		char buffer[200];
		int cnt = 0;
		int msg_id = 0;
		char topic[80] = "";
		if (ssm->product_type == SESAME_5 || ssm->product_type == SESAME_5_PRO) {
			cnt += sprintf(buffer + cnt, "{ ");
			if (ssm->mech_status.is_clutch_failed) {
				cnt += sprintf(buffer + cnt, "\"state\": \"JAMMED\", ");
			} else {
				if (ssm->mech_status.is_lock_range)
					cnt += sprintf(buffer + cnt, "\"state\": \"LOCK\", ");
				else if (ssm->mech_status.is_unlock_range)
					cnt += sprintf(buffer + cnt, "\"state\": \"UNLOCK\", ");
				else
					cnt += sprintf(buffer + cnt, "\"state\": \"MOVING\", ");
			}

			cnt += sprintf(buffer + cnt, "\"battery\": %.1f, ", ssm->battery_percentage);
			cnt += sprintf(buffer + cnt, "\"position\": %d, ", ssm->mech_status.position);
			cnt += sprintf(buffer + cnt, "\"lock_position\": %d, ", ssm->mech.lock_unlock.lock);
			cnt += sprintf(buffer + cnt, "\"unlock_position\": %d }", ssm->mech.lock_unlock.unlock);
			memset(topic, 0, sizeof(topic));
			sprintf(topic, "homeassistant/%s/state", ssm->topic);				  // state topic
			msg_id = esp_mqtt_client_publish(client_ssm, topic, buffer, 0, 2, 1); // QOS 2, retain 1
		} else if (ssm->product_type == SESAME_TOUCH || ssm->product_type == SESAME_TOUCH_PRO) {
			cnt += sprintf(buffer + cnt, "{ ");
			cnt += sprintf(buffer + cnt, "\"battery\": %.1f, ", ssm->battery_percentage);
			cnt += sprintf(buffer + cnt, "\"add_card\": %d, ", ssm->add_card);
			cnt += sprintf(buffer + cnt, "\"add_finger\": %d, ", ssm->add_finger);
			cnt += sprintf(buffer + cnt, "\"connect\": %d }", (ssm->device_status > SSM_CONNECTED));
			memset(topic, 0, sizeof(topic));
			sprintf(topic, "homeassistant/%s/state", ssm->topic);				  // state topic
			msg_id = esp_mqtt_client_publish(client_ssm, topic, buffer, 0, 2, 1); // QOS 2, retain 1
		}
		ESP_LOGI(TAG, "%s sent publish successful, msg_id=%d", SSM_PRODUCT_TYPE_STR(ssm->product_type), msg_id);
		//if (wait_published(msg_id) == 0) {
		//	ESP_LOGW(TAG, "topic = %s, product_type = %s, buffer = %s", topic, SSM_PRODUCT_TYPE_STR(ssm->product_type), buffer);
		//} else {
		//	ESP_LOGI(TAG, "topic = %s, product_type = %s, buffer = %s", topic, SSM_PRODUCT_TYPE_STR(ssm->product_type), buffer);
		//}
	}
}

namespace esphome {
namespace sesame2mqtt {

void Sesame::pass_to_libsesame2mqtt(string mqtt_broker_url, string wifi_ssid, string wifi_password, int number_devices) {
	real_num_ssms = (number_devices <= 8) ? number_devices : 8;
	memset(config_broker_url, 0, sizeof(config_broker_url));
	sprintf(config_broker_url, "mqtt://%s", mqtt_broker_url.c_str());
	memset(config_wifi_ssid, 0, sizeof(config_wifi_ssid));
	sprintf(config_wifi_ssid, "%s", wifi_ssid.c_str());
	memset(config_wifi_password, 0, sizeof(config_wifi_password));
	sprintf(config_wifi_password, "%s", wifi_password.c_str());
}

void Sesame::init(string mqtt_broker_url, string wifi_ssid, string wifi_password) {
	init(mqtt_broker_url, wifi_ssid, wifi_password, 8); // default is 8 devices
}

void Sesame::init(string mqtt_broker_url, string wifi_ssid, string wifi_password, int number_devices) {
	start_timer();
	ESP_LOGI(TAG, "SesameSDK_ESP32 [11/24][087]");
	pass_to_libsesame2mqtt(mqtt_broker_url, wifi_ssid, wifi_password, number_devices); // pass component parameters to libsesame2mqtt
	nvs_flash_init();
	wifi_init_sta();
	mqtt_start();
	ssm_init(ssm_action_handle);
	esp_ble_init();
}

void Sesame::loop(void) {
}

Sesame::~Sesame() {
    free(p_ssms_env);
}
} // namespace sesame2mqtt
} // namespace esphome