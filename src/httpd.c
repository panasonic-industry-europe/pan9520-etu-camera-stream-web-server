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

#include "httpd.h"
#include "esp_log.h"
#include "esp_http_server.h"
#include "esp_timer.h"
#include "driver/ledc.h"
#include "sdkconfig.h"
#include "config.h"
#include "esp_camera.h"

// Logging
static const char *TAG = "camera_httpd";

// Response header constants
#define PART_BOUNDARY "123456789000000000000987654321"
static const char _STREAM_CONTENT_TYPE[] = "multipart/x-mixed-replace;boundary=" PART_BOUNDARY;
static const char _STREAM_BOUNDARY[] = "\r\n--" PART_BOUNDARY "\r\n";
static const char _STREAM_PART[] = "Content-Type: image/jpeg\r\nContent-Length: " CAM_PIXELS_STRING "\r\n\r\n";

// Webserver instances
httpd_handle_t camera_httpd = NULL;

// Returns index.html
static esp_err_t index_handler(httpd_req_t *req)
{
    uint8_t ret[] = "<meta charset=\"utf-8\"/> \
                    <style> \
                        #content { \
                            display: flex; \
                            flex-direction: column; \
                            justify-content: center; \
                            align-items: center; \
                            text-align: center; \
                            min-height: 100vh; \
                        } \
                    </style> \
                    <body bgcolor=\"#FFFFFF\"> \
                        <div id=\"content\"> \
                            <h2 style=\"color:#003b68\">PAN9520 ETU Cam live stream </h2> \
                            <img src=\"stream\" style=\"width: 320px;height: 240px;\"> \
                        </div> \
                    </body>";
    if (httpd_resp_set_type(req, "text/html") != ESP_OK)
    {
        return ESP_FAIL;
    }
    if (httpd_resp_send(req, (const char *)ret, sizeof(ret)) != ESP_OK)
    {
        return ESP_FAIL;
    }
    return ESP_OK;
}

// Stream handler which takes jpg images from the camera and send it out as video stream
static esp_err_t stream_handler(httpd_req_t *req)
{
    camera_fb_t* fb = NULL;
    esp_err_t res = ESP_OK;
    int64_t last_frame = esp_timer_get_time();

    // Send content type header
    if (httpd_resp_set_type(req, _STREAM_CONTENT_TYPE) != ESP_OK)
    {
        return ESP_FAIL;
    }

    // Allow cross origin requests.
    httpd_resp_set_hdr(req, "Access-Control-Allow-Origin", "*");
    

    while (true)
    {
        // Take picture from camera
        fb = esp_camera_fb_get();
        if (!fb) {
            ESP_LOGE(TAG, "Camera capture failed");
            res = ESP_FAIL;
            break;
        }

        // Build response
        if (res == ESP_OK)
        {
            // Send stream boundary header
            res = httpd_resp_send_chunk(req, _STREAM_BOUNDARY, sizeof(_STREAM_BOUNDARY) - 1);
        }
        if (res == ESP_OK)
        {
            // Send stream part header
            res = httpd_resp_send_chunk(req, _STREAM_PART, sizeof(_STREAM_PART) - 1);
        }
        if (res == ESP_OK)
        {
            // Send data package
            res = httpd_resp_send_chunk(req, (const char *)fb->buf, CAM_PIXELS);
        }

        // Enable frame buffer to get the next frame data
        // cam_give(cam_buf);
        esp_camera_fb_return(fb);

        if (res != ESP_OK)
        {
            break;
        }

        // Calculate and output the framerate
        int64_t fr_end = esp_timer_get_time();
        int64_t frame_time = fr_end - last_frame;
        last_frame = fr_end;
        frame_time /= 1000;
        ESP_LOGI(TAG, "MJPG: %uB %ums (%.1ffps)",
                 (uint32_t)(CAM_PIXELS),
                 (uint32_t)frame_time, 1000.0 / (uint32_t)frame_time);
    }

    return ESP_FAIL;
}

// Setup and starts webserver and registers URI handlers
void app_httpd_main()
{
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.max_uri_handlers = 16;

    httpd_uri_t index_uri = {
        .uri = "/",
        .method = HTTP_GET,
        .handler = index_handler,
        .user_ctx = NULL};

    httpd_uri_t stream_uri = {
        .uri = "/stream",
        .method = HTTP_GET,
        .handler = stream_handler,
        .user_ctx = NULL};

    ESP_ERROR_CHECK(httpd_start(&camera_httpd, &config));
    ESP_ERROR_CHECK(httpd_register_uri_handler(camera_httpd, &index_uri));
    ESP_ERROR_CHECK(httpd_register_uri_handler(camera_httpd, &stream_uri));
    ESP_LOGI(TAG, "Started web server on port: '%d'", config.server_port);
}