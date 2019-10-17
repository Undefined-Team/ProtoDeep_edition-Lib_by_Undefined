#include "ud_protodeep_edition.h"

char                      *ud_pde_int_array_to_str(ud_arr *array)
{
    char  *string = ud_str_dup("{");
    size_t  *t_array_val = (size_t *)array->val;
    for (ud_ut_count i = 0; i <= t_array_val[0]; ++i)
        string = ud_str_vjoin("*", ud_math_itoa(t_array_val[i]));
    string = ud_str_cat(string, "}");
    printf("%s\n", string);
    return string;
}

ud_arr                      *ud_pde_stringify_dense(void *p_dense, char *name, ud_layer_grade layer_grade, ud_arr *before_layers, char *grades[])
{
    ud_dense_params     *dense = (ud_dense_params *)p_dense;

    ud_arr  *str = ud_pde_stringify(dense,
        UD_PDE_INT(dense, nb_neurons),
        UD_PDE_STR(dense, activation)
    );
    return str;
}

ud_arr                      *ud_pde_stringify_conv(void *p_conv, char *name, ud_layer_grade layer_grade, ud_arr *before_layers, char *grades[])
{
    ud_conv_params     *conv = (ud_conv_params *)p_conv;

    ud_arr  *str = ud_pde_stringify(conv,
        UD_PDE_INT(conv, strides),
        UD_PDE_STR(conv, activation)
    );
    return str;
}