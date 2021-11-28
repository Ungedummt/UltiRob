#ifndef	RGB_H
#define RGB_H

#include <Arduino.h>

typedef unsigned char byte;

const char HEX_LOOKUPTABLE [17] = "0123456789ABCDEF";

typedef struct {
  byte red;
  byte green;
  byte blue;
} rgb;

String rgb_to_hex_string(rgb RGB) {
  char hex[6] = {};

  byte mask_1 = 0b11110000;
  byte mask_2 = 0b00001111;

  hex[0] = HEX_LOOKUPTABLE[(mask_1 & RGB.red) >> 4];
  hex[1] = HEX_LOOKUPTABLE[ mask_2 & RGB.red ];

  hex[2] = HEX_LOOKUPTABLE[(mask_1 & RGB.green) >> 4];
  hex[3] = HEX_LOOKUPTABLE[ mask_2 & RGB.green ];

  hex[4] = HEX_LOOKUPTABLE[(mask_1 & RGB.blue) >> 4];
  hex[5] = HEX_LOOKUPTABLE[ mask_2 & RGB.blue ];

  String str = "";
  for (uint8_t i = 0; i < 6; i++) {
    str += hex[i];
  }

  return String(str);
}

String rgb_to_char_array(rgb *RGB) {
  String str;
  str.concat((char) RGB->red);
  str.concat((char) RGB->green);
  str.concat((char) RGB->blue);
  return str;
}

char hex_string_to_hex(String string) {
  return strtol(string.c_str(), NULL, 16);
}

void rgb_set(rgb *RGB, byte red, byte green, byte blue) {
  RGB->red   = red;
  RGB->green = green;
  RGB->blue  = blue;
}

void rgb_print(byte red, byte green, byte blue) {
  Serial.print("[red: ");
  Serial.print(red);
  Serial.print(", green: ");
  Serial.print(green);
  Serial.print(", blue: ");
  Serial.print(blue);
  Serial.print("]");
}

void rgb_print(rgb *RGB) {
  rgb_print(RGB->red, RGB->green, RGB->blue);
}

void rgb_print(rgb RGB) {
  rgb_print(&RGB);
}

String rgb_to_string(String prefix, rgb *RGB) {
  prefix.concat((char) 0);
  prefix.concat((char) 255);
  prefix.concat((char) 0);
  return prefix;
}

rgb rgb_hex_to_rgb(String rgb_string) {
  rgb RGB;
  RGB.red   = hex_string_to_hex(rgb_string.substring(0,2));
  RGB.green = hex_string_to_hex(rgb_string.substring(2,4));
  RGB.blue  = hex_string_to_hex(rgb_string.substring(4,6));
  return RGB;
}

rgb rgb_hex_string_to_rgb(String rgb_string) {
  return rgb_hex_to_rgb(rgb_string.substring(1,7));
}

String rgb_hex_to_string(String prefix, String rgb_string) {
  prefix.concat((char) hex_string_to_hex(rgb_string.substring(0,2)));
  prefix.concat((char) hex_string_to_hex(rgb_string.substring(2,4)));
  prefix.concat((char) hex_string_to_hex(rgb_string.substring(4,6)));
  return prefix;
}

String rgb_to_string(String prefix, char red, char green, char blue) {
  prefix.concat(red);
  prefix.concat(green);
  prefix.concat(blue);
  return prefix;
}

String rgb_hex_string_to_string(String prefix, String rgb_string) {
  return rgb_hex_to_string(prefix, rgb_string.substring(1,7));
}

String rgb_hex_string_to_string(String rgb_string) {
  return rgb_hex_to_string("", rgb_string.substring(1,7));
}

#endif
