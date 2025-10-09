//#include "iostream"
//#include "stdio.h"
//#include "test.h"
//using namespace std;
//
//
//int my_strlen(const char* str) {
//	int length = 0;
//	while (*str++) {
//		length++;
//	}
//	return length;
//}
//
//char* my_strcpy(char* dest, const char* src) {
//	char* temp = dest;
//	while ((*temp++ = *src++));
//	return temp;
//}
//
//void transpose(int* matrix, int* result, int rows, int cols) {
//	for (int i = 0; i < rows; i++) {
//		for (int j = 0; j < cols; j++) {
//			result[j * rows + i] = matrix[i * cols + j];
//			*(result + j * rows + i) = *(matrix + i * cols + j);
//		}
//	}
//}
//
//
//static void (*g_callback)(int) = NULL;
//void callback(p fuc) {
//	g_callback = fuc;
//}
//void trigger(int value) {
//	if (g_callback) {
//		g_callback(value);
//	}
//	else {
//		cout << "没有注册回调函数\n";
//	}
//}
//void my_callback(int value) {
//	cout << "回调函数被调用，值为: " << value << "\n";
//}
//
//
//
//
//
//
//int main() {
//    const char* str = "Hello,world!";
//    int length = my_strlen(str);
//    cout << "字符串 \"" << str << "\" 的长度是: " << length << "\n" << endl;
//
//
//
//	char dest[100];
//	my_strcpy(dest, str);
//	cout << "复制后的字符串是: " << dest << "\n" << endl;
//
//
//
//	int mat[2][3] = { {1,2,3},{4,5,6} };
//	int result[3][2];
//	transpose(&mat[0][0], &result[0][0], 2, 3);
//	cout << "转置前的矩阵:\n";
//	for (int i = 0; i < 2; i++){
//		for (int j = 0; j < 3; j++)
//			cout << mat[i][j] << " ";
//		cout << "\n";
//	}
//	cout << "转置后的矩阵:\n";
//	for (int i = 0; i < 3; ++i) {
//		for (int j = 0; j < 2; ++j)
//			cout << result[i][j] << " ";
//		cout << "\n";
//	}cout << "\n";
//
//
//	callback(my_callback);
//	trigger(1);
//
//    return 0;
//}