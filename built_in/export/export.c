#include "../../include/minishell.h"

int process_var(char *s, t_env *env);

/* Test
int main()
{
    t_shell data;

    t_env *n1 = (t_env *)malloc(sizeof(t_env));
    t_env *n2 = (t_env *)malloc(sizeof(t_env)); 
    t_env *n3 = (t_env *)malloc(sizeof(t_env));

    n1->key = strdup("HOME");
    n1->val = strdup("/home/jpaul");
    n1->next = n2;

    n2->key = strdup("USER");
    n2->val = strdup("Jason");
    n2->next = n3;

    n3->key = strdup("SHELL");
    n3->val = strdup("/bash/");
    n3->next = NULL;

    data.env = n1;
    // OK
    // char *a0[] = {"export", NULL};
    // char *a1[] = {"export", strdup("TEST=test"), NULL};
    // char *a2[] = {"export", strdup("TEST=test"), NULL};
    // char *a3[] = {"export", strdup("TEST=test user"), NULL};           
    // char *a4[] = {"export", strdup("TEST=ici=coucou"), NULL};
    // char *a5[] = {"export", strdup("TEST"), NULL};
    // char *a6[] = {"export", strdup("$DDD"), NULL};                        
    // char *a7[] = {"export", strdup("TEST="), NULL};     
    // char *a8[] = {"export", strdup("=Yoyo"), NULL};   
    // char *a9[] = {"export", strdup("_A55==Rolling+"), NULL};          
    // char *a10[] = {"export", "VAR", NULL};                       
    // char *a11[] = {"export", 
    //     strdup("AI=haha"), 
    //     strdup("BI=yoyo"), 
    //     strdup("TEST=change please"),
    //     NULL};   // Multiple argument

    // // ERROR
    // char *a12[] = {"export", 
    //     strdup("VAR"), 
    //     strdup("="), 
    //     strdup("Hello"), 
    //     NULL};                                                      
    // char *a13[] = {"export", strdup("55@=Time"), NULL};   
    // char *a14[] = {"export", "", "et", "unset", "", NULL};
     char *a15[] = {"export", "312=313", "#sddfs", NULL};

    export(a15, data.env);
    t_env *current = n1;
    printf("\n=================\n");
    while (current)
    {
        printf("%s=%s\n", current->key, current->val);
        current = current->next;
    }
    destroy_env(&data);
}
 */

/* export
Description: Update or append variable inside env 
    1) arg = 0   | print all var in env in accending order
    2) arg > 0
        Check 
            - str before '=' or '/0' is valid identifier.
            - if correct, must have '=' after that
        Proceed
            - If key exist in env, amend value
            - Else,  add new variable into the env

Return: None
*/
void builtin_export(char **arg, t_env *env)
{
    int i;

    i = 0;
    if (arg[1] == NULL)
    {
        print_sorted_env(env);
        return;
    }
    while (arg[++i])
    {
        if (!process_var(arg[i], env))
            printf("export: `%s\': fail to add into env\n");
    }
}

int process_var(char *s, t_env *env)
{
    int i;
    i = 0;
    if (!is_identifier(s, &i))
        printf("export: `%s\': not a valid identifier\n", s);
    else if (s[i] == '=')
    {
        s[i] = '\0';
        if (env_val(s, env))    return (update_env(s, &s[i + 1], env));
        else                    return (append_env(s, &s[i + 1], env));
    }
    return (TRUE);
}