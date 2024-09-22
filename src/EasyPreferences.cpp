/**************************************************
 * EasyPreferences Library
 * =======================
 * Config utlility used for general purpose
 * by @hpsaturn Copyright (C) 2024
 * Migrated from CanAirIO project
**************************************************/

#include "EasyPreferences.hpp"

#define X(kname, kreal, ktype) kreal, 
char const *keys[] = { CONFIG_KEYS_LIST };
#undef X

#define X(kname, kreal, ktype) ktype, 
int keys_type[] = { CONFIG_KEYS_LIST };
#undef X

void EasyPreferences::init(const char app_name[]) {
    _app_name = new char[strlen(app_name) + 1];
    strcpy(_app_name, app_name);
    chipid = ESP.getEfuseMac();
    deviceId = getDeviceId();
    // override with debug INFO level (>=3)
#if CORE_DEBUG_LEVEL >= 1
    devmode = true;
#endif
    log_i("debug mode:\t%s\r\n", devmode ? "enable" : "disable");
}

void EasyPreferences::saveString(String key, String value){
    std::lock_guard<std::mutex> lck(config_mtx);
    preferences.begin(_app_name, RW_MODE);
    preferences.putString(key.c_str(), value.c_str());
    preferences.end();
}

void EasyPreferences::saveString(CONFKEYS key, String value){
    saveString(getKey(key),value);
}

String EasyPreferences::getString(String key, String defaultValue){
    std::lock_guard<std::mutex> lck(config_mtx);
    preferences.begin(_app_name, RO_MODE);
    String out = preferences.getString(key.c_str(), defaultValue);
    preferences.end();
    return out;
}

String EasyPreferences::getString(CONFKEYS key, String defaultValue){
    return getString(getKey(key),defaultValue);
}

void EasyPreferences::saveInt(String key, int32_t value){
    std::lock_guard<std::mutex> lck(config_mtx);
    preferences.begin(_app_name, RW_MODE);
    preferences.putInt(key.c_str(), value);
    preferences.end();
}

void EasyPreferences::saveInt(CONFKEYS key, int32_t value){
    saveInt(getKey(key),value);
}

int32_t EasyPreferences::getInt(String key, int32_t defaultValue){
    std::lock_guard<std::mutex> lck(config_mtx);
    preferences.begin(_app_name, RO_MODE);
    int32_t out = preferences.getInt(key.c_str(), defaultValue);
    preferences.end();
    return out;
}

int32_t EasyPreferences::getInt(CONFKEYS key, int32_t defaultValue){ 
    return getInt(getKey(key),defaultValue);
}

void EasyPreferences::saveUInt(String key, uint32_t value){
    std::lock_guard<std::mutex> lck(config_mtx);
    preferences.begin(_app_name, RW_MODE);
    preferences.putUInt(key.c_str(), value);
    preferences.end();
}

void EasyPreferences::saveUInt(CONFKEYS key, uint32_t value){
    saveUInt(getKey(key),value);
}

uint32_t EasyPreferences::getUInt(String key, uint32_t defaultValue){
    std::lock_guard<std::mutex> lck(config_mtx);
    preferences.begin(_app_name, RO_MODE);
    uint32_t out = preferences.getUInt(key.c_str(), defaultValue);
    preferences.end();
    return out;
}

uint32_t EasyPreferences::getUInt(CONFKEYS key, uint32_t defaultValue){ 
    return getUInt(getKey(key),defaultValue);
}

void EasyPreferences::saveShort(String key, int16_t value){
    std::lock_guard<std::mutex> lck(config_mtx);
    preferences.begin(_app_name, RW_MODE);
    preferences.putShort(key.c_str(), value);
    preferences.end();
}

void EasyPreferences::saveShort(CONFKEYS key, int16_t value){
    saveShort(getKey(key),value);
}

int16_t EasyPreferences::getShort(String key, int16_t defaultValue){
    std::lock_guard<std::mutex> lck(config_mtx);
    preferences.begin(_app_name, RO_MODE);
    int16_t out = preferences.getShort(key.c_str(), defaultValue);
    preferences.end();
    return out;
}

int16_t EasyPreferences::getShort(CONFKEYS key, int16_t defaultValue){ 
    return getShort(getKey(key),defaultValue);
}

