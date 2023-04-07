/*
 * Brickworks
 *
 * Copyright (C) 2022, 2023 Orastron Srl unipersonale
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

/*!
 *  module_type {{{ dsp }}}
 *  version {{{ 0.4.0 }}}
 *  requires {{{
 *    bw_buf bw_config bw_comb bw_common bw_delay bw_gain bw_math bw_one_pole
 *    bw_osc_sin bw_phase_gen
 *  }}}
 *  description {{{
 *    Chorus / vibrato with variable speed and amount.
 *
 *    It outputs a mix of the dry input signal with itself going through a
 *    modulated delay.
 *  }}}
 *  changelog {{{
 *    <ul>
 *      <li>Version <strong>0.4.0</strong>:
 *          <li>First release.</li>
 *        </ul>
 *      </li>
 *    </ul>
 *  }}}
 */

#ifndef _BW_CHORUS_H
#define _BW_CHORUS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <bw_common.h>

/*! api {{{
 *    #### bw_chorus_coeffs
 *  ```>>> */
typedef struct _bw_chorus_coeffs bw_chorus_coeffs;
/*! <<<```
 *    Coefficients and related.
 *
 *    ### bw_chorus_state
 *  ```>>> */
typedef struct _bw_chorus_state bw_chorus_state;
/*! <<<```
 *    Internal state and related.
 *
 *    #### bw_chorus_init()
 *  ```>>> */
static inline void bw_chorus_init(bw_chorus_coeffs *BW_RESTRICT coeffs, float max_delay);
/*! <<<```
 *    Initializes input parameter values in `coeffs` using `max_delay` (s) as
 *    the maximum delay time.
 *
 *    #### bw_chorus_set_sample_rate()
 *  ```>>> */
static inline void bw_chorus_set_sample_rate(bw_chorus_coeffs *BW_RESTRICT coeffs, float sample_rate);
/*! <<<```
 *    Sets the `sample_rate` (Hz) value in `coeffs`.
 *
 *    ### bw_chorus_mem_req()
 *  ```>>> */
static inline BW_SIZE_T bw_chorus_mem_req(bw_chorus_coeffs *BW_RESTRICT coeffs);
/*! <<<```
 *    Returns the size, in bytes, of contiguous memory to be supplied to
 *    `bw_chorus_mem_set()` using `coeffs`.
 *
 *    ### bw_chorus_mem_set()
 *  ```>>> */
static inline void bw_chorus_mem_set(bw_chorus_state *BW_RESTRICT state, void *mem);
/*! <<<```
 *    Associates the contiguous memory block `mem` to the given `state`.
 *
 *    #### bw_chorus_reset_coeffs()
 *  ```>>> */
static inline void bw_chorus_reset_coeffs(bw_chorus_coeffs *BW_RESTRICT coeffs);
/*! <<<```
 *    Resets coefficients in `coeffs` to assume their target values.
 *
 *    #### bw_chorus_reset_state()
 *  ```>>> */
static inline void bw_chorus_reset_state(const bw_chorus_coeffs *BW_RESTRICT coeffs, bw_chorus_state *BW_RESTRICT state);
/*! <<<```
 *    Resets the given `state` to its initial values using the given `coeffs`.
 *
 *    #### bw_chorus_update_coeffs_ctrl()
 *  ```>>> */
static inline void bw_chorus_update_coeffs_ctrl(bw_chorus_coeffs *BW_RESTRICT coeffs);
/*! <<<```
 *    Triggers control-rate update of coefficients in `coeffs`.
 *
 *    #### bw_chorus_update_coeffs_audio()
 *  ```>>> */
static inline void bw_chorus_update_coeffs_audio(bw_chorus_coeffs *BW_RESTRICT coeffs);
/*! <<<```
 *    Triggers audio-rate update of coefficients in `coeffs`.
 *
 *    #### bw_chorus_process1()
 *  ```>>> */
