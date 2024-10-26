#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// 計算學號的檢查碼
int check_digit(const char *student_id) {
    int multipliers[] = {8, 7, 6, 8, 7, 6};
    int sum_digits = 0;

    for (int i = 1; i <= 6; i++) {
        int product = (student_id[i] - '0') * multipliers[i - 1];
        sum_digits += (product / 10) + (product % 10); // 將十位數和個位數相加
    }

    int check_digit = 10 - (sum_digits % 10);
    if (check_digit == 10) {
        check_digit = 0;
    }

    return check_digit;
}

// 取得當前年份
int get_current_year() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    return tm.tm_year + 1900;
}

// 發放折價券
void issue_discount(const char *student_id, int current_year) {
    int enrollment_year = (student_id[1] - '0') * 10 + (student_id[2] - '0'); // 學號第2和第3位
    int enrollment_year_full = enrollment_year + 100;

    // 計算年級
    int grade = (current_year - 1911) - enrollment_year_full + 1;

    // 判斷年級
    if (grade == 1) {
        printf("該學生是大一新鮮人，發放折價券\n");
    } else if (grade >= 2 && grade <= 4) {
        printf("該學生是一般學生，無法享受折價券\n");
    } else if (grade > 4) {
        printf("該學生是延畢生，發放折價券\n");
    } else {
        printf("該學生未入學，無法發放折價券\n");
    }
}

// 驗證學號是否有效
void validate_student_id(const char *student_id) {
    if (strlen(student_id) != 8) {
        printf("學號長度不正確\n");
        return;
    }
    if (toupper(student_id[0]) != 'D') { // 轉成大寫檢查
        printf("學號必須以 'D' 開頭\n");
        return;
    }
    for (int i = 1; i < 8; i++) {
        if (!isdigit(student_id[i])) {
            printf("學號包含非數字字符\n");
            return;
        }
    }

    int expected_check_digit = check_digit(student_id);
    int actual_check_digit = student_id[7] - '0';

    if (expected_check_digit == actual_check_digit) {
        printf("學號有效\n");

        int current_year = get_current_year();
        issue_discount(student_id, current_year);
    } else {
        printf("學號無效\n");
    }
}

int main() {
    char student_id[9];

    printf("請輸入學號: ");
    scanf("%8s", student_id);

    validate_student_id(student_id);

    return 0;
}
