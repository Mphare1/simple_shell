#include "main.h"

/**
 * _strtok - tokenizes a string
 * @str: string to tokenize
 * @delimit_: string that contains the delimit_iters
 * Return: pointer to position in string of a null-terminated word.
 */
char *_strtok(char *str, const char *delimit_)
{
    static char *w_start, *endd_, *end2;
    int word_found = 0;
    
    if(str == NULL)
    {
        if(w_start == NULL || end2 == NULL)
            return NULL;
        str = end2 + 1;
    }
    else
        endd_ = str + _strlen(str);
        
    for(unsigned int i = 0; str + i < endd_; i++)
    {
        for(unsigned int j = 0; delimit_ != NULL && delimit_[j] != '\0'; j++)
        {
            if(str[i] == delimit_[j])
            {
                if(word_found == 1)
                {
                    str[i] = '\0';
                    end2 = str + i;
                    return w_start;
                }
                break;
            }
        }
        if(delimit_[j] == '\0' && word_found == 0)
        {
            word_found = 1;
            w_start = str + i;
        }
    }
    
    end2 = NULL;
    if(word_found == 1)
        return w_start;
        
    return NULL;
}
