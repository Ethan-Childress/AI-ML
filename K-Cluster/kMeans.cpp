#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <limits>
#include <string>

void writeCentroidToFile(const std::pair<std::pair<double, double>, std::pair<double, double>>& centroid, const std::vector<std::pair<std::pair<double, double>, std::pair<double, double>>>& clusteredData, int centroidIndex, int size) {
    std::ofstream outFile("centroid_" + std::to_string(centroidIndex) + ".txt");
    if (outFile.is_open()) {
        outFile << "Centroid " << centroidIndex << ": " << centroid.first.first << ", " << centroid.first.second << std::endl;
        outFile << "Count: " << size << std::endl;
        
        // Write each point's x and y coordinates
        for (const auto& point : clusteredData) {
            if (point.second.first == centroid.first.first && point.second.second == centroid.first.second) {
                outFile << point.first.first << std::endl;
            }
        }

        outFile << "\n" << std::endl;

        for (const auto& point : clusteredData) {
            if (point.second.first == centroid.first.first && point.second.second == centroid.first.second) {
                outFile << point.first.second << std::endl;
            }
        }
        
        outFile.close();
    } else {
        std::cerr << "Unable to open file for writing centroid " << centroidIndex << std::endl;
    }
}
void initializeData(std::vector<std::pair<std::pair<double, double>, std::pair<double, double>>>& data) {
    std::ifstream myfile("HW_5_cluster_data_2D.dat");
    
    if (myfile.is_open()) {
        double x, y;
        while (myfile >> x >> y) {
            data.emplace_back(std::make_pair(x, y), std::make_pair(NULL,NULL));
        }
        myfile.close();
    } 
    else {
        std::cerr << "Unable to open file" << std::endl;
    }
}

double calcEuclidianDistance(std::pair<std::pair<double, double>, std::pair<double, double>> point, std::pair<std::pair<double, double>, std::pair<double, double>> mean) {
    // [(aX-bX)^2 + (aY-bY)^2]^.5
    double verticalDist = mean.first.second - point.first.second;
    double lateralDist = mean.first.first - point.first.first;
    lateralDist *= lateralDist;
    verticalDist *= verticalDist;
    return sqrt(lateralDist + verticalDist);
}

void calculateClusterMean(std::vector<std::pair<std::pair<double, double>, std::pair<double, double>>>& data, std::pair<std::pair<double, double>, std::pair<double, double>>& centroid, bool& change) {
    double xMean;
    double yMean;
    double xTotal = 0;
    double yTotal = 0;
    int counter = 0;
    
    for (const auto& item : data) {
        if (item.second.first == centroid.first.first && item.second.second == centroid.first.second) {
            counter++;
            double x = item.first.first;
            double y = item.first.second;
            xTotal+=x;
            yTotal+=y;
        }
        else {
        }
    }

    xMean = xTotal / counter;
    yMean = yTotal / counter;

    double checkXBefore = centroid.first.first; 
    double checkYBefore = centroid.first.second;

    std::cout << "B: " << centroid.first.first << ", " << centroid.first.second << std::endl;

    centroid.first.first = xMean;
    centroid.first.second = yMean;

    double checkXAfter = centroid.first.first; 
    double checkYAfter = centroid.first.second;

    std::cout << "A: " << centroid.first.first << ", " << centroid.first.second << std::endl;

    if (checkXBefore == checkXAfter && checkYBefore == checkYAfter) {
        std::cout << "No Change Detected!" << std::endl;
        change = false;
    } else {
        change = true;
    }

}

