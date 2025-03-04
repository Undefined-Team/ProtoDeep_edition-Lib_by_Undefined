#include "ud_protodeep_edition.h"

void __attribute__ ((destructor))  ud_pde_layers_dtor() { ud_pde_layer_free(); }

ud_list_define(ud_pde_names_list, ud_list_ud_pde_names_list_free, NULL);

void    ud_list_ud_pde_names_list_free(void *val)
{
    ud_pde_names_list *elem = (ud_pde_names_list *)val;
    ud_ut_free(elem->name);
    ud_ut_free(elem);
}

void    ud_pde_check_names(char *layer_name, ud_pde_names_list *layer_list)
{
    if (!layer_list)
        return;
    ud_pde_names_list *p_layer_list = layer_list;
    for (; p_layer_list; p_layer_list = p_layer_list->next)
        if (!ud_str_cmp(layer_name, p_layer_list->name)) ud_ut_error("Same name used twice (%s).", layer_name);
}

char    *ud_pde_auto_name(char *layer_name)
{
    if (layer_name) ud_ut_free(layer_name);
    static int id = 0;
    char *id_str = ud_math_itoa(id++);
    char *ret = ud_str_cat("layer", id_str);
    ud_ut_free(id_str);
    return ret;
}

void    ud_pde_names_list_init_begin(ud_pde_names_list *list, char *csv_path, char *name, char *csv, ud_bool allower)
{
    static ud_bool overwrite = false;
    if (allower)
    {
        overwrite = true;
        return;
    }
    else if (overwrite)
        ud_file_clear(csv_path);
    if (!overwrite && ud_file_exists(csv_path))
    {
        char buf[2] = {0};
        char inputs[] = "oOlLaA";
        int input_opt;
        int len;
        while (1)
        {
            printf("> File %s already exists, what do you want to do ? [o]verwrite [a]ppend [l]eave\n(you can add ud_pde_allow_overwrite before your main function to disable this warning)\n", csv_path);
            len = read(STDIN_FILENO, buf, 1);
            if (len < 0) ud_ut_error("Error while reading input on stdin.");
            if ((input_opt = ud_str_chr(inputs, buf[0])) > -1) break;
            while (buf[0] != '\n' && read(STDIN_FILENO, buf, 1));
        }
        while (buf[0] != '\n' && read(STDIN_FILENO, buf, 1));
        if (input_opt < 2)
            ud_file_clear(csv_path);
        else if (input_opt < 4)
        {
            ud_ut_free(list);
            ud_ut_free(name);
            ud_ut_free(csv);
            exit(EXIT_SUCCESS);
        }
    }
    list->name = name;
    list->next = NULL;
}

char    *ud_pde_layer_add_ctr(char *csv_path, ud_layer_grade layer_grade, char *layer_name, void *layer, ud_layer_type type, char **before_layers, ud_bool free)
{
    static ud_pde_names_list *begin = NULL;
    if (free)
    {
        if (begin) ud_list_free(ud_pde_names_list, begin);
        return NULL;
    }
    if (!csv_path) ud_ut_error("No csv file to save the network provided.");
    if (!layer_name || !layer_name[0] || !ud_str_cmp(layer_name, "NULL")) layer_name = ud_pde_auto_name(layer_name);
    else layer_name = ud_str_fescape(layer_name);

    static char *(*f[UD_NB_STRINGIFY_FT])(void *, char *, ud_layer_grade, char **, char*[]) = {UD_STRINGIFY_FT};
    static ud_pde_names_list *end = NULL;
    char *grades[] = {"input", "hidden", "output"};

    if (!before_layers || !*before_layers)
    {
        if (before_layers) ud_ut_free(before_layers);
        before_layers = end ? ud_ut_array(char *, ud_str_dup(end->name), NULL) : ud_ut_array(char *, ud_str_dup(""), NULL);
    }
    ud_pde_check_names(layer_name, begin);
    char *csv = f[type](layer, layer_name, layer_grade, before_layers, grades);
    if ((!begin && !(begin = ud_list_finit(ud_pde_names_list, ud_pde_names_list_init_begin, csv_path, layer_name, csv, false)))
    || (end && !(end = ud_list_push(end, name = layer_name))) || (!end && !(end = begin)))
        ud_ut_error("Error while storing layer with name %s.", layer_name);
    ud_file_write_append(csv_path, csv);
    ud_ut_free(csv);
    return (layer_name);
}