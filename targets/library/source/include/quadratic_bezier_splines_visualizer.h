#pragma once

#include <stdint.h>
#include <quadratic_bezier_splines.h>

struct qbsv_color
{	uint8_t r, g, b;
};

void qbsv_add_spline(struct qbs_point spline[], int length, struct qbsv_color color);
void qbsv_run(void);
void qbsv_reset(void);
