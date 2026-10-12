#ifndef INVERT_H
#define INVERT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define SUCCESS 1
#define FAILURE 0

#define SIZE 27

typedef struct file_list
{
    char *fname;
    struct file_list *link;
}flist;

typedef struct sub_node
{
    int word_count;
    char *file_name;
    struct sub_node *sub_link;
}snode;

typedef struct main_node{
    char word[30];
    int file_count;
    struct main_node *m_link;
    snode *s_link;
}mnode;

// function prototypes
int file_validation(int argc,char *argv[],flist **fhead,int *file_count);
int search_file(char *file,flist *fhead);
int create_db(mnode **arr,flist *fhead,int *create_exe);
snode *create_snode(char *fname);
mnode *create_mnode(char word[],char *fname);
void display(mnode **arr);
void search(char word[],mnode **arr);
int save(mnode **arr,char *file,flist *fhead,int file_count,int update_exe,char update_file[]);
int update_db(mnode **arr,char update_file[],flist **fhead,int *file_count,int *update_file_count);

#endif