#include <Arduino.h>

typedef unsigned char byte;

typedef struct {
  byte red;
  byte green;
  byte blue;
} rgb;

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
