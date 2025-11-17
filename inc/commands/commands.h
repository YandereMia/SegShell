#ifndef COMMANDS_H
#define COMMANDS_H

void help_main(void);
void exit_main();
void clear_main(void);
void echo_main(const char *echo);
void touch_main(const char *file);
void ls_main();
void whoami_main();
void cat_main(const char *filename);
void write_main(const char *PathTofile, const char *text);
void rm_main(const char *file);
void sudo_su();
void su_main(const char *login);
void cd_main(const char *path);
void pwd_main();
//Package manager called APX
void apx_install(const char *package_name);
void apx_list();
void apx_update(const char *package_name);
void apx_update_system();
void apx_update_all_packages();
void apx_sync_metadata();
#endif