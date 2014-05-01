//-----------------------------------------------------------------
// Added by Sydney Schinstock AIAA-KSU
// Eggdrop file
//=================================================================
#include <AP_Eggdrop.h>
#include <AP_Relay.h>
#include <AP_Math.h>
#include <RC_Channel.h>
#include <AP_HAL.h>

extern const AP_HAL::HAL& hal;

const AP_Param::GroupInfo AP_Camera::var_info[] PROGMEM = {

	// @Param: EGGDROP_CHANNEL
	// @DisplayName: 
	// @Description: 
	// @Range: 
	// @User: Standard
	AP_GROUPINFO("CHANNEL", 1, AP_Eggdrop, _eggdrop_channel, AP_EGGDROP_CHANNEL),

	// @Param: TIME_OPEN
	// @DisplayName: 
	// @Description: 
	// @Range: 
	// @User: Standard
	AP_GROUPINFO("TIME_OPEN", 2, AP_Eggdrop, _time_open, AP_EGGDROP_TIME_DOOR_OPEN),

	// @Param: SERVO_MAX
	// @DisplayName: 
	// @Description: 
	// @Range: 
	// @User: Standard
	AP_GROUPINFO("SERVO_MAX", 3, AP_Eggdrop, _servo_max, AP_EGGDROP_SERVO_MAX_PWM),

	// @Param: SERVO_MIN
	// @DisplayName: 
	// @Description: 
	// @User: 
    // @Range: Standard
	AP_GROUPINFO("SERVO_MIN", 4, AP_Eggdrop, _servo_min, AP_EGGDROP_SERVO_MIN_PWM),

	AP_GROUPEND
};