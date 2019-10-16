#include "ud_protodeep_edition.h"

ud_arr  *ud_pde_layer_add_dense(void *p_dense, char *name, ud_layer_grade layer_grade, ud_arr *before_layers, char *grades[])
{
    ud_dense *dense = (ud_dense *)p_dense;

    ud_arr  *csv_format = ud_stra_vjoin(
        NULL,
        name, ", ",
        grades[layer_grade],
        ", dense, {",
        "nb_neurons: ", (char *)ud_matha_itoa(dense->nb_neurons)->val, ", ",
        "activation: ", dense->activation ? dense->activation : "null", before_layers->len ? "}, " : "}",
        (char *)before_layers->val
    );
    return (csv_format);
}

ud_arr  *ud_pde_layer_add_convolution(void *p_convolution, char *name, ud_layer_grade layer_grade, ud_arr *before_layers, char *grades[])
{
    ud_convolution *convolution = (ud_convolution *)p_convolution;

    ud_arr  *csv_format = ud_stra_vjoin(
        NULL,
        name, ", ",
        grades[layer_grade],
        ", convolution, {",
        "kernel_size: ", (char *)ud_matha_itoa(convolution->kernel_size)->val, ", ",
        "strides: ", (char *)ud_matha_itoa(convolution->strides)->val, ", ",
        "activation: ", convolution->activation, before_layers->len ? "}, " : "}",
        (char *)before_layers->val
    );
    return (csv_format);
}

char    *ud_pde_layer_add_ctr(char *csv_path, ud_layer_grade layer_grade, char *layer_name, void *layer, ud_layer_type type, ud_arr *before_layers)
{
    if (!csv_path)
        ud_ut_error("No csv file to save the network provided.");
    static ud_arr *(*f[2])(void *, char *, ud_layer_grade, ud_arr *, char*[]) = {
        ud_pde_layer_add_dense,
        ud_pde_layer_add_convolution
    };
    static char *grades[] = {"input", "hidden", "output"};
    static char *last_name = NULL;
    if (!before_layers->len) before_layers = ud_stra_new(last_name);
    ud_arr *csv = f[type](layer, layer_name, layer_grade, before_layers, grades);
    printf("%s\n", (char *)csv->val);
    last_name = layer_name;
    return (layer_name);
}