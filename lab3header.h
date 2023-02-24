#define TRUE 1
#define FALSE 0

struct dirAddress {
    char dirAddress[1000];
};

struct Data {
    char name[65];
    char fileContent[265];
    int isDirectory;
};

typedef struct Node {
    struct Data details;
    struct dirAddress dirAddress;
    struct Node *next;
    struct Node *previous;
    struct Node *child;
    struct Node *parent;
} Node;

Node *createNewNode(char[], char[]);
void addSibling(Node *, char[], char[]);
void addChild(Node *, char[], char[]);
void freeEverything(Node *);
void askFileContent(char[]);
void removeTheDirectory(Node *, char[]);
void rRemoveTheDirectory(Node *, char[]);
void removeRMDIR(Node *);
void removeRMRDIR(Node *);
void lsCommand(Node *);
void cdCommand(Node **, Node *);
void cdDotDotCommand(Node **);
void pwdCommand(Node *);
void cdPathCommand(Node **, Node *, char[], int *);
void cdNameCommand(Node **, char[]);
void mvCommand(Node *, Node *, Node *, char[]);
void changeDirAddresses(Node *, Node *);
void cpPathCommand(Node *, Node *, char[]);
void cpSameDirCommand(Node *, char[]);
void mvMoveCommand(Node *, Node *, char[]);
void askRename(Node *, char[]);
void mvRenameCommand();
void assignCommand(Node *);
void catCommand(Node *, char[]);
void fileCommand(Node *, char[]);
void askUserName(char[]);
void readUserName(char[]);
void readUserInput(char[], char[], Node *);
void splitString(char[], char *[]);
void dirPrintCommand(Node *, Node *, int);
void printHelpManual();
void printDate();
int duplicateNames(Node *, char[]);
void rmFile(Node *, char[]);
void cpCommand(Node *, Node *, char[]);
Node *createArgNewNode(char[], char[]);
Node *cpCreateNewNode();
void addArgSibling(Node *, char[]);
void addArgChild(Node *, char[]);
void cdManual();
void lsManual();
void pwdManual();
void catManual();
void cpManual();
void rmManual();
void mvManual();
void mkdirManual();
void rmdirManual();
void fileManual();
void qManual();
void rmrdirManual();
void dateManual();
void dirprintManual();
