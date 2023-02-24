/* Name: Vishwa Venkateshwaran */

#include <stdio.h>
#include <stdlib.h>
#include "lab3header.h"
#include <string.h>
#include <time.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    Node *rootNode = createNewNode("mkdir", "Root");
    if (rootNode == NULL) {
        printf("Sorry, no memory available to allocate!\n");
    } else {
	strcpy(rootNode->dirAddress.dirAddress, "/Root/");
	if (argc > 1) {
		DIR *openDir;
		struct dirent *dirStruct;
		openDir = opendir(argv[1]);
		if (openDir) {
			while (dirStruct = readdir(openDir)) {
				addArgChild(rootNode, dirStruct->d_name);
			}
			closedir(openDir);
		} else {
			printf("Can't find the directory!\n");
		}
	}
        assignCommand(rootNode);
        freeEverything(rootNode);
    }
    return 0;
}

void assignCommand(Node *rootNode) {
	Node *currNode = rootNode;
	char userName[11];
	readUserName(userName);
	while(1) {
		char userInput[100];
		char userInputCheck[100];
		char *data[2];
		readUserInput(userInput, userName, currNode);
		strcpy(userInputCheck, userInput);	
		splitString(userInput, data);
		if(strcmp(data[0], "q") == 0) {
			break;
		} else if (strcmp(data[0], "help") == 0) {
			printHelpManual();
		} else if (strcmp(data[0], "cd") == 0) {
			char *str = data[1];
			if ((strlen(userInputCheck) == strlen(data[0])) || strcmp(data[1], "") == 0 || strcmp (data[1], " ") == 0 || strcmp(data[1], "~") == 0) {
				cdCommand(&currNode, rootNode);
			} else if (strcmp(data[1], "..") == 0) {
				cdDotDotCommand(&currNode);
				memset(data[1], 0, sizeof(data));
			} else if (str[0] == '/') {
				Node *extraNode = currNode;
				int isFile;
				cdPathCommand(&currNode, rootNode, data[1], &isFile);
				if(strcmp(currNode->dirAddress.dirAddress, data[1]) != 0) {
					if(strcmp(currNode->dirAddress.dirAddress, extraNode->dirAddress.dirAddress) == 0) {
						if(!(isFile)) {
							printf("The directory you're looking for doesn't exist.\n");
						}
					}
				}
				memset(data[1], 0, sizeof(data));
			} else {
				cdNameCommand(&currNode, data[1]);
				memset(data[1], 0, sizeof(data));
			}
                } else if (strcmp(data[0], "ls") == 0) {
			if(strlen(userInputCheck) == strlen(data[0])) {
				lsCommand(currNode);
			} else {
				printf("Invalid ls command.\n");
			}	
                } else if (strcmp(data[0], "pwd") == 0) {
			if(strlen(userInputCheck) == strlen(data[0])) {
				pwdCommand(currNode);
			} else {
				printf("Invalid pwd command.\n");
			}
                } else if (strcmp(data[0], "cat") == 0) {
			if(strlen(userInputCheck) != strlen(data[0])) {
                                catCommand(currNode, data[1]);
                        } else {
                                printf("Please enter a file name.\n");
                        }
                } else if (strcmp(data[0], "cp") == 0) {
			cpCommand(currNode, rootNode, data[1]);
                } else if (strcmp(data[0], "mv") == 0) {
			if (strcmp(data[1], "") != 0) {
				Node *extraNode = currNode;
				mvCommand(currNode, rootNode, extraNode, data[1]);
			} else {
				printf("Enter the name of the item you wish to move or rename.\n");
			}
                } else if (strcmp(data[0], "rm") == 0) {
			if(strcmp(data[1], "") != 0) { 
				rmFile(currNode, data[1]);
			} else {
				printf("Please enter a file name.\n");
			}
                } else if (strcmp(data[0], "mkdir") == 0) {
			if (strcmp(data[1], "") != 0) {
				addChild(currNode, data[0], data[1]);
			} else {
				printf("Please enter a directory name.\n");
			}
                } else if (strcmp(data[0], "rmdir") == 0) {
			if (strcmp(data[1], "") != 0) {
                                removeTheDirectory(currNode, data[1]);
                        } else {
                                printf("Please enter a directory name.\n");
                        }
                } else if (strcmp(data[0], "file") == 0) {
			if (strcmp(data[1], "") != 0) {
                                addChild(currNode, data[0], data[1]);
                        } else {
                                printf("Please enter a file name.\n");
                        }
                } else if (strcmp(data[0], "rmrdir") == 0) {
			if (strcmp(data[1], "") != 0) {
                                rRemoveTheDirectory(currNode, data[1]);
                        } else {
                                printf("Please enter a directory name.\n");
                        }
                } else if (strcmp(data[0], "date") == 0) {
			printDate();
                } else if (strcmp(data[0], "dirprint") == 0) {
			printf("CURRENT NODE: %s\n", currNode->details.name);
			dirPrintCommand(rootNode, currNode, 0);
                } else {
			printf("Sorry, the command you entered doesn't exist.\n");	
                }
	}
}

