#!/bin/python3
import math
import os
import random
import re
import sys
import ast
import numpy as np

class OpConv2D:
    def __init__(self, filters_count, kernel_size, inputs):
        self.inputs = inputs
        self.kernel_size = kernel_size
        
        # Shape of the input feature map
        input_height = inputs.shape[0]
        input_width = inputs.shape[1]
        input_channels = inputs.shape[2]
    
        # Shape of this layer's output feature map
        self.output_height = input_height - kernel_size + 1
        self.output_width = input_width - kernel_size + 1
        self.output_channels = filters_count
    
        # self.weights contains filters_count filters of shape: kernel_size x kernel_size x input_channels
        self.weights = np.random.normal(size=(filters_count, kernel_size, kernel_size, input_channels), scale=0.1)
    
    def forward(self):
        Z = np.zeros((self.output_height, self.output_width, self.output_channels), dtype=np.float32)

        for h in range(self.output_height):
            for w in range(self.output_width):
                # Apply all filters
                for c in range(self.output_channels):
                    for i in range(self.kernel_size):
                        for j in range(self.kernel_size):
                            for k in range(self.weights.shape[-1]):
                                z += self.inputs[h + i, w + j, k] * self.weights[c][i][j][k]
                    Z[h, w, c] = z
        return Z

    # dZ is the derivate of the loss with respect to the output of this layer's forward propagation.
    def backward(self, dZ):
        dW = np.zeros(self.weights.shape, dtype=np.float32)
        dA_prev = np.zeros(self.inputs.shape, dtype=np.float32)

        X, W = self.inputs, self.weights

        ks = self.kernel_size

        height, width, channel = dZ.shape
        #enter you code here
        for h in range(height):
            for w in range(width):
                for c in range(self.output_channels):
                    for i in range(self.weights.shape[-1]):
                        dA_prev[h:h + ks, w:w + ks, i] += W[c, :, :, i] * dZ[h, w, c]
                        dW += X[h:h + ks, w:w + ks, i] * dZ[h, w, c]
        
        return (dW, dA_prev)

a = eval(input())
a = np.array(a)
