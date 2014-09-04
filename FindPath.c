


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// include Graph and List Headers
#include "Graph.h"
#include "List.h"

#define MAX_LEN 500


int main( int argc, char * argv[]) 
{
  // variables
  
  // input and output file
  FILE *in, *out;
  
  int lineNum = 0; //keeps track of number of lines 
  char line[MAX_LEN]; // line
  int source, distance, src, dst;
  
  // Graph G and List L 
  Graph G;
  List L = newList();
  
  
  // conditions for file reading and writing

  //this part of the code was given in the example of FileIO.c
  // check command line for correct number of arguments
  if( argc != 3 )
  {
     printf("Usage: %s <input file> <output file>\n", argv[0]);
     exit(1);
  }
  
   // open files for reading and writing 
  in = fopen(argv[1], "r");
  out = fopen(argv[2], "w");
  if( in == NULL )
  {
    printf("Unable to open file %s for reading\n", argv[1]);
    exit(1);
  }

  if( out == NULL )
  {
     printf("Unable to open file %s for writing\n", argv[2]);
     exit(1);
  }
  
  // used the example form FileIO provided by the profesor
  // reads the input from the input file and prints the 
  // adjacency vertices 
  
   while(fgets(line, MAX_LEN, in) != NULL) 
   {
     lineNum++;
     if(lineNum == 1) 
     {
        source =  atoi(strtok(line, " \n"));
        G = newGraph(source);
     }
     else 
     {
        src = atoi(strtok(line, " \n"));
        dst = atoi(strtok(NULL, " \n"));
        if( src != 0)  { addEdge(G, src, dst); }
        else { break; }   
     }
  }
  
  printGraph(out, G);
  fprintf(out, "\n");
  
  // Runs BFS, prints the distance, shortest path
  // tells if path exits or is infinity.
  // print statements at the of the file

  while(fgets(line, MAX_LEN, in) != NULL)
  {
     
     source = atoi(strtok(line, " \n"));
     distance = atoi(strtok(NULL, " \n"));
     
     if(source != NIL) 
     {
        BFS(G, source);
        clear(L);
        getPath(L, G, distance);
        
        // print statements
        // used the example in the book and the psuedocode 
        // that was covered in lecture
    
        fprintf(out, "\nThe distance from %d to %d is ", source, distance);
  		
  		if(length(L) == 0) 
  		{
  		
     	fprintf(out, "infinity\n");
     	fprintf(out, "No %d-%d path exists", source, distance);
     	
  		}
  		else 
  		{
     	
     	fprintf(out, "%d\n", getDist(G, distance));
     	fprintf(out, "A shortest %d-%d path is: ", source, distance);
     	
     	printList(out, L);
     	
  		}
  
  fprintf(out, "\n");
         
        
     }
  }
  
  
  // free the Graph and List
  freeGraph(&G);
  freeList(&L);

  
  // close the files
  fclose(in);
  fclose(out);
  return(0);
}
