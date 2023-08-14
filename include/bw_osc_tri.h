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
 *  version {{{ 1.0.0 }}}
 *  requires {{{ bw_common bw_math bw_one_pole }}}
 *  description {{{
 *    Triangle oscillator waveshaper with variable slope (increasing time over
 *    period) and PolyBLEP antialiasing.
 *
 *    It turns a normalized phase signal, such as that geneated by
 *    [bw\_phase\_gen](bw_phase_gen), into a triangle wave.
 *
 *    The antialiasing algorithm is based on
 *
 *    V. Valimaki and A. Huovilainen, "Antialiasing Oscillators in Subtractive
 *    Synthesis", IEEE Signal Processing Magazine, vol. 24, no. 2, pp. 116-125,
 *    March 2007.
 *  }}}
 *  changelog {{{
 *    <ul>
 *      <li>Version <strong>1.0.0</strong>:
 *        <ul>
 *          <li><code>bw_osc_tri_process()</code> and
 *              <code>bw_osc_tri_process_multi()</code> now use
 *              <code>size_t</code> to count samples and channels.</li>
 *          <li>Added more <code>const</code> specifiers to input
 *              arguments.</li>
 *          <li>Moved C++ code to C header.</li>
 *          <li>Added overladed C++ <code>process()</code> function taking
 *              C-style arrays as arguments.</li>
 *          <li>Removed usage of reserved identifiers.</li>
 *        </ul>
 *      </li>
 *      <li>Version <strong>0.6.0</strong>:
 *        <ul>
 *          <li>Removed dependency on bw_config.</li>
 *        </ul>
 *      </li>
 *      <li>Version <strong>0.5.0</strong>:
 *        <ul>
 *          <li>Added <code>bw_osc_pulse_process_multi()</code>.</li>
 *          <li>Fixed typo in <code>bw_osc_tri_process1\*()</code>
 *              documentation.</li>
 *          <li>Added C++ wrapper.</li>
 *        </ul>
 *      </li>
 *      <li>Version <strong>0.4.0</strong>:
 *        <ul>
 *          <li>Fixed unused parameter warnings.</li>
 *        </ul>
 *      </li>
 *      <li>Version <strong>0.2.0</strong>:
 *        <ul>
 *          <li>Refactored API.</li>
 *        </ul>
 *      </li>
 *      <li>Version <strong>0.1.0</strong>:
 *        <ul>
 *          <li>First release.</li>
 *        </ul>
 *      </li>
 *    </ul>
 *  }}}
 */

#ifndef BW_OSC_TRI_H
#define BW_OSC_TRI_H

#include <bw_common.h>

