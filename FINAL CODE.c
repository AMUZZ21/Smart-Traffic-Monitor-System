#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SPEED_LIMIT 80.0
#define MAX_SPEEDERS 100

struct Vehicle {
    char id[100];
    float speed;
    char arrival_time[10];
    char date[12];  
    struct Vehicle *next, *prev;
} *head = NULL;

struct Vehicle *speedingQueue[MAX_SPEEDERS];
int front = -1, rear = -1;

void enqueueSpeeding(struct Vehicle *vehicle) {
    if ((rear + 1) % MAX_SPEEDERS == front) {
        printf("Speeding queue is full! Cannot add more speeding vehicles.\n");
        return;
    }
    if (front == -1) front = 0;
    rear = (rear + 1) % MAX_SPEEDERS;
    speedingQueue[rear] = vehicle;
}

char* getCurrentDate() {
    static char date[12];  
    time_t t = time(NULL);
    struct tm *tm_info = gmtime(&t); 
    tm_info->tm_hour += 5;           
    tm_info->tm_min += 30;           
    mktime(tm_info);                 
    strftime(date, sizeof(date), "%d-%m-%Y", tm_info);
    return date;
}

char* getCurrentTime() {
    static char time_str[10]; 
    time_t t = time(NULL);
    struct tm *tm_info = gmtime(&t); 
    tm_info->tm_hour += 5;           
    tm_info->tm_min += 30;           
    mktime(tm_info);                 
    strftime(time_str, sizeof(time_str), "%H:%M:%S", tm_info);
    return time_str;
}

void addvehicle() {
    struct Vehicle *newvehicle = (struct Vehicle*)malloc(sizeof(struct Vehicle));
    if (!newvehicle) {
        printf("Memory allocation failed\n");
        return;
    }
    
    printf("ENTER THE VEHICLE ID: \n");
    scanf("%s", newvehicle->id);
    printf("ENTER THE VEHICLE SPEED(km/h): \n");
    scanf("%f", &newvehicle->speed);
    
    strcpy(newvehicle->arrival_time, getCurrentTime());
    strcpy(newvehicle->date, getCurrentDate());

    newvehicle->next = newvehicle->prev = NULL;
    
    if (newvehicle->speed > SPEED_LIMIT) {
        enqueueSpeeding(newvehicle);
    }
    
    if (head == NULL) {
        head = newvehicle;
        newvehicle->next = newvehicle->prev = head;
    } else {
        struct Vehicle *temp = head->prev;
        temp->next = newvehicle;
        newvehicle->prev = temp;
        newvehicle->next = head;
        head->prev = newvehicle;
    }
    printf("DATA IS ADDED TO THE LIST\n");
}


void datamissed() {
    struct Vehicle *missedvehicle;
    missedvehicle = (struct Vehicle*)malloc(sizeof(struct Vehicle));
    if (!missedvehicle) {
        printf("Memory allocation failed\n");
        return;
    }
    
    printf("ENTER THE VEHICLE ID: \n");
    scanf("%s", missedvehicle->id);
    printf("ENTER THE VEHICLE SPEED(km/h): \n");
    scanf("%f", &missedvehicle->speed);
    printf("ENTER ARRIVAL TIME (HH:MM:SS FORMAT): \n");
    scanf("%s", missedvehicle->arrival_time);
    printf("ENTER DATE (DD-MM-YYYY FORMAT):\n");
    scanf("%s", missedvehicle->date);

    if (head == NULL) {
        head = missedvehicle;
        missedvehicle->next = missedvehicle->prev = head;
    } else {
        char search_time[10], search_date[12];
        printf("ENTER THE DATE WHERE YOU WOULD LIKE TO ADD VEHICLE (DD-MM-YYYY FORMAT):\n");
        scanf("%s", search_date);
        printf("ENTER THE TIME WHERE YOU WOULD LIKE TO ADD VEHICLE (HH:MM:SS FORMAT):\n");
        scanf("%s", search_time);

        struct Vehicle *temp = head;
        do {
            if (strcmp(temp->date, search_date) == 0 && strcmp(temp->arrival_time, search_time) == 0) {
                struct Vehicle *nextNode = temp->next;
                temp->next = missedvehicle;
                missedvehicle->prev = temp;
                missedvehicle->next = nextNode;
                nextNode->prev = missedvehicle;
                printf("DATA IS ADDED TO THE LIST\n");
                return;
            }
            temp = temp->next;
        } while (temp != head);

        printf("NO MATCHING DATE AND TIME FOUND. ADDING AT LAST.\n");
        temp = head->prev;
        temp->next = missedvehicle;
        missedvehicle->prev = temp;
        missedvehicle->next = head;
        head->prev = missedvehicle;
    }
}


