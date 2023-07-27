#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_SIZE 1024

void convertSqlToCsv(const char* sqlFileName, const char* csvFileName) {
    FILE* sqlFile = fopen(sqlFileName, "r");
    FILE* csvFile = fopen(csvFileName, "w");

    if (sqlFile == NULL || csvFile == NULL) {
        printf("Gagal membuka file.");
        return;
    }

    char buffer[MAX_BUFFER_SIZE];
    char* token;

    while (fgets(buffer, sizeof(buffer), sqlFile)) {
        buffer[strcspn(buffer, "\n")] = '\0';

        token = strtok(buffer, ",");
        while (token != NULL) {
            fprintf(csvFile, "%s,", token);
            token = strtok(NULL, ",");
        }

        fseek(csvFile, -1, SEEK_CUR);
        fprintf(csvFile, "\n");
    }

    fclose(sqlFile);
    fclose(csvFile);

    printf("Konversi selesai. File CSV telah dibuat.\n");
}

void convertCsvToSql(const char* csvFileName, const char* sqlFileName) {
    FILE* csvFile = fopen(csvFileName, "r");
    FILE* sqlFile = fopen(sqlFileName, "w");

    if (csvFile == NULL || sqlFile == NULL) {
        printf("Gagal membuka file.");
        return;
    }

    char buffer[MAX_BUFFER_SIZE];

    while (fgets(buffer, sizeof(buffer), csvFile)) {
        buffer[strcspn(buffer, "\n")] = '\0';

        fprintf(sqlFile, " %s;\n", buffer);
    }

    fclose(csvFile);
    fclose(sqlFile);

    printf("Konversi selesai. File SQL telah dibuat.\n");
}

int main() {
    convertSqlToCsv("gaminity.sql", "data.csv");
    convertCsvToSql("data.csv", "data.sql");

    return 0;
}

