#include <ud_protodeep_edition.h>

int main(void)
{
    char *dense1 = ud_pde_layer_add("./network.csv", ud_dense(dense1, .nb_neurons = 16, .activation = "relu"), NULL);
    ud_pde_layer_add("./network.csv", ud_dense(dense2, .activation = "relu", 16), dense1);
    char *dense3 = ud_pde_layer_add("./network.csv", ud_dense(dense3, .activation = "relu", .nb_neurons = 16), dense1, "dense2");
    ud_pde_layer_add("./network.csv", ud_dense(dense4), dense1, "dense2", dense3);
    ud_pde_layer_add("./network.csv", ud_dense(dense5), NULL);
    ud_pde_layer_add("./network.csv", ud_conv(conv1, "tanh", ud_shape(3), 2), dense1, dense3);
    ud_pde_layer_add("./network.csv", ud_conv(conv2, .kernel_size = ud_shape(2, 3, 4), .activation = "tanh", .strides = 2), "conv1");
}