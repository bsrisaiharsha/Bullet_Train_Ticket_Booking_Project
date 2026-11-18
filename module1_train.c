#include "railway.h"

/* Module 1 owns the train and station master data. */
Station stations[TOTAL_STATIONS] = {
{
    {"NEW DELHI", "-", "6:00"},
    {"JAIPUR", "7:03", "7:08"},
    {"AJMER", "7:28", "7:33"},
    {"UDAIPUR", "8:30", "8:35"},
    {"AHMEDABAD", "9:30", "9:35"},
    {"VADODARA", "10:00", "10:05"},
    {"SURAT", "10:35", "10:40"},
    {"VAPI", "11:05", "11:10"},
    {"MUMBAI", "11:40", "11:45"},
    {"THANE", "11:50", "11:55"},
    {"PUNE", "12:20", "12:25"},
    {"HYDERABAD", "14:10", "14:15"},
    {"BANGALORE", "16:05", "16:10"},
    {"VELLORE (KATPADI)", "16:48", "16:53"},
    {"CHENNAI", "17:20", "-"}
};
};
Train trains[TOTAL_TRAINS] = {
 {1,"Bullet Express - Morning",0,"06:00 AM"},{2,"Bullet Express - Midday",0,"09:00 AM"},
 {3,"Bullet Express - Afternoon",0,"12:00 PM"},{4,"Bullet Express - Morning",1,"06:00 AM"},
 {5,"Bullet Express - Midday",1,"09:00 AM"},{6,"Bullet Express - Afternoon",1,"12:00 PM"}
};
static const double segment_km[TOTAL_STATIONS - 1] = {300,550,110,160,280,150,700,300,700,440,450,620,570,350};

int find_train_by_id(int id) {
    int i; for (i = 0; i < TOTAL_TRAINS; i++) if (trains[i].id == id) return i;
    return -1;
}

double calculate_distance(int source, int destination) {
    int i, low, high; double total = 0;
    if (source == destination) return 0;
    low = source < destination ? source : destination; high = source < destination ? destination : source;
    for (i = low; i < high; i++) total += segment_km[i];
    return total;
}

void display_all_stations(void) {
    int i;
    printf("\n%-4s %-20s %-14s %s\n", "No.", "Station", "Arrival", "Departure");
    for (i = 0; i < TOTAL_STATIONS; i++)
        printf("%-4d %-20s %-14s %s\n", i + 1, stations[i].name, stations[i].arrival, stations[i].departure);
    printf("\nThis is the supplied Delhi-to-Chennai sample timetable. Reverse timings are illustrative.\n");
}

void display_all_trains(void) {
    int i;
    printf("\n%-5s %-23s %-14s %s\n", "ID", "Direction", "Departure", "Train name");
    for (i = 0; i < TOTAL_TRAINS; i++)
        printf("%-5d %-23s %-14s %s\n", trains[i].id,
          trains[i].direction == 0 ? "Chennai -> Delhi" : "Delhi -> Chennai", trains[i].departure, trains[i].name);
}

int validate_route_for_direction(int direction, int source, int destination) {
    if (source < 0 || source >= TOTAL_STATIONS || destination < 0 || destination >= TOTAL_STATIONS || source == destination) return 0;
    if (direction == 0) return source > destination;
    return source < destination;
}

void display_route(int source, int destination) {
    int i, step = source < destination ? 1 : -1;
    printf("Route: ");
    for (i = source; ; i += step) { printf("%s", stations[i].name); if (i == destination) break; printf(" -> "); }
    printf("\nApproximate distance: %.0f km\n", calculate_distance(source, destination));
}

void search_trains(void) {
    int direction, i, source, destination, found = 0;
    printf("1. Chennai to Delhi\n2. Delhi to Chennai\n");
    direction = read_int("Select direction: ", 1, 2) - 1;
    printf("\nMatching trains:\n");
    for (i = 0; i < TOTAL_TRAINS; i++) if (trains[i].direction == direction) {
        printf("Train ID %d | %s | Departure %s\n", trains[i].id, trains[i].name, trains[i].departure); found++;
    }
    printf("Found %d trains.\n", found);
    display_all_stations();
    source = read_int("Source station number: ", 1, TOTAL_STATIONS) - 1;
    destination = read_int("Destination station number: ", 1, TOTAL_STATIONS) - 1;
    if (!validate_route_for_direction(direction, source, destination)) printf("Invalid route for selected direction.\n");
    else display_route(source, destination);
}

void train_module(void) {
    int choice;
    do {
        printf("\n========== MODULE 1: TRAIN & ROUTE ==========\n");
        printf("1. Display all stations and timetable\n2. Display all six trains\n3. Search trains and route\n4. Back to main menu\n");
        choice = read_int("Choose: ", 1, 4);
        if (choice == 1) display_all_stations();
        else if (choice == 2) display_all_trains();
        else if (choice == 3) search_trains();
        if (choice != 4) pause_screen();
    } while (choice != 4);
}
