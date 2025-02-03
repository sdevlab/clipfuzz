/* HEARDER DECL */
#include <stddef.h>

#include <openthread/instance.h>
#include <openthread/ip6.h>
#include <openthread/link.h>
#include <openthread/message.h>
#include <openthread/srp_server.h>
#include <openthread/tasklet.h>
#include <openthread/thread.h>
#include <openthread/thread_ftd.h>
#include <openthread/platform/alarm-milli.h>

#include "fuzzer_platform.h"
#include "common/code_utils.hpp"
#include "common/time.hpp"
/* ~HEARDER DECL */

#define MAX_BUFFER_SIZE 1048576

/* FUZZ_WRITE */
#include "string.h"
#include "stdlib.h"
/* ~FUZZ_WRITE */

/* global variable/function */
void AdvanceTime(otInstance *aInstance, uint32_t aDuration)
{
    uint32_t time = otPlatAlarmMilliGetNow() + aDuration;

    while (ot::TimeMilli(otPlatAlarmMilliGetNow()) <= ot::TimeMilli(time))
    {
        while (otTaskletsArePending(aInstance))
        {
            otTaskletsProcess(aInstance);
        }

        FuzzerPlatformProcess(aInstance);
    }
}
/* ~global variable/function */

