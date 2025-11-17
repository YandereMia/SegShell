#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <jansson.h>

int version_is_newer(const char *v1, const char *v2) {
    int maj1=0,min1=0,pat1=0,maj2=0,min2=0,pat2=0;
    sscanf(v1, "%d.%d.%d", &maj1, &min1, &pat1);
    sscanf(v2, "%d.%d.%d", &maj2, &min2, &pat2);

    if (maj2 > maj1) return 1;
    if (maj2 < maj1) return 0;
    if (min2 > min1) return 1;
    if (min2 < min1) return 0;
    if (pat2 > pat1) return 1;
    return 0;
}

void apx_install(const char *package_name) {
    if (!package_name || strlen(package_name) == 0) {
        printf("Usage: apx install <package-name>\n");
        return;
    }

    const char *repo_url = "https://github.com/yanderemia/Packages.git";
    char install_dir[1024];
    snprintf(install_dir, sizeof(install_dir), "%s/.myshellos/packages", getenv("HOME"));

    printf("[*] Creating packages directory if it doesn't exist...\n");
    char cmd[4096];
    snprintf(cmd, sizeof(cmd), "mkdir -p %s", install_dir);
    if (system(cmd) != 0) { perror("mkdir failed"); return; }

    // Temporary directory
    char tmp_dir[1024];
    FILE *fp = popen("mktemp -d", "r");
    if (!fp) { perror("popen"); return; }
    if (!fgets(tmp_dir, sizeof(tmp_dir), fp)) { perror("reading temp dir"); pclose(fp); return; }
    tmp_dir[strcspn(tmp_dir, "\n")] = '\0';
    pclose(fp);

    printf("[*] Downloading package '%s' into temp folder '%s'...\n", package_name, tmp_dir);

    // Clone package
    snprintf(cmd, sizeof(cmd), "git clone --depth 1 --filter=blob:none --sparse %s %s/%s 2>/dev/null", repo_url, tmp_dir, package_name);
    if (system(cmd) != 0) { printf("[!] Failed to clone package '%s'\n", package_name); return; }

    // Sparse checkout
    snprintf(cmd, sizeof(cmd), "cd %s/%s && git sparse-checkout set %s 2>/dev/null", tmp_dir, package_name, package_name);
    if (system(cmd) != 0) { printf("[!] Sparse-checkout failed for '%s'\n", package_name); return; }

    // Optional git config
    snprintf(cmd, sizeof(cmd), "cd %s/%s && git config set advice.defaultBranchName false 2>/dev/null", tmp_dir, package_name);
    system(cmd);

    // Run install.sh if it exists
    char install_sh[1024];
    snprintf(install_sh, sizeof(install_sh), "%s/%s/install.sh", tmp_dir, package_name);
    if (access(install_sh, F_OK) == 0) {
        printf("[*] Running install.sh for '%s'...\n", package_name);
        snprintf(cmd, sizeof(cmd), "cd %s/%s && chmod +x install.sh && ./install.sh 2>/dev/null", tmp_dir, package_name);
        if (system(cmd) != 0) { printf("[!] install.sh failed for '%s'\n", package_name); return; }
    } else {
        printf("[*] No install.sh found for '%s', skipping script step...\n", package_name);
    }

    // Move package to local directory (rsync místo cp)
    snprintf(cmd, sizeof(cmd), "rsync -a --exclude='.git' %s/%s/ %s/%s/ && rm -rf %s/%s", tmp_dir, package_name, install_dir, package_name, tmp_dir, package_name);
    if (system(cmd) != 0) { printf("[!] Failed to move package '%s'\n", package_name); return; }

    // Clean up temp folder (už většinou prázdné, ale pro jistotu)
    snprintf(cmd, sizeof(cmd), "rm -rf %s", tmp_dir);
    system(cmd);

    printf("[+] Package '%s' installed successfully!\n", package_name);
}

// -------------------- apx_list --------------------
void apx_list() {
    char path[1024];
    snprintf(path, sizeof(path), "%s/.myshellos/packages", getenv("HOME"));

    DIR *dir = opendir(path);
    if (!dir) { perror("opendir"); return; }

    printf("Installed packages:\n-------------------\n");
    struct dirent *entry;
    int count = 0;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0 || strncmp(entry->d_name, "tmp.", 4) == 0 || strcmp(entry->d_name, "metadata.json") == 0)
            continue;
        printf("• %s\n", entry->d_name);
        count++;
    }

    if (count == 0) printf("(no packages installed)\n");
    closedir(dir);
}