void readUserName(char userInput[]) {
	printf("Enter your name (max length of 10 characters): ");
	fgets(userInput, 11, stdin);
	userInput[strcspn(userInput, "\n")] = 0;
	if(strlen(userInput) == 0) {
		printf("Automatically setting the name to LM...\n");
		strcpy(userInput, "LM");
	}
}

void readUserInput(char userInput[], char userName[], Node *currNode) {
	printf("Enter command [q to quit and help to see the manual].\n");
	printf("[%s %s]$ ", userName, currNode->details.name);
	fgets(userInput, 99, stdin);
	userInput[strcspn(userInput, "\n")] = 0;
}

void askUserChoice(char userInput[]) {
	printf("Would you like to rename this item or move this item?\n");
	printf("Enter r to rename and m to move: ");
	fgets(userInput, 9, stdin);
	userInput[strcspn(userInput, "\n")] = 0;
	if(strlen(userInput) == 0) {
		strcpy(userInput, "q");
	}
}

void askRename(Node *node, char rename[]) {
	printf("What would you like the new name of %s to be?: ", node->details.name);
	fgets(rename, 64, stdin);
	rename[strcspn(rename, "\n")] = 0;
	if(strlen(rename) == 0) {
		printf("Automatically setting the name to Random_Name...\n");
		strcpy(rename, "Random_Name");
	}
}

void getPath(char path[]) {
	printf("Enter the new path: ");
	fgets(path, 999, stdin);
	path[strcspn(path, "\n")] = 0;
	if(strlen(path) == 0) {
		printf("Automatically setting the path to Root...\n");
		strcpy(path, "/Root/");
	}
}

void splitString(char userInput[], char *words[]) {
	char *c;
	int i = 0;
	if(strlen(userInput) == 0) {
		strcpy(userInput, "Random Stuff");
	}
	c = strtok(userInput, " ");
	while (c && i < 2) {
		words[i++] = c;
		c = strtok(NULL, " ");
	}
}

void askFileContent(char fileContent[]) {
	printf("Enter contents of file: ");
	scanf("%[^\n]%*c", fileContent);
}
	
Node *createNewNode(char userChoice[], char name[]) {
	Node *newNode = malloc(sizeof(Node));
	if(newNode) {
		newNode->next = NULL;
		newNode->previous = NULL;
		newNode->child = NULL;
		newNode->parent = NULL;
		strcpy(newNode->details.name, name);
		if(strcmp(userChoice, "file") == 0) {
			newNode->details.isDirectory = FALSE;
			askFileContent(newNode->details.fileContent);
		} else {
			newNode->details.isDirectory = TRUE;
		}
	}
	return newNode;
}

int duplicateNames(Node *node, char name[]) {
	while(node) {
		if (strcmp(node->details.name, name) == 0) {
			return TRUE;
		}
		node = node->next;
	}
	return FALSE;
}

