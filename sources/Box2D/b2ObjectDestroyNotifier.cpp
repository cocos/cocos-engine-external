#include "b2ObjectDestroyNotifier.h"

static b2ObjectDestroyNotifer __objectDestroyNotifier = NULL;

void b2SetObjectDestroyNotifier(b2ObjectDestroyNotifer notifier)
{
    __objectDestroyNotifier = notifier;
}

void b2NotifyObjectDestroyed(void* obj, const char* typeName /* = NULL */)
{
    if (__objectDestroyNotifier != NULL)
    {
        __objectDestroyNotifier(obj, typeName);
    }
}
