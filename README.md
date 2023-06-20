# myAppStore

A C/C++ program in which applications of various categories are indexed simultaneously by a hash table, a max-heap, and by a binary search tree (BST) for optimal support of various queries and updates of your store.

## Getting Started

### Requirements

 [gcc](https://gcc.gnu.org/)
 
### Installation

```
cd ./myAppStore
Makefile
```
 
# Usage Example

```
3               // n=3, the number of app categories
Games           // n=3 lines containing the names of each of the n categories
Medical
Social Networking
4               // m=4, number of apps to add to myAppStore; here all in Games
Games           // Each field in app_info is provided in order; first the name of the category
Minecraft: Pocket Edition      // Name of the application
0.12.1          // Version number of the application
24.1            // Size of the application
MB              // Units corresponding to the size, i.e., MB or GB
6.99            // Price of the application
Games           // Start of record for the second app
FIFA 16 Ultimate Team
2.0
1.25
GB
0.00
Games           // Start of record for the third app
Candy Crush Soda Saga
1.50.8
61.3
MB
0.00
Games           // Start of record for the fourth app
Game of Life Classic Edition
1.2.21
15.3
MB
0.99
11                               // q=11, number of queries and/or updates to process
find app "Candy Crush Soda Saga" // List information about the application
// List all applications in the Medical category
// List all free applications in Games category
// List alphabetically all Games whose name is in the range A-F
print-apps category "Medical"
find price free "Games"
range "Games" app "A" "F"
print-apps category "Social Networking" // List all apps in the Social Networking category
range "Games" price 0.00 5.00
delete "Games" "Minecraft"
print-apps category "Games"
find max price apps "Games"
find app "Minecraft"
no report
// List all names of Games whose price is in the range $0.00-$5.00
// Delete the game Minecraft from the Games category
// List all applications in the Games category
// List all applications in Games with maximum price
// Application should not be found because it was deleted
// do not produce hash table and tree statistics

```



