#include <stdio.h>

typedef struct {
    int dd, mm, yy;
} dob;

typedef struct {
    int rollno;
    char name[50];
    float CGPA;
    dob age;
} student_info;

void printStudentInfo(student_info s) {
    printf("Roll No: %d\n", s.rollno);
    printf("Name: %s\n", s.name);
    printf("CGPA: %.2f\n", s.CGPA);
    printf("DOB: %d/%d/%d\n", s.age.dd, s.age.mm, s.age.yy);
}

student_info inputStudentInfo() {
    student_info s;
    printf("Enter Roll No: ");
    scanf("%d", &s.rollno);
    printf("Enter Name: ");
    scanf(" %[^\n]", s.name); 
    printf("Enter CGPA: ");
    scanf("%f", &s.CGPA);
    printf("Enter DOB (dd/mm/yyyy): ");
    scanf("%d/%d/%d", &s.age.dd, &s.age.mm, &s.age.yy);
    return s;
}

void ByValue(student_info s) {
    printf("\nUsing Call By Value\n");
    printStudentInfo(s);
}

void ByReference(student_info *s) {
    printf("\nUsing Call By Reference\n");
    printStudentInfo(*s);
}

int main() {
    student_info s = inputStudentInfo();
    ByValue(s);
    ByReference(&s);
    return 0;
}
