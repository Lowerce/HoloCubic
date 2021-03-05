#include "display.h"
#include "imu.h"
#include "ambient.h"
#include "network.h"
#include "sd_card.h"
#include "rgb_led.h"
#include "lv_port_indev.h"
#include "lv_port_fatfs.h"
#include "lv_cubic_gui.h"
#include "gui_guider.h"

/*** Component objects ***/
Display screen;
IMU mpu;
Pixel rgb;
SdCard tf;
Network wifi;

lv_ui guider_ui;

void setup()
{
	Serial.begin(115200);

	/*** Init screen ***/
	screen.init();
	screen.setBackLight(0.2);

	/*** Init IMU as input device ***/
	lv_port_indev_init();
	mpu.init();

	/*** Init on-board RGB ***/
	rgb.init();
	rgb.setBrightness(0.1).setRGB(0, 0, 122, 204).setRGB(1, 0, 122, 204);

	/*** Init micro SD-Card ***/
	tf.init();
	lv_fs_if_init();

	String ssid = tf.readFileLine("/wifi.txt", 1);		// line-1 for WiFi ssid
	String password = tf.readFileLine("/wifi.txt", 2);	// line-2 for WiFi password

	/*** Inflate GUI objects ***/
	lv_holo_cubic_gui();
	//setup_ui(&guider_ui);

	/*** Read WiFi info from SD-Card, then scan & connect WiFi ***/
#if 1
	wifi.init(ssid, password);

	// Change to your BiliBili UID ��
	Serial.println(wifi.getBilibiliFans("20259914"));
#endif
}


void loop()
{
	// run this as often as possible ��
	screen.routine();

	// 200 means update IMU data every 200ms
	mpu.update(200);

	delay(10);
}
