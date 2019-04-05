#ifndef PLANN_LIBRARY_H
#define PLANN_LIBRARY_H

#include <vector>


namespace plann {
    class Model;
    class Layer;

    using elementary_operation = float(*)(float, float);

    class Matrix {
    private:
        int m;
        int n;
        float* data;

        static void element_wise_operation(Matrix s1, Matrix s2, Matrix result, elementary_operation operation);
    public:

    };

    class ActivationFunction {

    };

    class TrainCache {
        Matrix dW;
        Matrix db;
        Matrix z;
        Matrix dz;

        friend class Layer;
        friend class Model;

        TrainCache(int previous_units_number, int current_units_number, int batch_size);
    };

    // this is Data
    class Activation {
    private:
        Matrix A;
        Matrix dA;

        friend class Layer;
        friend class Model;
    };


    class Layer {
    private:
        int units_number;
        Matrix W;
        Matrix b;
        TrainCache train_cache;

        void init_weights(int previous_unit_number);
        void allocate_train_cache();
        void free_train_cache();
        void update_weights();
    public:
        Layer(int units_number, ActivationFunction activation_function);
        void forward(Activation& prev_data, Activation& next_data);
        void backward(Activation&next_data, Activation& prev_data);

        friend class Model;
    };


    class LossFunction {
    public:
        LossFunction() {};
        float calculate_loss(Matrix prediction, Matrix y);
    };

    using cost_function = double(*)(Matrix, Matrix);

    class Model {
    private:
        int input_size;
        std::vector<Layer> layers;

    public:
        Model(int input_size, std::vector<Layer>& layers);
        Matrix predict(Matrix input);
        void fit(
                Matrix x,
                Matrix y,
                int batch_size,
                float rate,
                int epochs,
                LossFunction loss_function
         );
    };



}

#endif,