//test area for progmram
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "parser.h"
#include "tree.h"

void printHelp(){
    printf("WIP, please improve\n");
    printf("Format: ./prog \"expression\" [pre|post|in] [-e]\n");
}

void printGuide(){
    printf("WIP, please improve\n");
    printf("Format: ./prog \"expression\" [pre|post|in] [-e]\n");
}

int main(int argc, char *argv[]) {
    if (argc == 2){
        if(strcmp(argv[1], "--help") == 0){
            printHelp();
            return 0;
        } else if (strcmp(argv[1], "--guide") == 0){
            printGuide();
            return 0;
        }
    
        const char *expression = argv[1];
        Token tokens[MAX_TOKENS];
        int tokenCount = 0;
    
    //----------------------NO EVAL MODE--------------------//
        //tokenize the expression and check for errors
        if(tokenize(expression, tokens, &tokenCount)){
            
            int type = evalExpressionType(tokens, tokenCount);
            switch(type) {
                case 1:
                    printf("The input is in prefix notation.\n");
                    break;
                case 2:
                    printf("The input is in infix notation.\n");
                    break;
                case 3:
                    printf("The input is in postfix notation.\n");   
                    break; 
                default:
                    printf("Unknown notation.\n");
                    return 1;
            }
            
            TreeNode *root = NULL;

            switch(type){
                case 1: root = buildPrefix(tokens, tokenCount); break;
                case 2: root = buildInfix(tokens, tokenCount); break;
                case 3: root = buildPostfix(tokens, tokenCount); break;
            }

            if (!root) {
                printf("Expression was Invalid, try checking your input!");
                return 1;
            }

            Token result[MAX_TOKENS];
            int index = 0;
            PrefixTraversal(root, result, &index);
            printf("No specified conversion, defaulting to prefix....\n");
            printf("Prefix Expression:\n");
            for (int i = 0; i < index; i++){
                printf("%c ", result[i].value);
            }
            printf("\n");

            freeTree(root);

        } else {
            printf("Expression was Invalid, try checking your input!");
        }
    } else if (argc >= 3){
        const char *expression = argv[1];
        const char *targetTypeStr = argv[2];
        //check if 4 is input, then check if -e 
        bool evalFlag = (argc == 4 && strcmp(argv[3], "-e") == 0);

        Token tokens[MAX_TOKENS];
        int tokenCount = 0;

        if (!tokenize(expression, tokens, &tokenCount)) {
            printf("Error tokenizing expression.\n");
            return 1;
        }

        int inputType = evalExpressionType(tokens, tokenCount);
        int targetType = 0;

        if (strcmp(targetTypeStr, "pre") == 0) {
            targetType = 1;
        } else if (strcmp(targetTypeStr, "in") == 0) {
            targetType = 2;
        } else if (strcmp(targetTypeStr, "post") == 0) {
            targetType = 3;
        } else {
            printf("Invalid target type. Use 'pre', 'in', or 'post'.\n");
            return 1;
        }

        if (inputType == targetType){
            printf("Input and target types are the same. No conversion needed!\n");
            return 0;
        }

        TreeNode *root = NULL;
        switch (inputType) {
            case 1: root = buildPrefix(tokens, tokenCount); break;
            case 2: root = buildInfix(tokens, tokenCount); break;
            case 3: root = buildPostfix(tokens, tokenCount); break;
            default:
                printf("Unrecognized input expression type.\n");
                return 1;
        }

        if (!root) {
            printf("Error building expression tree.\n");
            return 1;
        }

        Token result[MAX_TOKENS];
        int index = 0;

        printf("Converted Expression:\n");
        switch(targetType){
            case 1: PrefixTraversal(root, result, &index); break;
            case 2: InfixTraversal(root, result, &index); break;
            case 3: PostfixTraversal(root, result, &index); break;
        }

        for (int i = 0; i < index; i++){
            printf("%c ", result[i].value);
        }
        printf("\n");

        //------------make eval file
        //-----------WHOEVER DOES IT, convert everything to postfix then use basic stack evaluation (safest method)!!!!!!
        if (evalFlag) {
            printf("WIP,please imporve!\n");
        }

        freeTree(root);

    } else {
        printf("Invalid usage. Use --help for instructions.\n");
        return 1;
    }

    return 0;
}
