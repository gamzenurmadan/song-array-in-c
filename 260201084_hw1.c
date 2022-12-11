//Gamze Nur Madan
#include <stdio.h>
#include <stdlib.h> // to use malloc(), realloc()
#include <string.h> //for string comparison strcmp


typedef struct dynamic_array {
    int capacity;
    int size;
    void** elements;
} dynamic_array;

void init_array(dynamic_array* array) { //initializing array capacity with capacity 2 using malloc
	array->capacity = 2;
	array->elements = (void**) malloc((array->capacity)*sizeof(void*));
	array->size = 0;
	return;
}

void put_element(dynamic_array* array, void* element) {
	
	if(array->size == array->capacity){  //checking if the capacity is available, if the number of elements is higher than capacity, the capacity is increased two times using realloc
		array->capacity = (array->capacity)*2;
		array->elements = (void**) realloc(array->elements, (array->capacity)*sizeof(void*));

	}
	array->elements[array->size++] = element;
	return;
	
}

void remove_element(dynamic_array* array, int position) {

	int j;
	for(j=position; j<(array->size)-1; j++){  //needed element is deleted, its location is replaced with next element
		array->elements[j] = array->elements[j+1];	
	}
	
	array->size = array->size-1; //after deletion size is reduced by 1
	
	if(array->size == (array->capacity)/2){ // checking the capacity, if the array's number of elements is less than capacity, capacity is reduced by half using realloc.
		array->capacity = (array->capacity)/2;
		array->elements = (void**) realloc(array->elements, array->capacity*sizeof(void*));
	}
    return;
	
}

void* get_element(dynamic_array* array, int position) { 
	
	return(array->elements[position]);
}

typedef struct song {
   char* name;
   float duration;
} song;

int main() {
	
    dynamic_array array;
    init_array(&array);
    printf("Welcome \n");
    while (1){
    	int input;
    	printf("\nTo add song --> 1\nTo delete song --> 2\nTo list all songs --> 3\nquit --> 0\n\n");
    	scanf("%d", &input);
    	if ( input == 0){
    		break;
		}
		else if (input == 1){
			song* new_song =(song*) malloc(sizeof(song));
			new_song->name = (char*) malloc(64*sizeof(char));
			float d;
			printf("Please write the song name \n");
			scanf("%s", new_song->name);
			printf("Please write the song duration \n");
			scanf("%f", &d);
			new_song->duration = d;
			put_element(&array, new_song);
		}
		else if ( input == 2){
			printf("Please write the song name \n");
			char* input_name = (char*) malloc(64*sizeof(char)); //type casting for the pointers
			scanf("%s", input_name); 
			int position = -1;
			int i;
			for(i=0; i<((&array)->size); i++){
					song* s = (song*) get_element(&array, i); //type casting for the pointers
					int equality = strcmp(input_name, s->name); //to find the element to be deleted string comparison is applied
					
					if(equality == 0){
						position = i;
						break;
					}
			}
			if (position == -1){
				printf("Song is not in list \n");
				continue;
			}else{
				remove_element(&array,position);
			}
		    free(input_name); // created input is freed here because no longer, we don't need it.
		}
		else if(input==3){
			if((&array)->size == 0){
				printf("There is no song in the list!\n");
			}
			int l;
			for(l=0; l<((&array)->size); l++){
					song* element = (song*) get_element(&array, l);
					printf(" %d _Song name: %s , Song duration: %f \n", l+1, element->name, element->duration);
			}
			
			
		}

	}
return 0;
}