void kMeansAlgorithm(std::vector<std::pair<std::pair<double, double>, std::pair<double, double>>>& data, int clusterCount, std::vector<std::pair<std::pair<double, double>, std::pair<double, double>>>& centroids) {
   
    //Init k random points
    //std::vector<std::pair<std::pair<double, double>, std::pair<double, double>>> centroids;
    srand(time(0)); //Seed rand with current time

    for (int i=0; i<clusterCount; i++){
        int randomIndex = rand() % 200;
        centroids.push_back(std::make_pair(std::make_pair(data[randomIndex].first.first, data[randomIndex].first.second),
        std::make_pair(data[randomIndex].second.first,data[randomIndex].second.second)));
    }

    int p1Counter = 0;
    int p2Counter = 0;
    int p3Counter = 0;
    int jCounter;
    bool change = true;
    
    int counter = 0;

    while (change == true) {
        change = false;
        for (auto& point : data) {
            std::pair<std::pair<double, double>, std::pair<double, double>> currentBestPair;
            double shortestDist = std::numeric_limits<double>::max();
            for (int j=0; j<clusterCount; j++){
                jCounter = 0;
                double distance = calcEuclidianDistance(point, centroids[j]);
                jCounter++;
                if (distance < shortestDist) {
                    shortestDist = distance;
                    currentBestPair = std::make_pair(std::make_pair(centroids[j].first.first,centroids[j].first.second),std::make_pair(centroids[j].second.first,centroids[j].second.second));
                }
            }

            point.second = std::make_pair(currentBestPair.first.first, currentBestPair.first.second); // Update point's centroid
            //std::cout << "Centroid " << jCounter << " updated with: " << point.second.first << ", " << point.second.second << std::endl;

            if (currentBestPair == centroids[0]) {
                p1Counter++;
            }
            else if (currentBestPair == centroids[1]) {
                p2Counter++;
            }
            else if (currentBestPair == centroids[2]) {
                p3Counter++;
            }
            
            //PRINT
            //std::cout << "Distance: " << shortestDist << ", To: (" << currentBestPair.first.first << ", " << currentBestPair.first.second << ")" << std::endl;
            counter++;
        }
        
        //Calculate new centroids
        for (auto& point : centroids) {
            calculateClusterMean(data, point, change);
        }
    }
    //Cluster Vectors
    std::vector<std::pair<std::pair<double, double>, std::vector<std::pair<double, double>>>> cluster1;
    std::vector<std::pair<std::pair<double, double>, std::vector<std::pair<double, double>>>> cluster2;
    std::vector<std::pair<std::pair<double, double>, std::vector<std::pair<double, double>>>> cluster3;

    //PRINT
    // for (const auto& item : centroids) {
    //     std::cout << item.first.first << ", " << item.first.second << std::endl;
    // }

    //PRINT
    // std::cout << "Cluster 1: (" << centroids[0].first.first << ", " << centroids[0].first.second << ") " 
    //       << "\nCount: " << p1Counter << std::endl;
    // std::cout << "Cluster 2: (" << centroids[1].first.first << ", " << centroids[1].first.second << ") " 
    //       << "\nCount: " << p2Counter << std::endl;
    // std::cout << "Cluster 3: (" << centroids[2].first.first << ", " << centroids[2].first.second << ") " 
    //       << "\nCount: " << p3Counter << std::endl;


}

void organizeDataByCentroid(const std::vector<std::pair<std::pair<double, double>, std::pair<double, double>>>& data,
                            const std::vector<std::pair<std::pair<double, double>, std::pair<double, double>>>& centroids,
                            std::vector<std::vector<std::pair<std::pair<double, double>, std::pair<double, double>>>>& clusteredData) {
    
    clusteredData.clear();
    clusteredData.resize(centroids.size());

    // Loop through data and assign points to corresponding centroids
    for (const auto& point : data) {
        double shortestDist = std::numeric_limits<double>::max();
        int closestCentroidIndex = -1;

        // Find the closest centroid for the current point
        for (size_t i = 0; i < centroids.size(); ++i) {
            double distance = calcEuclidianDistance(point, centroids[i]);
            if (distance < shortestDist) {
                shortestDist = distance;
                closestCentroidIndex = static_cast<int>(i);
            }
        }

        // Assign the point to the cluster corresponding to the closest centroid
        clusteredData[closestCentroidIndex].push_back(point);
    }
}

int main() {
    std::vector<std::pair<std::pair<double, double>, std::pair<double, double>>> data;
    int clusterCount = 3;
    initializeData(data);

    std::vector<std::pair<std::pair<double, double>, std::pair<double, double>>> centroids;
    kMeansAlgorithm(data, clusterCount, centroids);

    std::vector<std::vector<std::pair<std::pair<double, double>, std::pair<double, double>>>> clusteredData;
    organizeDataByCentroid(data, centroids, clusteredData);

    int counter = 0;
    for (const auto& point : centroids) {
        counter++;
        std::cout << "Centroid " << counter << ": " << point.first.first << ", " << point.first.second << std::endl;
        std::cout << "Count: " << clusteredData[counter-1].size() << std::endl;
        writeCentroidToFile(point, clusteredData[counter-1], counter, clusteredData[counter-1].size());
    } 

    return 0;
}