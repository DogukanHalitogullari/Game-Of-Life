 #include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

char **write_in_file(const char *filename, char **state,  int rows, int cols, int allived_cell, int dead_cell) {
	
	FILE *output_file; //initiliaze output file
	output_file = fopen(filename, "w"); //open output file using writer method

	fprintf(output_file, "%s%i\n", "Arrived_cell: ", allived_cell); //print arrived cell 
	fprintf(output_file, "%s%i\n", "Dead_cell: ", dead_cell); //print dead cell

    	int i, j;
    	for(i=0; i<rows; i++){ //print 2d dynamically allocated and populated array
        	for(j=0; j<cols; j++){
            		fprintf(output_file, "%c", state[i][j]);
        	}
        	fprintf(output_file, "\n"); 
    	}

	fclose(output_file); //close output file
}



// read the input from given filename and return a 2D dynamically allocated and populated array
// you can use char type for each cell value or bool from <stdbool.h>
char **read_from_file(const char *filename, int **iterations, int **rows, int **cols)
{

	int cycle=0; //initiliaze constants
	int row=0;
	int column=0;
	
	int Max_Char = 100;
	char str[Max_Char];

	FILE *readFile; //initiliaze input file
	readFile = fopen(filename, "r"); //read input file usig reader method

	int i = 0;
	for (i=0; i<3; i++) { //seperate first, second and third line 
		fgets(str, Max_Char, readFile); //gets data from file
		if (i==0) {
			cycle = atoi(str); //first line equal to iterations number
			*iterations = &cycle; //change iterations number in location point
		} else if (i==1) {
			row = atoi(str); // second line equal to row number
			*rows = &row; //chnage row number in location point		
		} else if (i==2) {
			column = atoi(str); //third line equal to column number
			*cols = &column; //change column number in location point	
		}
	}

	char **input_arr = (char **)malloc(row * sizeof(char *)); //initiliaze array
	int m;
	for ( m=0; m<row; m++){
		input_arr[m] = (char*)malloc(column*sizeof(char)); //convert array to 2D dynamically array
	}

	Max_Char = 2; //for reading item to item
	int row_step=0, column_step=0; //initiliaze current situation of row and column

	while( fgets(str, Max_Char, readFile) != NULL) { // this lopp works end of life
		char ch = str[0]; //initiliaze first element of  string(output of fgets) as a char
		input_arr[row_step][column_step]=ch; 

		if (ch  ==  '\n') { //if getting elemnts equal to '\n', this means; end of line. Therefore increase current row step 
			row_step+=1;
			column_step = 0 ; // when starting new line, column number should be zero 
		
		}else {
			column_step+=1; // if getting element not equal to ending synmbol, increase column current location
		}
	}
	 return input_arr; // return 2D dynamically array	
    
}

// given a game step return the next step applying game rules
char **next_state(char **state, int row, int column, int **dead_cell, int **allived_cell)
{
	int i,j; //initiliaze constants
	int live_cell =0;
	int dead_c=0;
	int allived_c=0;

	char **next_arr = (char **)malloc(row * sizeof(char *)); //initiliaze array
	int m;

	for ( m=0; m<row; m++){ //convert initiliazed array to 2D dynamically array
		next_arr[m] = (char*)malloc(column * sizeof(char)); 	
	}

	for (i=0; i<row; i++) { //visit all row
		for (j=0; j<column; j++) {//visit ol column
			live_cell =0; 
			if (state[i][j] == '-' ) { //deal condition

				if (i>0) { //this 'if' check out of border of array
					if (state[i-1][j] == 'X' && i>0) { //this 'if' check nort neigbor
						live_cell +=1;
					}
				}

				if (i>0 && j>0) { //this 'if' check out of border of array
				      	if (state[i-1][j-1] == 'X') {  //this 'if' check nortwest neigbor
						live_cell +=1;
					}
				}
				
				if (i>0 && j+1<column) { //this 'if' check out of border of array
			  	     	if (state[i-1][j+1] == 'X') { //this 'if' check northeast neigbor
						live_cell +=1;
					} 
				}

				if (j>0){ //this 'if' check out of border of array
				       	if (state[i][j-1] == 'X') { //this 'if' check west neigbor
						live_cell +=1;
					}
				}

				if (j+1<column) { //this 'if' check out of border of array
					if (state[i][j+1] == 'X') { //this 'if' check heast neigbor
						live_cell +=1;
					} 
				}

				if (i+1<row) {//this 'if' check out of border of array
			       		if (state[i+1][j] == 'X') { //this 'if' check south neigbor
						live_cell +=1;
					}
				}

				if (i+1<row && j>0) { //this 'if' check out of border of array
					if (state[i+1][j-1] == 'X') { //this 'if' check southwest neigbor
						live_cell +=1;
					}
				}

				if (i+1<row && j+1<column) { //this 'if' check out of border of array
					if (state[i+1][j+1] == 'X') { //this 'if' check southheast neigbor
						live_cell +=1;
					}
				}
				
				if (live_cell == 3) { //if cell has 3 live cell, this means; this cell shoul be allived
					allived_c += 1; //increase allived cell
					next_arr[i][j] = 'X'; //convert dead cell to live cell
				} else {
					next_arr[i][j] = '-'; 
				}

			}else if (state[i][j] == 'X') {

				if (i>0) { //this 'if' check out of border of array
					if (state[i-1][j] == 'X' && i>0) { //this 'if' check nort neigbor
						live_cell +=1;
					}
				}

				if (i>0 && j>0) { //this 'if' check out of border of array
				      	if (state[i-1][j-1] == 'X') {  //this 'if' check nortwest neigbor
						live_cell +=1;
					}
				}
				
				if (i>0 && j+1<column) { //this 'if' check out of border of array
			  	     	if (state[i-1][j+1] == 'X') { //this 'if' check northeast neigbor
						live_cell +=1;
					} 
				}

				if (j>0){ //this 'if' check out of border of array
				       	if (state[i][j-1] == 'X') { //this 'if' check west neigbor
						live_cell +=1;
					}
				}

				if (j+1<column) { //this 'if' check out of border of array
					if (state[i][j+1] == 'X') { //this 'if' check heast neigbor
						live_cell +=1;
					} 
				}

				if (i+1<row) { //this 'if' check out of border of array
			       		if (state[i+1][j] == 'X') { //this 'if' check south neigbor
						live_cell +=1;
					}
				}

				if (i+1<row && j>0) { //this 'if' check out of border of array
					if (state[i+1][j-1] == 'X') { //this 'if' check southwest neigbor
						live_cell +=1;
					}
				}

				if (i+1<row && j+1<column) { 
					if (state[i+1][j+1] == 'X') { //this 'if' check southheast neigbor
						live_cell +=1;
					}
				}

				if (live_cell<2 || live_cell>3) { //if cell hass not 2 or 3 lived cell, this means; this cell shoıul be dead
					dead_c += 1; //increase dead cell number 
					next_arr[i][j] = '-'; // convert lived cell to dead cell
						
				} else {
					next_arr[i][j] = 'X';
				}
			}

		}
	}

	*allived_cell = &allived_c; //initliaze allived cell in location point
	*dead_cell = &dead_c; //initiliaze dead cell in location point
       
	return next_arr; //return new game screen

}

    

