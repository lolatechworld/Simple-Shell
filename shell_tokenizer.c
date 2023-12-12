#include "shell.h"

/**
* split_string - splits a string into words. Repeat delimiters are ignored
* @str: the input string
* @delimiters: the delimeter string
* Return: a pointer to an array of strings, or NULL on failure
*/

char **split_string(char *str, char *delimiters)
{
int index_i, index_j, index_k, index_m, num_words = 0;
char **result_array;

if (str == NULL || str[0] == '0')
return (NULL);
if (!delimiters)
delimiters = " ";
for (index_i = 0; str[index_i] != '\0'; index_i++)
if (!is_delimiter(str[index_i], delimiters) &&
(is_delimiter(str[index_i + 1], delimiters) || !str[index_i + 1]))
num_words++;

if (num_words == 0)
return (NULL);
result_array = malloc((1 + num_words) *sizeof(char *));
if (!result_array)
return (NULL);
for (index_i = 0, index_j = 0; index_j < num_words; index_j++)
{
while (is_delimiter(str[index_i], delimiters))
index_i++;
index_k = 0;
while (!is_delimiter(str[index_i + index_k],
delimiters) && str[index_i + index_k])
index_k++;
result_array[index_j] = malloc((index_k + 1) * sizeof(char));
if (!result_array[index_j])
{
for (index_k = 0; index_k < index_j; index_k++)
free(result_array[index_k]);
free(result_array);
return (NULL);
}
for (index_m = 0; index_m < index_k; index_m++)
result_array[index_j][index_m] = str[index_i++];
result_array[index_j][index_m] = '\0';
}
result_array[index_j] = NULL;
return (result_array);
}

/**
* split_string_v2 - splits a string into words
* @str: the input string
* @delimiter: the delimiter
* Return: a pointer to an array of strings, or NULL on failure
*/
char **split_string_v2(char *str, char delimiter)
{
int index_i, index_j, index_k, index_m, num_words = 0;
char **result_array;

if (str == NULL || str[0] == '\0')
return (NULL);
for (index_i = 0; str[index_i] != '\0'; index_i++)
if ((str[index_i] != delimiter && str[index_i + 1] == delimiter) ||
(str[index_i] != delimiter && !str[index_i + 1])
|| str[index_i + 1] == delimiter)
num_words++;
if (num_words == 0)
return (NULL);
result_array = malloc((1 + num_words) *sizeof(char *));
if (!result_array)
return (NULL);
for (index_i = 0, index_j = 0; index_j < num_words; index_j++)
{
while (str[index_i] == delimiter && str[index_i] != delimiter)
index_i++;
index_k = 0;
while (str[index_i + index_k] != delimiter &&
str[index_i + index_k] && str[index_i + index_k] != delimiter)
index_k++;
result_array[index_j] = malloc((index_k + 1) * sizeof(char));
if (!result_array[index_j])
{
for (index_k = 0; index_k < index_j; index_k++)
free(result_array[index_k]);
free(result_array);
return (NULL);
}
for (index_m = 0; index_m < index_k; index_m++)
result_array[index_j][index_m] = str[index_i++];
result_array[index_j][index_m] = '0';
}
result_array[index_j] = NULL;
return (result_array);
}