void addSibling(Node *node, char userChoice[], char name[]) {
	char address[1000];
	int duplicates = duplicateNames(node, name);
	if (duplicates == FALSE) {
		Node *newNode = createNewNode(userChoice, name);
		if (newNode) {
			strcpy(address, node->parent->dirAddress.dirAddress);
			strcat(address, newNode->details.name);
			strcat(address, "/");
			strcpy(newNode->dirAddress.dirAddress, address);
			while (node->next) {
				node = node->next;
			}
			node->next = newNode;
			newNode->previous = node;
		}
	} else {
		printf("An item already exists in this directory with such name.\n");
	}
}


void addChild(Node *node, char userChoice[], char name[]) {
	if (node->child) {
		addSibling(node->child, userChoice, name);
	} else {
        	Node *newNode = createNewNode(userChoice, name);
        	if (newNode) {
			char address[1000];
			node->child = newNode;
			newNode->parent = node;
               		strcpy(address, node->dirAddress.dirAddress);
               		strcat(address, newNode->details.name);
               		strcat(address, "/");
               		strcpy(newNode->dirAddress.dirAddress, address);
		}
	}
}


void freeEverything(Node *rootNode) {
	Node *nextNode;
	while(rootNode) {
		if (rootNode->child) {
			freeEverything(rootNode->child);
		}
		nextNode = rootNode->next;
		free(rootNode);
		rootNode = nextNode;

	}
}

void removeTheDirectory(Node *node, char userInput[]) {
	if(strcmp(userInput, "Root") == 0) {
		printf("You can't delete the root directory!\n");
	} else {
		if (node->details.isDirectory) {
			node = node->child;
			if (node == NULL) {
				printf("Sorry, this directory has no items in it.\n");
			} else {
				while (node != NULL && strcmp(userInput, node->details.name) != 0) {
					node = node->next;
				}
				if (node == NULL) {
					printf("Sorry, this directory does not have your specified input directory.\n");
				} else {
					if (node->details.isDirectory) {
						removeRMDIR(node);
					} else {
						printf("You need rm to remove a file!\n");
					}
				}
			}
		}
	}
}

void removeRMDIR(Node *node) {
	if(node->child) {
		printf("Sorry, this directory has items in it. You need rmrdir to remove it!\n");
	} else {
		if(node->previous == NULL) {
			Node *parentNode = node->parent;
			if(node->next != NULL) {
				parentNode->child = node->next;
				node->next->parent = parentNode;
				node->next->previous = NULL;
			} else {
				parentNode->child = NULL;
			}
		} else {
			if(node->next == NULL) {
				node->previous->next = NULL;
			} else {
				node->next->previous = node->previous;
				node->previous->next = node->next;
			}
		}
		free(node);
	}
}

void rRemoveTheDirectory(Node *node, char userInput[]) {
	if(strcmp(userInput, "Root") == 0) {
		printf("You can't delete the root directory!\n");
	} else {
		if(node->details.isDirectory) {
			node = node->child;
			if(node == NULL) {
				printf("Sorry, this directory has no items in it.\n");
			} else {
				while(node != NULL && strcmp(userInput, node->details.name) != 0) {
					node = node->next;
				}
				if (node == NULL) {
					printf("Sorry, your specificied input directory does not exist here.\n");
				} else {
					if(node->details.isDirectory) {
						removeRMRDIR(node);
					} else {
						printf("You need rm to remove a file!\n");
					}
				}
			}
		}
	}
}

void removeRMRDIR(Node *node) {
	if(node->child) {
		removeRMRDIR(node->child);
	}
	if(node->previous == NULL) {
		Node *parentNode = node->parent;
		if(node->next != NULL) {
			parentNode->child = node->next;
			node->next->parent = parentNode;
			node->next->previous = NULL;
		} else {
			parentNode->child = NULL;
		}
	} else {
		if (node->next == NULL) {
			node->previous->next = NULL;
		} else {
			node->next->previous = node->previous;
			node->previous->next = node->next;
		}
	}
	free(node);
}


void lsCommand(Node *node) {
	printf("Items in %s:\n", node->details.name);
	node = node->child;
	if(node == NULL) {
		printf("\t\t[This is an empty directory!]\n");
	} else {
		while(node) {
			printf("\t\t%s", node->details.name);
			node = node->next;
		}
		putchar('\n');
	}
}


