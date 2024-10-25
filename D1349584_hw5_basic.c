#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int calculate_check_digit(const char *student_id) {
    int weights[] = {1, 2, 1, 2, 1, 2, 1, 2};
    int total = 0;

    for (int i = 1; i < 7; i++) { // 從第2位開始計算
        int digit = student_id[i] - '0'; // 將字符轉為整數
        int product = digit * weights[i - 1];
        total += (product / 10) + (product % 10);
    }

    return (10 - (total % 10)) % 10;
}

int is_valid_student_id(const char *student_id) {
    if (strlen(student_id) != 8 || student_id[0] != 'D') {
        printf("學號格式不正確！必須是8位以'D'開頭的字母。\n");
        return 0; // 無效
    }

    int check_digit = calculate_check_digit(student_id);
    if (check_digit != (student_id[7] - '0')) {
        printf("學號檢查碼不正確！\n");
        return 0; // 無效
    }

    return 1; // 有效
}

const char* check_student_type(const char *student_id) {
    int admission_year = atoi(student_id + 1); // 提取入學年份
    if (admission_year >= 11) {
        return "大一新鮮人";
    } else {
        return "延畢生";
    }
}

int main() {
    char student_id[9]; // 學號必須是8位，加上結尾的'\0'

    printf("請輸入學號（8位數字，以'D'開頭）：");
    scanf("%s", student_id);

    if (is_valid_student_id(student_id)) {
        const char *student_type = check_student_type(student_id);
        printf("學號有效！你是%s，可以獲得折價券！\n", student_type);
    }

    return 0;
}
