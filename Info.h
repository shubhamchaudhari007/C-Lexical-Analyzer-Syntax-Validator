#ifndef INFO_H
#define INFO_H

#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN    "\033[1;36m"
#define ORANGE   "\033[38;5;208m"
#define GRAY     "\033[1;90m"
#define PURPLE   "\033[1;95m" 

#define MAXBRAC 1000

extern int brac_index;
extern int line_number_brac;
extern char bracketschk[MAXBRAC];

char pop();
void push(char ch);
int matchBrackets(char open, char close);
void checkbrackets(FILE *fp);

int isalphabet(char ch);
int isSymbol(char ch);
int isnumber(char ch);
int iskeyword(char *str);
int isoperator(char ch);
int ishexdigit(char ch);
int checkExtension(char *str, char *extension);

void remove_ternary();
void add_ternary(char ch);
void checkternery(FILE *fp);
void resettoken();
void addchar(char ch);
void tokenidentifier_keyword(FILE *fp);
void skipincludes(FILE *fp);
void token_number(FILE *fp);
void token_operator(FILE *fp);
void token_symbol();
void token_StringLiteral(FILE *fp);
void token_character(FILE *fp);
void skipComment(FILE *fp);

void reportError(char *msg, int line, char ch);

#endif