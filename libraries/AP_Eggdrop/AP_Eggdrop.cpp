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

const AP_Param::GroupInfo AP_Eggdrop::var_info[] PROGMEM = {

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

void
AP_Eggdrop::door_open()
{
	RC_Channel_aux::set_radio(RC_Channel_aux::k_egg_drop, _servo_max);
	
	_time_open_counter = constrain_int16(_time_open * 5, 0, 255);

	if (door_delay())
	{
		RC_Channel_aux::set_radio(RC_Channel_aux::k_egg_drop, _servo_min);
	}
}

bool
AP_Eggdrop::door_delay()
{
	static bool notified = true;
	// if time is not equal to time door needs to be open, subtract one
	if (_time_open_counter)
	{
		_time_open_counter--;
		// Check to see if the notified variable needs reset
		if (notified == true)
		{
			notified = false;
		}
		return false;
	}
	// if time is equal to door time, close the door of egg drop mechanism
	else if (notified == false)
	{
		notified = true;
		return true;
	}
	return false;
}
