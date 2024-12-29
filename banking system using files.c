#include <stdio.h> #include <stdlib.h> #include <string.h>

typedef struct {
int accountNumber; char name[50]; double balance;
} Account;


void addAccount(); void deleteAccount(); void updateAccount(); void viewAccount(); void displayMenu();

FILE *file;


int main() { int choice; while (1) {
displayMenu();
printf("Enter your choice: "); scanf("%d", &choice);

switch (choice) { case 1:
addAccount(); break;
case 2:
 
deleteAccount(); break;
case 3:
updateAccount(); break;
case 4:
viewAccount(); break;
case 5:
printf("Exiting the program. Goodbye!\n"); exit(0);
default:
printf("Invalid choice. Please try again.\n");
}
}
return 0;
}


void displayMenu() {
printf("\n====== Bank Management System ======\n"); printf("1. Add Account\n");
printf("2. Delete Account\n"); printf("3. Update Account\n"); printf("4. View Account\n"); printf("5. Exit\n");
printf("====================================\n");
}


void addAccount() { Account acc;
printf("Enter Account Number: ");
 
scanf("%d", &acc.accountNumber); printf("Enter Name: ");
getchar(); // Clear input buffer fgets(acc.name, sizeof(acc.name), stdin);
acc.name[strcspn(acc.name, "\n")] = 0; // Remove newline printf("Enter Balance: ");
scanf("%lf", &acc.balance);


file = fopen("accounts.txt", "ab"); if (file == NULL) {
printf("Error opening file.\n"); return;
}
fwrite(&acc, sizeof(Account), 1, file); fclose(file);

printf("Account added successfully!\n");
}


void deleteAccount() { int accNumber; Account acc;
FILE *tempFile; int found = 0;

printf("Enter Account Number to delete: "); scanf("%d", &accNumber);

file = fopen("accounts.txt", "rb"); tempFile = fopen("temp.txt", "wb");
if (file == NULL || tempFile == NULL) {
 
printf("Error opening file.\n"); return;
}


while (fread(&acc, sizeof(Account), 1, file)) { if (acc.accountNumber != accNumber) {
fwrite(&acc, sizeof(Account), 1, tempFile);
} else {
found = 1;
}
}


fclose(file); fclose(tempFile);

remove("accounts.txt"); rename("temp.txt", "accounts.txt");

if (found)
printf("Account deleted successfully!\n"); else
printf("Account not found.\n");
}


void updateAccount() { int accNumber; Account acc;
FILE *tempFile; int found = 0;

printf("Enter Account Number to update: ");
 
scanf("%d", &accNumber);


file = fopen("accounts.txt", "rb"); tempFile = fopen("temp.txt", "wb");
if (file == NULL || tempFile == NULL) { printf("Error opening file.\n");
return;
}


while (fread(&acc, sizeof(Account), 1, file)) { if (acc.accountNumber == accNumber) {
found = 1;
printf("Enter New Name: "); getchar();
fgets(acc.name, sizeof(acc.name), stdin); acc.name[strcspn(acc.name, "\n")] = 0; printf("Enter New Balance: "); scanf("%lf", &acc.balance);
}
fwrite(&acc, sizeof(Account), 1, tempFile);
}


fclose(file); fclose(tempFile);

remove("accounts.txt"); rename("temp.txt", "accounts.txt");

if (found)
printf("Account updated successfully!\n"); else
 
printf("Account not found.\n");
}


void viewAccount() { int accNumber; Account acc;
int found = 0;


printf("Enter Account Number to view: "); scanf("%d", &accNumber);

file = fopen("accounts.txt", "rb"); if (file == NULL) {
printf("Error opening file.\n"); return;
}


while (fread(&acc, sizeof(Account), 1, file)) { if (acc.accountNumber == accNumber) {
found = 1;
printf("\nAccount Number: %d\n", acc.accountNumber); printf("Name: %s\n", acc.name);
printf("Balance: %.2lf\n", acc.balance);
}
}


fclose(file);


if (!found)
printf("Account not found.\n");
}