void removevehicle() {
    if (head == NULL) {
        printf("NO VEHICLES DATA WAS THERE IN THE LIST\n");
        return;
    }
    char search_id[100];
    printf("ENTER THE VEHICLE ID:\n");
    scanf("%s", search_id);
    
    struct Vehicle *temp = head;
    do {
        if (strcmp(temp->id, search_id) == 0) {
            if (temp == head && temp->next == head) {
                head = NULL;
            } else {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                if (temp == head) {
                    head = temp->next;
                }
            }
            printf("THE VEHICLE %s IS ERASED \n", temp->id);
            free(temp);
            return;
        }
        temp = temp->next;
    } while (temp != head);
    
    printf("VEHICLE NOT FOUND\n");
}

void displaySpeedingList() {
    if (front == -1) {
        printf("No vehicles exceeded the speed limit.\n");
        return;
    }
    printf("Speeding Vehicles:\n");
    printf("VEHICLE ID | SPEED (km/h) | ARRIVAL TIME | DATE\n");
    int i = front;
    do {
        printf("%s | %.2f | %s | %s\n", speedingQueue[i]->id, speedingQueue[i]->speed, 
               speedingQueue[i]->arrival_time, speedingQueue[i]->date);
        i = (i + 1) % MAX_SPEEDERS;
    } while (i != (rear + 1) % MAX_SPEEDERS);
}

void display() {
    if (head == NULL) {
        printf("NO VEHICLES DATA WAS THERE IN THE LIST\n");
        return;
    }
    int choice;
    printf("1. SEARCH VEHICLE BY ID\n");
    printf("2. DISPLAY ALL VEHICLES\n");
    printf("3. SPEEDING VEHICLES\n");
    scanf("%d", &choice);
    
    if (choice == 1) {
        char search_id[100];
        printf("ENTER THE VEHICLE ID TO SEARCH:\n");
        scanf("%s", search_id);
        struct Vehicle *temp = head;
        do {
            if (strcmp(temp->id, search_id) == 0) {
                printf("%s----%.2f----%s----%s \n", temp->id, temp->speed, temp->arrival_time, temp->date);
                return;
            }
            temp = temp->next;
        } while (temp != head);
        printf("VEHICLE NOT FOUND\n");
    }
    else if(choice ==2) {
        struct Vehicle *temp = head;
        printf("VEHICLEID----SPEED----ARRIVALTIME----DATE\n");
        do {
            printf("%s----%.2f----%s----%s \n", temp->id, temp->speed, temp->arrival_time, temp->date);
            temp = temp->next;
        } while (temp != head);
    }
    else{
      displaySpeedingList();
    }
}



int main() {
    int choice;
    while (1) {
        printf("SELECT THE MODE\n");
        printf("1. ADD NOT CAPTURED DATA\n");
        printf("2. ADD EXISTING DATA\n");
        printf("3. ERASE A VEHICLE FROM THE DATA\n");
        printf("4. DISPLAY THE DATA\n");
        printf("5. EXIT\n");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
               datamissed();
                break;
            case 2:
                addvehicle();
                break;
            case 3:
                removevehicle();
                break;
            case 4:
                display();
                break;
            case 5:
                return 0;
            default:
                printf("INVALID INPUT\n");
        }
    }
}
