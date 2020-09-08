#include "../inc/libmx.h"

void mx_print_unicode(wchar_t c) {
    int len = 0;
    char res[4];

    if (c < 0x80) {
        len = 1;
        res[0] = (c >> 0 & 0x7F) | 0x00;
    }
    else if (c < 0x0800) {
        len = 2;
        res[0] = (c >> 6 & 0x1F) | 0xC0;
        res[1] = (c >> 0 & 0x3F) | 0x80;
    }
    else if (c < 0x010000) {
        len = 3;
        res[0] = (c >> 12 & 0x0F) | 0xE0;
        res[1] = (c >> 6 & 0x3F) | 0x80;
        res[2] = (c >> 0 & 0x3F) | 0x80;
    }
    else if (c < 0x110000) {
        len = 4;
        res[0] = (c >> 18 & 0x07) | 0xF0;
        res[1] = (c >> 12 & 0x3F) | 0x80;
        res[2] = (c >> 6 & 0x3F) | 0x80;
        res[3] = (c >> 0 & 0x3F) | 0x80;
    }
    write(1, &res, len);
}
