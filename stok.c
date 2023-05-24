#include "main.h"
#include <stdbool.h>

/**
 * _strtok - custom implementation of strtok function
 * @str: the string to be tokenized
 * @delimit_: the delimiter used to tokenize the string
 *
 * Return: a pointer to the next token found in the string, or NULL if no more tokens are found
 */
char *_strtok(char *str, const char *delimit_)
{
    unsigned int x, y;
    static char *w_start, *endd_, *end2;
    bool got_it = false;
    
    if(str == NULL)
    {
        if(w_start == NULL || end2 == NULL)
            return NULL;
        
        str = end2 + 1;
    }
    else
        endd_ = str + _strlen(str);
        
    for(x = 0; str + x < endd_; x++)
    {
        for(y = 0; delimit_ != NULL && delimit_[y] != '\0'; y++)
        {
            if(str[x] == delimit_[y])
            {
                if(got_it)
                {
                    str[x] = '\0';
                    end2 = str + x;
                    return w_start;
                    
                }
                break;
            }
        }
        if(delimit_[y] == '\0' && !got_it)
        {
            got_it = true;
            w_start = str + x;
        }
    }
    
    end2 = NULL;
    
    if(got_it)
        
        return w_start;
        
    return NULL;
}
