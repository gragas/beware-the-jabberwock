#ifndef _SERIALIZE_UTILS_H
#define _SERIALIZE_UTILS_H

#include "utils.h"
#include "son.h"

son_t* create_son(char* name, float x, float y);
void save_son(son_t* son);
son_t* load_son(char* name);

#endif
