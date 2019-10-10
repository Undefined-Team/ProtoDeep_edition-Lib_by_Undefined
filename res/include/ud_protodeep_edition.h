#ifndef UD_PROTODEEP_EDITION_H
# define UD_PROTODEEP_EDITION_H

// Lib
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ud_array.h>
#include <ud_math_array.h>
#include <ud_string_array.h>
#include <ud_file.h>
#include <ud_protodeep_core.h>

// Macro
# define ud_dense(_name, ...)                                       #_name, ({ ud_dense _name = { __VA_ARGS__}; &_name; }), UD_LT_FULLCO
# define ud_convolution(_name, ...)                                 #_name, ({ ud_convolution _name = {__VA_ARGS__}; &_name; }), UD_LT_CONV

# define ud_pde_layer_add(csv_path, layer_type, ...)                ud_pde_layer_add_ctr(csv_path, UD_LG_HIDDEN, layer_type, ud_stra_vjoin(", ", __VA_ARGS__))
# define ud_pde_layer_add_input(csv_path, layer_type, ...)          ud_pde_layer_add_ctr(csv_path, UD_LG_INPUT, layer_type, ud_stra_vjoin(", ", __VA_ARGS__))
# define ud_pde_layer_add_output(csv_path, layer_type, ...)         ud_pde_layer_add_ctr(csv_path, UD_LG_OUTPUT, layer_type, ud_stra_vjoin(", ", __VA_ARGS__))

// Structures
typedef struct uds_dense_params {
    size_t nb_neurons;
    char *activation;
}   ud_dense;

typedef struct uds_convolution_params {
    size_t kernel_size;
    size_t strides;
    char *activation;
}   ud_convolution;

// Prototypes
char    *ud_pde_layer_add_ctr(char *csv_path, ud_layer_grade layer_grade, char *layer_name, void *layer, ud_layer_type type, ud_arr *before_layers);

#endif