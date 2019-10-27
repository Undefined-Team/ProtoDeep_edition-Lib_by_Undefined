#ifndef UD_PROTODEEP_EDITION_H
# define UD_PROTODEEP_EDITION_H

// Lib
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ud_array.h>
#include <ud_math_array.h>
#include <ud_string.h>
#include <ud_string_array.h>
#include <ud_list.h>
#include <ud_file.h>
#include <ud_protodeep_core.h>

// Layer types

// 1; Add layer type params to str here
# define UD_LT_TO_STR(x)                                            _Generic((x), \
                                                                        ud_dense_params*: "dense", \
                                                                        ud_conv_params*: "conv", \
                                                                        ud_maxpool_params*: "maxpool", \
                                                                        ud_rnn_params*: "rnn", \
                                                                        ud_lstm_params*: "lstm", \
                                                                        ud_dropout_params*: "dropout", \
                                                                        default: "undefined" \
                                                                    )

// 2; Add params stringify function here
# define UD_STRINGIFY_FT                                            ud_pde_stringify_dense, \
                                                                    ud_pde_stringify_conv, \
                                                                    ud_pde_stringify_maxpool, \
                                                                    ud_pde_stringify_rnn, \
                                                                    ud_pde_stringify_lstm, \
                                                                    ud_pde_stringify_dropout

// 3; Add constructor here
# define ud_dense(_name, ...)                                       ud_str_dup(#_name), ({ ud_dense_params _tmp = { __VA_ARGS__}; &_tmp; }), UD_LT_DENSE
# define ud_fullco(_name, ...)                                      ud_dense(_name, __VA_ARGS__)
# define ud_conv(_name, ...)                                        ud_str_dup(#_name), ({ ud_conv_params _tmp = {__VA_ARGS__}; &_tmp; }), UD_LT_CONV
# define ud_maxpool(_name, ...)                                     ud_str_dup(#_name), ({ ud_maxpool_params _tmp = {__VA_ARGS__}; &_tmp; }), UD_LT_MAXPOOL
# define ud_rnn(_name, ...)                                         ud_str_dup(#_name), ({ ud_rnn_params _tmp = {__VA_ARGS__}; &_tmp; }), UD_LT_RNN
# define ud_lstm(_name, ...)                                        ud_str_dup(#_name), ({ ud_lstm_params _tmp = {__VA_ARGS__}; &_tmp; }), UD_LT_LSTM
# define ud_dropout(_name, ...)                                     ud_str_dup(#_name), ({ ud_dropout_params _tmp = {__VA_ARGS__}; &_tmp; }), UD_LT_DROPOUT

//4; Add stringify functions
char                      *ud_pde_stringify_dense(void *p_dense, char *name, ud_layer_grade layer_grade, char **before_layers, char *grades[]);
char                      *ud_pde_stringify_conv(void *p_conv, char *name, ud_layer_grade layer_grade, char **before_layers, char *grades[]);
char                      *ud_pde_stringify_maxpool(void *p_conv, char *name, ud_layer_grade layer_grade, char **before_layers, char *grades[]);
char                      *ud_pde_stringify_rnn(void *p_conv, char *name, ud_layer_grade layer_grade, char **before_layers, char *grades[]);
char                      *ud_pde_stringify_lstm(void *p_conv, char *name, ud_layer_grade layer_grade, char **before_layers, char *grades[]);
char                      *ud_pde_stringify_dropout(void *p_dropout, char *name, ud_layer_grade layer_grade, char **before_layers, char *grades[]);

//5; Add conv params structure in ud_protodeep_core.h

// Macro


# define UD_GET_NB_STRINGIFY_FT(...)                                ud_ut_args_len(void *, __VA_ARGS__)
# define UD_NB_STRINGIFY_FT                                         UD_GET_NB_STRINGIFY_FT(UD_STRINGIFY_FT)

# define UD_PDE_INT_COND(cond, layer, value)                        ud_str_vfjoin(": ", ud_str_dup(#value), ud_pde_cond_str(layer->value cond, ud_math_itoa(layer->value), #layer, #value, #cond))
# define UD_PDE_FLOAT_COND(cond, layer, value)                      ud_str_vfjoin(": ", ud_str_dup(#value), ud_pde_cond_str(layer->value cond, ud_math_ftoa(layer->value), #layer, #value, #cond))
# define UD_PDE_STR_COND(cond, layer, value)                        ud_str_vfjoin(": ", ud_str_dup(#value), ud_pde_cond_str(layer->value cond, layer->value ? ud_str_dup(layer->value) : ud_str_dup("none"), #layer, #value, #cond))
# define UD_PDE_INT_ARRAY(layer, value)                             ud_str_vfjoin(": ", ud_str_dup(#value), ud_pde_int_array_to_str(layer->value))
# define UD_PDE_INT(layer, value)                                   UD_PDE_INT_COND(|| 1, layer, value)
# define UD_PDE_FLOAT(layer, value)                                 UD_PDE_FLOAT_COND(|| 1, layer, value)
# define UD_PDE_STR(layer, value)                                   UD_PDE_STR_COND(|| 1, layer, value)

# define ud_pde_stringify(type, ...)                                ud_str_vfjoin(", ", ud_pde_stringify_desc(name, layer_grade, type), ud_str_vfjoin("; ", __VA_ARGS__), ud_pde_stringify_before_layers(before_layers), ud_str_dup("NULL\n"))
# define ud_pde_stringify_desc(name, layer_grade, layer_type)       ud_pde_stringify_desc_ctr(name, grades[layer_grade], UD_LT_TO_STR(layer_type))
# define ud_pde_layer_add(csv_path, layer_type, ...)                ud_pde_layer_add_ctr(csv_path, UD_LG_HIDDEN, layer_type, ud_ut_sarray_null(char *, __VA_ARGS__), false)
# define ud_pde_layer_add_input(csv_path, layer_type, ...)          ud_pde_layer_add_ctr(csv_path, UD_LG_INPUT, layer_type, ud_ut_sarray_null(char *, __VA_ARGS__), false)
# define ud_pde_layer_add_output(csv_path, layer_type, ...)         ud_pde_layer_add_ctr(csv_path, UD_LG_OUTPUT, layer_type, ud_ut_sarray_null(char *, __VA_ARGS__), false)
# define ud_pde_layer_free()                                        ud_pde_layer_add_ctr(NULL, 0, NULL, NULL, 0, NULL, true)

# define ud_shape(...)                                              ud_ut_array(size_t, ud_ut_args_len(size_t, __VA_ARGS__), __VA_ARGS__)

# define ud_pde_allow_overwrite                                     void __attribute__ ((constructor))  ud_pde_allow_overwrite() { ud_pde_names_list_init_begin(NULL, NULL, NULL, NULL, true); }

// Structures
ud_list_struct(ud_pde_names_list, char *name);

// Prototypes
char                        *ud_pde_layer_add_ctr(char *csv_path, ud_layer_grade layer_grade, char *layer_name, void *layer, ud_layer_type type, char **before_layers, ud_bool free);
void                        ud_pde_names_list_init_begin(ud_pde_names_list *list, char *csv_path, char *name, char *csv, ud_bool allower);
char                        *ud_pde_stringify_desc_ctr(char *name, char *grade, char *layer_type);
char                        *ud_pde_stringify_before_layers(char **before_layers);
char                        *ud_pde_cond_str(int cond, char *str, char *name, char *value, char *cond_str);

#endif