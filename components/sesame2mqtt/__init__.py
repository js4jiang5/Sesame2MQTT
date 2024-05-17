import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID

CONF_MQTT_BROKER_URL = 'mqtt_broker_url'
CONF_WIFI_SSID = 'wifi_ssid'
CONF_WIFI_PASSWORD = 'wifi_password'
CONF_NUMBER_DEVICES = 'number_devices'

CONFLICTS_WITH = ['esp32_ble_tracker']

sesame2mqtt_ns = cg.esphome_ns.namespace("sesame2mqtt")
Sesame = sesame2mqtt_ns.class_("Sesame", cg.Component)

CONFIG_SCHEMA = cv.Schema({
  cv.GenerateID(): cv.declare_id(Sesame),
  cv.Required(CONF_MQTT_BROKER_URL): cv.string,
  cv.Required(CONF_WIFI_SSID): cv.string,
  cv.Required(CONF_WIFI_PASSWORD): cv.string,
  cv.Optional(CONF_NUMBER_DEVICES, default=8): cv.int_range(min=1, max=8),
}).extend(cv.COMPONENT_SCHEMA)

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    if CONF_NUMBER_DEVICES not in config:
        cg.add(var.init(config[CONF_MQTT_BROKER_URL], config[CONF_WIFI_SSID], config[CONF_WIFI_PASSWORD]))
    else:
        cg.add(var.init(config[CONF_MQTT_BROKER_URL], config[CONF_WIFI_SSID], config[CONF_WIFI_PASSWORD], config[CONF_NUMBER_DEVICES]))