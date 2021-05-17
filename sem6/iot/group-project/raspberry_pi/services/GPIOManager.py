import RPi.GPIO as GPIO


class GPIOManager:
    def __init__(self):
        self._blue_led = 8
        self._red_led = 10
        self._button = 16

    @staticmethod
    def cleanup():
        GPIO.cleanup()

    def add_callback(self, action_callback):
        GPIO.add_event_detect(self._button, GPIO.RISING, callback=action_callback, bouncetime=500)

    def setup(self):
        GPIO.setmode(GPIO.BOARD)
        GPIO.setwarnings(False)
        GPIO.setup(self._blue_led, GPIO.OUT)
        GPIO.setup(self._red_led, GPIO.OUT)
        GPIO.setup(self._button, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)
        GPIO.setmode(GPIO.BOARD)

    def turn_off_leds(self):
        GPIO.output(self._blue_led, GPIO.LOW)
        GPIO.output(self._red_led, GPIO.LOW)

    def turn_on_led(self, allow):
        if allow:
            GPIO.output(self._blue_led, GPIO.HIGH)
            GPIO.output(self._red_led, GPIO.LOW)
        else:
            GPIO.output(self._blue_led, GPIO.LOW)
            GPIO.output(self._red_led, GPIO.HIGH)
