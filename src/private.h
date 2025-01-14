/*
 * BASIC	A simple, extendable BASIC interpreter in C.
 *
 *		This file is part of the VARCem Project.
 *
 *		Private (non-API) definitions for the program.
 *
 * Version:	@(#)private.h	1.1.1	2023/05/05
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
#ifndef PRIVATE_H
# define PRIVATE_H


typedef enum {
    T_NFOUND = 0,			// (00) token not found indicator

    T_ERROR,				// (01) invalid token
    T_EOL,				// (02) end of line
    T_NUMBER,				// (03) this looks like a number
    T_STRING,				// (04) this looks like a string

    T_VARIABLE_STRING,			// (05) this is a string variable
    T_VARIABLE_NUMBER,			// (06) this is a numeric variable

    T_PLUS,				// (07) the + sign
    T_MINUS,				// (08) the - sign
    T_MULTIPLY,				// (09) the * sign
    T_DIVIDE,				// (10) the / sign
    T_MODULO,				// (11) the % sign
    T_POWER,				// (12) the ^ sign

    T_LEFT_BANANA,			// (13) the ( sign (start of function)
    T_RIGHT_BANANA,			// (14) the ) sign (end of function)

    T_COLON,				// (15) the : sign (end of statement)
    T_SEMICOLON,			// (16) the ; sign
    T_COMMA,				// (17) the , sign
    T_EXCL,				// (18) the ! sign

    T_EQUAL,				// (19) the = sign
    T_LESS,				// (20) the < sign
    T_GREATER,				// (21) the > sign

    T_AND,				// (22) the AND keyword
    T_OR,				// (23) the OR keyword
    T_EOR,				// (24) the EOR keyword
    T_XOR,				// (25) the XOR keyword
    T_NOT,				// (26) the NOT keyword

    T_STEP,				// (27) the STEP keyword
    T_THEN,				// (28) the THEN keyword
    T_ELSE,				// (29) the ELSE keyword
    T_TO,				// (30) the TO keyword
    T_FN,				// (31) the FN keyword

    T_BLACK,				// (32) color
    T_BLUE,				// (33) color
    T_GREEN,				// (34) color
    T_CYAN,				// (35) color
    T_RED,				// (36) color
    T_MAGENTA,				// (37) color
    T_BROWN,				// (38) color
    T_GRAY,				// (39) color
    T_LIGHTGRAY,			// (40) color
    T_LIGHTBLUE,			// (41) color
    T_LIGHTGREEN,			// (42) color
    T_LIGHTCYAN,			// (43) color
    T_LIGHTRED,				// (44) color
    T_LIGHTMAGENTA,			// (45) color
    T_YELLOW,				// (46) color
    T_WHITE,				// (47) color

    TOKEN_TYPE_END			// (48) last (standard) keyword
} token_type;
#define T_AUTO	TOKEN_TYPE_END		// auto-assign new token value

typedef enum {
    VAR_TYPE_UNKNOWN,
    VAR_TYPE_NUMERIC,
    VAR_TYPE_STRING
} var_type;

typedef enum {
    EXPR_TYPE_NUMERIC,
    EXPR_TYPE_STRING
} expr_type;

typedef union {
    float	numeric;
    char	*string;
} expr_value;

typedef struct {
    expr_type	type;
    expr_value	value;
} expr_result;

typedef struct {
    token	token;
    const char	*name;  
} token_entry;

typedef struct array array;
typedef struct variable variable;
typedef struct dict dict;

typedef void	(*dictionary_each_cb)(const char *, void *, void *);
typedef void	(*lines_list_cb)(uint16_t, const char *);
typedef void	(*variables_each_cb)(const variable *, void *);
 

extern size_t	__program_size;
extern size_t	__memory_size;
extern char	*__memory;
extern char	*__stack;
extern size_t	__stack_size;
extern size_t	__stack_p;
extern char	*__cursor,
		*__cursor_saved;
extern token	sym;


extern void     get_sym(void);
extern bool     accept(token);
extern bool     expect(token);
extern relop    get_relop(void);
extern int      get_vector(int *, int);
extern void     set_line(uint16_t);
extern void     move_to_next_statement(void);
extern void     move_to_next_line(void);
extern int      dispatch_function(token, func_type, basic_var *);
extern void     parse_line(void);
extern void	basic_run(void);

extern void	lines_init(void);
extern size_t	lines_memory_used(void);
extern size_t	lines_memory_available(void);
extern bool	lines_delete(uint16_t number);
extern bool	lines_store(uint16_t number, const char *contents);
extern void	lines_list(uint16_t start, uint16_t end, lines_list_cb);
extern void	lines_clear(void);
extern char	*lines_get_contents(uint16_t number);
extern uint16_t	lines_first(void);
extern uint16_t	lines_next(uint16_t number);

extern void	func_init(void);
extern void	stmt_init(void);
extern bool	do_stmt(void);

extern char	*string_expression(void);
extern float	numeric_expression(void);
extern void	expression(expr_result *);
extern void	expression_print(expr_result *);
extern bool	condition(expr_result *, expr_result *, relop);

extern float	evaluate(const char *expression_string);
extern void	evaluate_print(const char *line);

extern array	*array_new(size_t element_size);
extern array	*array_alloc(array *, size_t size);
extern void	array_destroy(array *);
extern void	*array_push(array *, void *value);
extern void	*array_get(array *, size_t index);
extern void	*array_set(array *, size_t index, void *value);
extern size_t	array_size(array *);

extern dict	*dict_new(void);
extern void	dict_destroy(dict *, dictionary_each_cb cb);
extern void	dict_put(dict *, const char *, void *value);
extern bool	dict_has(dict *, const char *);
extern void	*dict_get(dict *, const char *);
extern void	dict_each(dict *, dictionary_each_cb, void *ctx);
extern void	*dict_del(dict *, const char *);

extern void	bputc(int);
extern void	bputs(const char *);
extern int	bprintf(const char *, ...);
extern int	bgetc(int);
extern char	*bgets(char *, size_t);

extern void	tokenizer_setup(void);
extern void	tokenizer_init(char *input);
extern token	tokenizer_register_token(const token_entry *);
extern void	tokenizer_free_registered_tokens(void);
extern char	*tokenizer_char_pointer(char *);
extern void	tokenizer_block(void);
extern token	tokenizer_get_next_token(void);
extern char	*tokenizer_get_raw(void);
extern float	tokenizer_get_number(void);
extern char	*tokenizer_get_string(void);
extern void	tokenizer_get_variable_name(char *);

extern bool	vars_init(void);
extern void	vars_destroy(void);

extern variable	*vars_get(const char *);
extern var_type	vars_get_type(const char *);
extern float	vars_get_numeric(const char *);
extern variable	*vars_set_numeric(const char *, float value); 
extern char	*vars_get_string(const char *);
extern variable	*vars_set_string(const char *, const char *value);

extern variable	*vars_array_init(const char *, var_type type,
				 int dimensions, int *vector);
extern char	*vars_array_get_string(const char *, int *vector);
extern variable	*vars_array_set_string(const char *, const char *, int *vector);
extern float	vars_array_get_numeric(const char *, int *vector);
extern variable	*vars_array_set_numeric(const char *,
					float value, int *vector);

extern void	vars_each(variables_each_cb, void *ctx);
extern void	vars_dump(const variable *);


#endif	/*PRIVATE_H*/