#ifdef __cplusplus
extern "C" {
#endif

/*! api {{{
 *    #### bw_osc_tri_coeffs
 *  ```>>> */
typedef struct bw_osc_tri_coeffs bw_osc_tri_coeffs;
/*! <<<```
 *    Coefficients and related.
 *
 *    #### bw_osc_tri_init()
 *  ```>>> */
static inline void bw_osc_tri_init(bw_osc_tri_coeffs *BW_RESTRICT coeffs);
/*! <<<```
 *    Initializes input parameter values in `coeffs`.
 *
 *    #### bw_osc_tri_set_sample_rate()
 *  ```>>> */
static inline void bw_osc_tri_set_sample_rate(bw_osc_tri_coeffs *BW_RESTRICT coeffs, float sample_rate);
/*! <<<```
 *    Sets the `sample_rate` (Hz) value in `coeffs`.
 *
 *    #### bw_osc_tri_reset_coeffs()
 *  ```>>> */
static inline void bw_osc_tri_reset_coeffs(bw_osc_tri_coeffs *BW_RESTRICT coeffs);
/*! <<<```
 *    Resets coefficients in `coeffs` to assume their target values.
 *
 *    #### bw_osc_tri_update_coeffs_ctrl()
 *  ```>>> */
static inline void bw_osc_tri_update_coeffs_ctrl(bw_osc_tri_coeffs *BW_RESTRICT coeffs);
/*! <<<```
 *    Triggers control-rate update of coefficients in `coeffs`.
 *
 *    #### bw_osc_tri_update_coeffs_audio()
 *  ```>>> */
static inline void bw_osc_tri_update_coeffs_audio(bw_osc_tri_coeffs *BW_RESTRICT coeffs);
/*! <<<```
 *    Triggers audio-rate update of coefficients in `coeffs`.
 *
 *    #### bw_osc_tri_process1\*()
 *  ```>>> */
static inline float bw_osc_tri_process1(const bw_osc_tri_coeffs *BW_RESTRICT coeffs, float x);
static inline float bw_osc_tri_process1_antialias(const bw_osc_tri_coeffs *BW_RESTRICT coeffs, float x, float x_phase_inc);
/*! <<<```
 *    These function process one input sample `x`, indicating the normalized
 *    phase, using `coeffs`. They return the corresponding output sample.
 *
 *    In particular:
 *     * `bw_osc_tri_process1()` assumes that antialiasing is disabled;
 *     * `bw_osc_tri_process1_antialias()` assumes that antialiasing is enabled
 *       and requires the corresponding phase increment value to be passed via
 *       `x_phase_inc`.
 *
 *    #### bw_osc_tri_process()
 *  ```>>> */
static inline void bw_osc_tri_process(bw_osc_tri_coeffs *BW_RESTRICT coeffs, const float *x, const float *x_phase_inc, float *y, size_t n_samples);
/*! <<<```
 *    Processes the first `n_samples` of the input buffer `x`, containing the
 *    normalized phase signal, and fills the first `n_samples` of the output
 *    buffer `y`, while using and updating `coeffs`.
 *
 *    If antialiasing is enabled, `x_phase_inc` must contain phase increment
 *    values, otherwise it is ignored and can be `NULL`.
 *
 *    #### bw_osc_tri_process_multi()
 *  ```>>> */
static inline void bw_osc_tri_process_multi(bw_osc_tri_coeffs *BW_RESTRICT coeffs, const float * const *x, const float * const *x_phase_inc, float * const *y, size_t n_channels, size_t n_samples);
/*! <<<```
 *    Processes the first `n_samples` of the `n_channels` input buffers `x`,
 *    containing the normalized phase signals, and fills the first `n_samples`
 *    of the `n_channels` output buffers `y`, while using and updating the
 *    common `coeffs` (control and audio rate).
 *
 *    If antialiasing is enabled, `x_phase_inc` must contain `n_channels`
 *    buffers of phase increment values, otherwise it is ignored and can be
 *    `NULL`.
 *
 *    #### bw_osc_tri_set_antialiasing()
 *  ```>>> */
static inline void bw_osc_tri_set_antialiasing(bw_osc_tri_coeffs *BW_RESTRICT coeffs, char value);
/*! <<<```
 *    Sets whether the antialiasing is on (`value` non-`0`) or off (`0`) in
 *    `coeffs`.
 *
 *    Default value: `0` (off).
 *
 *    #### bw_osc_tri_set_slope()
 *  ```>>> */
static inline void bw_osc_tri_set_slope(bw_osc_tri_coeffs *BW_RESTRICT coeffs, float value);
/*! <<<```
 *    Sets the slope (increasing time over period) to `value` (range [`0.001f`,
 *    `0.999f`]) in `coeffs`.
 *
 *    Default value: `0.5f`.
 *  }}} */

#ifdef __cplusplus
}
#endif

/*** Implementation ***/

/* WARNING: This part of the file is not part of the public API. Its content may
 * change at any time in future versions. Please, do not use it directly. */

#include <bw_math.h>
#include <bw_one_pole.h>

