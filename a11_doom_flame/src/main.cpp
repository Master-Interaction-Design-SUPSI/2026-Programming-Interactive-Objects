// Pinout configuration for the PicoDriver v.5.0
#include "common/pico_driver_v5_pinout.h"

#include <Arduino.h>
#include <SmartMatrix.h>

#define COLOR_DEPTH 24   // valid: 24, 48
#define TOTAL_WIDTH 32   // Size of the total (chained) with of the matrix/matrices
#define TOTAL_HEIGHT 32  // Size of the total (chained) height of the matrix/matrices
#define kRefreshDepth 24 // Valid: 24, 36, 48
#define kDmaBufferRows 4 // Valid: 2-4
#define kPanelType SM_PANELTYPE_HUB75_32ROW_32COL_MOD8SCAN // custom
#define kMatrixOptions (SM_HUB75_OPTIONS_NONE)
#define kbgOptions (SM_BACKGROUND_OPTIONS_NONE)

// SmartMatrix setup & buffer alloction
SMARTMATRIX_ALLOCATE_BUFFERS(matrix, TOTAL_WIDTH, TOTAL_HEIGHT, kRefreshDepth, kDmaBufferRows, kPanelType, kMatrixOptions);

// A single background layer "bg"
SMARTMATRIX_ALLOCATE_BACKGROUND_LAYER(bg, TOTAL_WIDTH, TOTAL_HEIGHT, COLOR_DEPTH, kbgOptions);


uint8_t pixel_data[TOTAL_WIDTH * TOTAL_HEIGHT];

rgb24 palette[] = {
	rgb24(0, 0, 0),
	rgb24(32, 7, 7),      // Dark red
	rgb24(64, 7, 7),      // Red
	rgb24(128, 0, 0),     // Bright red
	rgb24(180, 32, 0),    // Red-orange
	rgb24(220, 64, 0),    // Orange
	rgb24(255, 128, 0),   // Yellow-orange
	rgb24(255, 255, 128), // Bright yellow/white
};

uint8_t palette_size = sizeof(palette) / sizeof(palette[0]);

void setup() {

	pinMode(PICO_LED_PIN, OUTPUT);
	digitalWrite(PICO_LED_PIN, 1);

	bg.enableColorCorrection(true);
	matrix.addLayer(&bg);
	matrix.setBrightness(255);

	matrix.begin();


	for (int i = 0; i < TOTAL_WIDTH * TOTAL_HEIGHT; i++) {
		pixel_data[i] = palette_size - 1;
	}

}

void loop() {


	// Propagate the pixels upwards
	for (int y = 0; y < TOTAL_HEIGHT - 1; y++) {
		for (int x = 0; x < TOTAL_WIDTH; x++) {
			uint64_t current_pixel = y * TOTAL_WIDTH + x;
			uint64_t previous_pixel = (y + 1) * TOTAL_WIDTH + x;
			pixel_data[current_pixel] = max(0, pixel_data[previous_pixel] - 1);
		}
	}

	// Randomize the bottom row
	for (int i = 0; i < TOTAL_WIDTH; i++) {
		pixel_data[TOTAL_WIDTH * (TOTAL_HEIGHT - 1) + i] = random(0, palette_size);
	}

	// Draw the pixels
	for (int i = 0; i < TOTAL_WIDTH * TOTAL_HEIGHT; i++) {
		uint8_t x = i % TOTAL_WIDTH;
		uint8_t y = i / TOTAL_WIDTH;
		bg.drawPixel(x, y, palette[pixel_data[i]]);
	}
	bg.swapBuffers();

	delay(40);
}