static inline float bw_chorus_process1(const bw_chorus_coeffs *BW_RESTRICT coeffs, bw_chorus_state *BW_RESTRICT state, float x);
/*! <<<```
 *    Processes one input sample `x` using `coeffs`, while using and updating
 *    `state`. Returns the corresponding output sample.
 *
 *    #### bw_chorus_process()
 *  ```>>> */
static inline void bw_chorus_process(bw_chorus_coeffs *BW_RESTRICT coeffs, bw_chorus_state *BW_RESTRICT state, const float *x, float *y, int n_samples);
/*! <<<```
 *    Processes the first `n_samples` of the input buffer `x` and fills the
 *    first `n_samples` of the output buffer `y`, while using and updating both
 *    `coeffs` and `state` (control and audio rate).
 *
 *    #### bw_chorus_set_rate()
 *  ```>>> */
static inline void bw_chorus_set_rate(bw_chorus_coeffs *BW_RESTRICT coeffs, float value);
/*! <<<```
 *    Sets the modulation rate `value` (Hz) in `coeffs`.
 *
 *    Default value: `1.f`.
 *
 *    #### bw_chorus_set_delay()
 *  ```>>> */
static inline void bw_chorus_set_delay(bw_chorus_coeffs *BW_RESTRICT coeffs, float value);
/*! <<<```
 *    Sets the center delay `value` (s) in `coeffs`.
 *
 *    Default value: `0.f`.
 *
 *    #### bw_chorus_set_amount()
 *  ```>>> */
static inline void bw_chorus_set_amount(bw_chorus_coeffs *BW_RESTRICT coeffs, float value);
/*! <<<```
 *    Sets the modulation amount (semi-amplitude) `value` (s) in `coeffs`.
 *
 *    Default value: `0.f`.
 *
 *    #### bw_chorus_set_coeff_x()
 *  ```>>> */
static inline void bw_chorus_set_coeff_x(bw_chorus_coeffs *BW_RESTRICT coeffs, float value);
/*! <<<```
 *    Sets the dry input coefficient `value` in `coeffs`.
 *
 *    Default value: `0.f`.
 *
 *    #### bw_chorus_set_coeff_mod()
 *  ```>>> */
static inline void bw_chorus_set_coeff_mod(bw_chorus_coeffs *BW_RESTRICT coeffs, float value);
/*! <<<```
 *    Sets the modulated branch coefficient `value` in `coeffs`.
 *
 *    Default value: `1.f`.
 *  }}} */

/*** Implementation ***/

/* WARNING: This part of the file is not part of the public API. Its content may
 * change at any time in future versions. Please, do not use it directly. */

#include <bw_phase_gen.h>
#include <bw_osc_sin.h>
#include <bw_comb.h>

struct _bw_chorus_coeffs {
	// Sub-components
	bw_phase_gen_coeffs	phase_gen_coeffs;
	bw_phase_gen_state	phase_gen_state;
	bw_comb_coeffs		comb_coeffs;

	// Parameters
	float			delay;
	float			amount;
};

struct _bw_chorus_state {
	// Sub-components
	bw_comb_state		comb_state;
};

static inline void bw_chorus_init(bw_chorus_coeffs *BW_RESTRICT coeffs, float max_delay) {
	bw_phase_gen_init(&coeffs->phase_gen_coeffs);
	bw_comb_init(&coeffs->comb_coeffs, max_delay);
	bw_comb_set_coeff_blend(&coeffs->comb_coeffs, 0.f);
	bw_comb_set_coeff_ff(&coeffs->comb_coeffs, 1.f);
	coeffs->delay = 0.f;
	coeffs->amount = 0.f;
}

static inline void bw_chorus_set_sample_rate(bw_chorus_coeffs *BW_RESTRICT coeffs, float sample_rate) {
	bw_phase_gen_set_sample_rate(&coeffs->phase_gen_coeffs, sample_rate);
	bw_comb_set_sample_rate(&coeffs->comb_coeffs, sample_rate);
}

