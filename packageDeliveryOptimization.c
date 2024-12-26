#include <stdio.h>
#include <string.h>

#define MAX 10

// Global variables
int distance[MAX][MAX] = {0};
int no_of_cities;
char city_name[MAX][50];
double avg_fuel_consumption; 
double fuel_capacity;        

void input(void);
void find_shortest_route(int start);

int main() {
    printf("----- Welcome to Package Delivery Optimization -----\n\n");
    printf("\t\t\t by Aditya Jain, Jiya Patel.\n\n");

    input();

    int start;
    printf("\nEnter the starting city (1 to %d): ", no_of_cities);
    scanf("%d", &start);
 
    find_shortest_route(start - 1);
    return 0;
}

void input() {
    printf("Enter the number of cities: ");
    scanf("%d", &no_of_cities);
    printf("\n\n");
    for (int i = 0; i < no_of_cities; i++) {
        printf("Enter name of city %d: ", i + 1);
        scanf(" %[^\n]", city_name[i]);
    }

    printf("\nEnter the distance matrix:\n");
    for (int i = 0; i < no_of_cities; i++) {
        for (int j = 0; j < no_of_cities; j++) {
            if (distance[i][j] != 0 || i == j) {
                continue;
            } else {
                printf("Enter distance between %s and %s: ", city_name[i], city_name[j]);
                scanf("%d", &distance[i][j]);
                distance[j][i] = distance[i][j];
            }
        }
    }
    printf("\nEnter average fuel consumption (distance per unit of fuel): ");
    scanf("%lf", &avg_fuel_consumption);
    printf("Enter fuel tank capacity (in units): ");
    scanf("%lf", &fuel_capacity);
}

void find_shortest_route(int start) {
    int visited[MAX] = {0};
    int total_distance = 0;
    int current_city = start;
    double fuel_range = avg_fuel_consumption * fuel_capacity;  // Maximum distance the vehicle can travel on a full tank
    double current_fuel = fuel_capacity;

    printf("\nThe route that should be followed is :--\n");
    for (int count = 0; count < no_of_cities; count++) {
        printf("%s", city_name[current_city]);

        // Mark the current city as visited
        visited[current_city] = 1;

        int nearest_city = -1;    // To store the index of the nearest city
        int min_distance = 10000;

        // Loop through all cities to find the nearest unvisited city
        for (int i = 0; i < no_of_cities; i++) {
            // Check if the city is unvisited and closer than the current nearest city
            if (!visited[i] && distance[current_city][i] < min_distance) {
                nearest_city = i;
                min_distance = distance[current_city][i];
            }
        }

        if (nearest_city == -1) break; // If no unvisited city, break the loop

        // Check if the vehicle can reach the nearest city with the current fuel
        if (current_fuel * avg_fuel_consumption < min_distance) {
            printf(" (Refuel here) ");
            current_fuel = fuel_capacity;  // Refuel to full capacity
        }

        total_distance += min_distance;
        current_fuel -= min_distance / avg_fuel_consumption;  // Update remaining fuel
        printf(" --> ");
        current_city = nearest_city;
    }

    // Return to the starting city
    if (current_fuel * avg_fuel_consumption < distance[current_city][start]) {
        printf(" (Refuel here) ");
        current_fuel = fuel_capacity;  // Refuel to full capacity
    }

    printf("%s\n", city_name[start]);
    total_distance += distance[current_city][start];

    // Print the total distance of the route
    printf("\nTotal Distance: %d\n", total_distance);
}
