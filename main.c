#include <stdio.h>
#include "Info.h"
#include <string.h>

int line_no = 0;

int ternary_ope = 0;

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        printf(RED "Please Give File !!\n" RESET);
        printf(YELLOW"Usage : ./a.out <sample.c> file\n"RESET);
        return 0;
    }

    if (!checkExtension(argv[1], ".c"))
    {
        printf(RED "Please give file with .c extension only \n" RESET);
        
        return 0;
    }
    FILE *fp;
    fp = fopen(argv[1], "r");

    brac_index = -1;
    line_number_brac = 1;

    checkbrackets(fp);

    rewind(fp);
    char ch;
    line_no = 1;
    while ((ch = getc(fp)) != EOF)
    {

        if (isalphabet(ch) || ch == '_')
        {
            addchar(ch);
            tokenidentifier_keyword(fp);
        }
        else if (ch == '#')
        {
            skipincludes(fp);
        }
        else if (isnumber(ch))
        {
            addchar(ch);
            token_number(fp);
        }
        else if (ch == '/')
        {
            addchar(ch);
            skipComment(fp);
            // continue;
        }
        else if (isoperator(ch))
        {
            if(ch == '?'){
                ternary_ope = 1;
                addchar(ch);
                token_operator(fp);
            }else if(ch == ':'){

                if(ternary_ope){
                    addchar(ch);
                    token_operator(fp);
                    ternary_ope = 0;
                }else{
                    addchar(ch);
                    token_symbol();
                }
            }else{
                addchar(ch);
                token_operator(fp);
            }
            
        }
        else if (isSymbol(ch))
        {
            addchar(ch);
            token_symbol();
        }
        else if (ch == '"')
        {
            addchar(ch);
            token_StringLiteral(fp);
        }
        else if (ch == 39)
        {
            addchar(ch);
            token_character(fp);
        }
        else if (ch == '\n')
        {
            line_no++;
        }
    }
    fclose(fp);
}
