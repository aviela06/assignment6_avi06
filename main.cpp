#include <iostream>
#include <cstdlib>   // rand, srand, atoi
#include <ctime>     // time, to seed rand
#include <cmath>     // sqrt
#include "coordinate.h"

void add_coordinate(Coordinate *list_end, float x, float y)
{
    Coordinate *new_coord = new Coordinate; // make a new node
    new_coord->x = x; // set x
    new_coord->y = y; // set y
    new_coord->coord_id = list_end->coord_id + 1; // next ID number
    new_coord->previous = list_end; // new node points back to old end
    new_coord->next = NULL;         // new node is the last one
    list_end->next = new_coord;     // old end points forward to new node
}

void forward_display(Coordinate *list_beginning)
{
    Coordinate *current = list_beginning; // start at the beginning
    while (current != NULL) // until the end of the list
    {
        std::cout << "ID: " << current->coord_id
                  << " x: " << current->x
                  << " y: " << current->y << "\n";
        current = current->next; // move to the next node
    }
}

void backward_display(Coordinate *list_end)
{
    Coordinate *current = list_end; // start at the end
    while (current != NULL) // until the beginning of the list
    {
        std::cout << "ID: " << current->coord_id
                  << " x: " << current->x
                  << " y: " << current->y << "\n";
        current = current->previous; // move to the previous node
    }
}

int list_length(Coordinate *list_beginning)
{
    int count = 0; // number of nodes
    Coordinate *current = list_beginning; // start at the top
    while (current != NULL) // until the end
    {
        count++; // count this node
        current = current->next; // next node
    }
    return count;
}

void delete_coordinate(Coordinate *list_beginning, int coord_id_to_delete)
{
    Coordinate *current = list_beginning; // start at the top
    while (current != NULL && current->coord_id != coord_id_to_delete) // until a match or the end
    {
        current = current->next; // next node
    }
    if (current == NULL) // ID wasn't in the list
    {
        std::cout << "ID not found\n";
        return;
    }
    if (current->previous != NULL)
        current->previous->next = current->next; // node before skips over current
    if (current->next != NULL)
        current->next->previous = current->previous; // node after skips over current
    delete current; // free the memory
}

void closest_to(Coordinate *list_beginning, float x, float y)
{
    Coordinate *closest = list_beginning; // closest so far
    float smallest = sqrt(pow(list_beginning->x - x, 2) + pow(list_beginning->y - y, 2)); // distance from first node to (x, y)
    Coordinate *current = list_beginning; // start at the top
    while (current != NULL) // until the end
    {
        float distance = sqrt(pow(current->x - x, 2) + pow(current->y - y, 2)); // distance from this node to (x, y)
        if (distance < smallest) // found a closer node
        {
            smallest = distance;  // new smallest distance
            closest = current;    // new closest node
        }
        current = current->next; // next node
    }
    std::cout << "Closest to (" << x << ", " << y << ") is ID " << closest->coord_id
              << " at (" << closest->x << ", " << closest->y << "), distance = " << smallest << "\n";
}

int main(int argc, char *argv[])
{
    if (argc < 2) // no number given
    {
        std::cout << "enter number of coordinates\n";
        return 1;
    }
    int num_coords = atoi(argv[1]); // convert command line text to a number
    srand(time(0)); // different random numbers each run

    Coordinate *list_beginning = new Coordinate; // make the first node
    list_beginning->x = rand() % 100; // random x from 0 to 99
    list_beginning->y = rand() % 100; // random y from 0 to 99
    list_beginning->coord_id = 1;     // first ID
    list_beginning->next = NULL;      // nothing after it yet
    list_beginning->previous = NULL;  // nothing before it
    Coordinate *list_end = list_beginning; // only one node, so it's also the end

    for (int i = 1; i < num_coords; i++) // add the rest of the points
    {
        add_coordinate(list_end, rand() % 100, rand() % 100); // random x and y between 0 and 99
        list_end = list_end->next; // move the end to the new node
    }

    std::cout << "Forward:\n";
    forward_display(list_beginning); // print from beginning to end

    std::cout << "Backward:\n";
    backward_display(list_end); // print from end to beginning

    std::cout << "Length: " << list_length(list_beginning) << "\n";

    delete_coordinate(list_beginning, 3); // remove ID 3
    std::cout << "After deleting ID 3:\n";
    forward_display(list_beginning); // printing coordinates without ID 3

    closest_to(list_beginning, 50, 50); // find the point closest to (50, 50)

    // free all memory
    Coordinate *current = list_beginning; // start at the top
    while (current != NULL) // until the end
    {
        Coordinate *next_node = current->next; // save the next node
        delete current; // free this node
        current = next_node; // move on
    }

    return 0;
}
