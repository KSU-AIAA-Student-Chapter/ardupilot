#include <AP_HAL.h>
#include <AP_HAL_AVR.h>
#include <AP_HAL_AVR_SITL.h>
#include <AP_HAL_PX4.h>
#include <AP_HAL_Empty.h>
#include <AP_Common.h>
#include <AP_Baro.h>
#include <AP_ADC.h>
#include <GCS_MAVLink.h>
#include <AP_Compass.h>
#include <AP_Declination.h>
#include <SITL.h>
#include <Filter.h>
#include <AP_Param.h>
#include <AP_Progmem.h>
#include <AP_Math.h>

const AP_HAL::HAL& hal = AP_HAL_BOARD_DRIVER;

void setup(void) {
    hal.console->println_P(PSTR("Starting Printf test"));
}

static const struct {
    const char *fmt;
    float v;
    const char *result;
} float_tests[] = {
    { "%f", 3.71f, "3.710000" },
    { "%.1f", 3.71f, "3.7" },
    { "%.1f", 3.75f, "3.8" },
    { "%.2f", 3.75f, "3.75" },
    { "%.7f", 3.75f, "3.7500000" }
};

static void test_printf(void)
{
    uint8_t i;
    char buf[30];
    uint8_t failures = 0;
    hal.console->printf("Running printf tests\n");
    for (i=0; i<sizeof(float_tests)/sizeof(float_tests[0]); i++) {
        hal.util->snprintf(buf, sizeof(buf), float_tests[i].fmt, float_tests[i].v);
        if (strcmp(buf, float_tests[i].result) != 0) {
            hal.console->printf("Failed float_tests[%u] '%s' -> '%s'\n", 
                                (unsigned)i, 
                                float_tests[i].fmt,
                                buf);
            failures++;
        }
    }
    hal.console->printf("%u failures\n", (unsigned)failures);
}

void loop(void) 
{	
    test_printf();
    hal.scheduler->delay(1000);
}

AP_HAL_MAIN();