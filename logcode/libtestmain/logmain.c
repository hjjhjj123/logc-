#include <stdio.h>
#include "include/oal_log.h"
void main()
{
    LogInit("test", 20*OAL_LOG_1M, 1);
    LOG_DEBUG_FMT("test ");
}
