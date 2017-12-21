/******************************************************************************
* Copyright 1986-2007 by mental images GmbH, Fasanenstr. 81, D-10623 Berlin,
* Germany. All rights reserved.
******************************************************************************
* Created:  06.04.12
* Module:   architectural
* Purpose:  the architecture & design material PUBLIC API
*
* Exports:
*
*      mia_material_api_*()
*
* History:
*   06.05.10: Zap: Created
*   06.05.22: Zap: Extended
*   07.05.08: Zap: mia_material_x support
*
* Description:
*****************************************************************************/

#define miA_MATERIAL_API_STORAGE   "miXMST"

/* 
    Protocol for extracting arbitrary outputs from the mia_material:

	1. Create a shader state named after the macro miA_MATERIAL_API_STORAGE
	   pointing to a struct mia_material_api_outputs

	2. Set it's struct_size to sizeof(mia_material_api_outputs);

	3. Set in_use to miFALSE; No further initialization is needed.

	4. Call the mia_material shader.

	5. Upon return of mia_material, see if in_use is miTRUE. 
	   If so, the structure in the shaderstate will be filled in with the 
	   topmost shaders values.
*/

typedef struct  {
	/* Set before calling mia_material shader: */
	miUint     struct_size;  /* Set to sizeof() struct */
	miBoolean  in_use;       /* Set to miFALSE */
	/* Return values after calling mia_material shader */
	miScalar   opacity;      /* scalar opacity */
	miColor    indir_result; /* Indirect shading (FG and GI) */
	miColor    diff_result;  /* Diffuse shading */
	miColor    spec_result;  /* Specular/Highlights */
	miColor    tran_result;  /* Translucency */
	miColor    refl_result;  /* Reflections */
	miColor    refr_result;  /* Refractions */
	miColor    add_result;   /* "Additional color" */
	miColor    ao_result;    /* AO contribution only */
	miColor    diff_level;   /* Actually used diffuse color/level */
	miColor    refl_level;   /* Actually used reflection color/level */
	miColor    refr_level;   /* Actually used refraction color/level */
	miColor    tran_level;   /* Actually used translucency color/level */
	miRay_type type; 	     /* Ray type for the stored data */
} mia_material_api_storage;

/* New: the return structure of mia_material_x, interface version 15 (or higher) */

typedef struct {
    miColor   result;

    miColor   diffuse_result;
    miColor   diffuse_raw;
    miColor   diffuse_level;

    miColor   spec_result;
    miColor   spec_raw;
    miColor   spec_level;

    miColor   refl_result;
    miColor   refl_raw;
    miColor   refl_level;

    miColor   refr_result;
    miColor   refr_raw;
    miColor   refr_level;

    miColor   tran_result;
    miColor   tran_raw;
    miColor   tran_level;

    miColor   indirect_result;
    miColor   indirect_raw;
    miColor   indirect_cooked;
    miColor   ao_raw;

    miColor   add_result;

    miColor   opacity_result;
    miColor   opacity_raw;
    miScalar  opacity;

    /* Extra space in the struct for padding, never accessed */
    miColor   spare[2]; 
} mia_material_x_return;

/* New mia_material_x_return struct */
typedef struct  {
	/* Set before calling mia_material shader: */
	miUint     struct_size;  /* Set to sizeof() struct */
	miBoolean  in_use;       /* Set to miFALSE */
	miRay_type type; 	     /* Ray type for the stored data */

	/* Return values after calling mia_material shader */
    mia_material_x_return    output;
} mia_material_x_api_storage;


#define miA_MATERIAL_API_LIGHTDATA "miXMLD"

typedef struct {
	/* All below set up by mia_material prior to calling each light */
	miUint     struct_size;  /* Set to sizeof() struct, for versioning */
	
	/* Read only's: DO NOT change in light shader */
	
	miScalar   glossiness;   /* Light shader can make decisions based on glossiness */	
	miScalar   importance;   /* Light shader can make decisions based on importance */
	
	/* Modify as needed in the light shader */

	/* How much does this light affect diffuse and specular? */
	miScalar   affect_diffuse;  /* defaults to 1.0 */
	miScalar   affect_specular; /* defaults to 1.0 */

	/* Is this the mr Sun? (should only be set by the mr sun) */
	miBoolean  is_mr_sun;       /* defaults to miFALSE */
	/* If this is a visible area light, but it still desires to 
	   get a highlight, set force_specular to true */
	miBoolean  force_specular;  /* defaults to miFALSE */
} mia_material_api_lightdata;

