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
 *  module_type {{{ foundation }}}
 *  version {{{ 0.6.0 }}}
 *  description {{{
 *    A common header to make sure that a bunch of basic definitions are
 *    available and consistent for all Brickworks modules.
 *  }}}
 *  changelog {{{
 *    <ul>
 *      <li>Version <strong>0.6.0</strong>:
 *        <ul>
 *          <li>Added <code>BW_ASSERT</code>, <code>bw_is_inf()</code>,
 *              <code>bw_is_nan()</code>, <code>bw_is_finite()</code>,
 *              <code>bw_has_inf()</code>, <code>bw_has_nan()</code>,
 *              <code>bw_has_only_finite()</code>, and
 *              <code>bw_hash_sdbm()</code>.</li>
 *          <li>Removed dependency on bw_config.</li>
 *        </ul>
 *      </li>
 *      <li>Version <strong>0.5.0</strong>:
 *        <ul>
 *          <li>Fixed typo in the documentation of <code>BW_SIZE_T</code>.</li>
 *        </ul>
 *      </li>
 *      <li>Version <strong>0.4.0</strong>:
 *        <ul>
 *          <li>Added <code>BW_SIZE_T</code>.</li>
 *        </ul>
 *      </li>
 *      <li>Version <strong>0.2.0</strong>:
 *        <ul>
 *          <li>Removed <code>BW_MALLOC</code>, <code>BW_REALLOC</code>,
 *              and <code>BW_FREE</code>.</li>
 *          <li>Added <code>BW_RESTRICT</code>.</li>
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

#ifndef _BW_COMMON_H
#define _BW_COMMON_H

/*! api {{{
 *    #### NULL and BW_SIZE_T
 *    If `NULL` or `BW_SIZE_T` are not defined, then `stddef.h` is `#include`d.
 *
 *    If `BW_SIZE_T` is not defined, then it is defined as `size_t`.
 *  >>> */
#if !defined(NULL) || !defined(BW_SIZE_T)
# include <stddef.h>
# if !defined(BW_SIZE_T)
#  define BW_SIZE_T size_t
# endif
#endif
/*! ...
 *
 *    #### Exact-width integer types
 *    If <code class="hljs">(u)int{8,16,32,64}_t</code>,
 *    `INT{8,16,32,64}_{MIN,MAX}`, and `UINT{8,16,32,64}_MAX` are not defined,
 *    then `stdint.h` is `#include`d (actually, only testing against
 *    `INT32_MAX` but expecting the others to be finally defined).
 *  >>> */
#ifndef INT32_MAX
# include <stdint.h>
#endif
/*! ...
 *
 *    #### INFINITY
 *    If `INFINITY` is not defined, then `math.h` is `#include`d.
 *  >>> */
#ifndef INFINITY
# include <math.h>
#endif
/*! ...
 *
 *    #### BW_RESTRICT
 *    If `BW_RESTRICT` is not defined, then it is defined as `restrict` if C99
 *    is supported.
 *  >>> */
#ifndef BW_RESTRICT
# if defined(__STDC__) && (__STDC_VERSION__ >= 199901L)
#  define BW_RESTRICT restrict
# else
#  define BW_RESTRICT
# endif
#endif
/*! ...
 *
 *    #### BW_ASSERT and BW_ASSERT_DEEP
 *    If `NDEBUG` is defined then "calls" to both `BW_ASSERT` and
 *    `BW_ASSERT_DEEP` will be stripped away by the preprocessor.
 *
 *    Whether `NDEBUG` is defined or not, "calls" to `BW_ASSERT_DEEP` will still
 *    be stripped anyway if `BW_DEBUG_DEEP` is not defined.
 *
 *    In all other cases, `BW_ASSERT` and `BW_ASSERT_DEEP` can either be
 *    provided by you, otherwise `BW_ASSERT` is defined as `assert` (and
 *    `assert.h` is `#include`d) and `BW_ASSERT_DEEP` is defined as `BW_ASSERT`.
 *
 *    `BW_ASSERT` is meant to perform rapid/basic validity checks (e.g., input
 *    pointer is not `NULL`, input `float` number is finite), while
 *    `BW_ASSERT_DEEP` should be used for deeper checks (e.g., validate data
 *    structures and internal states).
 *  >>> */
#ifdef NDEBUG
# undef BW_ASSERT
# undef BW_ASSERT_DEEP
# define BW_ASSERT(ignore)	((void)0)
# define BW_ASSERT_DEEP(ignore)	((void)0)
#else
# if !defined(BW_ASSERT) || !defined(BW_ASSERT_DEEP)
#  include <assert.h>
# endif
# ifndef BW_ASSERT
#  define BW_ASSERT assert
# endif
# ifdef BW_DEBUG_DEEP
#  ifndef BW_ASSERT_DEEP
#   define BW_ASSERT_DEEP BW_ASSERT
#  endif
# else
#  undef BW_ASSERT_DEEP
#  define BW_ASSERT_DEEP(ignore) ((void)0)
# endif
#endif
/*! ...
 *
 *    #### bw_is_inf()
 *  ```>>> */
static inline char bw_is_inf(float x);
/*! <<<```
 *    Returns non-`0` if `x` is positive or negative infinity, `0` otherwise.
 *
 *    #### bw_is_nan()
 *  ```>>> */
static inline char bw_is_nan(float x);
/*! <<<```
 *    Returns non-`0` if `x` is NaN, `0` otherwise.
 *
 *    #### bw_is_finite()
 *  ```>>> */
static inline char bw_is_finite(float x);
/*! <<<```
 *    Returns non-`0` if `x` is finite (neither NaN nor positive or negative
 *    infinity), `0` otherwise.
 *
 *    #### bw_has_inf()
 *  ```>>> */
static inline char bw_has_inf(const float *x, BW_SIZE_T n_elems);
/*! <<<```
 *    Scans the fist `n_elems` in buffer `x` and returns non-`0` if it contains
 *    at least one positive or negative inifinity value, `0` otherwise.
 *
 *    #### bw_has_nan()
 *  ```>>> */
static inline char bw_has_nan(const float *x, BW_SIZE_T n_elems);
/*! <<<```
 *    Scans the fist `n_elems` in buffer `x` and returns non-`0` if it contains
 *    at least one NaN value, `0` otherwise.
 *
 *    #### bw_has_only_finite()
 *  ```>>> */
static inline char bw_has_only_finite(const float *x, BW_SIZE_T n_elems);
/*! <<<```
 *    Scans the fist `n_elems` in buffer `x` and returns non-`0` if it only
 *    finds finite values (neither NaN nor positive or negative infinity), `0`
 *    otherwise.
 *
 *    #### bw_hash_sdbm()
 *  ```>>> */
static inline uint32_t bw_hash_sdbm(const char *string);
/*! <<<```
 *    Returns the sdbm hash of the given `string`.
 *  }}} */

/*** Implementation ***/

/* WARNING: This part of the file is not part of the public API. Its content may
 * change at any time in future versions. Please, do not use it directly. */

static inline char bw_is_inf(float x) {
	union {uint32_t u; float f;} v;
	v.f = x;
	return (v.u & 0x7fffffff) == 0x7f800000;
}

static inline char bw_is_nan(float x) {
	union {uint32_t u; float f;} v;
	v.f = x;
	return ((v.u & 0x7f800000) == 0x7f800000) && (v.u & 0x7fffff);
}

static inline char bw_is_finite(float x) {
	union {uint32_t u; float f;} v;
	v.f = x;
	return (v.u & 0x7f800000) != 0x7f800000;
}

static inline char bw_has_inf(const float *x, BW_SIZE_T n_elems) {
	char ret = 0;
	for (BW_SIZE_T i = 0; i < n_elems && !ret; i++)
		ret = bw_is_inf(x[i]);
	return ret;
}

static inline char bw_has_nan(const float *x, BW_SIZE_T n_elems) {
	char ret = 0;
	for (BW_SIZE_T i = 0; i < n_elems && !ret; i++)
		ret = bw_is_nan(x[i]);
	return ret;
}

static inline char bw_has_only_finite(const float *x, BW_SIZE_T n_elems) {
	char ret = 1;
	for (BW_SIZE_T i = 0; i < n_elems && ret; i++)
		ret = bw_is_finite(x[i]);
	return ret;
}

static inline uint32_t bw_hash_sdbm(const char *string) {
	uint32_t hash = 0;
	for (; *string != '\0'; string++)
		hash = *string + (hash << 6) + (hash << 16) - hash;
	return hash;
}

#endif
