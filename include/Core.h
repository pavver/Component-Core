#pragma once

#include <stdio.h>

char *GetUniqueDeviceID(uint16_t initVal = 0);

char *RemovingString(const char *str);

char *EscapingString(const char *str);

int StringFindeCharIndex(const char *str, char findeChar, int startPos);

bool CharIsDigit(char c);

bool CharIsWord(char c);

bool cmpstr(const char *c1, const char *c2);

char *substr(char *src, int start, int length);

int findeDigit(char *src, int start, size_t length);

int findeEndDigit(char *src, int start, size_t length);

int findeWord(char *src, int start, size_t length);

int findeEndWord(char *src, int start, size_t length);
