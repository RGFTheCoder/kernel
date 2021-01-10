#pragma once
#include <types/ints.hh>

extern const char *decimalCharset;
extern const char *hexCharset;

size_t strLen(const char *str);

const char *padLeft(const char *str, u8 targetLength, char padding = ' ');

const char *toString(u64 value, const char *dict = decimalCharset);
const char *toString(i64 value, const char *dict = decimalCharset);
inline const char *toHString(u64 value) { return padLeft(toString((u64)value, hexCharset), 16, '0'); };
inline const char *toHString(ul value) { return padLeft(toString((u64)value, hexCharset), sizeof(ul) * 2, '0'); };
inline const char *toHString(u32 value) { return padLeft(toString((u64)value, hexCharset), 8, '0'); };
inline const char *toHString(u16 value) { return padLeft(toString((u64)value, hexCharset), 4, '0'); };
inline const char *toHString(u8 value) { return padLeft(toString((u64)value, hexCharset), 2, '0'); };
inline const char *toHString(i64 value) { return padLeft(toString((u64)value, hexCharset), 16, '0'); };
inline const char *toHString(il value) { return padLeft(toString((u64)value, hexCharset), sizeof(il) * 2, '0'); };
inline const char *toHString(i32 value) { return padLeft(toString((u64)value, hexCharset), 8, '0'); };
inline const char *toHString(i16 value) { return padLeft(toString((u64)value, hexCharset), 4, '0'); };
inline const char *toHString(i8 value) { return padLeft(toString((u64)value, hexCharset), 2, '0'); };

const char *toString(double value, u8 decimalPlaces = 5, const char *dict = decimalCharset);