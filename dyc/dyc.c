#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SKILL_COUNT 100
#define DATA_FILE_NAME "skills_data.txt"
#define CHOICES_FILE_NAME "choices_data.txt"

char **skills;
char **descriptions;
int *categories;
int actualSkillCount = 0;

void initializeArrays();
void freeMemory();
void flushInputBuffer();
void importData();
void exportData();
void addSkill();
void sortSkills();
void displaySortedSkills();
void saveChoices();
void loadChoices();
void viewChoices();
void deleteSkill(int skillIndex);



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


void importData() {
    loadChoices();
    FILE *file = fopen(DATA_FILE_NAME, "r");
    if (file == NULL) {
        printf("Failed to open file for reading.\n");
        return;
    }

    char line[512];
    int index = 0;
    while (fgets(line, sizeof(line), file) != NULL && index < MAX_SKILL_COUNT) {
        char *token = strtok(line, ";");
        if (token) {
            strncpy(skills[index], token, 49);
            token = strtok(NULL, "\n");
            if (token) {
                strncpy(descriptions[index], token, 255);
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
    saveChoices();
    printf("Data exported successfully.\n");
}

void addSkill() {
    if (actualSkillCount >= MAX_SKILL_COUNT) {
        printf("Maximum skill count reached, cannot add more skills.\n");
        return;
    }

    printf("Enter skill name: ");
    fgets(skills[actualSkillCount], sizeof(skills[actualSkillCount]), stdin);
    skills[actualSkillCount][strcspn(skills[actualSkillCount], "\n")] = 0;

    printf("Enter skill description: ");
    fgets(descriptions[actualSkillCount], sizeof(descriptions[actualSkillCount]), stdin);
    descriptions[actualSkillCount][strcspn(descriptions[actualSkillCount], "\n")] = 0;

    actualSkillCount++;

    printf("Skill added successfully.\n");
}

void sortSkills() {
    printf("Please read each skill and its description, then categorize it:\n");
    printf("1 - Energizes Me, 2 - Depletes Me, 3 - Has Little to No Effect\n\n");

    for(int i = 0; i < actualSkillCount; i++) {
        printf("%d. Skill: %s\n", i+1, skills[i]);
        printf("Description: %s\n", descriptions[i]);
        printf("Category (1-3): ");
        scanf("%d", &categories[i]);
        flushInputBuffer();
        while(categories[i] < 1 || categories[i] > 3) {
            printf("Invalid category. Please enter 1, 2, or 3: ");
            scanf("%d", &categories[i]);
            flushInputBuffer();
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
        for(int i = 0; i < actualSkillCount; i++) {
            if(categories[i] == cat) {
                printf("- %s\n", skills[i]);
            }
        }
    }
}

void saveChoices() {
    FILE *file = fopen(CHOICES_FILE_NAME, "w");
    if (!file) {
        printf("Failed to open file for writing choices.\n");
        return;
    }
    for (int i = 0; i < actualSkillCount; i++) {
        fprintf(file, "%d\n", categories[i]);
    }
    fclose(file);
}

void loadChoices() {
    FILE *file = fopen(CHOICES_FILE_NAME, "r");
    if (!file) {
        // It's okay if file doesn't exist; it means no choices were saved previously.
        return;
    }
    int choice;
    int i = 0;
    while (fscanf(file, "%d", &choice) == 1 && i < actualSkillCount) {
        categories[i++] = choice;
    }
    fclose(file);
}

void viewChoices() {
    printf("\nYour Choices:\n");
    for (int i = 0; i < actualSkillCount; i++) {
        printf("%d. %s - ", i + 1, skills[i]);
        switch (categories[i]) {
            case 1: printf("Energizes Me\n"); break;
            case 2: printf("Depletes Me\n"); break;
            case 3: printf("Has Little to No Effect\n"); break;
            default: printf("Not chosen yet\n");
        }
    }
}

void deleteSkill(int skillIndex) {
    if (skillIndex < 0 || skillIndex >= actualSkillCount) {
        printf("Invalid skill index.\n");
        return;
    }
    
    free(skills[skillIndex]);
    free(descriptions[skillIndex]);
    
    for (int i = skillIndex; i < actualSkillCount - 1; i++) {
        skills[i] = skills[i + 1];
        descriptions[i] = descriptions[i + 1];
        categories[i] = categories[i + 1];
    }
    
    // Allocate new memory for the last skill (now empty) if not the last element
    if (skillIndex != actualSkillCount - 1) {
        skills[actualSkillCount - 1] = malloc(50 * sizeof(char));
        descriptions[actualSkillCount - 1] = malloc(256 * sizeof(char));
    }

    actualSkillCount--;
    printf("Skill deleted successfully.\n");
}


int main(void) {
    initializeArrays();
    importData();

    int choice;
    do {
        printf("\nMain Menu\n");
        printf("1. Start Choosing\n");
        printf("2. View Choices\n");
        printf("3. Display Sorted Skills\n");
        printf("4. Export Data\n");
        printf("5. Import Data\n");
        printf("6. Add Skill\n");
        printf("7. Delete Skill\n");
        printf("8. Exit Program\n");
        printf("Select an option: ");
        scanf("%d", &choice);
        flushInputBuffer();

        switch (choice) {
            case 1: sortSkills(); break;
            case 2: viewChoices(); break;
            case 3: displaySortedSkills(); break;
            case 4: exportData(); break;
            case 5: importData(); break;
            case 6: addSkill(); break;
            case 7: 

                printf("Enter the number of the skill to delete: ");
                int indexToDelete;
                scanf("%d", &indexToDelete);
                flushInputBuffer();
                deleteSkill(indexToDelete - 1);
                break;
            case 8:
                printf("Exiting program...\n");
                break;
            default: printf("Invalid choice, please try again.\n");
        }
    } while (choice != 8);

    freeMemory();
    return 0;
}