
static void check_drop_control()
{

	static bool ArmPosition_debouncer;
	uint8_t NewArmState = readArmPosition();

	if (failsafe.ch3_failsafe || failsafe.ch3_counter > 0) {
		// when we are in ch3_failsafe mode then RC input is not
		// working, and we need to ignore the mode switch channel
		return;
	}

	//need to define ArmState somewhere in the code...
	//If the old arm position is what we need now it wont change the arm position 
	if (ArmState != NewArmState   )
	{
		if (ArmPosition_debouncer == false) 
		{
			// this ensures that mode switches only happen if the
			// switch changes for 2 reads. This prevents momentary
			// spikes in the mode control channel from causing a mode
			// switch
			ArmPosition_debouncer = true;
			return;
		}
		ArmState = NewArmState;
		if (ArmState == 1)
		{
			gcs_send_text_P(SEVERITY_HIGH, PSTR("EGG DROP ARMED"));
		}
		else if (ArmState == 0)
		{
			gcs_send_text_P(SEVERITY_HIGH, PSTR("EGG DROP DISARMED"));
		}
		else if (ArmState == 255)
		{
			gcs_send_text_P(SEVERITY_HIGH, PSTR("EGG DROP ARM ERROR"));
		}

	}
	ArmPosition_debouncer = false;
}

static uint8_t readArmPosition(void){
	uint16_t pulsewidth = hal.rcin->read(g.egg_drop_arm_channel - 1);
	if (pulsewidth <= 910 || pulsewidth >= 2090) return 255;            // This is an error condition
	if (pulsewidth > 1000 && pulsewidth <= 1300) return 0;
	if (pulsewidth > 1300 && pulsewidth <= 2000) return 1;             // Software Manual
	                                                                  // Hardware Manual
	return 0;
}

static void reset_arm_switch()
{
	ArmState = 0;
	check_drop_control();
}

