#include "ud_protodeep_edition.h"

char    *ud_pde_layer_add_ctr(char *csv_path, ud_layer_grade layer_grade, char *layer_name, void *layer, ud_layer_type type, ud_arr *before_layers)
{
    if (!csv_path)
        ud_ut_error("No csv file to save the network provided.");
    static ud_arr *(*f[UD_NB_STRINGIFY_FT])(void *, char *, ud_layer_grade, ud_arr *, char*[]) = {UD_STRINGIFY_FT};
    static char *grades[] = {"input", "hidden", "output"};
    static char *last_name = NULL;
    if (!before_layers->len) before_layers = ud_stra_new(last_name);
    ud_arr *csv = f[type](layer, layer_name, layer_grade, before_layers, grades);
    ud_file_write_append(csv_path, csv);
    last_name = layer_name;
    return (layer_name);
}