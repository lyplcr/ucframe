#include <stdio.h>  
#include <stdlib.h>  
#include <stdint.h>  
  
#include "command.h"  
  
  
#define MAX_ARGC 10  
  
#define MAX_CMD_NUM 50


uint8_t console_buffer[CONFIG_SYS_CBSIZE + 1];  	/* console I/O buffer   */  
static char erase_seq[] = "\b \b";      					/* erase sequence   */  
static char tab_seq[] = "        ";       				/* used to expand TABs  */  
  
typedef void (*cmd_fun_t)(int , char *[])  ;  
//命令结构体
typedef struct CMD_STRUCT  
{   
		char name[32]; 		/* Command Name */   
    char usage[64];		/* Usage message */   
    cmd_fun_t CmdFun;	//void (*CmdFun)(int , char *[]);/* Command execute function */   
}CMD_STRUCT_T;   
  
  
int cmd_num_current = 0;  
  
//命令列表   
CMD_STRUCT_T CmdTbl[MAX_CMD_NUM];   
  
#ifdef debug_cmd  
#define debug_print() printf("[%s] line:%d\n", __FUNCTION__, __LINE__)  
#else  
#define debug_print()   
#endif  
  
  
void HelpCmdExeFun(int agrc, char *argv[])  
{  
		debug_print() ;  
  
    int i = 0;  
      
    while (i < cmd_num_current)  
    {  
        printf("%3d. %-32s -- %s\n", i, CmdTbl[i].name,  CmdTbl[i].usage);  
          
        i++;  
    }  
  
    return;   
  
}  
  
void read_fun(int agrc, char * argv [ ])  
{  
		debug_print() ;  
  
    int i = 0;  
      
    while (i < cmd_num_current)   
    {  
        if (read_fun == CmdTbl[i].CmdFun)  
        {  
            printf("%s -- %s\n", CmdTbl[i].name,  CmdTbl[i].usage);  
            break;  
        }  
          
        i++;  
    }  
  
          
    return;   
}  
  
void write_fun(int agrc, char * argv [ ])  
{  
		debug_print() ;  
  
    int i = 0;  
      
    while (i < cmd_num_current)   
    {  
        if (write_fun == CmdTbl[i].CmdFun)  
        {  
            printf("%s -- %s\n", CmdTbl[i].name,  CmdTbl[i].usage);  
            break;  
        }  
          
        i++;  
    }  
  
          
    return;   
}  
  
void setenv_fun(int agrc, char * argv [ ])  
{  
		debug_print() ;  
  
    int i = 0;  
      
    while (i < cmd_num_current)   
    {  
        if (setenv_fun == CmdTbl[i].CmdFun)  
        {  
            printf("%s -- %s\n", CmdTbl[i].name,  CmdTbl[i].usage);  
            break;  
        }  
          
        i++;  
    }  
  
          
    return;   
}  
  
int register_cmd(char *name, char *usage, cmd_fun_t fun)  
{  
    int ret;  
      
    if (cmd_num_current < MAX_CMD_NUM)  
    {  
        strcpy(CmdTbl[cmd_num_current].name, name);  
        strcpy(CmdTbl[cmd_num_current].usage, usage);            
        CmdTbl[cmd_num_current].CmdFun = fun;    
        cmd_num_current++;  
    }  
    else  
    {  
        printf("%s error\n");  
        return 1;  
    }  
      
    return 0;  
}  
  
char parse_buf[256] ;  
int parse_line(const char * const line, char *argv[])  
{  
		debug_print();  
    int argc = 0;  
      
    char *ptr = parse_buf;  
    memset(parse_buf, '\0', 256);  
    strncpy(parse_buf, line, strlen(line));  
      
    while ((argv[argc]=strtok(ptr, " "))!=NULL)  
    {  
				debug_print();  
				//printf("argv[%d]:%s\n", argc, argv[argc]);  
        argc++;  
          
        if (argc > MAX_ARGC)  
            break;  
        ptr = NULL;  
    }  
		debug_print();  
    return argc;  
}  
  
