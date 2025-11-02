#include <stdio.h>
#include "Info.h"
#include <string.h>
#include <stdlib.h>

extern int line_no;          // line no for program errors
extern int line_number_brac; // line number for bracket errors
int line = 0;                // line number for ternary numbers

char token[100];
int token_index = 0;

void resettoken()
{
    token[0] = '\0';
    token_index = 0;
}

void addchar(char ch)
{
    token[token_index++] = ch;
    token[token_index] = '\0';
}

void tokenidentifier_keyword(FILE *fp)
{

    char ch;
    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '\n')
        {
            line_no++;
        }
        if (isalphabet(ch))
        {
            token[token_index++] = ch;
        }
        else if ((isalphabet(token[token_index - 1]) || (token[token_index - 1] == '_')) && (isnumber(ch) || ch == '_'))
        {
            token[token_index++] = ch;
        }
        else
        {
            break;
        }
    }
    token[token_index] = '\0';
    if (iskeyword(token))
    {
        printf(GREEN "Keyword : %s\n" RESET, token);
    }
    else
    {
        printf(YELLOW "Identifier : %s\n" RESET, token);
    }
    resettoken();
    fseek(fp, -1, SEEK_CUR);
}

void skipincludes(FILE *fp)
{

    char ch;
    while ((ch = fgetc(fp)) != '\n')
        ;
    if (ch == '\n')
    {
        line_no++;
        line_number_brac++;
        line++;
    }
}

void token_number(FILE *fp)
{
    char ch;
    int hasdot = 0;
    int ishex = 0, isoct = 0, isbin = 0;
    int invalid = 0;
    int floatf = 0;

    if (token[token_index - 1] == '0')
    {

        char next = fgetc(fp);

        if (next == 'X' || next == 'x')
        {
            ishex = 1;
            token[token_index++] = next;
        }
        else if (next == 'b' || next == 'B')
        {
            isbin = 1;
            token[token_index++] = next;
        }
        else if (isnumber(next))
        {
            isoct = 1;
            fseek(fp, -1, SEEK_CUR);
            // token[token_index++] = next;
        }
        else
        {
            fseek(fp, -1, SEEK_CUR);
        }
    }
    while ((ch = fgetc(fp)) != EOF)
    {

        if (ch == ';')
        {
            break;
        }
        if (ch == '\n')
        {
            line_no++;
        }
        if (ishex)
        {

            if (ishexdigit(ch))
            {
                token[token_index++] = ch;
            }
            else
            {
                if (isalphabet(ch))
                {
                    reportError("Invalid hexadecimal number", line_no, ch);
                }
                else if (isoperator(ch))
                {
                    // fseek(fp,-1,SEEK_CUR);
                    break;
                }
            }
        }
        else if (isbin)
        {
            if (ch == '0' || ch == '1')
            {
                token[token_index++] = ch;
            }
            else if (isoperator(ch) || ch == ' ')
            {
                // fseek(fp,-1,SEEK_CUR);
                break;
            }
            else
            {
                reportError("Inavlid Binary Number", line_no, ch);
            }
        }
        else if (isoct)
        {
            if (ch >= '0' && ch <= '7')
            {
                token[token_index++] = ch;
            }
            else if ((isoperator(ch) || ch == ' ') && ch != '.')
            {
                // fseek(fp,-1,SEEK_CUR);
                break;
            }
            else
            {
                reportError("Invalid Octal Number", line_no, ch);
            }
        }
        else
        {

            if (isnumber(ch))
            {
                token[token_index++] = ch;
            }
            else if (ch == '.' && !hasdot)
            {
                token[token_index++] = ch;
                hasdot = 1;
            }
            else if ((ch == 'f' || ch == 'F') && !floatf)
            {
                token[token_index++] = ch;
                floatf = 1;
            }
            else if (isalphabet(ch) && hasdot && (!floatf))
            {
                reportError("invalid suffix on floating constant", line_no, ch);
            }
            else if (floatf && (ch == 'f' || ch == 'F'))
            {
                reportError("invalid suffix on floating constant", line_no, ch);
            }
            else if (ch == '.' && hasdot)
            {
                reportError("Invalid floating conatants (too many dots)", line_no, ch);
            }
            else
            {
                break;
            }
        }
    }
    if (isalphabet(ch) && (!hasdot))
    {
        reportError("invalid suffix on integer constant", line_no, ch);
    }

    token[token_index] = '\0';

    if (hasdot)
    {
        printf(BLUE "Float Constant : %s\n" RESET, token);
    }
    else
    {
        printf(MAGENTA "Numeric Constant : %s\n" RESET, token);
    }
    resettoken();
    fseek(fp, -1, SEEK_CUR);
}

void token_operator(FILE *fp)
{
    char ch;
    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '\n')
        {
            line_no++;
        }
        if (isoperator(ch))
        {
            token[token_index++] = ch;
        }
        else
        {
            break;
        }
    }
    token[token_index] = '\0';
    if (isoperator(token[0]))
    {
        printf(CYAN "Operator : %s\n" RESET, token);
    }
    resettoken();
    fseek(fp, -1, SEEK_CUR);
}

void token_symbol()
{
    token[token_index] = '\0';
    if (isSymbol(token[0]))
    {
        printf(GRAY "Symbol : %s\n" RESET, token);
    }
    resettoken();
}

void token_StringLiteral(FILE *fp)
{
    char ch;
    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '\n')
        {
            line_no++;
            reportError("Missing Terminating Character", line_no - 1, '"');
        }
        if (ch != '"')
        {
            token[token_index++] = ch;
        }
        else
        {
            break;
        }
    }
    if (ch == EOF)
    {
        reportError("Missing Terminating Character", line_no - 1, '"');
    }
    token[token_index++] = ch;
    token[token_index] = '\0';

    printf(ORANGE "String Literal : %s\n" RESET, token);

    resettoken();
}

void token_character(FILE *fp)
{
    char ch;

    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '\n')
        {
            line_no++;
            reportError("Missing Terminating Character", line_no - 1, 39);
        }
        if ((token_index > 1) && (token[1] != 92) && (ch != 39))
        {
            reportError("multi-character character constant", line_no, ch);
        }
        if ((token_index > 2) && (token[1] == 92) && (ch != 39))
        {
            reportError("multi-character character constant", line_no, ch);
        }
        if (ch != 39)
        {
            token[token_index++] = ch;
        }
        else
        {
            break;
        }
    }
    if (ch == EOF)
    {
        reportError("Missing Terminating Character", line_no, 39);
    }
    token[token_index++] = ch;
    token[token_index] = '\0';

    printf(PURPLE "Character Constant : %s\n" RESET, token);

    resettoken();
}

void skipComment(FILE *fp)
{
    char ch;
    ch = fgetc(fp);
    if (ch == '/')
    {
        while ((ch = fgetc(fp)) != EOF)
        {
            if (ch == '\n')
            {
                line_no++;
                line_number_brac++;
                line++;
                break;
            }
        }
    }
    else if (ch == '*')
    {
        char prev = 0;
        while ((ch = fgetc(fp)) != EOF)
        {
            if (ch == '\n')
            {
                line_no++;
                line_number_brac++;
                line++;
            }
            if (prev == '*' && ch == '/')
            {
                break;
            }
            prev = ch;
        }
    }
    else
    {
        fseek(fp, -1, SEEK_CUR);
        token_operator(fp);
    }
    if (ch == EOF)
    {
        reportError("unterminated comment", line_number_brac, '/');
        return;
    }

    resettoken();
}
