#include <cstdio>
#include <cstring>

void SavePlayerName(const char* name) {
    FILE* file = fopen("player_name.txt", "w");
    if (file) {
        fprintf(file, "%s", name);
        fclose(file);
    }
}

void LoadPlayerName(char* nameBuffer, int bufferSize) {
    FILE* file = fopen("player_name.txt", "r");
    if (file) {
        fgets(nameBuffer, bufferSize, file);
        fclose(file);

        // Remove newline if present
        int len = strlen(nameBuffer);
        if (len > 0 && nameBuffer[len - 1] == '\n') {
            nameBuffer[len - 1] = '\0';
        }
    }
}
