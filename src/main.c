#include <dirent.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/dirent.h>
#include <unistd.h>

#include "main.h"

void changeTheme(char *newTheme);
void get_home(char *buffer, int size);
void expand_tilde(char *path, char *buf, int buflen);

char themes[256][64];
int theme_idx = 0;
int idx = 0;

int main(void) /* <<< */
{

    char alacrittyDir[64] = {0};
    expand_tilde(ALACRITTY_DIR, alacrittyDir, sizeof(alacrittyDir));

    DIR *dir = opendir(alacrittyDir);
    struct dirent *entry;

    if (dir == NULL)
    {
        perror("Directory Opening");
        return 0;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if (strstr(entry->d_name, "toml") != NULL &&
            strstr(entry->d_name, "alacritty") == NULL)
        {
            strncpy(themes[theme_idx], entry->d_name,
                    sizeof(themes[theme_idx]));
            theme_idx++;
        }
    }

    closedir(dir);

    /* Interface */
    initscr();
    noecho();
    curs_set(0);

    char ch;

    int maxY = getmaxy(stdscr);
    int left = 0, right = maxY - 1;

    while (1)
    {

        /* Draw */
        for (int i = left; i <= right; i++)
        {
            if (i == idx)
            {
                attron(A_STANDOUT);
            }
            else
            {
                attroff(A_STANDOUT);
            }
            printw("  %s  \n", themes[i]);
        }

        /* Handle Input */
        ch = getch();
        if (ch == 'q')
        {
            break;
        }

        if (ch == 'j')
        {
            if (idx == theme_idx - 1)
            {
                left = 0;
                right = maxY - 1;
                idx = left;
            }
            else
            {

                idx++;
                if (idx == right)
                {
                    left++;
                    right++;
                }
            }
        }
        else if (ch == 'k')
        {
            if (idx == 0)
            {
                right = theme_idx - 1;
                left = right - maxY + 1;
                idx = right;
            }
            else
            {
                idx--;
                if (idx == left)
                {
                    left--;
                    right--;
                }
            }
        }
        else if (ch == '\n')
        {
            changeTheme(themes[idx]);
        }

        /* Refresh */
        clear();
    }

    endwin();

    return 0;
} /* >>> */

void changeTheme(char *newTheme) /* <<< */
{

    char alacrittyConf[64] = {0};
    expand_tilde(ALACRITTY_CONF, alacrittyConf, sizeof(alacrittyConf));

    FILE *fp = fopen(alacrittyConf, "r");
    FILE *temp_fp = fopen("theme-temp", "w");
    if (fp == NULL)
    {
        perror("Alacritty.toml");
        exit(1);
    }
    if (temp_fp == NULL)
    {
        perror("Temp file");
        exit(1);
    }

    char line[256];
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        if (strstr(line, "import") != NULL)
        {
            char newString[256];
            snprintf(newString, sizeof(newString), "import = [\"%s\"]\n",
                     newTheme);
            fputs(newString, temp_fp);
        }
        else
        {
            fputs(line, temp_fp);
        }
    }

    fclose(temp_fp);
    fclose(fp);

    rename("theme-temp", alacrittyConf);
} /* >>> */

void get_home(char *buffer, int size) /* <<< */
{
    FILE *homeCmd = popen("echo $HOME", "r");
    fread(buffer, size, 1, homeCmd);
    buffer[size - 1] = '\0';

    char *ret = strchr(buffer, '\n');
    if (ret != NULL)
    {
        *ret = '\0';
    }
} /* >>> */

void expand_tilde(char *path, char *buf, int buflen) /* <<< */
{
    char *ptr = NULL;

    if ((ptr = strchr(path, '~')) != NULL)
    {
        char homeDir[64] = {0};
        get_home(homeDir, sizeof(homeDir));

        snprintf(buf, buflen, "%s%s", homeDir, ptr + 1);
    }
    else
    {
        snprintf(buf, buflen, "%s", path);
    }
} /* >>> */