void EasyPreferences::saveDouble(String key, double_t value){
    std::lock_guard<std::mutex> lck(config_mtx);
    preferences.begin(_app_name, RW_MODE);
    preferences.putDouble(key.c_str(), value);
    preferences.end();
}

void EasyPreferences::saveDouble(CONFKEYS key, double_t value){
    saveDouble(getKey(key),value);
}

double_t EasyPreferences::getDouble(String key, double_t defaultValue){
    std::lock_guard<std::mutex> lck(config_mtx);
    preferences.begin(_app_name, RO_MODE);
    double_t out = preferences.getDouble(key.c_str(), defaultValue);
    preferences.end();
    return out;
}

double_t EasyPreferences::getDouble(CONFKEYS key, double_t defaultValue){ 
    return getDouble(getKey(key),defaultValue);
}

void EasyPreferences::saveBool(String key, bool value){
    std::lock_guard<std::mutex> lck(config_mtx);
    preferences.begin(_app_name, RW_MODE);
    preferences.putBool(key.c_str(), value);
    preferences.end();
}

void EasyPreferences::saveBool(CONFKEYS key, bool value){
    saveBool(getKey(key),value);
}

bool EasyPreferences::getBool(String key, bool defaultValue){
    std::lock_guard<std::mutex> lck(config_mtx);
    preferences.begin(_app_name, RO_MODE);
    bool out = preferences.getBool(key.c_str(), defaultValue);
    preferences.end();
    return out;
}

bool EasyPreferences::getBool(CONFKEYS key, bool defaultValue){
    return getBool(getKey(key),defaultValue);
}

void EasyPreferences::saveFloat(String key, float_t value){
    std::lock_guard<std::mutex> lck(config_mtx);
    preferences.begin(_app_name, RW_MODE);
    preferences.putFloat(key.c_str(), value);
    preferences.end();
}

void EasyPreferences::saveFloat(CONFKEYS key, float_t value){
    saveFloat(getKey(key),value);
}

float_t EasyPreferences::getFloat(String key, float_t defaultValue){
    std::lock_guard<std::mutex> lck(config_mtx);
    preferences.begin(_app_name, RO_MODE);
    float_t out = preferences.getFloat(key.c_str(), defaultValue);
    preferences.end();
    return out;
}

float_t EasyPreferences::getFloat(CONFKEYS key, float_t defaultValue){
    return getFloat(getKey(key),defaultValue);
}

PreferenceType EasyPreferences::keyType(String key) {
    std::lock_guard<std::mutex> lck(config_mtx);
    preferences.begin(_app_name, RO_MODE);
    PreferenceType type = preferences.getType(key.c_str());
    preferences.end();
    return type;
}

bool EasyPreferences::isKey(String key) {
    std::lock_guard<std::mutex> lck(config_mtx);
    preferences.begin(_app_name, RO_MODE);
    bool iskey = preferences.isKey(key.c_str());
    preferences.end();
    return iskey;
}

bool EasyPreferences::isKey(CONFKEYS key) {
    return isKey(getKey(key));
}

bool EasyPreferences::isValidKey(String key) {
  for (int i = 0; i < KCOUNT; i++) {
    if (key.equals(cfg.getKey((CONFKEYS)i))) return true;
  }
  return false;
}

void saveBoolAuto(String key, String v) {
  v.toLowerCase();
  cfg.saveBool(key, v.equals("on") || v.equals("1") || v.equals("enable") || v.equals("true"));
  log_i("saved: %s:%s\r\n", key.c_str(), cfg.getBool(key, false) ? "true" : "false");
}

void saveIntegerAuto(String key, String v) {
  int32_t value = v.toInt();
  cfg.saveInt(key, value);
  log_i("saved: %s:%i\r\n",key.c_str(),value);
}

void saveFloatAuto(String key, String v) {
  float_t value = v.toFloat();
  cfg.saveFloat(key, value);
  log_i("saved: %s:%.5f\r\n",key.c_str(),value);
}

void saveShortAuto(String key, String v) {
  int16_t value = v.toInt();
  cfg.saveShort(key, value);
  log_i("saved: %s:%i\r\n",key.c_str(),value);
}