#ifdef __cplusplus
extern "C" {
#endif

struct bw_osc_tri_coeffs {
	// Sub-components
	bw_one_pole_coeffs	smooth_coeffs;
	bw_one_pole_state	smooth_state;

	// Parameters
	char			antialiasing;
	float			slope;
};

static inline void bw_osc_tri_init(bw_osc_tri_coeffs *BW_RESTRICT coeffs) {
	bw_one_pole_init(&coeffs->smooth_coeffs);
	bw_one_pole_set_tau(&coeffs->smooth_coeffs, 0.005f);
	coeffs->antialiasing = 0;
	coeffs->slope = 0.5f;
}

static inline void bw_osc_tri_set_sample_rate(bw_osc_tri_coeffs *BW_RESTRICT coeffs, float sample_rate) {
	bw_one_pole_set_sample_rate(&coeffs->smooth_coeffs, sample_rate);
	bw_one_pole_reset_coeffs(&coeffs->smooth_coeffs);
}

static inline void bw_osc_tri_reset_coeffs(bw_osc_tri_coeffs *BW_RESTRICT coeffs) {
	bw_one_pole_reset_state(&coeffs->smooth_coeffs, &coeffs->smooth_state, coeffs->slope);
}

static inline void bw_osc_tri_update_coeffs_ctrl(bw_osc_tri_coeffs *BW_RESTRICT coeffs) {
	(void)coeffs;
}

static inline void bw_osc_tri_update_coeffs_audio(bw_osc_tri_coeffs *BW_RESTRICT coeffs) {
	bw_one_pole_process1(&coeffs->smooth_coeffs, &coeffs->smooth_state, coeffs->slope);
}

static inline float bw_osc_tri_process1(const bw_osc_tri_coeffs *BW_RESTRICT coeffs, float x) {
	const float slope = bw_one_pole_get_y_z1(&coeffs->smooth_state); // output should always be in bounds given good input
	const float phase_d = x + x;
	return x < slope ? (phase_d - slope) * bw_rcpf(slope) : (1.f + slope - phase_d) * bw_rcpf(1.f - slope);
}

// PolyBLAMP residual based on Parzen window (4th-order B-spline), one-sided (x in [0, 2])
static inline float bw_osc_tri_blamp_diff(float x) {
	return x < 1.f
		? x * (x * ((0.05f * x - 0.1666666666666667f) * x * x + 0.6666666666666666f) - 1.0f) + 0.4666666666666667f
		: x * (x * (x * ((0.1666666666666667f - 0.01666666666666667f * x) * x - 0.6666666666666666f) + 1.333333333333333f) - 1.333333333333333f) + 0.5333333333333333f;
}

static inline float bw_osc_tri_process1_antialias(const bw_osc_tri_coeffs *BW_RESTRICT coeffs, float x, float x_phase_inc) {
	const float slope = bw_one_pole_get_y_z1(&coeffs->smooth_state); // output should always be in bounds given good input
	const float s_1_p_pw = 1.f + slope;
	const float s_1_m_pw = 1.f - slope;
	const float phase_d = x + x;
	float v = x < slope ? (phase_d - slope) * bw_rcpf(slope) : (s_1_p_pw - phase_d) * bw_rcpf(s_1_m_pw);
	if (x_phase_inc != 0.f) {
		const float phase_inc_2 = x_phase_inc + x_phase_inc;
		const float phase_inc_rcp = bw_rcpf(x_phase_inc);
		const float pw_m_phase = slope - x;
		const float phase_2 = bw_copysignf(0.5f, pw_m_phase) + 0.5f - pw_m_phase;
		const float s_1_m_phase = 1.f - x;
		const float s_1_m_phase_2 = 1.f - phase_2;
		float blamp = 0.f;
		if (s_1_m_phase_2 < phase_inc_2)
			blamp += bw_osc_tri_blamp_diff(s_1_m_phase_2 * phase_inc_rcp);
		if (s_1_m_phase < phase_inc_2)
			blamp -= bw_osc_tri_blamp_diff(s_1_m_phase * phase_inc_rcp);
		if (x < phase_inc_2)
			blamp -= bw_osc_tri_blamp_diff(x * phase_inc_rcp);
		if (phase_2 < phase_inc_2)
			blamp += bw_osc_tri_blamp_diff(phase_2 * phase_inc_rcp);
		v -= bw_rcpf(slope * s_1_m_pw) * bw_absf(x_phase_inc) * blamp;
	}
	return v;
}

static inline void bw_osc_tri_process(bw_osc_tri_coeffs *BW_RESTRICT coeffs, const float *x, const float *x_phase_inc, float *y, size_t n_samples) {
	if (coeffs->antialiasing)
		for (size_t i = 0; i < n_samples; i++) {
			bw_osc_tri_update_coeffs_audio(coeffs);
			y[i] = bw_osc_tri_process1_antialias(coeffs, x[i], x_phase_inc[i]);
		}
	else
		for (size_t i = 0; i < n_samples; i++) {
			bw_osc_tri_update_coeffs_audio(coeffs);
			y[i] = bw_osc_tri_process1(coeffs, x[i]);
		}
}

static inline void bw_osc_tri_process_multi(bw_osc_tri_coeffs *BW_RESTRICT coeffs, const float * const *x, const float * const *x_phase_inc, float * const *y, size_t n_channels, size_t n_samples) {
	if (coeffs->antialiasing)
		for (size_t i = 0; i < n_samples; i++) {
			bw_osc_tri_update_coeffs_audio(coeffs);
			for (size_t j = 0; j < n_channels; j++)
				y[j][i] = bw_osc_tri_process1_antialias(coeffs, x[j][i], x_phase_inc[j][i]);
		}
	else
		for (size_t i = 0; i < n_samples; i++) {
			bw_osc_tri_update_coeffs_audio(coeffs);
			for (size_t j = 0; j < n_channels; j++)
				y[j][i] = bw_osc_tri_process1(coeffs, x[j][i]);
		}
}

static inline void bw_osc_tri_set_antialiasing(bw_osc_tri_coeffs *BW_RESTRICT coeffs, char value) {
	coeffs->antialiasing = value;
}

static inline void bw_osc_tri_set_slope(bw_osc_tri_coeffs *BW_RESTRICT coeffs, float value) {
	coeffs->slope = value;
}

#ifdef __cplusplus
}

