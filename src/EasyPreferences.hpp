/**************************************************
 * ESP32Cam
 * ========
 * Config utlility used for general purpose
 * by @hpsaturn Copyright (C) 2024
 * This file is part ESP32S3 camera tests project:
 * https://github.com/hpsaturn/esp32s3-cam
**************************************************/

#ifndef EasyPreferences_hpp
#define EasyPreferences_hpp

#include <Preferences.h>
#include "esp_mac.h"
#include <mutex>

#define EPV_VERSION "0.1.4"
#define EPV_REVISION 014

#define RW_MODE false
#define RO_MODE true

typedef enum {
    INT, UINT, SHORT, DOUBLE, BOOL, FLOAT, STRING, UNKNOWN
} ConfKeyType;

#include <preferences-keys.h>

/*******************************
You should first define your "preferences-key.h" in
your lib directory with your keys with something like that:

#define CONFIG_KEYS_LIST         \
  X(KPWRON, "PowerOn", INT)      \
  X(KPINUM, "PiNumber", FLOAT)   \
  X(KDEBUG, "debug", BOOL)      \
  X(KBASIC, "-----", UNKNOWN)    \
  X(KCOUNT, "KCOUNT", UNKNOWN)

*********************************/

#define X(kname, kreal, ktype) kname,
typedef enum PKEYS : size_t { CONFIG_KEYS_LIST } CONFKEYS; 
#undef X

class EasyPreferences {
   public:
    uint64_t chipid;
    String deviceId;
    String dname;
    bool devmode;
    
    void init(const char app_name[]);

    void saveInt(String key, int32_t value);
    void saveInt(CONFKEYS key, int32_t value);

    int32_t getInt(String key, int32_t defaultValue);
    int32_t getInt(CONFKEYS key, int32_t defaultValue);

    void saveUInt(String key, uint32_t value);
    void saveUInt(CONFKEYS key, uint32_t value);

    uint32_t getUInt(String key, uint32_t defaultValue);
    uint32_t getUInt(CONFKEYS key, uint32_t defaultValue);

    void saveShort(String key, int16_t value);
    void saveShort(CONFKEYS key, int16_t value);

    int16_t getShort(String key, int16_t defaultValue);
    int16_t getShort(CONFKEYS key, int16_t defaultValue);
    
    void saveDouble(String key, double_t value);
    void saveDouble(CONFKEYS key, double_t value);

    double_t getDouble(String key, double_t defaultValue);
    double_t getDouble(CONFKEYS key, double_t defaultValue);

    bool getBool(String key, bool defaultValue);
    bool getBool(CONFKEYS key, bool defaultValue);

    void saveBool(String key, bool value);
    void saveBool(CONFKEYS key, bool value);

    float_t getFloat(String key, float_t defaultValue = 0.0);
    float_t getFloat(CONFKEYS key, float_t defaultValue = 0.0);

    void saveFloat(String key, float_t value);
    void saveFloat(CONFKEYS key, float_t value);

    void saveString(String key, String value);
    void saveString(CONFKEYS key, String value);

    String getString(String key, String defaultValue);
    String getString(CONFKEYS key, String defaultValue);

    String getValue(String key);

    String getDeviceId();

    String getDeviceIdShort();

    PreferenceType keyType(String key);

    bool isKey(String key);
    
    bool isKey(CONFKEYS key);

    bool isValidKey(String key);

    String getKey(CONFKEYS key);

    ConfKeyType getKeyType(String key);

    ConfKeyType getKeyType(CONFKEYS key);

    bool saveAuto(String key, String v);
    bool saveAuto(CONFKEYS key, String v);

    void clear();
    
   private:  
    /// mutex for R/W actions
    std::mutex config_mtx;
    ///preferences main key
    char* _app_name;
    ///ESP32 preferences abstraction
    Preferences preferences;

    // void DEBUG(const char* text, const char* textb = "");

    // @todo use DEBUG_ESP_PORT ?
#ifdef WM_DEBUG_PORT
    Stream& _debugPort = WM_DEBUG_PORT;
#else
    Stream& _debugPort = Serial;  // debug output stream ref
#endif
};

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_CFGHANDLER)
extern EasyPreferences cfg;
#endif

#endif