void saveDoubleAuto(String key, String v) {
  double_t value = v.toDouble();
  cfg.saveDouble(key, value);
  log_i("saved: %s:%f\r\n",key.c_str(),value);
}

void saveUIntAuto(String key, String v) {
  uint32_t value = v.toInt();
  cfg.saveUInt(key, value);
  log_i("saved: %s:%u\r\n",key.c_str(),value);
}

bool EasyPreferences::saveAuto(CONFKEYS key, String v) {
  return saveAuto(getKey(key),v);
}

bool EasyPreferences::saveAuto(String key, String v) {
  if(cfg.isValidKey(key)){
    if(cfg.getKeyType(key) == ConfKeyType::BOOL) saveBoolAuto(key,v);
    else if(cfg.getKeyType(key) == ConfKeyType::FLOAT) saveFloatAuto(key,v);
    else if(cfg.getKeyType(key) == ConfKeyType::INT) saveIntegerAuto(key,v);
    else if(cfg.getKeyType(key) == ConfKeyType::UINT) saveUIntAuto(key,v);
    else if(cfg.getKeyType(key) == ConfKeyType::SHORT) saveShortAuto(key,v);
    else if(cfg.getKeyType(key) == ConfKeyType::DOUBLE) saveDoubleAuto(key,v);
    else if(cfg.getKeyType(key) == ConfKeyType::STRING) cfg.saveString(key,v);
    else {
      log_e("Invalid key action for: %s",key.c_str());
      return false;
    }
    return true;
  }
  else {
    log_e("invalid key: %s\r\nPlease set a registered key.\r\n",key.c_str());
    return false;
  }
}

String EasyPreferences::getKey(CONFKEYS key) {
  if (key < 0 || key > CONFKEYS::KCOUNT) return "";
  return String(keys[key]);
}

ConfKeyType EasyPreferences::getKeyType(CONFKEYS key) {
  if (key < 0 || key > CONFKEYS::KCOUNT) return ConfKeyType::UNKNOWN;
  return (ConfKeyType)keys_type[key];
}

ConfKeyType EasyPreferences::getKeyType(String key) {
  for (int i = 0; i < KCOUNT; i++) {
    if (key.equals(keys[i])) return (ConfKeyType)keys_type[i];
  }
  return ConfKeyType::UNKNOWN;
}

String EasyPreferences::getValue(String key) {
  ConfKeyType type = cfg.getKeyType(key);
  if (type == ConfKeyType::BOOL) return cfg.getBool(key, false) ? "true" : "false";
  if (type == ConfKeyType::FLOAT) return String(cfg.getFloat(key, false), 8);
  if (type == ConfKeyType::INT) return String(cfg.getInt(key, false));
  if (type == ConfKeyType::UINT) return String(cfg.getUInt(key, false));
  if (type == ConfKeyType::SHORT) return String(cfg.getShort(key, false));
  if (type == ConfKeyType::DOUBLE) return String(cfg.getDouble(key, false), 8);
  if (type == ConfKeyType::STRING) return cfg.getString(key, "");
  return "";
}

String EasyPreferences::getDeviceId() {
    uint8_t baseMac[6];
    // Get MAC address for WiFi station
    esp_read_mac(baseMac, ESP_MAC_WIFI_STA);
    char baseMacChr[19] = {0};
    sprintf(baseMacChr, "%02X:%02X:%02X:%02X:%02X:%02X", baseMac[0], baseMac[1], baseMac[2], baseMac[3], baseMac[4], baseMac[5]+2);
    return String(baseMacChr);
}

String EasyPreferences::getDeviceIdShort() {
    String devId = getDeviceId();
    devId = devId.substring(13);
    devId.replace(":","");
    return devId;
}

void EasyPreferences::clear() {
    std::lock_guard<std::mutex> lck(config_mtx);
    preferences.begin(_app_name, RW_MODE);
    preferences.clear();
    preferences.end();
    log_i("clear settings cleared!");
}

// void EasyPreferences::DEBUG(const char *text, const char *textb) {
//     if (devmode) {
//         _debugPort.print(text);
//         if (textb) {
//             _debugPort.print(" ");
//             _debugPort.print(textb);
//         }
//         _debugPort.println();
//     }
// }

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_CFGHANDLER)
EasyPreferences cfg;
#endif