#include <array>

namespace Brickworks {

/*** Public C++ API ***/

/*! api_cpp {{{
 *    ##### Brickworks::OscTri
 *  ```>>> */
template<size_t N_CHANNELS>
class OscTri {
public:
	OscTri();
	
	void setSampleRate(float sampleRate);
	void reset();
	void process(
		const float * const *x,
		const float * const *x_phase_inc,
		float * const *y,
		size_t nSamples);
	void process(
		std::array<const float *, N_CHANNELS> x,
		std::array<const float *, N_CHANNELS> x_phase_inc,
		std::array<float *, N_CHANNELS> y,
		size_t nSamples);
	
	void setAntialiasing(bool value);
	void setSlope(float value);
/*! <<<...
 *  }
 *  ```
 *  }}} */

/*** Implementation ***/

/* WARNING: This part of the file is not part of the public API. Its content may
 * change at any time in future versions. Please, do not use it directly. */

private:
	bw_osc_tri_coeffs	 coeffs;
};

template<size_t N_CHANNELS>
inline OscTri<N_CHANNELS>::OscTri() {
	bw_osc_tri_init(&coeffs);
}

template<size_t N_CHANNELS>
inline void OscTri<N_CHANNELS>::setSampleRate(float sampleRate) {
	bw_osc_tri_set_sample_rate(&coeffs, sampleRate);
}

template<size_t N_CHANNELS>
inline void OscTri<N_CHANNELS>::reset() {
	bw_osc_tri_reset_coeffs(&coeffs);
}

template<size_t N_CHANNELS>
inline void OscTri<N_CHANNELS>::process(
		const float * const *x,
		const float * const *x_phase_inc,
		float * const *y,
		size_t nSamples) {
	bw_osc_tri_process_multi(&coeffs, x, x_phase_inc, y, N_CHANNELS, nSamples);
}

template<size_t N_CHANNELS>
inline void OscTri<N_CHANNELS>::process(
		std::array<const float *, N_CHANNELS> x,
		std::array<const float *, N_CHANNELS> x_phase_inc,
		std::array<float *, N_CHANNELS> y,
		size_t nSamples) {
	process(x.data(), x_phase_inc.data(), y.data(), nSamples);
}

template<size_t N_CHANNELS>
inline void OscTri<N_CHANNELS>::setAntialiasing(bool value) {
	bw_osc_tri_set_antialiasing(&coeffs, value);
}

template<size_t N_CHANNELS>
inline void OscTri<N_CHANNELS>::setSlope(float value) {
	bw_osc_tri_set_slope(&coeffs, value);
}

}
#endif

#endif