static char * delete_char (char *buffer, char *p, int *colp, int *np, int plen)  
{  
    char *s;  
  
    if (*np == 0)   
    {  
        return (p);  
    }  
  
    if (*(--p) == '\t') {           /* will retype the whole line   */  
        while (*colp > plen) {  
            puts (erase_seq);  
            (*colp)--;  
        }  
        for (s=buffer; s<p; ++s) {  
            if (*s == '\t') {  
                puts (tab_seq+((*colp) & 07));  
                *colp += 8 - ((*colp) & 07);  
            } else {  
                ++(*colp);  
                putc (*s, stdout );  
            }  
        }  
    } else {  
        puts (erase_seq);  
        (*colp)--;  
    }  
    (*np)--;  
    return (p);  
}  
  
  
int32_t readline_into_buffer ( int8_t *const prompt, int8_t * buffer)  
{  
    int8_t *p = buffer;  
    int8_t * p_buf = p;  
    int32_t n = 0;              /* buffer index     */  
    int32_t plen = 0;           /* prompt length    */  
    int32_t col;                /* output column cnt    */  
    int8_t c;  
    int8_t *ptr = prompt;  
  
    /* print prompt */  
    if (prompt)   
    {  
        plen = strlen (prompt);  
        while (*ptr)  
            putc(*ptr++, stdout);  
  
        //puts (prompt);  
    }  
      
    col = plen;  
  
    while (1)  
    {    
        c = getc(stdin);  
  
        /* 
         * Special character handling 
         */  
        switch (c)   
        {  
            case '\r':              /* Enter        */  
            case '\n':  
                *p = '\0';  
                //puts ("\r");  
                return (p - p_buf);  
  
            case '\0':              /* nul          */  
                continue;  
  
            case 0x03:              /* ^C - break       */  
                p_buf[0] = '\0';    /* discard input */  
                return (-1);  
  
            case 0x15:              /* ^U - erase line  */  
                while (col > plen) {  
                    puts (erase_seq);  
                    --col;  
                }  
                p = p_buf;  
                n = 0;  
                continue;  
  
            case 0x17:              /* ^W - erase word  */  
                p=delete_char(p_buf, p, &col, &n, plen);  
                while ((n > 0) && (*p != ' ')) {  
                    p=delete_char(p_buf, p, &col, &n, plen);  
                }  
                continue;  
  
            case 0x08:              /* ^H  - backspace  */  
            case 0x7F:              /* DEL - backspace  */  
                p=delete_char(p_buf, p, &col, &n, plen);  
                continue;  
  
            default:  
                /* 
                 * Must be a normal character then 
                 */  
                if (n < CONFIG_SYS_CBSIZE-2)  
                {  
                    if (c == '\t')   
                    {   /* expand TABs      */  
                        //puts (tab_seq+(col&07));  
                        col += 8 - (col&07);  
                    }   
                    else  
                    {  
                        ++col;      /* echo input       */  
                        //putc (c, stdout);  
                    }  
                      
                    *p++ = c;  
                    ++n;  
                }   
                else   
                {           /* Buffer full      */  
                    putc ('\a', stdout);  
                }  
        }  
    }  
      
}  
  
  
int32_t readline ( int8_t *const prompt)  
{  
    /* 
     * If console_buffer isn't 0-length the user will be prompted to modify 
     * it instead of entering it from scratch as desired. 
     */  
       
    memset(console_buffer, '\0', CONFIG_SYS_CBSIZE+1);  
    console_buffer[0] = '\0';  
  
    return readline_into_buffer(prompt, console_buffer);  
}  
  
  
  
  
int find_cmd(char *cmd)  
{  
		debug_print();  
		//printf("cmd:%s\n",cmd);  
  
    int cmd_index = 0;  
  
    if (('0' == cmd[0]) && ('\0' == cmd[1]))  
        return cmd_index;  
          
    cmd_index = atoi(cmd);  
    if ((cmd_index >0 ) && (cmd_index < cmd_num_current))  
    {  
        return cmd_index;  
    }  
  
    cmd_index = 0;  
    while (cmd_index < MAX_CMD_NUM)  
    {  
        if (0 == strncmp(CmdTbl[cmd_index].name, cmd, strlen(cmd)))  
            return cmd_index;  
  
        cmd_index++;  
    }  
  
    printf("Command  [%s ]  don't support!\n", cmd);  
      
debug_print();  
    return -1 ;  
}  
/**************************************************************************** 
 * returns: 
 *  1  - command executed, repeatable 
 *  0  - command executed but not repeatable, interrupted commands are 
 *       always considered not repeatable 
 *  -1 - not executed (unrecognized, bootd recursion or too many args) 
 *           (If cmd is NULL or "" or longer than CONFIG_SYS_CBSIZE-1 it is 
 *           considered unrecognized) 
 * 
 * WARNING: 
 * 
 * We must create a temporary copy of the command since the command we get 
 * may be the result from getenv(), which returns a pointer directly to 
 * the environment data, which may change magicly when the command we run 
 * creates or modifies environment variables (like "bootp" does). 
 */  
