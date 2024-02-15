#ifndef MYLIB_PEOPLE_H
#define MYLIB_PEOPLE_H

typedef struct People {
    int age;
    const char* name;
#ifdef __cplusplus
    People() : age(0), name("Default Name") {}
    void Show() const;
#endif
} People;

#endif  // MYLIB_PEOPLE_H
