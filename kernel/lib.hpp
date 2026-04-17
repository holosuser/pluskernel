#pragma once

extern volatile char* vimem;
extern int cursor;

void print(const char* str);
void clearscreen();
void startlogo();
