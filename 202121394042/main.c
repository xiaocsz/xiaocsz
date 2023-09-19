#include <stdio.h>
#include <stdlib.h>
#include <string.h>
double calculateSimilarity(const char *str1, const char *str2); 
int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <original_file> <plagiarized_file> <output_file>\n", argv[0]);
        return 1;
    }

    const char *original_file_path = argv[1];
    const char *plagiarized_file_path = argv[2];
    const char *output_file_path = argv[3];

    // 打开原文文件
    FILE *original_file = fopen(original_file_path, "r");
    if (!original_file) {
        perror("Error opening original file");
        return 1;
    }

    // 打开抄袭版文件
    FILE *plagiarized_file = fopen(plagiarized_file_path, "r");
    if (!plagiarized_file) {
        perror("Error opening plagiarized file");
        fclose(original_file);
        return 1;
    }

    // 读取原文和抄袭版内容
    char original_text[4096];
    char plagiarized_text[4096];

    if (fgets(original_text, sizeof(original_text), original_file) == NULL) {
        perror("Error reading original file");
        fclose(original_file);
        fclose(plagiarized_file);
        return 1;
    }

    if (fgets(plagiarized_text, sizeof(plagiarized_text), plagiarized_file) == NULL) {
        perror("Error reading plagiarized file");
        fclose(original_file);
        fclose(plagiarized_file);
        return 1;
    }

    // 计算相似度
    double similarity = calculateSimilarity(original_text, plagiarized_text);

    // 打开输出文件并写入相似度
    FILE *output_file = fopen(output_file_path, "w");
    if (!output_file) {
        perror("Error opening output file");
        fclose(original_file);
        fclose(plagiarized_file);
        return 1;
    }

    fprintf(output_file, "重复率：%.2f%%\n", similarity * 100);

    // 关闭所有文件
    fclose(original_file);
    fclose(plagiarized_file);
    fclose(output_file);

    printf("重复率计算完成，结果已保存到 %s\n", output_file_path);

    return 0;
}