static inline BW_SIZE_T bw_chorus_mem_req(bw_chorus_coeffs *BW_RESTRICT coeffs) {
	return bw_comb_mem_req(&coeffs->comb_coeffs);
}

static inline void bw_chorus_mem_set(bw_chorus_state *BW_RESTRICT state, void *mem) {
	bw_comb_mem_set(&state->comb_state, mem);
}

static inline void bw_chorus_reset_coeffs(bw_chorus_coeffs *BW_RESTRICT coeffs) {
	bw_phase_gen_reset_coeffs(&coeffs->phase_gen_coeffs);
	bw_phase_gen_reset_state(&coeffs->phase_gen_coeffs, &coeffs->phase_gen_state, 0.f);
	bw_comb_reset_coeffs(&coeffs->comb_coeffs);
}

static inline void bw_chorus_reset_state(const bw_chorus_coeffs *BW_RESTRICT coeffs, bw_chorus_state *BW_RESTRICT state) {
	bw_comb_reset_state(&coeffs->comb_coeffs, &state->comb_state);
}

static inline void bw_chorus_update_coeffs_ctrl(bw_chorus_coeffs *BW_RESTRICT coeffs) {
	bw_phase_gen_update_coeffs_ctrl(&coeffs->phase_gen_coeffs);
	bw_comb_update_coeffs_ctrl(&coeffs->comb_coeffs);
}

static inline void bw_chorus_update_coeffs_audio(bw_chorus_coeffs *BW_RESTRICT coeffs) {
	bw_phase_gen_update_coeffs_audio(&coeffs->phase_gen_coeffs);
	float p, pi;
	bw_phase_gen_process1(&coeffs->phase_gen_coeffs, &coeffs->phase_gen_state, &p, &pi);
	const float mod = coeffs->delay + coeffs->amount * bw_osc_sin_process1(p);
	bw_comb_set_delay_ff(&coeffs->comb_coeffs, mod);
	bw_comb_update_coeffs_ctrl(&coeffs->comb_coeffs);
	bw_comb_update_coeffs_audio(&coeffs->comb_coeffs);
}

static inline float bw_chorus_process1(const bw_chorus_coeffs *BW_RESTRICT coeffs, bw_chorus_state *BW_RESTRICT state, float x) {
	return bw_comb_process1(&coeffs->comb_coeffs, &state->comb_state, x);
}

static inline void bw_chorus_process(bw_chorus_coeffs *BW_RESTRICT coeffs, bw_chorus_state *BW_RESTRICT state, const float *x, float *y, int n_samples) {
	bw_chorus_update_coeffs_ctrl(coeffs);
	for (int i = 0; i < n_samples; i++) {
		bw_chorus_update_coeffs_audio(coeffs);
		y[i] = bw_chorus_process1(coeffs, state, x[i]);
	}
}

static inline void bw_chorus_set_rate(bw_chorus_coeffs *BW_RESTRICT coeffs, float value) {
	bw_phase_gen_set_frequency(&coeffs->phase_gen_coeffs, value);
}

static inline void bw_chorus_set_delay(bw_chorus_coeffs *BW_RESTRICT coeffs, float value) {
	coeffs->delay = value;
}

static inline void bw_chorus_set_amount(bw_chorus_coeffs *BW_RESTRICT coeffs, float value) {
	coeffs->amount = value;
}

static inline void bw_chorus_set_coeff_x(bw_chorus_coeffs *BW_RESTRICT coeffs, float value) {
	bw_comb_set_coeff_blend(&coeffs->comb_coeffs, value);
}

static inline void bw_chorus_set_coeff_mod(bw_chorus_coeffs *BW_RESTRICT coeffs, float value) {
	bw_comb_set_coeff_ff(&coeffs->comb_coeffs, value);
}

#ifdef __cplusplus
}
#endif

#endif
