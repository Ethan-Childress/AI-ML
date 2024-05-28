import numpy as np
import matplotlib.pyplot as plt

# Get training data
path = "homework_classify_train_2D.dat"
trainingData = []
with open(path, "r") as data:
    for line in data:
        items = line.split()
        inputs = [float(items[0]), float(items[1])]
        data_point = (inputs, int(items[2])-1)
        trainingData.append(data_point)

# Get test data
path = "homework_classify_test_2D.dat"
testData = []
with open(path, "r") as data:
    for line in data:
        items = line.split()
        inputs = [float(items[0]), float(items[1])]
        data_point = (inputs, int(items[2])-1)
        testData.append(data_point)

class Perceptron:
    def __init__(self, num_inputs):
        self.weights = np.random.rand(num_inputs)   # Initialize weights to small random values
        self.bias = 0
        self.learning_rate = 0.000005

    def step_function(self, x):
        return 1 if x >= 0 else 0

    def predict(self, inputs):
        weighted_sum = np.dot(inputs, self.weights) + self.bias
        return self.step_function(weighted_sum)

    def train(self, training_data):
        for _ in range(1000):
            for inputs, label in training_data:
                prediction = self.predict(inputs)
                error = label - prediction
                self.weights += self.learning_rate * error * np.array(inputs)
                self.bias += self.learning_rate * error

perceptron1 = Perceptron(2)
perceptron1.train(trainingData)

# Plotting
def plot_data_and_decision_boundary(perceptron, training_data):
    # Separate the data by classifier
    class_1 = [point[0] for point in training_data if point[1] == 0]
    class_2 = [point[0] for point in training_data if point[1] == 1]
    
    class_1_x = [point[0] for point in class_1]
    class_1_y = [point[1] for point in class_1]
    class_2_x = [point[0] for point in class_2]
    class_2_y = [point[1] for point in class_2]

    # Create the plot
    plt.scatter(class_1_x, class_1_y, color='red', label='Class 1')
    plt.scatter(class_2_x, class_2_y, color='blue', label='Class 2')
    
    # Plot decision boundary
    x_values = np.linspace(min(class_1_x + class_2_x), max(class_1_x + class_2_x), 100)
    y_values = -((perceptron.weights[0] * x_values + perceptron.bias) / perceptron.weights[1])
    
    plt.plot(x_values, y_values, color='green', label='Decision Boundary')
    plt.xlabel('Feature 1')
    plt.ylabel('Feature 2')
    plt.legend()
    plt.show()

plot_data_and_decision_boundary(perceptron1, trainingData)

# Test predictions
for inputs, label in testData:
    prediction = perceptron1.predict(inputs)
    print(f"Input: {inputs}, Predicted: {prediction+1}, Actual: {label+1}")
