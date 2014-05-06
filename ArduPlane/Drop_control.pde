
static void check_drop_control()
{

	static bool ArmPosition_debouncer;
	uint8_t armPosition = readArmPosition();

	if (failsafe.ch3_failsafe || failsafe.ch3_counter > 0) {
		// when we are in ch3_failsafe mode then RC input is not
		// working, and we need to ignore the mode switch channel
		return;
	}

	//need to define oldArmPosition somewhere in the code...
	//If the old arm position is what we need now it wont change the arm position 
	if (oldArmPosition != armPosition   ) {

		if (ArmPosition_debouncer == false) {
			// this ensures that mode switches only happen if the
			// switch changes for 2 reads. This prevents momentary
			// spikes in the mode control channel from causing a mode
			// switch
			ArmPosition_debouncer = true;
			return;
		}
		oldArmPosition = armPosition;
	}
	ArmPosition_debouncer = false;
}

static uint8_t readArmPosition(void){
	uint16_t pulsewidth = hal.rcin->read(g.egg_drop_arm_channel - 1);
	if (pulsewidth <= 910 || pulsewidth >= 2090) return 255;            // This is an error condition
	if (pulsewidth > 1230 && pulsewidth <= 1360) return 1;
	if (pulsewidth > 1360 && pulsewidth <= 1490) return 2;             // Software Manual
	                                                                  // Hardware Manual
	return 0;
}

static void reset_arm_switch()
{
	oldArmPosition = 0;
	check_drop_control();
}

