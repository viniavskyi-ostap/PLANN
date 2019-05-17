#include <plann_math.h>
#include <cmath>

Matrix softmax(const Matrix& x) {
    Matrix result(x.get_rows_number(), x.get_columns_number());

    x.map([](float v){ return expf(v); }, &result);

    for (int i = 0; i < result.get_rows_number(); ++i) {
        float row_sum = 0;
        for (int j = 0; j < result.get_columns_number(); ++j) {
            row_sum += result.get(i, j);
        }

        for (int j = 0; j < result.get_columns_number(); ++j) {
            result.set(i, j, result.get(i, j) / row_sum);
        }
    }

    return result;
}

