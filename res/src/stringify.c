#include "ud_protodeep_edition.h"

char                      *ud_pde_int_array_to_str(size_t *array)
{
    if (!array) return ud_str_dup("0");
    char  *string = ud_str_dup("");
    for (ud_ut_count i = 1; i <= array[0]; ++i)
        string = ud_str_vfjoin(i > 1 ? "*" : "", string, ud_math_itoa(array[i]));
    return string;
}

char                        *ud_pde_cond_str(int cond, char *str, char *name, char *value, char *cond_str)
{
    if (cond) return str;
    else ud_ut_error("Value %s of layer of type %s does not match expectations (%s->%s %s).", value, name, name, value, cond_str);
    return NULL;
}

char                        *ud_pde_stringify_desc_ctr(char *name, char *grade, char *layer_type)
{
    return ud_str_vjoin(", ", name, grade, layer_type);
}

char                        *ud_pde_stringify_before_layers(char **before_layers)
{
    char *ret = ud_str_vrjoin(before_layers, "; ");
    ud_ptr_free(before_layers, 1);
    return ret;
}

char                      *ud_pde_stringify_dense(void *p_dense, char *name, ud_layer_grade layer_grade, char **before_layers, char *grades[])
{
    ud_dense_params     *dense = (ud_dense_params *)p_dense;

    char  *str = ud_pde_stringify(dense,
        UD_PDE_STR(dense, activation),
        UD_PDE_INT_ARRAY(dense, neurons_shape)
    );
    ud_ut_free(dense->neurons_shape);
    return str;
}

char                      *ud_pde_stringify_conv(void *p_conv, char *name, ud_layer_grade layer_grade, char **before_layers, char *grades[])
{
    ud_conv_params     *conv = (ud_conv_params *)p_conv;

    char  *str = ud_pde_stringify(conv,
        UD_PDE_STR(conv, activation),
        UD_PDE_INT_ARRAY(conv, kernel_size),
        UD_PDE_INT(conv, strides)
    );
    ud_ut_free(conv->kernel_size);
    return str;
}

char                      *ud_pde_stringify_maxpool(void *p_maxpool, char *name, ud_layer_grade layer_grade, char **before_layers, char *grades[])
{
    ud_maxpool_params     *maxpool = (ud_maxpool_params *)p_maxpool;

    char  *str = ud_pde_stringify(maxpool,
        UD_PDE_INT_ARRAY(maxpool, pool_size),
        UD_PDE_INT(maxpool, strides)
    );
    ud_ut_free(maxpool->pool_size);
    return str;
}

char                      *ud_pde_stringify_rnn(void *p_rnn, char *name, ud_layer_grade layer_grade, char **before_layers, char *grades[])
{
    ud_rnn_params     *rnn = (ud_rnn_params *)p_rnn;

    char  *str = ud_pde_stringify(rnn,
        UD_PDE_STR(rnn, activation)
    );
    return str;
}

char                      *ud_pde_stringify_lstm(void *p_lstm, char *name, ud_layer_grade layer_grade, char **before_layers, char *grades[])
{
    ud_lstm_params     *lstm = (ud_lstm_params *)p_lstm;

    char  *str = ud_pde_stringify(lstm,
        UD_PDE_STR(lstm, activation),
        UD_PDE_STR(lstm, recurrent_activation),
        UD_PDE_STR(lstm, padding)
    );
    return str;
}

char                      *ud_pde_stringify_dropout(void *p_dropout, char *name, ud_layer_grade layer_grade, char **before_layers, char *grades[])
{
    ud_dropout_params     *dropout = (ud_dropout_params *)p_dropout;

    char  *str = ud_pde_stringify(dropout,
        UD_PDE_STR(dropout, activation),
        UD_PDE_INT_ARRAY(dropout, neurons_shape),
        UD_PDE_FLOAT(dropout, dropout_rate)
    );
    ud_ut_free(dropout->neurons_shape);
    return str;
}