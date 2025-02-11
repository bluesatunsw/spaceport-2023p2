// System.cpp
// Manages all device accesses and IO in a fault-resilient way.
// Failed devices are automatically brought offline and regularly
// retested. Active devices have their readings checked regularly.
// Matt Rossouw (omeh-a)
// 05/2023

#include "System.hpp"

/**
 * Default constructor for the system class.
 * Encaspualtes all initialisation logic. This technically should be
 * a singleton class but I think nobody is going to go crazy with this.
 */
System::System() {
    // Initialise GPIO pins for system control
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = (1ULL<<PIN_OFFLOAD) | (1ULL<<PIN_TESTMODE);
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    gpio_config(&io_conf);
    
    // Check jumpers to decide system mode.
    // This line of code is potentially nefarious because I'm not too sure
    // how C++ handles enum types
    mode = (system_mode)(gpio_get_level(PIN_OFFLOAD) | (gpio_get_level(PIN_TESTMODE) << 1));

    // Check if external flash is OK
    if (flash.checkOK()) {
        flashmode = FLASH_EXTERNAL;
        // flash.init(); 
    } else {
        // Switch to internal flash
        flashmode = FLASH_INTERNAL;
    }
    // Initialise logger
    log_init();
    
    // TODO: mount filesystem

    // Check if RTC is connected
    // Timezone is hardcoded to UTC because we don't really care about it.
    struct timeval tv;
    if (rtc.checkOK()) {
        // If OK, set system time to RTC time
        tv = rtc.getTime();
        settimeofday(&tv, NULL);
        log_internal(std::string("RTC found. Setting system time to RTC time.\n"), LOG_INFO);
    } else {
        // Otherwise, leave system time as is.
        tv.tv_sec = 0;
        tv.tv_usec = 0;
        settimeofday(&tv, NULL);
        log_internal(std::string("RTC not found. Falling back to relative time.\n"), LOG_WARNING);
    }
    // NOTE: We settimeofday inside of both branches of the if statement so
    //       our logging system can use the system time.

    log_internal(std::string("Core initialisation complete.\n"), LOG_INFO);
}

/**
 * Logs a message to the system log.
 * 
 * Automatically arbitrates between internal and external flash, and
 * will also output to serial if the system is in test mode or 
 * diagnostic mode.
 * 
 * @param msg The message to log.
*/
void System::log_msg(std::string msg, log_type type) {
    // Placeholder
    std::cout << msg;
}

/**
 * Logs a message to the system log. Same as `log_msg` but prepends
 * the source as coming from the System manager.
 * 
 * Automatically arbitrates between internal and external flash, and
 * will also output to serial if the system is in test mode or 
 * diagnostic mode.
 * 
 * @param msg The message to log.
*/
void System::log_internal(std::string msg, log_type type) {
    // Placeholder
    std::cout << "System: " << msg;
}

/**
 * Initialises the system logger.
 * 
 * Generates a new logfile if appropriate on the correct
 * device.
*/
void System::log_init() {
    // Placeholder
    std::cout << "Initialising logger...\n";
}

void System::i2c_init() {
    // Placeholder
}