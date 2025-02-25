#pragma once

#include <stdint.h>
#include <cubic_bezier_splines.h>

struct cbsv_color
{	uint8_t r, g, b;
};

void cbsv_add_spline(struct cbs_point spline[], int length, struct cbsv_color color);
void cbsv_run(void);
void cbsv_reset(void);
