// Copyright , by Charles Yiu
//   URL: https://yiu.ch/arles https://github.com/charlesyiu
//  All rights reserved. Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
// following conditions are met:
//     Redistributions of source code must retain the above copyright notice, this list of conditions and the
//     following disclaimer.
//     Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
//   following disclaimer in the documentation and/or other materials provided with the distribution.
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
//   USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

//
// Created by charles yiu on 25/3/2023.
//

#include <stdio.h>
#include <stdlib.h>

int request_int(char* query) {
    int requested;
    printf("%s: ", query);
    scanf("%d", &requested);
    return requested;
}

int remove_element(int index, int** array, int* count) {
    register int shift_index;
    for (shift_index = index + 1; shift_index < *count; shift_index++) {
        (*array)[shift_index - 1] = (*array)[shift_index];
    }
    *count -= 1;
    *array = realloc(*array, sizeof(int) * *count);
    return 0;
}

int main() {
    int inputs = request_int("number of inputs");

    register int inputs_index;
    for (inputs_index = 0; inputs_index < inputs; inputs_index++) {
        int input_length = request_int("length of input");
        int input_values[input_length];
        int input_sum = 0;

        register int input_index;
        for (input_index = 0; input_index < input_length; input_index++) {
            input_values[input_index] = request_int("value for input");
            input_sum = input_sum + input_values[input_index];
        }

        register int divisor;
        int actions = 0;
        for (divisor = 0; divisor <= input_sum; divisor++) {
            if (input_sum % divisor == 0) {
                int valid = 1;
                int input_length_ = input_length;
                int* input_values_ = malloc(sizeof(int) * input_length_);
                actions = 0;
                for (input_index = 0; input_index < input_length; input_index++) {
                    input_values_[input_index] = input_values[input_index];
                }

                while (input_length_ > 0 && valid) {
                    int first_index = -1;

                    register int index;
                    for (index = 0; index < input_length_; index++) {
                        if (input_values_[index] < divisor) {
                            if (first_index == -1)
                                first_index = index;
                            else {
                                input_values_[first_index] = input_values_[first_index] + input_values_[index];
                                remove_element(index, &input_values_, &input_length_);
                                actions += 1;
                                break;
                            }
                        }
                        else if (input_values_[index] == divisor)
                            remove_element(index, &input_values_, &input_length_);
                        else {
                            valid = 0;
                            break;
                        }
                    }
                }
                free(input_values_);
                if (valid == 1)
                    break;
            }
        }
        printf("actions: %d\n", actions);
    }

    return 0;
}