int run_command (const char * const cmd, int flag)  
{  
		debug_print();  
  
    //puts(cmd);  
  
    int cmd_index = 0;  
    int argc = 0;  
    char *argv[MAX_ARGC];  
  
    argc = parse_line(cmd, argv);  
  
    if ((argc > 0) &&(argc < MAX_ARGC))  
        cmd_index = find_cmd(argv[0]);  
    else  
        return 1;  
  
  
    if ( -1 != cmd_index)  
        CmdTbl[cmd_index].CmdFun(argc, argv);  
          
		debug_print();  
  
    return 0;  
  
#if 0  
    cmd_tbl_t *cmdtp;  
    char cmdbuf[CONFIG_SYS_CBSIZE]; /* working copy of cmd      */  
    char *token;            /* start of token in cmdbuf */  
    char *sep;          /* end of token (separator) in cmdbuf */  
    char finaltoken[CONFIG_SYS_CBSIZE];  
    char *str = cmdbuf;  
    char *argv[CONFIG_SYS_MAXARGS + 1]; /* NULL terminated  */  
    int argc, inquotes;  
    int repeatable = 1;  
    int rc = 0;  
  
#ifdef DEBUG_PARSER  
    printf ("[RUN_COMMAND] cmd[%p]=\"", cmd);  
    puts (cmd ? cmd : "NULL");  /* use puts - string may be loooong */  
    puts ("\"\n");  
#endif  
  
    clear_ctrlc();      /* forget any previous Control C */  
  
    if (!cmd || !*cmd) {  
        return -1;  /* empty command */  
    }  
  
    if (strlen(cmd) >= CONFIG_SYS_CBSIZE) {  
        puts ("## Command too long!\n");  
        return -1;  
    }  
  
    strcpy (cmdbuf, cmd);  
  
    /* Process separators and check for invalid 
     * repeatable commands 
     */  
  
#ifdef DEBUG_PARSER  
    printf ("[PROCESS_SEPARATORS] %s\n", cmd);  
#endif  
    while (*str) {  
  
        /* 
         * Find separator, or string end 
         * Allow simple escape of ';' by writing "\;" 
         */  
        for (inquotes = 0, sep = str; *sep; sep++) {  
            if ((*sep=='\'') &&  
                (*(sep-1) != '\\'))  
                inquotes=!inquotes;  
  
            if (!inquotes &&  
                (*sep == ';') &&    /* separator        */  
                ( sep != str) &&    /* past string start    */  
                (*(sep-1) != '\\')) /* and NOT escaped  */  
                break;  
        }  
  
        /* 
         * Limit the token to data between separators 
         */  
        token = str;  
        if (*sep) {  
            str = sep + 1;  /* start of command for next pass */  
            *sep = '\0';  
        }  
        else  
            str = sep;  /* no more commands for next pass */  
#ifdef DEBUG_PARSER  
        printf ("token: \"%s\"\n", token);  
#endif  
  
        /* find macros in this token and replace them */  
        process_macros (token, finaltoken);  
  
        /* Extract arguments */  
        if ((argc = parse_line (finaltoken, argv)) == 0) {  
            rc = -1;    /* no command at all */  
            continue;  
        }  
  
        /* Look up command in command table */  
        if ((cmdtp = find_cmd(argv[0])) == NULL) {  
            printf ("Unknown command '%s' - try 'help'\n", argv[0]);  
            rc = -1;    /* give up after bad command */  
            continue;  
        }  
  
        /* found - check max args */  
        if (argc > cmdtp->maxargs) {  
            cmd_usage(cmdtp);  
            rc = -1;  
            continue;  
        }  
  
#if defined(CONFIG_CMD_BOOTD)  
        /* avoid "bootd" recursion */  
        if (cmdtp->cmd == do_bootd) {  
#ifdef DEBUG_PARSER  
            printf ("[%s]\n", finaltoken);  
#endif  
            if (flag & CMD_FLAG_BOOTD) {  
                puts ("'bootd' recursion detected\n");  
                rc = -1;  
                continue;  
            } else {  
                flag |= CMD_FLAG_BOOTD;  
            }  
        }  
#endif  
  
        /* OK - call function to do the command */  
        if ((cmdtp->cmd) (cmdtp, flag, argc, argv) != 0) {  
            rc = -1;  
        }  
  
        repeatable &= cmdtp->repeatable;  
  
        /* Did the user stop this? */  
        if (had_ctrlc ())  
            return -1;  /* if stopped then not repeatable */  
    }  
  
    return rc ? rc : repeatable;  
  
#endif  
}  
  
  
  
int main(int argc, char **argv)  
{    
    int32_t rc = -1;  
    int32_t len;  
    static int8_t lastcommand[CONFIG_SYS_CBSIZE] = { 0, };    
  
    memset(CmdTbl, 0, sizeof(CMD_STRUCT_T)*MAX_CMD_NUM);  
      
    register_cmd("help", "list all cmd\n\r", HelpCmdExeFun);  
    register_cmd("read", "read memory\n\r", read_fun);  
    register_cmd("write", "write memory\n\r", write_fun);  
    register_cmd("setenv", "set env\n\r", setenv_fun);  
      
		debug_print();  
    while (1)  
    {
        len = readline (CONFIG_SYS_PROMPT);  
        if (len > 0)  
        {
            memset(lastcommand, '\0', CONFIG_SYS_CBSIZE);                
            strncpy (lastcommand, console_buffer, strlen(console_buffer));    
            rc = run_command (lastcommand, 0);  
            if (rc <= 0)  
            {  
                /* invalid command or not repeatable, forget it */  
                lastcommand[0] = 0;  
            }  
        }  
  
    }  
    return 0;  
}  