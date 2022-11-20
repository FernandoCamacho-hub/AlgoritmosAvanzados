/*
    E2. Actividad Integradora 2

    Salvador Fernando Camacho Hernandez A01634777
    Emilio Octavio Vazquez FLores A01635304

    Viernes 18 de noviembre del 2022
*/

// #include <iostream>
// #include <vector>
// #include <queue>
// #include <map>
// #include <set>
#include <bits/stdc++.h>
#include <queue>
#include <iostream>
#include <map>
#include <set>
#include <vector>

#define INF INT_MAX

using namespace std;

int N; 

//Time Complexity O(n)
//Space Complexity O(1)
int getMin(vector<int> &dist , vector<bool> &visited){
    int key = 0; 
    int min = INF; 

    for(int i = 0; i < N; i++){
        if(!visited[i] && dist[i] < min){
            min = dist[i]; 
            key = i; 
        }
    }

    return key ; 
}

//Time Complexity O(n)
//Space Complexity O(1)
int getMax(vector<int> &flow, vector<bool> &visited){
    int key = 0; 
    int max = 0; 

    for(int i = 0; i < N; i++){
        if(!visited[i] && flow[i] > max){
            max = flow[i]; 
            key = i; 
        }
    }

    return key ; 
}

//Time Complexity O(n)
//Space Complexity O(1)
void showDistances(vector<int> &distance, int node){
    //assign a letter to each city
    vector<char> letter_cities(N);
    for(int i = 0; i < N; i++){
        letter_cities[i] = i + 65;
    }
    for(int i = 0; i < N; i++){
        if(i != node){
            if(distance[i] == INF){
                cout << "(" << letter_cities[node] << ", " << letter_cities[i] << ") : INF" << endl;
            }
            else{
                cout << "(" << letter_cities[node] << ", " << letter_cities[i] << ") : " << distance[i] << " km" << endl;
            }
        }
    }
}

//Time Complexity O(n^2)
//Space Complexity O(n), if we dont count the matrix the function gets as a parameter. If we count it space complexity is O(n^2)
void dijkstra(int node, vector<vector<int> > &matrix){
    vector<int> distance (N, INF);
    vector<bool> visited (N, false);

    distance[node] = 0;

    for(int i = 0; i < N; i++){
        //get the closest node also current node
        int closest = getMin(distance, visited);
        //mark it as visited
        visited[closest] = true;

        //get the distance from the current node to all the nodes
        for(int j = 0; j < N; j++){
            //check that we havent visited the node and the node has a connection and the distance is less than previous distance
            if(!visited[j] && matrix[closest][j] != INF && (distance[closest] + matrix[closest][j]) < distance[j]) {
                distance[j] = distance[closest] + matrix[closest][j]; 
            }
        }
    }
    //show distances
    showDistances(distance, node);
}

//Time Complexity O(n^3)
//Space Complexity O(n^2)
vector<vector<int> > floydWarshall(vector<vector<int> > &matrix){
    //create result matrix as a copy of the input matrix, initially
    vector<vector<int> > result = matrix;

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            for(int k = 0; k < N; k++){
                if(result[i][k] != INF && result[k][j] != INF && result[i][j] > result[i][k] + result[k][j]){
                    result[i][j] = result[i][k] + result[k][j];
                }
            }
        }
    }

    return result;
}

// algorithm implementation from https://www.geeksforgeeks.org/traveling-salesman-problem-tsp-implementation/

//travelling salesman problem
//Time Complexity O(n^3)
//Space Complexity O(n^2)
vector<char> tsp(vector<vector<int> > &graph, int s) {
    // store path
    vector<char> path;
    //assign a letter to each city
    vector<char> letter_cities;
    for(int i = 0; i < N; i++){
        letter_cities.push_back( i + 65);
    }
    // store all vertex apart from source vertex
    vector<int> vertex;
    for (int i = 0; i < N; i++){
        if (i != s){
            vertex.push_back(i);
        }
    }   
    // store minimum weight Hamiltonian Cycle.
    int min_path = INT_MAX;
    // the person starts in the first city
    path.push_back(letter_cities[0]);
    do {
        // store current Path weight(cost)
        int current_pathweight = 0;
        // compute current path weight
        int k = s;
        for (int i = 0; i < vertex.size(); i++) {
            current_pathweight += graph[k][vertex[i]];
            k = vertex[i];
        }
        current_pathweight += graph[k][s];
        path.push_back(letter_cities[k]);
        // update minimum
        min_path = min(min_path, current_pathweight);
 
    } 
    while (next_permutation(vertex.begin(), vertex.end()));
    // the person finishes in the city they started
    path.push_back(letter_cities[0]);
 
    return path;
    // return min_path;
}

