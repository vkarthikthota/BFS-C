


#include<stdio.h>
#include<stdlib.h>

// Header files: List.h and Graph.h

#include "List.h"
#include "Graph.h"

// typedef struct GraphObj is similar to the 
// ListObj in List.c ( I used that as an example to
// create GraphObj). 
 
  typedef struct GraphObj 
  {

     List * adjacency;

     int * color;   // white, gray, or black 
     int * d;       // distance
     int * p;       // parent 
  
     int order;      // order stores the number of vertices
     int size;       // size represents the number of edges
     int source;     // source represents the recently used vertex
     
  } GraphObj;
  
  
  
  // an example of this was covered in class on 2-18-14
  
  Graph newGraph(int n) 
  {
     // create a new Graph G of malloc/calloc
     
     Graph G = malloc(sizeof(GraphObj));
     G->adjacency = calloc(n+1, sizeof(List));
     G->color = calloc(n+1, sizeof(int));
     G->d = calloc(n+1, sizeof(int));
     G->p = calloc(n+1, sizeof(int));
     
     G->order = n;
     G->size = 0;
     G->source = NIL;
    
    // loop i from 1 to n
    
     int i;
     for (i = 1; i <= n; i++) 
     {  
        G->adjacency[i] = newList();
        G->color[i] = WHITE;
        G->d[i] = INF;
        G->p[i] = NIL;
     }
   
     return (G);
 
  }
  
  
  
  // free the graph and its elements
  // I used listFree from List.c as an 
  // example to create freeGraph
  
  
  void freeGraph( Graph* pG) 
  {
  
  // pre-condition: 
     if(pG == NULL || *pG == NULL) { return; }
     
     int i;
     for(i = 1; i <= getOrder(*pG); i++)
     {
        freeList(&((*pG)->adjacency[i])); // free every element in adjacency
        ((*pG)->adjacency[i]) = NULL;
     }
     
    // frees all heap memory associated with *pG
    // received help on this part from a class mate. 
    // used freeList as reference 
    
    free((*pG)->adjacency);
    ((*pG)->adjacency) = NULL;
    free((*pG)->color);
    ((*pG)->color) = NULL;
    free((*pG)->d);
    ((*pG)->d) = NULL;
    free((*pG)->p);
    ((*pG)->p) = NULL;
    free(*pG);
    *pG = NULL;

  }
  
  

// --------------------------------------------------------------------
//  
// ********************** Access Functions ********************* //
//
// --------------------------------------------------------------------
 
 
 
  // getOrder(Graph G) returns the number of vertices(called the 
  // order of the graph).
 
  int getOrder(Graph G)
  {
     if ( G == NULL ) 
     {
        printf( "Graph Error: getOrder() on NULL graph\n" );
        exit(1);
     }
  
     return G->order;

  }
 
 
 
  // getSize(Graph G) returns the number of the edges(called the 
  // size of the graph).
  
  int getSize ( Graph G ) 
  {
     // pre-condtion:
     if( G == NULL ) 
     {
        printf ( "Graph Error: getSize() on NULL graph\n" );
        exit(1);
     }

     return G->size;

  }



  // getSource(Graph G) returns the label of the vertex that was
  // used most recently used as source for BFS. 

  int getSource ( Graph G )
  {
  
     // pre-condition:
     if ( G == NULL ) 
     {
        printf ( "Graph Error: getSource() on NULL graph\n" );
        exit(1);
     }

     return G->source;
  
  }
  
  
  
  // Function getParent() will return the parent of vertex 
  // u in the Breadth-First tree created by BFS(), or NIL 
  // if BFS() has not yet been called. 
   
  int getParent ( Graph G, int u ) 
  {
     
     // pre-condtion: 
     if ( G == NULL ) 
     {
        printf ( "Graph Error: getParent() on NULL graph\n" );    
        exit(1);
     }
    
     // pre condtion for u:
     if ( u < 1 || u > getOrder(G) ) 
     {
        printf ( "Graph Error: u undefined\n" );
        exit(1);
     }
 
     // return the parent of the vertex u
    return G->p[u];
 
  } 


  
  // Function  getDist() returns the distance from the most recent
  // BFS source to vertex u,  //  or INF if BFS() has not 
 
  int getDist ( Graph G, int u ) 
  {
  
     // pre-condition:
     if ( G == NULL ) 
     {
        printf( "Graph Error: getDist() on NULL graph\n" );
        exit(1);
     }
  
     // pre-condtion for u:
     if ( u < 1 || u > getOrder(G) ) 
     {
        printf ( "Graph Error: u undefined\n" );  
        exit(1);
     }
  
     // return the distance of the vertex
     return G->d[u];
  
  }


  
  // Function getPath() appends to the List L the vertices of
  // a shortest path in G from source to u, or appends to L
  // the value NIL if no such path exists. getPath() has the 
  // precondition getSource(G)!=NIL, so BFS() must be
  // called before getPath().
  
  void getPath ( List L, Graph G, int u ) 
  {  
     
     // pre-condition
     if ( L == NULL ) 
     {
        printf ( "Graph Error: getPath() on NULL list\n" );
        exit(1);
     }
     
      // pre-condition
     if ( G == NULL ) 
     {
        printf ( "Graph Error: getPath() on NULL graph\n" );
        exit(1);
     }
    
     // pre-condtion 
     // pseudocode for this was give in lecture notes
     // received help from a class mate with this
     
     if ( u < 1 || u > getOrder(G) ) 
     {
        printf ( "Graph Error: u defined\n" );
        exit(1);
     }
   
     // pre-condtion 
     if (u == getSource(G) )
     {
        append(L, u);
       // return;
     }
     
     else if (getParent(G, u) == NIL)
     {
        //append(L, NIL);
       // return;
     }
     
     else 
     {
        getPath(L, G, getParent(G,u));
        append(L, u);
        //return;
     }
     
  }
        
  
 

