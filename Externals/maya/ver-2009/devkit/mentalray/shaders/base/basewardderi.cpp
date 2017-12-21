/******************************************************************************
 * Copyright 1986-2008 by mental images GmbH, Fasanenstr. 81, D-10623 Berlin,
 * Germany. All rights reserved.
 ******************************************************************************
 * Created:	10.02.98
 * Module:	baseshader
 * Purpose:	base shaders for Phenomenon writers
 *
 * Exports:
 *      mib_illum_ward_deriv
 *      mib_illum_ward_deriv_version
 *
 * History:
 *	10.07.08: support texture or surface derivs on any geometry
 *
 * Description:
 *      Perform illumination with the following reflection model:
 *      - Ward anisotropic glossy plus
 *      - Lambert diffuse (cosine) plus
 *      - ambient (constant)
 *
 * The anisotropic Ward reflection model of glossy reflection was
 * developed in "Measuring and modeling anisotropic reflection" by
 * Gregory J. Ward, Proceedings of Siggraph '92, pp. 265--272.
 * The brushing directions (u and v) are taken from the surface derivatives
 *****************************************************************************/

#include <math.h>
#include <assert.h>
#include "shader.h"
#include "mi_shader_if.h"

#define INTENSITY(c)	((1./3) * ((c).r + (c).g + (c).b))
#define miEPS		0.0001


struct mib_illum_ward_deriv {
	miColor		ambience;	/* ambient color multiplier */
	miColor		ambient;	/* ambient color */
	miColor		diffuse;	/* diffuse color */
	miColor		glossy;		/* glossy color */
	miScalar	shiny_u;	/* shiny coef in u direction (5-100) */
	miScalar	shiny_v;	/* shiny coef in v direction (5-100) */
	int		mode;		/* light mode: 0..2 */
	int		i_light;	/* index of first light */
	int		n_light;	/* number of lights */
	miTag		light[1];	/* list of lights */
};

/* Get derivatives (not normalized).
 * Try texture derivs (bump basis) first (polys, nurbs) then
 * surface derivs (subd, nurbs). Convert to target coordinate
 * space accordingly.
 */

void get_derivs(

	miState		*state,
	miVector	*u,
	miVector	*v,
	int		space,		/* 0-internal, 1-camera, 2-object */
	int		tangentSet)
{
	int num;

	if (mi_query(miQ_NUM_BUMPS, state, 0, &num) && num) {
		if (tangentSet <= 0 || tangentSet >= num) {
			*u = state->bump_x_list[0];
			*v = state->bump_y_list[0];
			}
		else {
			*u = state->bump_x_list[tangentSet];
			*v = state->bump_y_list[tangentSet];
			}
		switch (space) {
			case 0: mi_vector_from_object(state, u, u);
				mi_vector_from_object(state, v, v);
				break;
			case 1: mi_vector_from_object(state, u, u);
				mi_vector_from_object(state, v, v);
				mi_vector_to_camera(state, u, u);
				mi_vector_to_camera(state, v, v);
				break;
			case 2: break;
			}
		return;
		}

	if (mi_query(miQ_GEO_HAS_DERIVS, state, 0, &num) && num) {
		*u = state->derivs[0];
		*v = state->derivs[1];
		switch (space) {
			case 0: break;
			case 1: mi_vector_to_camera(state, u, u);
				mi_vector_to_camera(state, v, v);
				break;
			case 2: mi_vector_to_object(state, u, u);
				mi_vector_to_object(state, v, v);
				break;
			}
		return;
		}

	/* Fallback, create default derivs. */
	u->x = 1.0f; u->y = u->z = 0.0f;
	v->x = v->y = 0.0f; v->z = 1.0f;
	switch (space) {
		case 0: mi_vector_from_camera(state, u, u);
			mi_vector_from_camera(state, v, v);
			break;
		case 1: break;
		case 2: mi_vector_from_camera(state, u, u);
			mi_vector_from_camera(state, v, v);
			mi_vector_to_object(state, u, u);
			mi_vector_to_object(state, v, v);
			break;
		}
}

