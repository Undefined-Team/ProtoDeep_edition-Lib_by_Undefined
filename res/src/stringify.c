#include "ud_protodeep_edition.h"

char                      *ud_pde_int_array_to_str(size_t *array)
{
    char  *string = ud_str_dup("{");
    for (ud_ut_count i = 1; i <= array[0]; ++i)
        string = ud_str_vjoin(i > 1 ? "*" : "", string, ud_math_itoa(array[i]));
    string = ud_str_cat(string, "}");
    return string;
}

char                        *ud_pde_cond_str(int cond, char *str, char *name, char *value, char *cond_str)
{
    if (cond)
        return str;
    else
        ud_ut_error("Value %s of layer of type %s does not match expectations (%s->%s %s).", value, name, name, value, cond_str);
    return NULL;
}

char                        *ud_pde_stringify_desc_ctr(char *name, char *grade, char *layer_type)
{
    return ud_str_vjoin(", ", name, grade, layer_type);
}

char                        *ud_pde_stringify_before_layers(ud_arr *before_layers)
{
    return (char *)before_layers->val;
}

ud_arr                      *ud_pde_stringify_dense(void *p_dense, char *name, ud_layer_grade layer_grade, ud_arr *before_layers, char *grades[])
{
    ud_dense_params     *dense = (ud_dense_params *)p_dense;

    ud_arr  *str = ud_pde_stringify(dense,
        UD_PDE_STR(dense, activation),
        UD_PDE_INT(dense, nb_neurons)
    );
    return str;
}

ud_arr                      *ud_pde_stringify_conv(void *p_conv, char *name, ud_layer_grade layer_grade, ud_arr *before_layers, char *grades[])
{
    ud_conv_params     *conv = (ud_conv_params *)p_conv;

    ud_arr  *str = ud_pde_stringify(conv,
        UD_PDE_STR(conv, activation),
        UD_PDE_INT_ARRAY(conv, kernel_size),
        UD_PDE_INT(conv, strides)
    );
    return str;
}