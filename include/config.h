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

// Camera interface
#define CAM_XCLK  GPIO_NUM_10
#define CAM_PCLK  GPIO_NUM_13
#define CAM_VSYNC GPIO_NUM_3
#define CAM_HSYNC GPIO_NUM_5    // HREF
#define CAM_D0    GPIO_NUM_15 /*!< hardware pins: D2 */
#define CAM_D1    GPIO_NUM_17 /*!< hardware pins: D3 */
#define CAM_D2    GPIO_NUM_18 /*!< hardware pins: D4 */
#define CAM_D3    GPIO_NUM_16 /*!< hardware pins: D5 */
#define CAM_D4    GPIO_NUM_14 /*!< hardware pins: D6 */
#define CAM_D5    GPIO_NUM_12 /*!< hardware pins: D7 */
#define CAM_D6    GPIO_NUM_11 /*!< hardware pins: D8 */
#define CAM_D7    GPIO_NUM_6  /*!< hardware pins: D9 */
#define CAM_SCL   GPIO_NUM_7
#define CAM_SDA   GPIO_NUM_8