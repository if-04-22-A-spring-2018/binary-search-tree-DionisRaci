/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class name here>
 *-----------------------------------------------------------------------------
 * Exercise Number: #exercise_number#
 * File:			bst.cpp
 * Author(s):		Peter Bauer
 * Due Date:		May 31, 2017
 *-----------------------------------------------------------------------------
 * Description:
 * <your description here>
 *-----------------------------------------------------------------------------
*/
#include <stdlib.h>
#include <stdio.h>
#include "general.h"
#include "bst.h"

struct Node{
  int value;
  Bst right;
  Bst left;
};

Bst new_bst(){
  Bst bst = (Bst)malloc(sizeof(struct Node));
  bst = 0;
  return bst;
}

void delete_bst(Bst bst){
  if(bst == 0){
    return;
  }
  delete_bst(bst->left);
  delete_bst(bst->right);
  sfree(bst);
}

int get_depth(Bst bst){
  if (bst == 0) {
    return 0;
  }
  int left_depth = get_depth(bst->left) + 1;
  int right_depth = get_depth(bst->right) + 1;

  if (left_depth > right_depth) {
    return left_depth;
  }
  return right_depth;
}

void add(Bst* bst, int value){
  Bst &new_node = *bst;
  if (new_node == 0){
    new_node = (Bst)malloc(sizeof(struct Node));
    new_node->value = value;
    new_node->right = 0;
    new_node->left = 0;
  }
  else if (value <= new_node->value) {
    add(&new_node->left,value);
  }
  else  {
    add(&new_node->right,value);
  }
}

int root_value(Bst bst){
  if (bst != 0) {
    return bst->value;
  }

  return 0;
}

Bst left_subtree(Bst root){
  if (root->left != 0) {
    return root->left;
  }
  return 0;
}

Bst right_subtree(Bst root){
  if (root->right != 0) {
    return root->right;
  }
  return 0;
}

int traverse_pre_order(Bst bst, int *elements, int start){
  if (bst == 0) {
    return 0;
  }
  int count_of_subtrees = 0;
  elements[start] = bst->value;
  count_of_subtrees += 1;
  count_of_subtrees += traverse_pre_order(bst->left, elements, start + 1);
  count_of_subtrees += traverse_pre_order(bst->right, elements, start + count_of_subtrees);
  return count_of_subtrees;
}

int traverse_in_order(Bst bst, int *elements, int start){
  if (bst == 0) {
    return 0;
  }
  int count_of_subtrees = 0;
  count_of_subtrees += traverse_in_order(bst->left, elements, start);
  elements[start + count_of_subtrees] = bst->value;
  count_of_subtrees += 1;
  count_of_subtrees += traverse_in_order(bst->right, elements, start + count_of_subtrees);
  return count_of_subtrees;
}

int traverse_post_order(Bst bst, int *elements, int start){
  if (bst == 0) {
    return 0;
  }
  int count_of_subtrees = 0;
  count_of_subtrees += traverse_post_order(bst->left, elements, start);
  count_of_subtrees += traverse_post_order(bst->right, elements, start + count_of_subtrees);
  elements[start + count_of_subtrees] = bst->value;
  count_of_subtrees += 1;
  return count_of_subtrees;
}

bool are_equal(Bst bst1, Bst bst2){
  int elements1[100];
  int elements2[100];
  int count = traverse_in_order(bst1,elements1,0);
  int count2 = traverse_in_order(bst2,elements2,0);
  if (count == count2) {
    for (int i = 0; i < count; i++) {
      if (elements1[i] != elements2[i]) {
        return false;
      }
    }
  }
  else
  {
    return false;
  }
  return true;
}

void most_left_longest_branch(Bst bst, Bst* branch){
  if (bst == 0) {
    return;
  }
  add(branch, bst->value);
  if (get_depth(bst->left) >= get_depth(bst->right)) {
      most_left_longest_branch(bst->left, branch);
  }
  else{
      most_left_longest_branch(bst->right, branch);
  }
}

int get_number_of_subtrees(Bst bst){
  int elements[100];
  int count = traverse_in_order(bst,elements,0);
  return count - 1;
}
