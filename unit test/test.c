#include <ud_protodeep_edition.h>

int main(void)
{
    char *dense1 = ud_pde_layer_add("./network.csv", ud_dense(dense1, .nb_neurons = 16, .activation = "relu"), NULL);
    ud_pde_layer_add("./network.csv", ud_dense(dense2, 16, .activation = "relu"), dense1);
    char *dense3 = ud_pde_layer_add("./network.csv", ud_dense(dense3, .activation = "relu", .nb_neurons = 16), dense1, "dense2");
    ud_pde_layer_add("./network.csv", ud_dense(dense4), dense1, "dense2", dense3);
    ud_pde_layer_add("./network.csv", ud_dense(dense5), NULL);
    ud_pde_layer_add("./network.csv", ud_convolution(conv1, 3, 2, "tanh"), dense1, dense3);
    ud_pde_layer_add("./network.csv", ud_convolution(conv2, .kernel_size = 2, .activation = "tanh", .strides = 2), "conv1");
}