void print_state(char **state, int rows, int cols) //printing point
{

    int i, j;
    for(i=0; i<rows; i++){
        for(j=0; j<cols; j++){
            printf("%c", state[i][j]);
        }
        printf("\n");
    }
}

// Bonus Task
bool is_oscillator(char **starting_str, char **state, int rows, int cols) {
	 
	int total_state_element = rows*cols; //total array element 
	int counter_equal_element = 0;

	int y,z;
	for ( y=0; y<rows; y++){
		for (z=0; z<cols; z++){
			if (starting_str[y][z] == state[y][z]) { // check initial state and current state elements one by one
				counter_equal_element += 1; //counter same element (dead and lived cells)
			}
		}
	}
	
	if (counter_equal_element == total_state_element) { // if initial sttae equal to counter of equal elemnt, this means; these state are same
		return true;
	} else {
		return false;
		}
}

int main(int argc, char **argv) 
{

	int *iterations=0; //initiliaze some constants and variable 
	int *rows=0;
	int *cols=0;

	char **state = read_from_file(argv[1], &iterations, &rows, &cols); //reading input file and create 2D Dynamically aray
	int iteration = *iterations;
	int row = *rows;
	int column = *cols;

	int *allived_cell = 0; //allived_cell number for next_state function
	int *dead_cell = 0; //dead_cell function for next_state function
	int allived_c = 0;
	int dead_c = 0;


	/* --- BONUS PART START --- */ //copy initial state to compare
	bool isOscillator; //call in 'for' loop (iteration process loop)
	char **starting_str = (char **)malloc(row * sizeof(char *)); //initiliaze array
	int m;
	for ( m=0; m<row; m++){ //convert initiliazed array to 2D dynamically array
		starting_str [m] = (char*)malloc(column * sizeof(char)); 	
	}

	int l, j;
    	for(l=0; l<row; l++){ //visit all row
        	for(j=0; j<column; j++){ //visit all column
            		starting_str[l][j] = state[l][j]; //copying array value one by one
        	}
	}
	/* --- BONUS PART END --- */

	system("@cls||clear"); // clear terminal
	printf("%s\n", "----THE GAMES BEGINS----"); //print starting point
	printf("%s\n", "--will start in 3 seconds--");
	printf("%s%i%s\n", "This game has ",iteration, " iterations.");
	printf("%s\n", "Input Item");
	print_state(state, row, column);
	sleep(3);

	int i;
	for(i=0; i<iteration; i++) {
		system("@cls||clear"); // clear terminal

		char **state_next = next_state(state, row, column, &allived_cell, &dead_cell); // next state function
		allived_c = *allived_cell;
		dead_c = *dead_cell;
		state = state_next; //state 2 is output of next_state function. Next_state function needs current state to work. State = current situation and state_next = next situation

		printf("%s\n",  "Next State:"); //printing output
		printf("%s%i\n", "Allived Cell: ", allived_c); //printing allived cell
		printf("%s%i\n", "Dead Cell: ", dead_c); //printign dead cell
		print_state(state, row, column); //printing state

		char *out = strdup(*(argv+2)); //copy output path
		sprintf(out, "%s%d", out, (i+1)); //adding number of output text
		write_in_file(out, state, row, column, allived_c, dead_c); // writing state in text file 

		/* --- BONUS PART START --- */
		if (!isOscillator) {
			isOscillator = is_oscillator(starting_str, state_next, row, column);
		}		
		/* --- BONUS PART END --- */

		usleep(200000); //delay time
	       		
	
	}

	//free arrays
	free(state);
	free(starting_str);

	/* --- PRİNT BONUS PART END OF GAME -START- --- */
	if (isOscillator) {
		printf("%s\n", "***This game is_oscillator***");
	} else {
		printf("%s\n", "***This game is_not_oscillator***");
	}
	/* --- PRİNT BONUS PART END OF GAME -END- --- */

	printf("%s\n", "----GAME OVER!!----");
    	return 0;
}               