void pwdCommand(Node *node) {
	printf("\t\t%s\n", node->dirAddress.dirAddress);
}


void cdCommand(Node **node, Node *rootNode) {
	if (strcmp((*node)->details.name, "Root") != 0) {
		*node = rootNode;
        
	} else {
		printf("We're already at the root!\n");
	}	
}

void cdDotDotCommand(Node **node) {
	if (strcmp((*node)->details.name, "Root") != 0) {
		if ((*node)->parent == NULL) {
			while ((*node)->previous) {
				(*node) = (*node)->previous;
			}
		}
		(*node) = (*node)->parent;
	} else {
		printf("We're already at the root!\n");
	}
}

void cdPathCommand(Node **node, Node *rootNode, char path[], int *isFile) {
	Node *traversalNode = rootNode;
	while(traversalNode) {
		if(traversalNode->child) {
			cdPathCommand(node, traversalNode->child, path, isFile);
		}
		if (strcmp(traversalNode->dirAddress.dirAddress, path) == 0) {
			if(traversalNode->details.isDirectory) {
				*node = traversalNode;
				break;
			} else {
				printf("Can't change directory into a file!\n");
				*isFile = TRUE;
			}
		}
		traversalNode = traversalNode->next;
	}
}

void cdNameCommand(Node **node, char name[]) {
	Node *traversalNode = (*node)->child;
	if(traversalNode) {
		while(traversalNode != NULL && strcmp(name, traversalNode->details.name) != 0) {
			traversalNode = traversalNode->next;
		}
		if (traversalNode == NULL) {
			printf("Sorry, your input directory doesn't exist in this directory.\n");
		} else {
			if (traversalNode->details.isDirectory) {
				(*node) = (*node)->child;
				while(strcmp((*node)->details.name, name) != 0) {
					(*node) = (*node)->next;
				}
			} else {
				printf("Can't change directory into a file!\n");
			}
		}
	} else {
		printf("Sorry, this directory doesn't exist.\n");
	}
}


void catCommand(Node *node, char name[]) {
	node = node->child;
	if(node == NULL) {
		printf("\t\t[This is an empty directory!]\n");
	} else {
		while (node != NULL && strcmp(node->details.name, name) != 0) {
			node = node->next;
		}
		if (node == NULL) {
			printf("Sorry, your input file doesn't exist in this directory.\n");
		} else {
			if (node->details.isDirectory) {
				printf("%s is a directory.\n", node->details.name);
			} else{
				printf("%s\n", node->details.fileContent);
			}
		}
	}
}

void rmFile(Node *node, char userInput[]) {
	node = node->child;
	if(node == NULL) {
		printf("\t\t[This is an empty directory!]\n");
	} else {
		while (node != NULL && strcmp(node->details.name, userInput) != 0) {
			node = node->next;
		}
		if (node == NULL) {
			printf("This file doesn't exist in this directory.\n");	
		} else {
			if (node->details.isDirectory == FALSE) {
				if(node->previous == NULL) {
					Node *parentNode = node->parent;
                			if(node->next != NULL) {
                        			parentNode->child = node->next;
                        			node->next->parent = parentNode;
                        			node->next->previous = NULL;
                			} else {
                        			parentNode->child = NULL;
                			}
        			} else {
                			if (node->next == NULL) {
                        			node->previous->next = NULL;
                			} else {
                        			node->next->previous = node->previous;
                        			node->previous->next = node->next;
                			}
        			}
        			free(node);
			} else {
				printf("You need rmdir to remove a directory!\n");
			}
		}
	}
}

void printSpaces(int spacing) {
	int i = 0;
	for (i = 0; i < spacing; i++) {
		printf(" ");
	}
}

void dirPrintCommand(Node *rootNode, Node *currNode, int spacing) {
	while (rootNode) {
		printSpaces(spacing);
		printf("%s\n", rootNode->details.name);
		if (rootNode->child) {
			printSpaces(spacing);
			printf("Children of %s:\n", rootNode->details.name);
			dirPrintCommand(rootNode->child, currNode, spacing + 5);
		}
		rootNode = rootNode->next;
	}
}

