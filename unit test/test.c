#include <ud_protodeep_edition.h>

ud_pde_allow_overwrite

int main(void)
{
    char *csv = "network.csv";
    char *input = ud_pde_layer_add_input(csv, ud_dense(input, .neurons_shape = ud_shape(16), .activation = "relu"));
    char *test = ud_pde_layer_add(csv, ud_dense("dense1", .neurons_shape = ud_shape(16), .activation = "relu"));
    char *dense3 = ud_pde_layer_add(csv, ud_dense(dense3, .activation = "relu", .neurons_shape = ud_shape(16)), "dense1", "dense2");
    ud_pde_layer_add(csv, ud_dense(NULL));
    ud_pde_layer_add(csv, ud_dense());
    ud_pde_layer_add(csv, ud_dense());
    ud_pde_layer_add(csv, ud_dense());
    ud_pde_layer_add(csv, ud_conv("conv1", "tanh", ud_shape(3), 2));
    ud_pde_layer_add(csv, ud_conv("conv2", .kernel_size = ud_shape(2, 3, 4), .activation = "tanh", .strides = 2));
    ud_pde_layer_add(csv, ud_maxpool(maxpool, ud_shape(2, 2), 2));
    ud_pde_layer_add(csv, ud_rnn(rnn, "tanh"));
    ud_pde_layer_add(csv, ud_dropout(dropout, "relu", ud_shape(5, 3), 0.1));
    ud_pde_layer_add(csv, ud_lstm(lstm, "relu", "tanh", "valid"));
    char *output = ud_pde_layer_add_output(csv, ud_dense(output, .neurons_shape = ud_shape(16), .activation = "relu"));
}