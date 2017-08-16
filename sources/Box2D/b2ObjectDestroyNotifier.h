#pragma once

#include <stdlib.h>

typedef void (*b2ObjectDestroyNotifer)(void*, const char*);

void b2SetObjectDestroyNotifier(b2ObjectDestroyNotifer notifier);
void b2NotifyObjectDestroyed(void* obj, const char* typeName = NULL);
