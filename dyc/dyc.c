#include <stdio.h>
#include <string.h>

#define SKILL_COUNT 5 // Reduced for brevity

// Function Declarations
void sortSkills(char skills[SKILL_COUNT][50], char descriptions[SKILL_COUNT][150], int categories[SKILL_COUNT]);
void displaySortedSkills(char skills[SKILL_COUNT][50], int categories[SKILL_COUNT]);

int main() {
    char skills[SKILL_COUNT][50] = {
        "Active Listening",
        "Complex Problem Solving",
        "Coordination",
        "Critical Thinking",
        "Databases"
    };
    
    char descriptions[SKILL_COUNT][150] = {
        "Giving full attention to what other people are saying, taking time to understand the points being made.",
        "Identifying complex problems and reviewing related information to develop and evaluate options and implement solutions.",
        "Adjusting actions in relation to others' actions.",
        "Using logic and reasoning to identify the strengths and weaknesses of alternatives.",
        "Using a computer application to manage large amounts of information, including using databases."
    };
    
    int categories[SKILL_COUNT] = {0}; // 1-Energizes Me, 2-Depletes Me, 3-Has Little to No Effect

    sortSkills(skills, descriptions, categories);
    displaySortedSkills(skills, categories);

    return 0;
}

void sortSkills(char skills[SKILL_COUNT][50], char descriptions[SKILL_COUNT][150], int categories[SKILL_COUNT]) {
    printf("Please read each skill and its description, then categorize it:\n");
    printf("1 - Energizes Me, 2 - Depletes Me, 3 - Has Little to No Effect\n\n");

    for(int i = 0; i < SKILL_COUNT; i++) {
        printf("Skill: %s\n", skills[i]);
        printf("Description: %s\n", descriptions[i]);
        printf("Category (1-3): ");
        scanf("%d", &categories[i]);
        while(categories[i] < 1 || categories[i] > 3) {
            printf("Invalid category. Please enter 1, 2, or 3: ");
            scanf("%d", &categories[i]);
        }
        printf("\n");
    }
}

void displaySortedSkills(char skills[SKILL_COUNT][50], int categories[SKILL_COUNT]) {
    printf("\nSkills Sorted by Category:\n");

    for(int cat = 1; cat <= 3; cat++) {
        printf("\nCategory %d:\n", cat);
        for(int i = 0; i < SKILL_COUNT; i++) {
            if(categories[i] == cat) {
                printf("- %s\n", skills[i]);
            }
        }
    }
}