// -------------------------------------------------------------------
//
// ****************** Manipulation Procedures ***************** //
//
// -------------------------------------------------------------------



  // Function makeNull() deletes all edges of G,
  // restoring it to its original (no edge) state. 
  // (This is called a null graph in graph theory literature).

  void makeNull ( Graph G ) 
  {
  
     // pre-condition
     if ( G == NULL ) 
     {
        printf ( "Graph Error: makeNull() on NULL graph" );
        exit(1);
     }
     
     // loop from i to n and clear/makeNull 
     
     int i;
     for ( i = 1; i <= getOrder(G); i++ ) 
     {
        clear( G->adjacency[i] );
        G->color[i] = NIL;
        G->d[i] = NIL;
        G->p[i] = NIL;
     }
     
     // set to 0/NIL
     
     G->order = 0;    
     G->size = 0;   
     G->source = NIL;
    
  }



  // addEdge() inserts a new edge joining u to v, 
  // i.e. u is added to the adjacency List of v, 
  // and v to the adjacency List of u. Your program
  // is required to maintain these lists in sorted 
  // order by increasing labels. 

  void addEdge ( Graph G, int u, int v )
  {
  
     // pre-condition
     if ( G == NULL ) 
     {
        printf ( "Graph Error: addEdge() on NULL graph" );
        exit(1);
     }
     // pre-condition
     if ( u < 1 || u > getOrder(G) ) 
     {
        printf ( "Graph Error: u undefined" );
        exit(1);
     }
     // pre-condition
     if ( v < 1 || v > getOrder(G) ) 
     {
        printf ( "Graph Error: v undefined" );
        exit(1);
     }
     // add u to v 
     if(length(G->adjacency[u]) == 0) { 
        append (G->adjacency[u], v );
     }
     
     else 
     {
       moveTo(G->adjacency[u], 0);
       while(getIndex(G->adjacency[u]) != -1 ) 
       {
           if(v < getElement(G->adjacency[u])) {
              insertBefore(G->adjacency[u], v);
              break;
            }
            else {
            moveNext(G->adjacency[u]);
            }
        }
        
         if(getIndex(G->adjacency[u]) == -1) {
           append ( G->adjacency[u], v );
        }
     }
           
        // add v to u 
         if(length(G->adjacency[v]) == 0) { 
        append ( G->adjacency[v], u );
     }
     else 
     {
       moveTo(G->adjacency[v], 0);
       while(getIndex(G->adjacency[v]) != -1 ) {
           if(u < getElement(G->adjacency[v])) {
              insertBefore(G->adjacency[v], u);
              break;
            }
            else {
            moveNext(G->adjacency[v]);
            }
        }
        
        if(getIndex(G->adjacency[v]) == -1) {
           append ( G->adjacency[v], u );
        }
     }
        
     
     G->size++;
     G->size++;
  }
  
  

  // addArc() inserts a new directed edge from u to v, 
  // i.e. v is added to the adjacency List of u (but not
  //  u to the adjacency List of v). 

  void addArc ( Graph G, int u, int v ) 
  {
  
     // pre-condition
     if ( G == NULL ) 
     {
        printf ( "Graph Error: addArc() on NULL graph" );
        exit(1);
     }
     // pre-condition
     if ( u < 1 || u > getOrder(G) ) 
     {
        printf ( "Graph Error: u undefined" );
        exit(1);
     }
     // pre-condition
     if ( v < 1 || v > getOrder(G) )
     {
        printf ( "Graph Error: v undefined" );
        exit(1);
     }
    
    // add u to v 
     if(length(G->adjacency[u]) == 0) { 
        append (G->adjacency[u], v );
     }
     
     else 
     {
       moveTo(G->adjacency[u], 0);
       while(getIndex(G->adjacency[u]) != -1 ) 
       {
           if(v < getElement(G->adjacency[u])) {
              insertBefore(G->adjacency[u], v);
              break;
            }
            else {
            moveNext(G->adjacency[u]);
            }
        }
        
         if(getIndex(G->adjacency[u]) == -1) {
           append ( G->adjacency[u], v );
        }
     }
    
     G->size++;
     
  }
 
 



  // Function BFS() runs the BFS algorithm on
  // the Graph G with source s, setting the color, 
  // distance, parent, and source fields of G accordingly. 
  // the algorithm is based of the psuedocode in the book
  // and the lecture notes. 
  
  void BFS ( Graph G, int s ) 
  {
  
     // pre-condition
     if ( G == NULL ) 
     {
        printf ( "Graph Error: BFS() on NULL graph" );
        exit(1);
     }
     // pre-condition
     if ( s < 1 || s > getOrder(G) ) 
     {
        printf ( "Graph Error: s undefined" );
        exit(1);
     }
     
     // this part of the code was strictly from the textbook
     // on page 595 from section 22.2. Also mentioned in pa4 pdf 
     // received help from a cs student 
     
     G->source = s;
     int i, j, k;
     for ( i = 1; i <= getOrder(G); i++ )
     {
        G->color[i] = WHITE;
        G->d[i] = INF;
        G->p[i] = NIL;
    
     }
     G->color[s] = GRAY;
     G->d[s] = 0;
     G->p[s] = NIL;
     
     List L = newList();  // Q != /0
     append(L, s);
     // received help on this while loop from a student 
     while( length(L) != 0) 
     {
        j = front(L);
        deleteFront(L);
        moveTo(G->adjacency[j], 0);
        while(getIndex(G->adjacency[j]) != -1)
        {
           k = getElement(G->adjacency[j]);
        
        // need help with the for loop
        // ask professor
        
           if(G->color[k] == WHITE) 
           {
              G->color[k] = GRAY;
              G->d[k] = (getDist(G, j) +1);
              G->p[k] = j;
              append(L, k);
           }
            moveNext(G->adjacency[j]);
        }
           G->color[j] = BLACK;
     }
     // free the list after use
     freeList(&L);
  }
     


// -------------------------------------------------------------------
// 
// *********************** Other Procedures ************************ //
//
// -------------------------------------------------------------------

 
  // Finally, function printGraph() prints the
  // adjacency list representation of G to
  // the file pointed to by out.
  // Based off the example form professor Tantalo
  // Received TA's help and Professor's help for this 
  // function 
  
  void printGraph ( FILE* out, Graph G ) 
  {
   
     if ( G == NULL ) 
     {
        printf ( "Graph Error: printGraph() on NULL graph" );
        exit(1);
     }
     
     int x;
     for(  x = 1; x <= getOrder(G); x++) 
     {
        fprintf(out, "%d: ", x);  
        printList ( out, G->adjacency[x] );
        fprintf(out, "\n");
     }
    
  }
     
     
     
  // END OF PROGRAM.





