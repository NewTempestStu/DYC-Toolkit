# DYC-Toolkit
A toolkit for DYC

## Introduction
The Skill Categorization Program is designed to help users categorize a list of skills based on personal preferences. It allows for dynamically managing skills, categorizing them, and persisting these categorizations across sessions. This guide provides instructions on how to use the program, outlines its key features, and clarifies important usage considerations.

## Key Features

1. **Dynamic Skill Management**: Add and delete skills as needed.
2. **Skill Categorization**: Assign categories to skills based on how they energize, deplete, or have little effect on you.
3. **Persistence**: Your categorizations are saved automatically, allowing you to pick up where you left off in subsequent sessions.
4. **Data Import and Export**: Easily import skills from and export to a `.txt` file, enabling external modification and sharing.
5. **View Choices**: Review your categorizations at any time during the program execution.

## Getting Started

### Prerequisites

- A C compiler (GCC recommended) to compile the source code.
- A text editor to edit the skill data file or the source code, if necessary.

### Compilation

Navigate to the directory containing the source code and compile it using the following command:

```sh
make
```

This command generates an executable named `dyc`.

### Running the Program

Execute the program by running the following command in the same directory:

```sh
./dyc
```

## Usage Guide

Upon starting the program, you'll be greeted with the main menu offering several options. Navigate through these options by entering the number corresponding to your choice and pressing Enter.

### Menu Options

1. **Start Choosing**: Begin or continue the process of categorizing skills.
2. **View Choices**: Display your current skill categorizations.
3. **Display Sorted Skills**: List all skills sorted by their categories.
4. **Export Data**: Save your current skill list and categorizations to a `.txt` file.
5. **Import Data**: Load skills from a `.txt` file.
6. **Add Skill**: Add a new skill to the list.
7. **Delete Skill**: Remove an existing skill from the list.
8. **Exit Program**: Quit the program.

### Adding and Deleting Skills

- To **add a skill**, choose option 6 and follow the prompts to enter the skill name and description. The skill name and description are limited to 49 and 255 characters, respectively.
- To **delete a skill**, choose option 7, then enter the number of the skill you wish to remove, based on its order in the list shown under "Display Sorted Skills".

### Importing and Exporting Data

- **Data files** should be formatted with each skill and its description on separate lines, separated by a semicolon (`;`).
- Ensure the **skills_data.txt** file is in the same directory as the executable for importing.
- When **exporting**, the current skill list and categorizations will be saved to `skills_data.txt`, and the choices to `choices_data.txt`.

### Legal and Illegal Inputs

- **Skill Name and Description**: Limit to 49 and 255 characters, respectively, to prevent truncation.
- **Categorization Choices**: Enter only `1`, `2`, or `3` during the categorization process. Entering `4` saves progress and returns to the main menu.
- **Menu Navigation**: Only numbers corresponding to menu options are valid. Other inputs are considered illegal and will prompt re-entry.

### Cleaning Up

- **Remove Executable**: You can clean up the directory by running `make clean`. This command removes the compiled executable, keeping your directory tidy.