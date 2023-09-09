#include "Core.h"
#include "esp_log.h"
#include "esp_mac.h"
#include "esp_system.h"
#include "string.h"

#define DEVICE_ADD_NUMBER(mac, ret, count) \
  for (uint8_t i = 0; i < count; i++)      \
  {                                        \
    ret[i] += mac[i];                      \
  }

const char CharMap[33] = "0123456789ABCDEFGHIKLMNPRSTUVXYZ";

char *GetUniqueDeviceID(uint16_t initVal)
{
  uint8_t mac[6] = {0};
  uint16_t ret[6] = {initVal, initVal, initVal, initVal, initVal, initVal};
  esp_read_mac(mac, ESP_MAC_WIFI_STA);
  DEVICE_ADD_NUMBER(mac, ret, 6);
  esp_read_mac(mac, ESP_MAC_WIFI_SOFTAP);
  DEVICE_ADD_NUMBER(mac, ret, 6);
  esp_read_mac(mac, ESP_MAC_BT);
  DEVICE_ADD_NUMBER(mac, ret, 6);
  esp_read_mac(mac, ESP_MAC_ETH);
  DEVICE_ADD_NUMBER(mac, ret, 6);

  char *DeviceId = (char *)malloc(sizeof(char) * 7);

  for (int i = 0; i < 6; i++)
    DeviceId[i] = CharMap[ret[i] % 32];

  DeviceId[6] = '\0';

  return DeviceId;
}

bool isEscapeChar(char c)
{
  return c == '"';
}

size_t EscapingStringLength(const char *str)
{
  uint16_t length = strlen(str);
  uint16_t count = 0;

  for (size_t i = 0; i < length; i++)
  {
    if (isEscapeChar(str[i]))
      count++;
  }
  return length + count;
}

char *EscapingString(const char *str)
{
  uint16_t srcLength = strlen(str);
  uint16_t escLength = EscapingStringLength(str);

  char *ret = (char *)malloc(sizeof(char) * (escLength + 1));

  uint16_t offset = 0;

  for (size_t i = 0; i < srcLength; i++)
  {
    if (isEscapeChar(str[i]))
    {
      ret[i + offset] = '\\';
      offset++;
    }
    ret[i + offset] = str[i];
  }

  ret[escLength] = '\0';

  return ret;
}

int StringFindeCharIndex(const char *str, char findeChar, int startPos = 0)
{
  int length = strlen(str);
  for (int i = startPos; i < length; i++)
  {
    if (str[i] == findeChar)
      return i;
  }
  return -1;
}

bool CharIsDigit(char c)
{
  return c >= 48 && c <= 57;
}

int findeDigit(char *src, int start, size_t length)
{
  for (size_t i = start; i < length; i++)
  {
    if (CharIsDigit(src[i]))
      return i;
  }

  return -1;
}

int findeEndDigit(char *src, int start, size_t length)
{
  for (size_t i = start; i < length; i++)
  {
    if (!CharIsDigit(src[i]))
      return i;
  }

  return length;
}

bool CharIsWord(char c)
{
  return (c >= 65 && c <= 90) || (c >= 97 && c <= 122);
}

int findeWord(char *src, int start, size_t length)
{
  for (size_t i = start; i < length; i++)
  {
    if (CharIsWord(src[i]))
      return i;
  }

  return -1;
}

int findeEndWord(char *src, int start, size_t length)
{
  for (size_t i = start; i < length; i++)
  {
    if (!CharIsWord(src[i]))
      return i;
  }

  return length;
}

bool cntstr(const char *c1, const char *c2)
{
  size_t length = strlen(c1);
  if (length != strlen(c2))
    return false;
  for (size_t i = 0; i < length; i++)
  {
    if (c1[i] != c2[i])
      return false;
  }
  return true;
}

char *substr(char *src, int start, int length)
{
  char *ret = (char *)malloc(sizeof(char) * (length + 1));
  memcpy(ret, &src[start], length);
  ret[length] = '\0';
  return ret;
}