void askWhichCP(char userChoice[]) {
	printf("Would you like to copy the file to the same directory with a different name or copy to a different directory with the same name?\n");
	printf("Enter sd for the first option and dd for the second option: ");
	fgets(userChoice, 10, stdin);
	userChoice[strcspn(userChoice, "\n")] = 0;
	if(strlen(userChoice) == 0) {
		strcpy(userChoice, "Q");
	}
}

void cpCommand(Node *node, Node *rootNode, char name[]) {
	char userChoice[10];
	askWhichCP(userChoice);
	if(strcmp(userChoice, "sd") == 0) {
		cpSameDirCommand(node, name);
	} else if (strcmp(userChoice, "dd") == 0) {
		char path[1000];
		int isFile;
		Node *targetNode = node;
		getPath(path);
		cdPathCommand(&targetNode, rootNode, path, &isFile);
		if(strcmp(node->dirAddress.dirAddress, path) != 0) {
			if(strcmp(node->dirAddress.dirAddress, targetNode->dirAddress.dirAddress) == 0) {
				printf("The directory you're looking for doesn't exist.\n");
			} else {
				int isDuplicate = duplicateNames(targetNode->child, name);
				if(isDuplicate == FALSE) {
					cpPathCommand(node, targetNode, name);
				} else {
					printf("Sorry, an item already exists at that location with that name.\n");
				}
			}
		}
	} else {
		printf("Invalid option.\n");
	}
}

void cpSameDirCommand(Node *node, char name[]) {
	Node *parentNode = node;
	Node *traversalNode;
	node = node->child;
	traversalNode = node;
	if(node) {
		while(node != NULL && strcmp(node->details.name, name) != 0) {
			node = node->next;
		}
		if(node == NULL) {
			printf("The specified item does not exist in this directory.\n");
		} else {
			if(node->details.isDirectory == FALSE) {
				char newName[65];
				int isDuplicate;
				askRename(node, newName);
				isDuplicate = duplicateNames(traversalNode, newName);
				if(!isDuplicate) {
					Node *newNode = cpCreateNewNode();
					while(traversalNode->next) {
						traversalNode = traversalNode->next;
					}
					strcpy(newNode->details.name, newName);
					strcpy(newNode->details.fileContent, node->details.fileContent);
					traversalNode->next = newNode;
					newNode->previous = traversalNode;
				} else {
					printf("No duplicate names allowed.\n");
					cpSameDirCommand(parentNode, name);
				}
			} else {
				printf("Can't copy directories.\n");
			}
		}
	} else {
		printf("Empty directory.\n");
	}
}

void cpPathCommand(Node *node, Node *targetNode, char name[]) {
	if(node->child) {
		node = node->child;
		while(node != NULL && strcmp(node->details.name, name) != 0) {
			node = node->next;
		}
		if(node->details.isDirectory == FALSE) {
			if(strcmp(node->dirAddress.dirAddress, targetNode->dirAddress.dirAddress) != 0) {
				Node *parentNode = targetNode;
				Node *newNode = cpCreateNewNode();
				if(newNode) {
					strcpy(newNode->details.name, node->details.name);
					strcpy(newNode->details.fileContent, node->details.fileContent);
					if(targetNode->child) {
						targetNode = targetNode->child;
						while(targetNode->next) {
							targetNode = targetNode->next;
						}
						targetNode->next = newNode;
						newNode->previous = targetNode;
					} else {
						newNode->parent = targetNode;
						targetNode->child = newNode;
					}
				}
			}
		} else {
			printf("The item you're looking for doesn't exist or is a directory.\n");
		}
	} else {
		printf("Empty directory.\n");
	}
}

