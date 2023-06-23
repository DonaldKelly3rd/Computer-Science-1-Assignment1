// Headers
#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include "leak_detector_c.h"

#include "cop3502_as1.h"

#include <math.h>

#include <time.h>

// In class function
void remove_crlf(char *s) {

  char *end = s + strlen(s);

  end--;

  while ((end >= s) && (*end == '\n' || *end == '\r')) {
    *end = '\0';
    end--;
  }
}


int get_next_nonblank_line(FILE *ifp, char *buffer, int max_length) {
  buffer[0] = '\0'; // Start with an empty string

  while (!feof(ifp) && (buffer[0] == '\0')) {

    fgets(buffer, max_length, ifp);
    remove_crlf(buffer);
  }

  if (buffer[0] == '\0') {
    return 0;
  } else {
    return 1;
  }
}

typedef struct monster {

  int id;

  char *name;

  char *element;

  int population;

} monster;


// Contructor for Monster
monster *new_monster(int id, char *name, char *element, int population) {
  // allocate memory for structure
  monster *monster_results = malloc(sizeof(monster));

  monster_results->id = id;

  monster_results->name = malloc(strlen(name) + 1);
  strcpy(monster_results->name, name);

  monster_results->element = malloc(strlen(element) + 1);
  strcpy(monster_results->element, element);

  monster_results->population = population;

  return monster_results;
}






typedef struct region {

  char *name;

  int nmonsters;

  int total_population;
  // monsters pointer from monster struct
  monster **monsters;

} region;


// Constructor for region
region *new_region(char *name, int nmonsters, int total_population,monster **monsters) {
  region *region_results = malloc(sizeof(region));

  region_results->name = malloc(strlen(name) + 1);
  strcpy(region_results->name, name);

  region_results->nmonsters = nmonsters;

  region_results->total_population = total_population;

  region_results->monsters = (monster **)malloc(sizeof(monster *) * 100);

  return region_results;
}


typedef struct itinerary {

  int nregions;

  region **regions;

  int captures;

} itinerary;



// Constructor for itinerary
itinerary *new_itinerary(int nregions, region **regions, int captures) {
  itinerary *itinerary_results = malloc(sizeof(itinerary));

  itinerary_results->nregions = nregions;

  // double pointer **regions allocation
  itinerary_results->regions = (region **)malloc(sizeof(region *) * 100);

  itinerary_results->captures = captures;

  return itinerary_results;
}



typedef struct trainer {

  char *name;

  itinerary *visits;

} trainer;



// Constructor for trainer
trainer *new_trainer(char *name, itinerary *visits) {
  trainer *trainer_results = malloc(sizeof(trainer));

  trainer_results->name = malloc(strlen(name) + 1);
  strcpy(trainer_results->name, name);

  trainer_results->visits = (itinerary *)malloc(sizeof(itinerary) * 100);

  return trainer_results;
}



// Free struct function from class
void dispose_point(monster *monster_results) {

  free(monster_results->name);
  free(monster_results->element);

  free(monster_results);
}



// printer function for debugging
void print_monster(monster *monster_results) {

  printf("ID: %.2d\n", monster_results->id);
  printf("Monster Name %s:\n", monster_results->name);
  printf("Element %s:\n", monster_results->element);
  printf("Population: %.2d\n", monster_results->population);
}




void print_region(region *region_results,monster **monsters) {

  printf("Region Name %s:\n", region_results->name);
  printf("Number of Monsters: %.2d\n", region_results->nmonsters);
  printf("Total Population: %.2d\n", region_results->total_population);
  printf("region name %s:\n", region_results->monsters);
}




void print_itinerary(itinerary *itinerary_results) {

  printf("Number Regions: %.2d\n", itinerary_results->nregions);
  printf("Region %s:\n", itinerary_results->regions);
  printf("Number of Captures: %.2d\n", itinerary_results->captures);
}




void print_trainer(trainer *trainer_results) {

   printf("Monster Name %s:\n", trainer_results->name);
   printf("Number of Visits: %.2d\n", trainer_results->visits);
}



void Calclations(region *region_results, monster *monster_results,itinerary *itinerary_results, trainer *trainer_results)
  {



  }


int main() {

  //atexit(report_mem_leak);



  monster **monster_results;
  // I/O files
  FILE *ifp;
  FILE *ofp;


  // read text file
  char buffer[255];

  // Array to struct
  char monsterData[255];

  int i = 0;
  int firstchecker = 0;
  int wordchecker = 0;
  int index = 0;


  ifp = fopen("cop3502-as1-input.txt", "r");

  ofp = fopen("cop3502-as1-output-kelly-donald.txt", "w");


//inclass function
  while (get_next_nonblank_line(ifp, buffer, 255)) {

    printf("%s\n", buffer);

  }


  fclose(ifp);

  fopen("cop3502-as1-input.txt", "r");



  for (int i; i<50;i++){
    sscanf(buffer,"%s",monsterData);
  }

  //Lab Code
  while (!feof(ifp)) {

    if (fgets(buffer, 255, ifp) > 0) {
      remove_crlf(buffer);

      while (buffer[i] != ' ') {
        monsterData[i] = buffer[i];

        i++;

      }

      if (firstchecker == 0) {
        int numMonster = atoi(buffer);
        monster_results = malloc(numMonster * sizeof(monster));

        firstchecker = 1;

        continue;
      }

      if (wordchecker == 0) {
       monster_results[index]->id = atoi(monsterData);
        index++;

        wordchecker = 1;
      }

      if (wordchecker == 1) {
        int MonsterSize = strlen(monsterData);

       monster_results[index]->name = malloc((MonsterSize) * sizeof(char));

      strcpy(monster_results[index]->name, monsterData);

        wordchecker = 2;
      }
      if (wordchecker == 2) {
        int elementType = strlen(monsterData);

       monster_results[index]->element = malloc((elementType + 1) * sizeof(char));

       strcpy(monster_results[index]->element, monsterData);

        wordchecker = 3;
      }
      if (wordchecker == 3) {
        monster_results[index]->population = atoi(monsterData);
        index++;

        wordchecker = 0;
      }
    }
    fclose(ifp);
  }

  return 0;
}
