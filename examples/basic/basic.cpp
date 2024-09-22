/**************************************************
 * Basic sample and tests of EasyPreferences library
 * by @hpsaturn Copyright (C) 2024
**************************************************/

#include <Arduino.h>
#include <EasyPreferences.hpp> 

void showPreferences() {
  Serial.printf("\n%11s \t%s \t%s \r\n", "KEYNAME", "DEFINED", "VALUE");
  Serial.printf("\n%11s \t%s \t%s \r\n", "=======", "=======", "=====");

  for (int i = 0; i < KCOUNT; i++) {
    String key = cfg.getKey((PKEYS)i);
    bool isDefined = cfg.isKey(key);
    String defined = isDefined ? "custom " : "default";
    String value = "";
    if (isDefined) value = cfg.getValue(key);
    Serial.printf("%11s \t%s \t%s \r\n", key.c_str(), defined.c_str(), value.c_str());
  }
}

void clear_preferences() {
  cfg.clear();
  Serial.println("\r\n[preferences cleared]");
}

void start_test() {
  Serial.println("=========================");
  Serial.println("TEST START");
  Serial.println("Current preferences:");
  showPreferences();
  clear_preferences();
}

void end_test() {
  Serial.println("\r\nFinal preferences:");
  showPreferences();
  clear_preferences();
  Serial.println("TEST END");
}

void setup() {
  Serial.begin(115200);
  delay(2000); // for debugging
  Serial.println();

  cfg.init("MyApp");

  start_test();
  Serial.println("\r\n== Float Key tests:");

  float pi = cfg.getFloat(PKEYS::KPINUM, 3.1415);
  Serial.printf("Pi default: %.6f\r\n", pi);
  
  cfg.saveAuto(PKEYS::KPINUM, "3.1415926");
  pi = cfg.getFloat(PKEYS::KPINUM, 3.1415);
  Serial.printf("Pi saveAuto(3.1415926): %.6f\r\n", pi);

  cfg.saveFloat(PKEYS::KPINUM, 3.1415926);
  pi = cfg.getFloat(PKEYS::KPINUM, 3.1415);
  Serial.printf("Pi saveFloat(3.1415926): %.8f\r\n", pi);

  Serial.println("\r\n== Integer Key tests:");

  uint32_t mint = cfg.getInt(PKEYS::KMYINT, 123456);
  Serial.printf("MyInteger default: %i\r\n", mint);

  cfg.saveInt(PKEYS::KMYINT, 98765);
  mint = cfg.getInt(PKEYS::KMYINT, 123456);
  Serial.printf("saveInt(98765): %i\r\n", mint);

  cfg.saveInt(PKEYS::KMYINT, -123456789);
  mint = cfg.getInt(PKEYS::KMYINT, 123456);
  Serial.printf("saveInt(-123456789): %i\r\n", mint);

  cfg.saveInt(PKEYS::KMYINT, 2147483647);
  mint = cfg.getInt(PKEYS::KMYINT, 123456);
  Serial.printf("saveInt(2147483647): %i\r\n", mint);

  cfg.saveAuto(PKEYS::KMYINT, "2147483647");
  mint = cfg.getInt(PKEYS::KMYINT, 123456);
  Serial.printf("saveAuto(2147483647): %i\r\n", mint);

  Serial.println("\r\n== String Key tests:");

  String ms = cfg.getString(PKEYS::KMYSTR, "ABCD");
  Serial.printf("MyString default: %s\r\n", ms);

  cfg.saveString(PKEYS::KMYSTR, "abcdeABCDE1234_-@()\\s");
  ms = cfg.getString(PKEYS::KMYSTR, "ABCD");
  Serial.printf("saveString(\"abcdeABCDE1234_-@()\\s\"): %s\r\n", ms.c_str());

  cfg.saveAuto(PKEYS::KMYSTR, "abcdeABCDE1234_-@()***[]'");
  ms = cfg.getString(PKEYS::KMYSTR, "ABCD");
  Serial.printf("saveAuto(\"abcdeABCDE1234_-@()***[]'\"): %s\r\n", ms.c_str());

  Serial.println("\r\n== Boolean Key tests:");

  bool mb = cfg.getBool(PKEYS::KMBOOL, true);
  Serial.printf("MyBoolean default: %i\r\n", mb);

  cfg.saveBool(PKEYS::KMBOOL, false);
  mb = cfg.getBool(PKEYS::KMBOOL, true);
  Serial.printf("saveBool(false): %i\r\n", mb);

  cfg.saveAuto(PKEYS::KMBOOL, "false");
  mb = cfg.getBool(PKEYS::KMBOOL, true);
  Serial.printf("saveAuto(\"false\"): %i\r\n", mb);

  cfg.saveAuto(PKEYS::KMBOOL, "true");
  mb = cfg.getBool(PKEYS::KMBOOL, true);
  Serial.printf("saveAuto(\"true\"): %i\r\n", mb);

  cfg.saveAuto(PKEYS::KMBOOL, "0");
  mb = cfg.getBool(PKEYS::KMBOOL, true);
  Serial.printf("saveAuto(\"0\"): %i\r\n", mb);

  cfg.saveAuto(PKEYS::KMBOOL, "1");
  mb = cfg.getBool(PKEYS::KMBOOL, true);
  Serial.printf("saveAuto(\"1\"): %i\r\n", mb);

  end_test();
}

void loop() {
}
