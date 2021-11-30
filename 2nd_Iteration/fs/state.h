#ifndef INODES_H
#define INODES_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../tecnicofs-api-constants.h"

/* FS root inode number */
#define FS_ROOT 0

#define FREE_INODE -1
#define INODE_TABLE_SIZE 50
#define MAX_DIR_ENTRIES 20

#define SUCCESS 0
#define FAIL -1

#define DELAY 5000

#define READ 0
#define WRITE 1

//Used to determine whether lookup should lock for read or write
#define CREATE 1
#define DELETE 1
#define MOVE 2
#define LOOKUP 0

/*
 * Contains the name of the entry and respective i-number
 */
typedef struct dirEntry {
	char name[MAX_FILE_NAME];
	int inumber;
} DirEntry;

/*
 * Data is either text (file) or entries (DirEntry)
 */
union Data {
	char *fileContents; /* for files */
	DirEntry *dirEntries; /* for directories */
};

/*
 * I-node definition
 */
typedef struct inode_t {
	pthread_rwlock_t rwlock;
	type nodeType;
	union Data data;
    /* more i-node attributes will be added in future exercises */
} inode_t;

void insert_delay(int cycles);
void inode_table_init();
void inode_table_destroy();
int inode_create(type nType, int parent_inumber);
int inode_delete(int inumber);
int inode_get(int inumber, type *nType, union Data *data);
int inode_set_file(int inumber, char *fileContents, int len);
int dir_reset_entry(int inumber, int sub_inumber);
int dir_add_entry(int inumber, int sub_inumber, char *sub_name);
void inode_print_tree(FILE *fp, int inumber, char *name);
void lock(int inode_number, char rw);
void unlock_array(int locked_inumbers[]);
void unlock(int inode_number);

#endif /* INODES_H */
