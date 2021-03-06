#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"

typedef struct Pair Pair;
typedef struct HashMap HashMap;
int enlarge_called=0;

struct Pair {
     char * key;
     void * value;
};

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {
  if(map==NULL)return;
  long position = hash(key, map->capacity);
  int cap = map->capacity;
  if(map->buckets[position]==NULL || map->buckets[position]->key == NULL){ //Comprueba si la position esta vacia o la key es invalida
    map->buckets[position] = createPair(key, value);
    map->size += 1;
  }
  else{ 
    if(map->buckets[position]!=NULL){
      for(int i=position;i<cap;i++){//For que comprueba una casilla vacia hasta capacity
        if(map->buckets[i]==NULL || map->buckets[i]->key == NULL){
          map->buckets[i] = createPair(key, value);
          map->size += 1;
          return;
        }
      }
    }
    if(map->buckets[position]!=NULL){
      for(int i = 0; i<position;i++){//En caso de no existir una casilla vacia comprueba desde la primera casilla
        if(map->buckets[i]==NULL || map->buckets[i]->key == NULL){
          map->buckets[i] = createPair(key, value);
          map->size += 1;
          return;
        }
      }
    }
  }
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)  


}


HashMap * createMap(long capacity) {
  HashMap * newMap = (HashMap *)malloc(sizeof(HashMap));
  newMap->buckets = (Pair **)calloc(capacity,sizeof(Pair*));
  newMap->size = 0;
  newMap->capacity = capacity;
  newMap->current = -1;
    return newMap;
}

void eraseMap(HashMap * map,  char * key) {    


}

void * searchMap(HashMap * map,  char * key) {
  int cap = map->capacity;   
  long position = hash(key, cap);
  
  if(map==NULL || map->buckets[position]== NULL){
    return NULL;
  }
  if(strcmp(map->buckets[position]->key, key)) {
    map->current = position;
    return map->buckets[position]->value;
  }
  for(int i = position ; i<cap ; i++){
    if(strcmp(map->buckets[i]->key, key) == 0){
      map->current = i;
      return map->buckets[i]->value;
    }
    if(map->buckets[i] == NULL || map->buckets[i]->key == NULL){
      return NULL;
    }
  }
  for(int i = 0 ; i<position ; i++){
    if(strcmp(map->buckets[i]->key, key) == 0){
      map->current = i;
      return map->buckets[i]->value;
    }
    if(map->buckets[i] == NULL || map->buckets[i]->key == NULL){
      return NULL;
    }
  }
  return NULL;
}

void * firstMap(HashMap * map) {
  if(map->buckets == NULL || map == NULL){
    return NULL;
  }
  for(int i = 0; i < map->capacity; i++) {
        if (map->buckets[i]->value != NULL){
            map->current = i;
            return map->buckets[i]->value;
        }
    }
    return NULL;
}

void * nextMap(HashMap * map) {
  int current = map->current + 1;
  for(int i = current; i<map->capacity; i++){
    if(map->buckets[i]->value != NULL){
      map->current = i;
      return map->buckets[i]->value;
    }
  }
    return NULL;
}
