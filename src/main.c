/*MIT License

Copyright (c) 2021 Panasonic Industrial Devices Europe GmbH

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/

#include "esp_event.h"
#include "esp_log.h"

#include "config.h"
#include "esp_camera.h"
#include "driver/gpio.h"

#include "httpd.h"
#include "wifi.h"

// Logging
static const char *TAG = "main";

static void initialize_cam(void)
{
    camera_config_t camera_config = {
        .pin_pwdn = -1,
        .pin_reset = -1,
        .pin_xclk = CAM_XCLK,
        .pin_sscb_sda = CAM_SDA,
        .pin_sscb_scl = CAM_SCL,

        .pin_d7 = CAM_D7,
        .pin_d6 = CAM_D6,
        .pin_d5 = CAM_D5,
        .pin_d4 = CAM_D4,
        .pin_d3 = CAM_D3,
        .pin_d2 = CAM_D2,
        .pin_d1 = CAM_D1,
        .pin_d0 = CAM_D0,
        .pin_vsync = CAM_VSYNC,
        .pin_href = CAM_HSYNC,
        .pin_pclk = CAM_PCLK,

        //XCLK 20MHz or 10MHz for OV2640 double FPS (Experimental)
        .xclk_freq_hz = 20000000,
        .ledc_timer = LEDC_TIMER_0,
        .ledc_channel = LEDC_CHANNEL_0,

        .pixel_format = PIXFORMAT_JPEG, //YUV422,GRAYSCALE,RGB565,JPEG
        .frame_size = FRAMESIZE_HVGA,    //QQVGA-UXGA Do not use sizes above QVGA when not JPEG

        .jpeg_quality = 30, //0-63 lower number means higher quality
        .fb_count = 2       //if more than one, i2s runs in continuous mode. Use only with JPEG
    };
    ESP_ERROR_CHECK(esp_camera_init(&camera_config));
}

void app_main(void)
{
    // Initialize camera
    initialize_cam();
    // Configure and Start WiFi Access Point
    app_wifi_main();
    // Configure and start webserver
    app_httpd_main();
}
