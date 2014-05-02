//------------------------------------------------
// Added by Sydney Schinstock AIAA-KSU
// Header file for egg drop and GCS parameters
//================================================

#ifndef AP_EGGDROP_H
#define AP_EGGDROP_H

#include <AP_Param.h>
#include <AP_Common.h>
#include <GCS_MAVLink.h>
#include <AP_Relay.h>


#define AP_EGGDROP_CHANNEL    10      // ardupilot channel to attach servo to

#define AP_EGGDROP_TIME_DOOR_OPEN		10		// Amount of time we want the egg drop door to be open

#define AP_EGGDROP_SERVO_MAX_PWM             1300    // default PWM value to move servo to maximum position
#define AP_EGGDROP_SERVO_MIN_PWM             1100    // default PWM value to move servo to minimum position

class AP_Eggdrop {

public:
	void door_open();
	void door_close();
	
	static const struct AP_Param::GroupInfo        var_info[];
private:
	AP_Int16         _eggdrop_channel;      // Channel on arduino board to attach servo
	AP_Int16         _time_open;			// duration in 10ths of a second that the door is held open
	uint16_t		 _time_open_counter;	//count number of cycles for delay
	AP_Int16         _servo_max;		// max PWM value to move servo to when egg is dropped
	AP_Int16         _servo_min;     // PWM value to move servo to when shutter is deactivated
	
	bool door_delay();
};
#endif //AP_EGGDROP_H