#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "bstsort.h"


void usage(){
  fprintf(stderr, "usage: bstsort [-c] [-o output_file_name] [input_file_name]\n");
  exit(1);
}

struct Node{
  char* data;
  struct Node* left;
  struct Node* right;

};

struct Tree{
  struct Node* root;
}; 


struct Tree* create_binary_tree(){
  struct Tree* t = (struct Tree*)malloc(sizeof(struct Tree));
  t->root = 0;
  return t;
}

void insert_node (struct Node* node, struct Node* current, int cs){
  /* add lower string to right subtree */
  if(strCompare(node->data, current->data, cs) > 0){
    if(!current->right){
      current->right = node;
    } else{
      insert_node(node, current->right, cs);
    }
  }

  /* add lower string to left subtree */
  if(strCompare(node->data, current->data, cs) <= 0){
    if(!current->left){
      current->left = node;
    } else{
      insert_node(node, current->left, cs);
    }
  }
  return;
}

void add_to_tree(struct Tree* t, int* data, int cs){
  struct Node* node = (struct Node*)malloc(sizeof(struct Node*));
  node->data = data;
  node->left = 0;
  node->right = 0;

  if(!t){
    t->root = node;
  } else {
    printf("bobs your uncle");
    insert_node(node, t->root, cs);
  }
  return;
}

void print_tree (struct Tree* root){
  /* print tree and reclaim memory using an in-order traversal (left, root, right) */

}

int main(int argc, char* argv[])
{
  int c;
  int cs, of; /* case sensistive, output file */
  FILE *fin, *fout;
  struct Tree* t;

  cs = of = 0;
  while((c = getopt(argc, argv, "co")) != -1){
    switch(c) {
      case 'c':
        cs = 1;
        break;
      case 'o':
	of = 1;
	break;
      case '?':
      default:
        usage();
        printf("default");
    }
  }
  argc -= optind;
  argv += optind;

  /* open input and output files */
  if(!of && argc == 1){
    fout = stdout;
    fin = fopen(argv[0],"r");
	if(!fin) {
      fprintf(stderr, "ERROR: can't open file (to read): %s\n", argv[0]);
      return -1;
    }
  } else if(of && argc == 2){
    fout = fopen(argv[0],"w");
	if(!fout) {
      fprintf(stderr, "ERROR: can't open file (to write): %s\n", argv[0]);
      return -1;
    }
	fin = fopen(argv[1],"r");
	if(!fin) {
      fprintf(stderr, "ERROR: can't open file (to read): %s\n", argv[1]);
      return -1;
    }
  } else {
    fprintf(stderr, "ERROR: wrong arguments!\n");
	usage();
    return -1;
  }
/*
  while((c = fgetc(fin)) != EOF){
    fputc(c, fout);
  }
*/

  struct Tree* tree;
  tree = create_binary_tree();

  int in;
  char* ch;
  in = 0;
  /* find line from file and insert into tree */
  while((c = fgetc(fin)) != EOF){
    fputc(c, fout);
    if(!in && c != '\n'){
      //ch = (char*)&c;
      add_to_tree(tree, c, cs);
      in = 1;
    }
    if(c == '\n'){
      in = 0;
    }
  }


  /* print tree */



  /* close input and output files */
  if(!of && argc == 1){
    fclose(fin);
  } else if(of && argc == 2){
    fclose(fout);
    fclose(fin);
  }

  return 0;
}

