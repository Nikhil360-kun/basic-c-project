#include <stdio.h>
#include <string.h>

#define MAX_ACCOUNTS 100

typedef struct {
    char name[100];
    int accountNumber;
    char accountType[10];
    float balance;
} BankAccount;

BankAccount accounts[MAX_ACCOUNTS];
int accountCount = 0;

// Function prototypes
void createAccount();
void depositMoney();
void withdrawMoney();
void displayAccount();
int findAccount(int accountNumber);

int main() {
    int choice;

    do {
        printf("\n--- Bank Menu ---\n");
        printf("1. Create Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Display Account Details\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear input buffer

        switch (choice) {
            case 1: createAccount(); break;
            case 2: depositMoney(); break;
            case 3: withdrawMoney(); break;
            case 4: displayAccount(); break;
            case 5: printf("Thank you for using the banking system. Goodbye!\n"); break;
            default: printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 5);

    return 0;
}

void createAccount() {
    if (accountCount >= MAX_ACCOUNTS) {
        printf("Maximum account limit reached!\n");
        return;
    }

    BankAccount newAcc;
    printf("Enter full name: ");
    fgets(newAcc.name, sizeof(newAcc.name), stdin);
    newAcc.name[strcspn(newAcc.name, "\n")] = '\0'; // Remove newline

    newAcc.accountNumber = 1000 + accountCount;
    printf("Account number assigned: %d\n", newAcc.accountNumber);

    printf("Enter account type (Savings/Current): ");
    fgets(newAcc.accountType, sizeof(newAcc.accountType), stdin);
    newAcc.accountType[strcspn(newAcc.accountType, "\n")] = '\0';

    printf("Enter initial deposit amount: ");
    scanf("%f", &newAcc.balance);
    getchar();

    if (newAcc.balance < 0) {
        printf("Initial deposit cannot be negative.\n");
        return;
    }

    accounts[accountCount++] = newAcc;
    printf("Account created successfully!\n");
}

void depositMoney() {
    int accNum;
    float amount;
    printf("Enter account number: ");
    scanf("%d", &accNum);

    int index = findAccount(accNum);
    if (index == -1) {
        printf("Account not found.\n");
        return;
    }

    printf("Enter amount to deposit: ");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("Invalid deposit amount.\n");
        return;
    }

    accounts[index].balance += amount;
    printf("Deposit successful. New balance: %.2f\n", accounts[index].balance);
}

void withdrawMoney() {
    int accNum;
    float amount;
    printf("Enter account number: ");
    scanf("%d", &accNum);

    int index = findAccount(accNum);
    if (index == -1) {
        printf("Account not found.\n");
        return;
    }

    printf("Enter amount to withdraw: ");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("Invalid withdrawal amount.\n");
        return;
    }

    if (accounts[index].balance >= amount) {
        accounts[index].balance -= amount;
        printf("Withdrawal successful. Remaining balance: %.2f\n", accounts[index].balance);
    } else {
        printf("Insufficient funds.\n");
    }
}

void displayAccount() {
    int accNum;
    printf("Enter account number: ");
    scanf("%d", &accNum);

    int index = findAccount(accNum);
    if (index == -1) {
        printf("Account not found.\n");
        return;
    }

    printf("\n--- Account Details ---\n");
    printf("Name: %s\n", accounts[index].name);
    printf("Account Number: %d\n", accounts[index].accountNumber);
    printf("Account Type: %s\n", accounts[index].accountType);
    printf("Balance: %.2f\n", accounts[index].balance);
}

int findAccount(int accountNumber) {
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            return i;
        }
    }
    return -1;
}