extern "C" DLLEXPORT int mib_illum_ward_deriv_version(void) { return(1); }

extern "C" DLLEXPORT miBoolean mib_illum_ward_deriv(
	miColor		*result,
	miState		*state,
	struct mib_illum_ward_deriv *paras)
{
	miColor		*ambi, *diff, *glos;
	miTag		*light;		/* tag of light instance */
	int		n_l;		/* number of light sources */
	int		i_l;		/* offset of light sources */
	int		m;		/* light mode: 0=all, 1=incl, 2=excl */
	int		samples;	/* # of samples taken */
	miColor		color;		/* color from light source */
	miColor		sum;		/* summed sample colors */
	miVector	dir;		/* direction towards light */
	miScalar	dot_nl;		/* dot prod of normal and dir */
	miScalar	shiny_u;	/* shiny coef in u direction (5-100) */
	miScalar	shiny_v;	/* shiny coef in v direction (5-100) */
	miScalar	s;		/* amount of specular reflection */

        /* check for illegal calls */
        if (state->type == miRAY_SHADOW || state->type == miRAY_DISPLACE ) {
		return(miFALSE);
	}

        
	ambi    =  mi_eval_color(&paras->ambient);
	diff    =  mi_eval_color(&paras->diffuse);
	glos    =  mi_eval_color(&paras->glossy);
	shiny_u = *mi_eval_scalar(&paras->shiny_u);
	shiny_v = *mi_eval_scalar(&paras->shiny_v);
	m       = *mi_eval_integer(&paras->mode);

	*result    = *mi_eval_color(&paras->ambience);	/* ambient term */
	result->r *= ambi->r;
	result->g *= ambi->g;
	result->b *= ambi->b;

	n_l   = *mi_eval_integer(&paras->n_light);
	i_l   = *mi_eval_integer(&paras->i_light);
	light = mi_eval_tag(paras->light) + i_l;

	if (m == 1)		/* modify light list (inclusive mode) */
		mi_inclusive_lightlist(&n_l, &light, state);
	else if (m == 2)	/* modify light list (exclusive mode) */
		mi_exclusive_lightlist(&n_l, &light, state);
	else if (m == 4) {
		n_l = 0;
		light = 0;
	}

	/* Loop over all light sources */
	if (m == 4 || n_l) {
		for (mi::shader::LightIterator iter(state, light, n_l);
						!iter.at_end(); ++iter) {
			sum.r = sum.g = sum.b = 0;
			while (iter->sample()) {
				/* Lambert's cosine law */
				dot_nl = iter->get_dot_nl();
				dir    = iter->get_direction();
				iter->get_contribution(&color);
				sum.r += dot_nl * diff->r * color.r;
				sum.g += dot_nl * diff->g * color.g;
				sum.b += dot_nl * diff->b * color.b;

				/* Ward's glossy reflection */
				if (shiny_u == shiny_v)		/* isotropic refl. */
					s = dot_nl * mi_ward_glossy(&state->dir, &dir,
								    &state->normal, shiny_u);

				else {				/* anisotropic refl. */
					miVector	u, v;
					float		d;

					get_derivs(state, &u, &v, 0, 0);
					mi_vector_normalize(&u);
					/* Compute v to be perpendicular to u */
					/* (in the tangent plane) */
					mi_vector_prod(&v, &state->normal, &u);
					s = dot_nl * mi_ward_anisglossy(&state->dir,
									&dir, &state->normal,
									&u, &v, shiny_u, shiny_v);
				}
				if (s > 0.0) {
					sum.r += s * glos->r * color.r;
					sum.g += s * glos->g * color.g;
					sum.b += s * glos->b * color.b;
				}
			}
			samples = iter->get_number_of_samples();
			if (samples) {
				result->r += sum.r / samples;
				result->g += sum.g / samples;
				result->b += sum.b / samples;
			}
		}
	}

	/* add contribution from indirect illumination (caustics) */
	mi_compute_irradiance(&color, state);
	result->r += color.r * diff->r;
	result->g += color.g * diff->g;
	result->b += color.b * diff->b;
	result->a  = 1;
	return(miTRUE);
}