void mvCommand(Node *node, Node *rootNode, Node *extraNode, char name[]) {
	char userChoice[10];
	askUserChoice(userChoice);
	if(strcmp(userChoice, "r") == 0) {
		mvRenameCommand(node, name);
	} else if (strcmp(userChoice, "m") == 0) {
		char path[1000];
		int isFile;
		Node *extraNode = node;
		getPath(path);
		cdPathCommand(&extraNode, rootNode, path, &isFile);
		if(strcmp(node->dirAddress.dirAddress, path) != 0) {
			if(strcmp(node->dirAddress.dirAddress, extraNode->dirAddress.dirAddress) == 0) {
				printf("The directory you're looking for doesn't exist.\n");
			} else {
				if(isFile != 1) {
					int isDuplicate = duplicateNames(extraNode->child, name);
					if(isDuplicate == FALSE) {
						mvMoveCommand(node, extraNode, name);
					} else {
						printf("Sorry, an item already exists at that location with that name.\n");
					}
				}
			}
		}
	} else {
		printf("Invalid option.\n");
	}
}

void mvRenameCommand(Node *node, char name[]) {
	Node *parentNode = node;
	node = node->child;
	if(node == NULL) {
		printf("\t\t[This is an empty directory!]\n");
	} else {
		while (node != NULL && strcmp(node->details.name, name) != 0) {
			node = node->next;
		}
		if (node == NULL) {
			printf("Sorry, your inputted item doesn't exist in this directory.\n");
		} else {
			char rename[65];
			int isDuplicate;
			askRename(node, rename);
			isDuplicate = duplicateNames(parentNode->child, rename);
			if(isDuplicate) {
				printf("Sorry, an item already exists with that name.\n");
			} else {
				strcpy(node->details.name, rename);
				changeDirAddresses(node, parentNode);
			}
		}
	}
}

void mvMoveCommand(Node *node, Node *targetNode, char name[]) {
	if(node->child) {
		node = node->child;
		while(node != NULL && strcmp(node->details.name, name) != 0) {
			node = node->next;
		}
		if (node == NULL) {
			printf("Sorry, your specified item doesn't exist in this directory.\n");
		} else {
			if(strcmp(targetNode->dirAddress.dirAddress, node->dirAddress.dirAddress) != 0) {
				if (targetNode->child) {
					Node *parentNode = targetNode;
					targetNode = targetNode->child;
					while(targetNode->next) {
						targetNode = targetNode->next;
					}
					if (node->previous) {
						if(node->next) {
							node->previous->next = node->next;
							node->next->previous = node->previous;
						} else {
							node->previous->next = NULL;
						}
					} else {
						if (node->next) {
							node->parent->child = node->next;
							node->next->parent = node->parent;
						} else {
							node->parent->child = NULL;
						}
					}
					targetNode->next = node;
					node->previous = targetNode;
					changeDirAddresses(node, parentNode);
				} else {
					if (node->previous) {
						if(node->next) {
							node->previous->next = node->next;
							node->next->previous = node->previous;
						} else {
							node->previous->next = NULL;
						}
					} else {
						if (node->next) {
							node->parent->child = node->next;
							node->next->parent = node->parent;
						} else {
							node->parent->child = NULL;
						}
					}
					targetNode->child = node;
					node->parent = targetNode;
					changeDirAddresses(node, targetNode);
				}
			} else {
				printf("Already at that location.\n");
			}
		}
	} else {
		printf("Empty directory.\n");
	}
}

void changeDirAddresses(Node *node, Node *parentNode) {
	strcpy(node->dirAddress.dirAddress, parentNode->dirAddress.dirAddress);
	strcat(node->dirAddress.dirAddress, node->details.name);
	strcat(node->dirAddress.dirAddress, "/");
	
	if(node->next) {
		changeDirAddresses(node->next, parentNode);
	}
	
	if(node->child) {
		changeDirAddresses(node->child, node);
	}
}

void printDate() {
	time_t currTime;
	time(&currTime);
	printf("Current date and time: %s", ctime(&currTime));
}

void printHelpManual() {
	cdManual();
	lsManual();
	pwdManual();
	catManual();
	cpManual();
	mvManual();
	rmManual();
	mkdirManual();
	rmdirManual();
	fileManual();
	dateManual();
	rmrdirManual();
	qManual();
}

