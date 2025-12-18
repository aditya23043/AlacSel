#include <dirent.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/dirent.h>
#include <unistd.h>

#define ALACRITTY_DIR "~/.config/alacritty"
#define ALACRITTY_CONF "/Users/adi/.config/alacritty/alacritty.toml"

char themes[256][32];
int theme_idx = 0;
int idx = 0;

void changeTheme(char *newTheme);
void get_home(char *buffer, int size);

int main(void)
{

    char alacrittyDir[64] = {0};
    char *ptr;

    // expand tilde to home dir
    if ((ptr = strchr(ALACRITTY_DIR, '~')) != NULL)
    {
        char homeDir[64] = {0};
        get_home(homeDir, sizeof(homeDir));

        snprintf(alacrittyDir, sizeof(alacrittyDir), "%s%s", homeDir, ptr + 1);
    }
    else
    {
        snprintf(alacrittyDir, sizeof(alacrittyDir), "%s", ALACRITTY_DIR);
    }

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

    char ch;

    while (1)
    {

        for (int i = 0; i < theme_idx; i++)
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

        ch = getch();
        if (ch == 'q')
        {
            break;
        }

        if (ch == 'j')
        {
            idx++;
        }
        else if (ch == 'k')
        {
            idx--;
        }
        else if (ch == '\n')
        {
            changeTheme(themes[idx]);
        }

        clear();
    }

    endwin();

    return 0;
}

void changeTheme(char *newTheme)
{

    printf("%s\n", newTheme);
    FILE *fp = fopen(ALACRITTY_CONF, "r");
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

    rename("theme-temp", ALACRITTY_CONF);
}

void get_home(char *buffer, int size)
{
    FILE *homeCmd = popen("echo $HOME", "r");
    fread(buffer, size, 1, homeCmd);
    buffer[size - 1] = '\0';

    char *ret = strchr(buffer, '\n');
    if (ret != NULL)
    {
        *ret = '\0';
    }
}
