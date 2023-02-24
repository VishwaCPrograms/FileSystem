#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lab3header.h"

Node *createArgNewNode(char name[], char content[]) {
        Node *newNode = malloc(sizeof(Node));
        if(newNode) {
                newNode->next = NULL;
                newNode->previous = NULL;
                newNode->child = NULL;
                newNode->parent = NULL;
                strcpy(newNode->details.name, name);
                newNode->details.isDirectory = FALSE;
                strcpy(newNode->details.fileContent, "It started when an alien device did what it did!");
        }
        return newNode;
}

void addArgSibling(Node *node, char name[]) {
	Node *newNode = createArgNewNode(name, name);
	if (newNode) {
		while (node->next) {
			node = node->next;
		}
		node->next = newNode;
		newNode->previous = node;
	}
}


void addArgChild(Node *node, char name[]) {
        if (node->child) {
                addArgSibling(node->child, name);
        } else {
                Node *newNode = createArgNewNode(name, name);
                if (newNode) {
                        node->child = newNode;
                        newNode->parent = node;
                }
        }
}

void cdManual() {
	printf("CAPITILIZATIONS AND SPACING MATTERS A LOT!!!\n");
	printf("--------------------------------------------------\n");
	printf("cd: To change directories.\n");
	printf("\t1. To go to the root: cd or cd  or cd ~\n");
	printf("\t2. To go to an immediate child directory: cd <child-directory-name>\n");
	printf("\t3. To go to any directory in the file system: cd <PATH>\n");
	printf("\t\t3.1. You must start your path address with a '/'.\n");
	printf("\t\t3.2. You must start the address from the Root (R is capitalized in the Root).\n");
	printf("\t\t3.3. Your path address must end with a '/'.\n");
	printf("--------------------------------------------------\n");
}

void lsManual() {
	printf("ls: To list all the items in the current directory.\n");
	printf("\t1. ls\n");
	printf("--------------------------------------------------\n");
	
}

void pwdManual() {
	printf("pwd: To list the address of the current directory.\n");
	printf("\t1. pwd\n");
	printf("--------------------------------------------------\n");
}

void catManual() {
	printf("cat: To output the contents of a file that is IN the current directory.\n");
	printf("\t1. cat <file-name>\n");
	printf("--------------------------------------------------\n");
}

void cpManual() {
	printf("cp: To copy a file. (File only. Copying directories not allowed).\n");
	printf("\t1. cp <file-name-to-be-copied>\n");
	printf("\t\tYou'll be prompted a message on whether you want to copy a file to the same directory with a different name or to a different directory with the same name.\n");
	printf("\t\tDepending on the option you pick, you'll either be asked for a name or directory path.\n");
	printf("\t\t\tPlease do remember that the directory path has to start with a '/', must start from the Root and must end with a '/'.\n");
	printf("--------------------------------------------------\n");
}

void mvManual() {
	printf("mv: To move or rename a file or a directory (moves the items in the directory if there are any and will update the addresses).\n");
	printf("\t1. mv <file-name or directory-name>\n");
	printf("\t\tYou'll be prompted a message on a rename or moving the item.\n");
	printf("\t\tDepending on the option you pick, you'll either be asked for a rename or a directory path.\n");
	printf("\t\t\tPlease do remember that the directory path has to start with a '/', must start from the Root and must end with a '/'\n");
	printf("--------------------------------------------------\n");
}

void rmManual() {
	printf("rm: To remove a file that is IN the current directory.\n");
	printf("\t1. rm <file-name>\n");
	printf("--------------------------------------------------\n");
}

void mkdirManual() {
	printf("mkdir: To create a new directory in the current directory.\n");
	printf("\t1. mkdir <directory-name>\n");
	printf("\t\tDuplicate names are not allowed\n");
	printf("--------------------------------------------------\n");
}

void rmdirManual() {
	printf("rmdir: To remove a directory that is in the current directory.\n");
	printf("\t1. rmdir <directory-name>\n");
	printf("\t\tIf the directory to be removed has items in it, this command will not work. Check rmrdir for that.\n");
	printf("--------------------------------------------------\n");
}

void fileManual() {
	printf("file: To create a new file\n");
	printf("\t1. file <file-name>\n");
	printf("\t\tDuplicate names are not allowed\n");
	printf("--------------------------------------------------\n");
}

void qManual() {
	printf("q: To quit the program.\n");
	printf("\t1. q\n");
	printf("--------------------------------------------------\n");
}

void rmrdirManual() {
	printf("rmrdir: To remove a directory that has items in it and is in the current working directory.\n");
	printf("\t1. rmrdir <directory-name>\n");
	printf("--------------------------------------------------\n");
}

void dateManual() {
	printf("date: To print the date and time to the screen.\n");
	printf("\t1. date\n");
	printf("--------------------------------------------------\n");
}

void dirprintManual() {
	printf("dirprint: Outputs the entire file system tree.\n");
	printf("\t1. dirprint\n");
	printf("--------------------------------------------------\n");
}


Node *cpCreateNewNode() {
        Node *newNode = malloc(sizeof(Node));
        if(newNode) {
                newNode->next = NULL;
                newNode->previous = NULL;
                newNode->child = NULL;
                newNode->parent = NULL;
                newNode->details.isDirectory = FALSE;
        }
        return newNode;
}

