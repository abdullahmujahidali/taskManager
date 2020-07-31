#include <stdio.h>

#include <stdlib.h>

#include <string.h>

typedef struct node{

char color;//color whether 'R' or 'B'

int key; //val of node

struct node *left;//ptr to left node

char id[20];

struct node *right;//ptr to right node

struct node *p;//parent pointer

}node;

node *root,*nul;//nul is sentinel node

int max_count=0,curr_count=0;

void create_sentinel(){ //A sentinel node is a blacknode to which all null pointers in tree point to.

nodep=(node)malloc(sizeof(node));

if(p==NULL){

printf("Memory allocation failed\n");

return ;

}

p->color='B';

p->left=NULL;

p->right=NULL;

nul=p;

root=nul;

root->p=nul;

}

/*Left rotation*/

void left_rotate(node *x){

node *y=x->right;

x->right=y->left;

if(y->left!=nul) y->left->p=x;

y->p=x->p;

if(x->p==nul) root=y;

else if(x==x->p->left) x->p->left=y;

else x->p->right=y;

y->left=x;

x->p=y;

}

/*Right rotation*/

void right_rotate(node *y){

node *x=y->left;

y->left=x->right;

if(x->right!=nul) x->right->p=y;

x->p=y->p;

if(y->p==nul) root=x;

else if(y==y->p->left) y->p->left=x;

else y->p->right=x;

x->right=y;

y->p=x;

}

/*corrects the color of the nodes by traversing up the tree*/

void insert_fixup(node *z){

node *y;

while(z->p->color=='R'){ //Upto parent color is red , as black color node can have its children of any color

if(z->p==z->p->p->left) { //If parent of z is left sibling

y=z->p->p->right;//y is right sibling of parent

if(y->color=='R'){//checks if color of y is R

z->p->color='B';

y->color='B';

z->p->p->color='R';

z=z->p->p;

}

else if(z==z->p->right){//if z is right sibling

z=z->p;

left_rotate(z);

}

else { //if z is left sibling

z->p->color='B';

z->p->p->color='R';

right_rotate(z->p->p);

}

}

else{

y=z->p->p->left;

if(y->color=='R'){

z->p->color='B';

y->color='B';

z->p->p->color='R';

z=z->p->p;

}

else if(z==z->p->left){

z=z->p;

right_rotate(z);

}

else {

z->p->color='B';

z->p->p->color='R';

left_rotate(z->p->p);

}

}

}

root->color='B';

}

/* Inserts independent of the color of nodes which will be fixed up in the insert-fixup-method*/

void insert(char *pid,int val){

noden=(node)malloc(sizeof(node));

if(n==NULL){

printf("Memory allocation failed\n");

return ;

}

n->key=val;

strcpy(n->id,pid);

node *x,*y;

x=root;

y=nul;

while(x!=nul){

y=x;

if(n->key<x->key) x=x->left;

else x=x->right;

}

n->p=y;

if(y==nul) root=n;

else if(n->key<y->key) y->left=n;

else y->right=n;

n->left=nul;

n->right=nul;

n->color='R';

insert_fixup;

}

/* Searches for the noe*/

nodesearch(int val,nodecurr){

if(curr==nul) return curr;

else if(curr->key==val) return curr;

else if(curr->key>val) return search(val,curr->left);

else return search(val,curr->right);

}

void sabfree(node *curr){

if(curr!=nul){

if(curr->left!=nul) sabfree(curr->left);

if(curr->right!=nul) sabfree(curr->right);

free(curr);

}

}

int main(){

int n;

scanf("%d",&n);

create_sentinel();

int count=0;

while(count<n){

int x;

scanf("%d",&x);

if(x==1){

char id[20];

int priority;

scanf("%s%d",id,&priority);

if(search(priority,root)!=nul) printf("REDUNDANT\n");

else {

insert(id,priority);

printf("ADDED\n");

}

}

else if(x==2){

int y;

scanf("%d",&y);

node *z=search(y,root);

if(z==nul) printf("NON-EXISTANT\n");

else printf("%s\n",z->id);

}

count++;

}

sabfree(root);

free(nul);

}