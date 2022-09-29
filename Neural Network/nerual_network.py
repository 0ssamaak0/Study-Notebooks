import numpy as np

# helper functions

# activations

def sigmoid(z):
    return 1 / (1 + np.exp(-z))

def relu(z):
    return np.maximum(0, z)

activations = {"sigmoid":sigmoid, "relu": relu}

# activations_derivatives

def sigmoid_prime(z):
    return sigmoid(z) * (1 - sigmoid(z))

def relu_prime(z):
    z = np.copy(z)
    z[z >= 0] = 1
    return np.maximum(0, z)

activations_prime = {"sigmoid_prime":sigmoid_prime, "relu_prime": relu_prime}

# 1. parameter_initialization
def initialize_parameters(layers_dims):
    parameters = {}

    for l in range(1,len(layers_dims)):
        parameters[f"W{l}"] = np.random.randn(layers_dims[l], layers_dims[l - 1]) # * 0.01 or any factor e.g., sqrt of length
        parameters[f"b{l}"] = np.zeros((layers_dims[l], 1))
    
    return parameters



# 2. forward propagation
def forward_propagation(X, parameters):
    L = len(parameters) // 2

    A = X
    caches = []

    # hidden layers
    for l in range(1 , L):
        A_prev = A
        Z = (parameters[f"W{l}"] @ A_prev) + parameters[f"b{l}"]
        caches.append((A_prev, parameters[f"W{l}"], parameters[f"b{l}"], Z))
        A = activations["relu"](Z)

    # Layer L (output)
    A_prev = A
    Z = (parameters[f"W{L}"] @ A_prev) + parameters[f"b{L}"]
    caches.append((A_prev, parameters[f"W{L}"], parameters[f"b{L}"], Z))
    AL = activations["sigmoid"](Z)

    return AL, caches



# 3. cost computation
def compute_cost(AL, Y):
    m = Y.shape[1]
    return - (1 / m) * np.sum((np.log(AL) * Y) + (np.log(1 - AL) * (1 - Y)))



# 4. backward propagation
def backward_propagation(AL, Y, caches):
    L = len(caches)

    dAL = ((1 - Y) / (1 - AL)) - (Y / AL)
    m = Y.shape[1]
    grads = {}
    
    # Layer L (output)
    current_cache = caches[L - 1]
    A, W, Z = (current_cache[0], current_cache[1], current_cache[3])


    dZL = dAL * activations_prime["sigmoid_prime"](Z)
    grads[f"dA{L - 1}"] = W.T @ dZL
    grads[f"dW{L}"] = (1 / m) * (dZL @ A.T)
    grads[f"db{L}" ] = (1 / m) * np.sum(dZL, axis = 1, keepdims = True)


    # hidden layers
    for l in reversed(range(L-1)):
        current_cache = caches[l]
        A, W, Z = (current_cache[0], current_cache[1], current_cache[3])


        dZ = grads[f"dA{l + 1}"] * activations_prime["relu_prime"](Z)
        grads[f"dA{l}"] = W.T @ dZ
        grads[f"dW{l + 1}"] = (1 / m) * (dZ @ A.T)
        grads[f"db{l + 1}" ] = (1 / m) * np.sum(dZ, axis = 1, keepdims = True)

    return grads



# 5. update parameters
def update_parameters(parameters, grads, learning_rate):
    parameters = parameters.copy()
    L = len(parameters) // 2

    for l in range(L):
        parameters[f"W{l + 1}"] = parameters[f"W{l + 1}"] - learning_rate * grads[f"dW{l + 1}"]
        parameters[f"b{l + 1}"] = parameters[f"b{l + 1}"] - learning_rate * grads[f"db{l + 1}"]
    
    return parameters


# Combining
def neural_network(X, Y, layers_dims, learning_rate, num_iterations):
    parameters = initialize_parameters(layers_dims)

    for i in range(0, num_iterations):

        AL, caches = forward_propagation(X, parameters)

        cost = compute_cost(AL, Y)
        if i % 100 == 0:
            print(f"cost after iteration {i}: {cost}")
        
        grades = backward_propagation(AL, Y, caches)

        parameters = update_parameters(parameters, grades, learning_rate)
    return parameters, cost