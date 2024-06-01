import numpy as np

class DataPoint:
    def __init__(self, x, y, group):
        self.x = float(x)
        self.y = float(y)
        self.group = group

    def printPoint(self):
        print(self.x, self.y, self.group)

    def getClassifier(self):
        return self.group

path = "homework_classify_train_2D.dat"
trainingData1 = []
trainingData2 = []
with open(path, "r") as data:
    for line in data:
        items = line.split()
        if (items[2] == '1'):
            trainingData1.append([float(items[0]), float(items[1])])
        else:
            trainingData2.append([float(items[0]), float(items[1])])

path = "homework_classify_test_2D.dat"
testData = []
with open(path, "r") as data:
    for line in data:
        items = line.split()
        testData.append([[float(items[0]), float(items[1])], float(items[2])])

mu_1 = np.mean(trainingData1, axis=0)
mu_2 = np.mean(trainingData2, axis=0)

def getG(x, mu):
    return 2 * np.dot(x, mu) - np.dot(mu, mu)

for x in testData:
    print(x[0])
    g1 = getG(x[0], mu_1)
    g2 = getG(x[0], mu_2)

    if g1 > g2:
        print("Prediction:",1, "| Actual:", int(x[1]))
    else:
        print("Prediction:",2, "| Actual:", int(x[1]))

