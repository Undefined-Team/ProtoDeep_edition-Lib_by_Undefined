#include <ud_protodeep_edition.h>

int main(void)
{
    char *csv = "network.csv";
    char *input = ud_pde_layer_add_input(csv, ud_dense(input, .neurons_shape = ud_shape(16), .activation = "relu"), NULL);
    char *test = ud_pde_layer_add(csv, ud_dense("dense1", .neurons_shape = ud_shape(16), .activation = "relu"), NULL);
    char *dense3 = ud_pde_layer_add(csv, ud_dense(dense3, .activation = "relu", .neurons_shape = ud_shape(16)), "dense1", "dense2");
    ud_pde_layer_add(csv, ud_dense(NULL), "dense1", "dense2", "dense3");
    ud_pde_layer_add(csv, ud_dense(), NULL);
    ud_pde_layer_add(csv, ud_dense(), NULL);
    ud_pde_layer_add(csv, ud_dense(), NULL);
    ud_pde_layer_add(csv, ud_conv("conv1", "tanh", ud_shape(3), 2), "dense1", "dense3");
    ud_pde_layer_add(csv, ud_conv("conv2", .kernel_size = ud_shape(2, 3, 4), .activation = "tanh", .strides = 2), "conv1");
    ud_pde_layer_add(csv, ud_maxpool(maxpool, ud_shape(2, 2), 2), NULL);
    ud_pde_layer_add(csv, ud_rnn(rnn, "tanh"), NULL);
    ud_pde_layer_add(csv, ud_lstm(lstm, "relu", "tanh", "valid"), NULL);
    char *output = ud_pde_layer_add_output(csv, ud_dense(output, .neurons_shape = ud_shape(16), .activation = "relu"), NULL);
    ud_pde_free();
}