// -------------------- apx_update --------------------
void apx_update(const char *package_name) {
    if (!package_name || strlen(package_name) == 0) {
        printf("Usage: apx update <package-name>\n");
        return;
    }

    char install_dir[1024];
    snprintf(install_dir, sizeof(install_dir), "%s/.myshellos/packages", getenv("HOME"));
    char pkg_dir[2048];
    snprintf(pkg_dir, sizeof(pkg_dir), "%s/%s", install_dir, package_name);

    if (access(pkg_dir, F_OK) != 0) {
        printf("[!] Package '%s' is not installed. Use 'apx install %s' first.\n", package_name, package_name);
        return;
    }

    printf("[*] Updating package '%s'...\n", package_name);

    // Temporary directory
    char tmp_dir[1024];
    FILE *fp = popen("mktemp -d", "r");
    if (!fp) { perror("popen"); return; }
    if (!fgets(tmp_dir, sizeof(tmp_dir), fp)) { perror("reading temp dir"); pclose(fp); return; }
    tmp_dir[strcspn(tmp_dir, "\n")] = '\0';
    pclose(fp);

    const char *repo_url = "https://github.com/yanderemia/Packages.git";

    char cmd[4096];
    snprintf(cmd, sizeof(cmd), "git clone --depth 1 --filter=blob:none --sparse %s %s/%s 2>/dev/null", repo_url, tmp_dir, package_name);
    if (system(cmd) != 0) { printf("[!] Failed to clone package '%s'\n", package_name); return; }

    snprintf(cmd, sizeof(cmd), "cd %s/%s && git sparse-checkout set %s 2>/dev/null", tmp_dir, package_name, package_name);
    if (system(cmd) != 0) { printf("[!] Sparse-checkout failed for '%s'\n", package_name); return; }

    // Optional install.sh
    char install_sh[1024];
    snprintf(install_sh, sizeof(install_sh), "%s/%s/install.sh", tmp_dir, package_name);
    if (access(install_sh, F_OK) == 0) {
        printf("[*] Running install.sh for '%s'...\n", package_name);
        snprintf(cmd, sizeof(cmd), "cd %s/%s && chmod +x install.sh && ./install.sh 2>/dev/null", tmp_dir, package_name);
        if (system(cmd) != 0) { printf("[!] install.sh failed for '%s'\n", package_name); return; }
    } else {
        printf("[*] No install.sh found for '%s', skipping script step...\n", package_name);
    }

    // Move updated package to install_dir (rsync místo cp)
    snprintf(cmd, sizeof(cmd), "rsync -a --exclude='.git' %s/%s/ %s/ && rm -rf %s/%s", tmp_dir, package_name, pkg_dir, tmp_dir, package_name);
    if (system(cmd) != 0) { printf("[!] Failed to update package '%s'\n", package_name); return; }

    snprintf(cmd, sizeof(cmd), "rm -rf %s", tmp_dir);
    system(cmd);

    printf("[+] Package '%s' updated successfully!\n", package_name);
}

// -------------------- apx_update_system --------------------
void apx_update_system() {
    printf("[*] Updating system packages (pacman)...\n");
    if (system("sudo pacman -Syu --noconfirm > /dev/null 2>&1") != 0) {
        printf("[!] Failed to update system packages.\n");
        return;
    }
    printf("[+] All system packages were updated successfully!\n");
}

