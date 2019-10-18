#include "ud_protodeep_edition.h"

char    *ud_pde_check_names(char *layer_name, char *layer_list)
{
    if (!layer_list)
        return NULL;
    char    **names = ud_str_split(layer_list, ",");
    char    **p_names = names;
    for (; *p_names; ++p_names)
    {
        if (!ud_str_cmp(layer_name, *p_names)) ud_ut_error("Same name used twice (%s).", layer_name);
        if (*(p_names + 1)) ud_ut_free(*p_names);
    }
    --p_names;
    char *last_name = ud_str_dup(*p_names);
    ud_ut_free(names);
    return last_name;
}

char    *ud_pde_auto_name(void)
{
    char *name = "layer";
    static int id = 0;
    return ud_str_cat(name, ud_math_itoa(id++));
}

char    *ud_pde_layer_add_ctr(char *csv_path, ud_layer_grade layer_grade, char *layer_name, void *layer, ud_layer_type type, ud_arr *before_layers)
{
    if (!csv_path) ud_ut_error("No csv file to save the network provided.");

    if (!layer_name || !layer_name[0] || !ud_str_cmp(layer_name, "NULL")) layer_name = ud_pde_auto_name();
    else layer_name = ud_str_escape(layer_name);

    static ud_arr *(*f[UD_NB_STRINGIFY_FT])(void *, char *, ud_layer_grade, ud_arr *, char*[]) = {UD_STRINGIFY_FT};
    static char *layer_list = NULL;
    char *grades[] = {"input", "hidden", "output"};

    char *last_layer = ud_pde_check_names(layer_name, layer_list);
    if (before_layers->len <= 1) before_layers = last_layer ? ud_stra_new(last_layer) : ud_stra_new("NULL");
    ud_arr *csv = f[type](layer, layer_name, layer_grade, before_layers, grades);
    ud_file_write_append(csv_path, csv);
    layer_list = layer_list ? ud_str_vjoin(",", layer_list, layer_name) : layer_name;
    return (layer_name);
}