//Time Complexity O(n^2)
//Space Complexity O(n), if we dont count the matrix the function gets as a parameter. If we count it space complexity is O(n^2)
int max_flow(vector<vector<int> > &graph){
    vector<int> distance (N, 0);
    vector<bool> visited (N, false);

    for(int i = 0; i < N; i++){
        //get the farthest node also current node
        int farthest = getMin(distance, visited);
        //mark it as visited
        visited[farthest] = true;
        //get the distance from the current node to all the nodes
        for(int j = 0; j < N; j++){
            //check that we havent visited the node and the node has a connection and the distance is greater than previous distance
            if(!visited[j] && (distance[farthest] + graph[farthest][j]) > distance[j]) {
                distance[j] = distance[farthest] + graph[farthest][j]; 
            }
        }
    }
    return distance[N - 1];
}

struct Point
{
    int x;
    int y;
};

//Time and space complexity O(1)
float distance(Point p1, Point p2){
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y , 2) * 1.0);
}

//Time Complexity O(n^2)
//Space Complexity O(n)
vector<int> minDistance(vector<Point> &points, Point target){
    vector<float> distances;

    for(int i = 0; i < points.size(); i++){
        float dis = distance(points[i], target);
        distances.push_back(dis);
    }

    float min = distances[0];
    int central = 0;
    for(int i = 0; i < distances.size(); i++){
        if(distances[i] < min && distances[i] > 0){
            min = distances[i];
            central = i;
        }
    }
    vector<int> res;
    res.push_back(min);
    res.push_back(central);
    return res;
}

int main(){

    // LEER INPUT

    // number of colonies
    cin >> N;
    // cout << N << endl;
    //nxn matrix that represents distances between colonies in km
    vector<vector<int> > m_distance(N, vector<int>(N));
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> m_distance[i][j];
            if(m_distance[i][j] == 0){
                m_distance[i][j] = INF;  
            }
        }
    }
    //nxn matrix that represents the max data flow between colonies
    vector<vector<int> > m_data_flow(N, vector<int>(N));
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> m_data_flow[i][j];
        }
    }
    //coordenates of the energy/internet central y target de la nueva contratacion en pos[n]
    vector<Point> central_coordinates(N + 1);
    for(int i = 0; i < N + 1; i++){
        Point p;
        cin >> p.x;
        cin >> p.y;
        central_coordinates[i] = p;
        cout << p.x << ", " << p.y << endl;
    }

    // PARTE 1

    cout << endl << endl << "1. Forma de cablear las colonias con fibra" << endl << endl;
    for(int i = 0; i < N; i++){
        dijkstra(i, m_distance);
    }

    // PARTE 2

    cout << endl << endl;
    vector<vector<int> > floyd = floydWarshall(m_distance);

    vector<char> ruta = tsp(floyd, 0);
    cout << "2. Ruta: ";
    for(int i = 0; i < ruta.size(); i++){
        cout << ruta[i] << " ";
    }

    // PARTE 3
    cout << endl << endl;
    cout << "3. Max flow: " << max_flow(m_data_flow);

    // PARTE 4
    cout << endl << endl;
    Point target = central_coordinates[N];
    central_coordinates.pop_back();
    vector<int> dist_central = minDistance(central_coordinates, target);
    cout << "4. Nearest central from (" << target.x << ", " << target.y << "): (" << central_coordinates[dist_central[1]].x << ", " << central_coordinates[dist_central[1]].y << ")" << endl;
    cout << endl << endl;

    return 0;
}