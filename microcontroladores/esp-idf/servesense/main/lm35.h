#ifndef LM35_H
#define LM35_H

#include <stdbool.h>

void lm35_init(void);
float lm35_read_celsius(void);
bool lm35_is_over_limit(void);

#endif
