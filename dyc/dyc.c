#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SKILL_COUNT 100
#define DATA_FILE_NAME "skills_data.txt"

char **skills;
char **descriptions;
int *categories;
int actualSkillCount = 0;

void initializeArrays();
void freeMemory();
void importData();
void exportData();
void addSkill();
void sortSkills();
void displaySortedSkills();
void flushInputBuffer();

int main(void) {
    initializeArrays();
    importData(); // Load data at program start

    int choice;
    do {
        printf("\nMain Menu\n");
        printf("1. Start Choosing\n");
        printf("2. Display Sorted Skills\n");
        printf("3. Export Data\n");
        printf("4. Import Data\n");
        printf("5. Add Skill\n");
        printf("6. Exit Program\n");
        printf("Select an option: ");
        scanf("%d", &choice);
        flushInputBuffer();

        switch (choice) {
            case 1: sortSkills(); break;
            case 2: displaySortedSkills(); break;
            case 3: exportData(); break;
            case 4: importData(); break;
            case 5: addSkill(); break;
            case 6: printf("Exiting program...\n"); break;
            default: printf("Invalid choice, please try again.\n");
        }
    } while (choice != 6);

    freeMemory();
    return 0;
}

void initializeArrays() {
    skills = malloc(MAX_SKILL_COUNT * sizeof(char*));
    descriptions = malloc(MAX_SKILL_COUNT * sizeof(char*));
    categories = malloc(MAX_SKILL_COUNT * sizeof(int));
    for (int i = 0; i < MAX_SKILL_COUNT; i++) {
        skills[i] = malloc(50 * sizeof(char));
        descriptions[i] = malloc(256 * sizeof(char));
    }
}

void freeMemory() {
    for (int i = 0; i < MAX_SKILL_COUNT; i++) {
        free(skills[i]);
        free(descriptions[i]);
    }
    free(skills);
    free(descriptions);
    free(categories);
}

void flushInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// Define other functions like importData, exportData, addSkill, sortSkills, displaySortedSkills


void importData() {
    FILE *file = fopen(DATA_FILE_NAME, "r");
    if (file == NULL) {
        printf("Failed to open file for reading.\n");
        return;
    }

    char line[512];
    int index = 0;
    while (fgets(line, sizeof(line), file) != NULL && index < actualSkillCount) {
        char *token = strtok(line, ";");
        if (token) {
            strncpy(skills[index], token, sizeof(skills[index]) - 1);
            token = strtok(NULL, "\n");
            if (token) {
                strncpy(descriptions[index], token, sizeof(descriptions[index]) - 1);
            }
            index++;
        }
    }
    actualSkillCount = index;
    fclose(file);
    printf("Data imported successfully.\n");
}

void exportData() {
    printf("Are you sure you want to overwrite the existing data? (y/n): ");
    char confirm = getchar();
    flushInputBuffer();
    if (confirm != 'y') {
        printf("Export canceled.\n");
        return;
    }

    FILE *file = fopen(DATA_FILE_NAME, "w");
    if (file == NULL) {
        printf("Failed to open file for writing.\n");
        return;
    }

    for (int i = 0; i < actualSkillCount; i++) {
        if (fprintf(file, "%s;%s\n", skills[i], descriptions[i]) < 0) {
            printf("Failed to write data to file.\n");
            fclose(file);
            return;
        }
    }

    fclose(file);
    printf("Data exported successfully.\n");
}

void addSkill() {
    if (actualSkillCount >= actualSkillCount) {
        printf("Maximum skill count reached, cannot add more skills.\n");
        return;
    }

    printf("Enter skill name: ");
    fgets(skills[actualSkillCount], sizeof(skills[actualSkillCount]), stdin);
    skills[actualSkillCount][strcspn(skills[actualSkillCount], "\n")] = 0; // Remove newline character

    printf("Enter skill description: ");
    fgets(descriptions[actualSkillCount], sizeof(descriptions[actualSkillCount]), stdin);
    descriptions[actualSkillCount][strcspn(descriptions[actualSkillCount], "\n")] = 0; // Remove newline character

    actualSkillCount++;

    printf("Skill added successfully.\n");
}

void sortSkills() {
    printf("Please read each skill and its description, then categorize it:\n");
    printf("1 - Energizes Me, 2 - Depletes Me, 3 - Has Little to No Effect\n\n");

    for(int i = 0; i < actualSkillCount; i++) { // Use actualSkillCount instead of SKILL_COUNT
        printf("%d. Skill: %s\n", i+1, skills[i]);
        printf("Description: %s\n", descriptions[i]);
        printf("Category (1-3): ");
        scanf("%d", &categories[i]);
        flushInputBuffer(); // Important to clean up input buffer after scanf
        while(categories[i] < 1 || categories[i] > 3) {
            printf("Invalid category. Please enter 1, 2, or 3: ");
            scanf("%d", &categories[i]);
            flushInputBuffer(); // Again, clean up input buffer
        }
        printf("\n");
    }
}

void displaySortedSkills() {
    printf("\nSkills Sorted by Category:\n");

    for(int cat = 1; cat <= 3; cat++) {
        switch(cat) {
            case 1:
                printf("\nEnergizes Me:\n");
                break;
            case 2:
                printf("\nDepletes Me:\n");
                break;
            case 3:
                printf("\nHas Little to No Effect:\n");
                break;
        }
        for(int i = 0; i < actualSkillCount; i++) { // Again, use actualSkillCount
            if(categories[i] == cat) {
                printf("- %s\n", skills[i]);
            }
        }
    }
}


void importData() {
    FILE *file = fopen(DATA_FILE_NAME, "r");
    if (file == NULL) {
        printf("Failed to open file for reading.\n");
        return;
    }

    char line[512]; // Assuming a line won't be longer than 512 characters
    int index = 0;
    while (fgets(line, sizeof(line), file) != NULL && index < actualSkillCount) {
        char *token = strtok(line, ";");
        if (token != NULL) {
            strncpy(skills[index], token, 49);
            skills[index][49] = '\0'; // Ensure null termination

            token = strtok(NULL, ";");
            if (token != NULL) {
                strncpy(descriptions[index], token, 255);
                descriptions[index][255] = '\0'; // Ensure null termination
            }

            index++;
        }
    }
    actualSkillCount = index; // Update the actual skill count based on the file
    fclose(file);
    printf("Data imported successfully.\n");
}

void exportData() {
    FILE *file = fopen(DATA_FILE_NAME, "w");
    if (file == NULL) {
        printf("Failed to open file for writing.\n");
        return;
    }

    for (int i = 0; i < actualSkillCount; i++) {
        fprintf(file, "%s;%s\n", skills[i], descriptions[i]);
    }

    fclose(file);
    printf("Data exported successfully.\n");
}



void addSkill() {
    if (actualSkillCount >= actualSkillCount) {
        printf("Maximum skill count reached, cannot add more skills.\n");
        return;
    }

    printf("Enter skill name: ");
    fgets(skills[actualSkillCount], sizeof(skills[actualSkillCount]), stdin);
    skills[actualSkillCount][strcspn(skills[actualSkillCount], "\n")] = 0; // Remove newline character

    printf("Enter skill description: ");
    fgets(descriptions[actualSkillCount], sizeof(descriptions[actualSkillCount]), stdin);
    descriptions[actualSkillCount][strcspn(descriptions[actualSkillCount], "\n")] = 0; // Remove newline character

    actualSkillCount++;

    printf("Skill added successfully.\n");
}