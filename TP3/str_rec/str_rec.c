#include "str_rec.h"

char *str_chr(const char *s, int c) {
    if (*s == '\0') {
      if (c == '\0'){
        return (char *)s;
      }

    return nullptr;
    }
    if(*s == (char)c){
      return (char*)s;
    }
    return str_chr(s + 1 , c);
}

char *str_pbrk(const char *s1, const char *s2) {
    if (*s1 == '\0') {
        return nullptr;
    }
    if(str_chr(s2, *s1) != nullptr){
        return (char*)s1;
    }
    return str_pbrk(s1 + 1, s2);
}

char *str_rchr(const char *s, int c) {
    if (*s == '\0') {
        return nullptr;
    }

    char *found = str_rchr(s + 1, c);
    if (found) {
        return found;
    }

    if (*s == (char)c) {
        return (char *)s;
    }
    return nullptr;
}

size_t str_spn(const char *s1, const char *s2) {
    if (*s1 == '\0' || str_chr(s2, *s1) == nullptr) {
        return 0;
    }
    return 1 + str_spn(s1 + 1, s2);
}
