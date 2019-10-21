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
                                                                        default: "undefined" \
                                                                    )

// 2; Add params stringify function here
# define UD_STRINGIFY_FT                                            ud_pde_stringify_dense, \
                                                                    ud_pde_stringify_conv, \
                                                                    ud_pde_stringify_maxpool, \
                                                                    ud_pde_stringify_rnn, \
                                                                    ud_pde_stringify_lstm

// 3; Add constructor here
# define ud_dense(_name, ...)                                       #_name, ({ ud_dense_params _tmp = { __VA_ARGS__}; &_tmp; }), UD_LT_DENSE
# define ud_fullco(_name, ...)                                      ud_dense(_name, __VA_ARGS__)
# define ud_conv(_name, ...)                                        #_name, ({ ud_conv_params _tmp = {__VA_ARGS__}; &_tmp; }), UD_LT_CONV
# define ud_maxpool(_name, ...)                                     #_name, ({ ud_maxpool_params _tmp = {__VA_ARGS__}; &_tmp; }), UD_LT_MAXPOOL
# define ud_rnn(_name, ...)                                         #_name, ({ ud_rnn_params _tmp = {__VA_ARGS__}; &_tmp; }), UD_LT_LSTM
# define ud_lstm(_name, ...)                                        #_name, ({ ud_lstm_params _tmp = {__VA_ARGS__}; &_tmp; }), UD_LT_LSTM

// 4; Create params structure
typedef struct              uds_dense_params {
    char                    *activation;
    size_t                  nb_neurons;
}                           ud_dense_params;

typedef struct              uds_conv_params {
    char                    *activation;
    size_t                  *kernel_size;
    size_t                  strides;
}                           ud_conv_params;

typedef struct              uds_maxpool_params {
    size_t                  *pool_size;
    size_t                  strides;
}                           ud_maxpool_params;

typedef struct              uds_rnn_params {
    char                    *activation;
}                           ud_rnn_params;

typedef struct              uds_lstm_params {
    char                    *activation;
    char                    *recurrent_activation;
    char                    *padding;
}                           ud_lstm_params;

//5; Add stringify functions
ud_arr                      *ud_pde_stringify_dense(void *p_dense, char *name, ud_layer_grade layer_grade, ud_arr *before_layers, char *grades[]);
ud_arr                      *ud_pde_stringify_conv(void *p_conv, char *name, ud_layer_grade layer_grade, ud_arr *before_layers, char *grades[]);
ud_arr                      *ud_pde_stringify_maxpool(void *p_conv, char *name, ud_layer_grade layer_grade, ud_arr *before_layers, char *grades[]);
ud_arr                      *ud_pde_stringify_rnn(void *p_conv, char *name, ud_layer_grade layer_grade, ud_arr *before_layers, char *grades[]);
ud_arr                      *ud_pde_stringify_lstm(void *p_conv, char *name, ud_layer_grade layer_grade, ud_arr *before_layers, char *grades[]);

// Macro

# define UD_GET_NB_STRINGIFY_FT(...)                                UD_ARGS_LEN(void *, __VA_ARGS__)
# define UD_NB_STRINGIFY_FT                                         UD_GET_NB_STRINGIFY_FT(UD_STRINGIFY_FT)

# define UD_PDE_INT_COND(cond, layer, value)                        #value": ", ud_pde_cond_str(layer->value cond, (char *)ud_matha_itoa(layer->value)->val, #layer, #value, #cond)
# define UD_PDE_STR_COND(cond, layer, value)                        #value": ", ud_pde_cond_str(layer->value cond, layer->value ? layer->value : "none", #layer, #value, #cond)
# define UD_PDE_INT_ARRAY(layer, value)                             #value": ", ud_pde_int_array_to_str(layer->value)
# define UD_PDE_INT(layer, value)                                   UD_PDE_INT_COND(|| 1, layer, value)
# define UD_PDE_STR(layer, value)                                   UD_PDE_STR_COND(|| 1, layer, value)

# define ud_pde_stringify(type, ...)                                ud_stra_vjoin(", ", ud_pde_stringify_desc(name, layer_grade, type), (char *)ud_stra_vnjoin("; ", 2, __VA_ARGS__)->val, ud_pde_stringify_before_layers(before_layers), "NULL\n")
# define ud_pde_stringify_desc(name, layer_grade, layer_type)       ud_pde_stringify_desc_ctr(name, grades[layer_grade], UD_LT_TO_STR(layer_type))
# define ud_pde_layer_add(csv_path, layer_type, ...)                ud_pde_layer_add_ctr(csv_path, UD_LG_HIDDEN, layer_type, ud_stra_vjoin("; ", __VA_ARGS__))
# define ud_pde_layer_add_input(csv_path, layer_type, ...)          ud_pde_layer_add_ctr(csv_path, UD_LG_INPUT, layer_type, ud_stra_vjoin("; ", __VA_ARGS__))
# define ud_pde_layer_add_output(csv_path, layer_type, ...)         ud_pde_layer_add_ctr(csv_path, UD_LG_OUTPUT, layer_type, ud_stra_vjoin("; ", __VA_ARGS__))

# define ud_shape(...)                                              ud_ut_array(size_t, UD_ARGS_LEN(size_t, __VA_ARGS__), __VA_ARGS__)

// Structures

// Prototypes
char                        *ud_pde_layer_add_ctr(char *csv_path, ud_layer_grade layer_grade, char *layer_name, void *layer, ud_layer_type type, ud_arr *before_layers);
char                        *ud_pde_stringify_desc_ctr(char *name, char *grade, char *layer_type);
char                        *ud_pde_stringify_before_layers(ud_arr *before_layers);
char                        *ud_pde_cond_str(int cond, char *str, char *name, char *value, char *cond_str);

#endif