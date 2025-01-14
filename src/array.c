/*
 * BASIC	A simple, extendable BASIC interpreter in C.
 *
 *		This file is part of the VARCem Project.
 *
 *		Handle arrays.
 *
 * Version:	@(#)array.c	1.1.0	2023/05/01
 *
 * Authors:	Fred N. van Kempen, <waltje@varcem.com>
 *		Johan Van den Brande <johan@vandenbrande.com>
 *
 *		Copyright 2023 Fred N. van Kempen.
 *		Copyright 2015,2016 Johan Van den Brande.
 *
 *		Redistribution and  use  in source  and binary forms, with
 *		or  without modification, are permitted  provided that the
 *		following conditions are met:
 *
 *		1. Redistributions of  source  code must retain the entire
 *		   above notice, this list of conditions and the following
 *		   disclaimer.
 *
 *		2. Redistributions in binary form must reproduce the above
 *		   copyright  notice,  this list  of  conditions  and  the
 *		   following disclaimer in  the documentation and/or other
 *		   materials provided with the distribution.
 *
 *		3. Neither the  name of the copyright holder nor the names
 *		   of  its  contributors may be used to endorse or promote
 *		   products  derived from  this  software without specific
 *		   prior written permission.
 *
 * THIS SOFTWARE  IS  PROVIDED BY THE  COPYRIGHT  HOLDERS AND CONTRIBUTORS
 * "AS IS" AND  ANY EXPRESS  OR  IMPLIED  WARRANTIES,  INCLUDING, BUT  NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE  ARE  DISCLAIMED. IN  NO  EVENT  SHALL THE COPYRIGHT
 * HOLDER OR  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL,  EXEMPLARY,  OR  CONSEQUENTIAL  DAMAGES  (INCLUDING,  BUT  NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE  GOODS OR SERVICES;  LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED  AND ON  ANY
 * THEORY OF  LIABILITY, WHETHER IN  CONTRACT, STRICT  LIABILITY, OR  TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING  IN ANY  WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arch.h"
#include "basic.h"
#include "private.h"


struct array {
    size_t	element_size;
    size_t	size;
    char	*ptr;
};


array *
array_new(size_t element_size)
{
    array *a = malloc(sizeof(array));  

    a->element_size = element_size;
    a->size = 0;
    a->ptr = NULL;

    return a;
}


array *
array_alloc(array *array, size_t size)
{
    array->size = size;
    array->ptr = realloc(array->ptr, array->element_size * array->size);

    // Always clear arrays
    memset(array->ptr, 0, array->element_size * array->size);

    return array;
}


void
array_destroy(array *array)
{
    free(array->ptr);
    free(array);
}


void *
array_push(array *array, void *value)
{
    array->size++;
    array->ptr = realloc(array->ptr, array->element_size * array->size);
    void *element = array->ptr + array->element_size * (array->size - 1);
    memcpy(element, value, array->element_size);

    return element;
}


void *
array_get(array *array, size_t index)
{
    return array->ptr + index * array->element_size;
}


void *
array_set(array *array, size_t index, void *value)
{
    void *element = array_get(array, index);

    memcpy(element, value, array->element_size);

    return element;
}


size_t
array_size(array *array)
{
    return array->size;
}

