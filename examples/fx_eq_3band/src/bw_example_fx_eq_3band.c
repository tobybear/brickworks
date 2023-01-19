/*
 * Brickworks
 *
 * Copyright (C) 2023 Orastron Srl unipersonale
 *
 * Brickworks is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * Brickworks is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Brickworks.  If not, see <http://www.gnu.org/licenses/>.
 *
 * File author: Stefano D'Angelo
 */

#include "bw_example_fx_eq_3band.h"

#include <bw_ls2.h>
#include <bw_hs2.h>
#include <bw_peak.h>
#ifdef __WASM__
# include "walloc.h"
#else
# include <stdlib.h>
#endif

enum {
	p_ls_cutoff,
	p_ls_gain,
	p_ls_slope,
	p_peak_cutoff,
	p_peak_gain,
	p_peak_bw,
	p_hs_cutoff,
	p_hs_gain,
	p_hs_slope,
	p_n
};

struct _bw_example_fx_eq_3band {
	// Sub-components
	bw_ls2_coeffs	ls2_coeffs;
	bw_ls2_state	ls2_state;
	bw_peak_coeffs	peak_coeffs;
	bw_peak_state	peak_state;
	bw_hs2_coeffs	hs2_coeffs;
	bw_hs2_state	hs2_state;

	// Parameters
	float		params[p_n];
};

bw_example_fx_eq_3band bw_example_fx_eq_3band_new() {
	bw_example_fx_eq_3band instance = (bw_example_fx_eq_3band)malloc(sizeof(struct _bw_example_fx_eq_3band));
	if (instance == NULL)
		return NULL;
	bw_ls2_init(&instance->ls2_coeffs);
	bw_peak_init(&instance->peak_coeffs);
	bw_hs2_init(&instance->hs2_coeffs);
	bw_ls2_set_use_slope(&instance->ls2_coeffs, 0);
	bw_hs2_set_use_slope(&instance->hs2_coeffs, 0);
	return instance;
}

void bw_example_fx_eq_3band_free(bw_example_fx_eq_3band instance) {
	free(instance);
}

void bw_example_fx_eq_3band_set_sample_rate(bw_example_fx_eq_3band instance, float sample_rate) {
	bw_ls2_set_sample_rate(&instance->ls2_coeffs, sample_rate);
	bw_peak_set_sample_rate(&instance->peak_coeffs, sample_rate);
	bw_hs2_set_sample_rate(&instance->hs2_coeffs, sample_rate);
}

void bw_example_fx_eq_3band_reset(bw_example_fx_eq_3band instance) {
	bw_ls2_reset_coeffs(&instance->ls2_coeffs);
	bw_ls2_reset_state(&instance->ls2_coeffs, &instance->ls2_state);
	bw_peak_reset_coeffs(&instance->peak_coeffs);
	bw_peak_reset_state(&instance->peak_coeffs, &instance->peak_state);
	bw_hs2_reset_coeffs(&instance->hs2_coeffs);
	bw_hs2_reset_state(&instance->hs2_coeffs, &instance->hs2_state);
}

void bw_example_fx_eq_3band_process(bw_example_fx_eq_3band instance, const float** x, float** y, int n_samples) {
	bw_ls2_process(&instance->ls2_coeffs, &instance->ls2_state, x[0], y[0], n_samples);
	bw_peak_process(&instance->peak_coeffs, &instance->peak_state, y[0], y[0], n_samples);
	bw_hs2_process(&instance->hs2_coeffs, &instance->hs2_state, y[0], y[0], n_samples);
	//bw_peak_process(&instance->peak_coeffs, &instance->peak_state, x[0], y[0], n_samples);
}

void bw_example_fx_eq_3band_set_parameter(bw_example_fx_eq_3band instance, int index, float value) {
	instance->params[index] = value;
	switch (index) {
	case p_ls_cutoff:
		bw_ls2_set_cutoff(&instance->ls2_coeffs, 20.f + (20e3f - 20.f) * value * value * value);
		break;
	case p_ls_gain:
		bw_ls2_set_dc_gain_dB(&instance->ls2_coeffs, -20.f + 40.f * value);
		break;
	case p_ls_slope:
		break;
	case p_peak_cutoff:
		bw_peak_set_cutoff(&instance->peak_coeffs, 20.f + (20e3f - 20.f) * value * value * value);
		break;
	case p_peak_gain:
		bw_peak_set_peak_gain_dB(&instance->peak_coeffs, -20.f + 40.f * value);
		break;
	case p_peak_bw:
		bw_peak_set_bandwidth(&instance->peak_coeffs, 0.5f + 3.9f * value);
		break;
	case p_hs_cutoff:
		bw_hs2_set_cutoff(&instance->hs2_coeffs, 20.f + (20e3f - 20.f) * value * value * value);
		break;
	case p_hs_gain:
		bw_hs2_set_high_gain_dB(&instance->hs2_coeffs, -20.f + 40.f * value);
		break;
	case p_hs_slope:
		break;
	}
}

float bw_example_fx_eq_3band_get_parameter(bw_example_fx_eq_3band instance, int index) {
	return instance->params[index];
}