// -------------------- apx_update_all_packages --------------------
void apx_update_all_packages() {
    const char *home = getenv("HOME");
    if (!home) { printf("[!] Cannot determine HOME directory.\n"); return; }

    char packages_path[1024];
    snprintf(packages_path, sizeof(packages_path), "%s/.myshellos/packages", home);

    char metadata_path[1024];
    snprintf(metadata_path, sizeof(metadata_path), "%s/metadata.json", packages_path);

    // Load metadata
    json_error_t err;
    json_t *root = json_load_file(metadata_path, 0, &err);
    if (!root) { printf("[!] Failed to load metadata.json: %s\n", err.text); return; }

    json_t *packages = json_object_get(root, "packages");
    if (!json_is_array(packages)) { printf("[!] Invalid metadata format.\n"); json_decref(root); return; }

    DIR *dir = opendir(packages_path);
    if (!dir) { perror("opendir"); json_decref(root); return; }

    struct dirent *entry;
    int updated_count = 0, checked_count = 0;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        size_t index;
        json_t *pkg;
        json_array_foreach(packages, index, pkg) {
            const char *name = json_string_value(json_object_get(pkg, "name"));
            const char *remote_version = json_string_value(json_object_get(pkg, "version"));
            if (strcmp(name, entry->d_name) == 0) {
                char local_meta[1024];
                snprintf(local_meta, sizeof(local_meta), "%s/%s/metadata.json", packages_path, entry->d_name);
                json_t *local_root = json_load_file(local_meta, 0, &err);
                const char *local_version = "0.0.0";
                if (local_root) {
                    json_t *lv = json_object_get(local_root, "version");
                    if (lv && json_is_string(lv)) local_version = json_string_value(lv);
                    json_decref(local_root);
                }
                checked_count++;
                if (version_is_newer(local_version, remote_version)) {
                    printf("[*] Updating package: %s (local: %s, remote: %s)\n", entry->d_name, local_version, remote_version);
                    apx_update(entry->d_name);
                    updated_count++;
                }
                break;
            }
        }
    }

    closedir(dir);
    json_decref(root);

    if (checked_count == 0) printf("[!] No installed SegLinux packages found.\n");
    else if (updated_count == 0) printf("[+] All packages are up to date.\n");
    else printf("[+] %d package(s) updated successfully.\n", updated_count);
}

// -------------------- apx_sync_metadata --------------------
void apx_sync_metadata() {
    const char *home = getenv("HOME");
    if (!home) { printf("[!] Cannot determine HOME directory.\n"); return; }

    char packages_dir[1024];
    snprintf(packages_dir, sizeof(packages_dir), "%s/.myshellos/packages", home);

    DIR *dir = opendir(packages_dir);
    if (!dir) { printf("[!] No installed packages found to sync.\n"); return; }

    char global_meta_path[1024];
    snprintf(global_meta_path, sizeof(global_meta_path), "%s/metadata.json", packages_dir);

    json_error_t error;
    json_t *global_meta = json_load_file(global_meta_path, 0, &error);
    if (!global_meta) global_meta = json_object();
    if (!json_object_get(global_meta, "packages")) json_object_set_new(global_meta, "packages", json_array());

    json_t *global_packages = json_object_get(global_meta, "packages");

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char local_meta_path[1024];
        snprintf(local_meta_path, sizeof(local_meta_path), "%s/%s/metadata.json", packages_dir, entry->d_name);

        json_t *local_meta = json_load_file(local_meta_path, 0, &error);
        if (!local_meta) continue;

        json_t *local_packages = json_object_get(local_meta, "packages");
        if (!local_packages) { json_decref(local_meta); continue; }

        size_t index;
        json_t *pkg;
        json_array_foreach(local_packages, index, pkg) {
            const char *name = json_string_value(json_object_get(pkg, "name"));
            const char *version = json_string_value(json_object_get(pkg, "version"));
            const char *description = json_string_value(json_object_get(pkg, "description"));
            const char *author = json_string_value(json_object_get(pkg, "author"));

            size_t g_index;
            json_t *g_pkg;
            int found = 0;
            json_array_foreach(global_packages, g_index, g_pkg) {
                const char *g_name = json_string_value(json_object_get(g_pkg, "name"));
                if (strcmp(name, g_name) == 0) {
                    json_object_set_new(g_pkg, "version", json_string(version));
                    json_object_set_new(g_pkg, "description", json_string(description));
                    json_object_set_new(g_pkg, "author", json_string(author));
                    found = 1;
                    break;
                }
            }

            if (!found) {
                json_t *new_pkg = json_object();
                json_object_set_new(new_pkg, "name", json_string(name));
                json_object_set_new(new_pkg, "version", json_string(version));
                json_object_set_new(new_pkg, "description", json_string(description));
                json_object_set_new(new_pkg, "author", json_string(author));
                json_array_append_new(global_packages, new_pkg);
            }
        }

        json_decref(local_meta);
    }

    closedir(dir);

    if (json_dump_file(global_meta, global_meta_path, JSON_INDENT(4)) != 0)
        printf("[!] Failed to write global metadata.json\n");
    else
        printf("[+] Global metadata.json synced successfully.\n");

    json_decref(global_meta);
}
