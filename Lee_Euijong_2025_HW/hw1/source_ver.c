#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<stdlib.h>
#include <time.h>
//malloc ��ũ�� ����
#define MALLOC(p,s) \
   if(!((p)=malloc(s))){\
      fprintf(stderr,"Improper value of n \n");\
      exit(EXIT_FAILURE);\
   }
//MAX ��ũ�� ����
#define MAX(a,b) ((a) > (b) ? (a) : (b))
typedef struct {//����, ��� �����Ͽ� �����ϱ� ���� ����ü ����
    int coef;
    int exp;
}Term;
typedef struct polyNode {
    int coef;
    int exp;
    struct polyNode* link;
}polyNode;

//�迭_�ʱ� ������� �迭�� ����ϴ� �Լ� 
int* make_array1(FILE* fp, int num_terms) {
    // ���Ͽ��� ���׽� �׵��� �а�, 
    //����� ���� ������������ ������ �迭�� �����Ͽ� ��ȯ�ϴ� �Լ�

    Term* terms;//����� ������ �Բ� ������ ����ü 

    //�迭�� �����Ҵ�
    MALLOC(terms, num_terms * sizeof(Term));

    int max_exp = 0;//�ִ� ������ ������ ����

    for (int i = 0; i < num_terms; i++) {//����ü �������� �迭�� ����, ��� ����
        fscanf(fp, "%d\t%d", &terms[i].coef, &terms[i].exp);
        if (terms[i].exp > max_exp)//�ִ� ���� ���� 
            max_exp = terms[i].exp;
    }
    //�迭�� ũ��: �ִ� ����+2
    int* arr;//�迭 �����Ҵ�
    MALLOC(arr, (max_exp + 2) * sizeof(int));

    arr[0] = max_exp;//�迭 ù�κп� �ִ� ���� ����
    //��� �κ��� �켱 �ʱ�ȭ
    for (int i = 1; i <= max_exp + 1; i++) {
        arr[i] = 0;
    }
    //����ü �迭�� ��ȸ�ϸ鼭, �ش� ���� ��ġ�� ��� ����
    //�迭�� �ε����� �������� ������ ����ǹǷ� �ڵ� �������� ����
    for (int i = 0; i < num_terms; i++) {
        int pos = max_exp - terms[i].exp + 1;
        arr[pos] = terms[i].coef;
    }
    //�ӽ÷� �� ����ü �迭 �޸� ����
    free(terms);
    //������ �迭 ��ȯ
    return arr;
}
//�迭_�ʱ� �ؽ�Ʈ ���Ϸ� ����ϴ� �Լ�
void write_poly(FILE* fp, int* poly) {
    int max_deg = poly[0];
    int firstTerm = 1;
    // �ִ� �������� 0���� �ݺ� (�迭 �ε����� 1���� max_deg+1)
    for (int i = 1; i <= max_deg + 1; i++) {
        int exp = max_deg - (i - 1);
        int coef = poly[i];
        if (coef != 0) {
            if (!firstTerm) { // ù ���� �ƴ϶�� �տ� " + " �߰�
                fprintf(fp, " + ");
            }
            // ���� "��� x^����" �������� ���
            // ���� ��� coef=2, exp=4�� ��� "2x^4" ���
            fprintf(fp, "%dx^%d", coef, exp);
            firstTerm = 0;
        }
    }
    fprintf(fp, "\n");
}


//�迭_������ ������� �迭�� �Ҵ�
int** make_array2(FILE* fp, int n1, int n2, int** out_data) {
    Term* termsA, * termsB;//����� ������ �Բ� ������ ����ü 

    //�迭�� �����Ҵ�
    MALLOC(termsA, n1 * sizeof(Term));
    for (int i = 0; i < n1; i++) {//ù ���׽�,����ü �������� �迭�� ����, ��� ����
        fscanf(fp, "%d\t%d", &termsA[i].coef, &termsA[i].exp);
    }
    MALLOC(termsB, n2 * sizeof(Term));
    for (int i = 0; i < n2; i++) {//�ι�° ���׽�,����ü �������� �迭�� ����, ��� ����
        fscanf(fp, "%d\t%d", &termsB[i].coef, &termsB[i].exp);
    }
    //������ �迭 �����
    // 1: ��ü ������ �޸� �� ��� �Ҵ�
    int rows = n1 + n2 + 1;
    int* data = (int*)malloc(rows * 2 * sizeof(int));
    // 2: �� ������ �迭 �Ҵ�
    int** arr = (int**)malloc(rows * sizeof(int*));
    // 3: �� �� �����Ϳ� ������ ��ġ ����
    for (int i = 0; i < rows; i++) {
        arr[i] = data + (i * 2);
        //arr[i]�� ���� data���� ���� �������� ������ġ ����
        //data+0->row 0����, data+2->row1����(cols=2)
    }
    // 4: �� �Ҵ� 
    for (int i = 0; i < n1; i++) {
        arr[i][0] = termsA[i].coef;
        arr[i][1] = termsA[i].exp;
    }
    for (int i = 0; i < n2; i++) {
        arr[n1 + i][0] = termsB[i].coef;
        arr[n1 + i][1] = termsB[i].exp;
    }

    // 5: �޸� ���� 
    free(termsA);
    free(termsB);

    //arr�� �ۿ����� ������Ű��, 
    // free(data)�ϱ� ���� data�� ������ ������. 
    *out_data = data;
    return arr;
}

// �� ���׽��� ���� ����� 2���� �迭�� ��ȯ�ϴ� �Լ�
// out_rows�� ��� ���׽��� �� ������ �����ϴ� ������ �ּ�
int** add_array2(int** arr, int n1, int n2, int* out_rows) {
    int total_terms = n1 + n2;
    int max_exp = 0;

    // 1. �� ���׽��� �ִ� ���� ã��
    for (int i = 0; i < total_terms; i++) {
        if (arr[i][1] > max_exp)
            max_exp = arr[i][1];
    }

    // 2. �ӽ� �ջ� �迭 �Ҵ� (�ε���: ���� 0 ~ max_exp)
    int* sum_temp = (int*)calloc(max_exp + 1, sizeof(int));
    if (sum_temp == NULL) {
        fprintf(stderr, "�޸� �Ҵ� ����\n");
        exit(EXIT_FAILURE);
    }

    // 3. �� ���׽��� ��� �׿� ���� ����� ����
    // �� ��: arr[i][0] = ���, arr[i][1] = ����
    for (int i = 0; i < total_terms; i++) {
        int coef = arr[i][0];
        int exp = arr[i][1];
        sum_temp[exp] += coef;
    }

    // 4. ���� ��� �� ����� 0�� �ƴ� ���� ���� ���
    int count = 0;
    for (int exp = 0; exp <= max_exp; exp++) {
        if (sum_temp[exp] != 0)
            count++;
    }

    // 5. ��� 2���� �迭 �Ҵ�
    // ��� �迭�� �� ���� [���, ����] �����̸�, �� count ��
    int** result = (int**)malloc(count * sizeof(int*));
    int* result_data = (int*)malloc(count * 2 * sizeof(int));
    if (result == NULL || result_data == NULL) {
        fprintf(stderr, "�޸� �Ҵ� ����\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < count; i++) {
        result[i] = result_data + i * 2;
    }

    // 6. ��� �迭�� ��������(���� ��������)���� �� ����
    // exp: max_exp �� 0
    int row = 0;
    for (int exp = max_exp; exp >= 0; exp--) {
        if (sum_temp[exp] != 0) {
            result[row][0] = sum_temp[exp]; // ���
            result[row][1] = exp;           // ����
            row++;
        }
    }

    free(sum_temp);
    *out_rows = count;  // ��� ���׽��� �� ������ ��ȯ
    return result;
}
//���׽� ����Լ� 
// poly: 2���� �迭, �� ���� [���, ����] ���·� �����
// row_count: poly�� ����� ���� ����
// ��� ����: �� ���� "���x^����"�� ����ϸ�, �׵� ���̿��� " + " �Ǵ� " - "�� ���� �����Ͽ� ����
void write_poly_file(FILE* fp, int** poly, int row_count) {
    int firstTerm = 1;  // ù ���̸� " + "�� ������� �ʱ� ���� ���
    for (int i = 0; i < row_count; i++) {
        int coef = poly[i][0];
        int exp = poly[i][1];
        if (coef == 0) continue;  // ����� 0�̸� ������� ����
        if (firstTerm) {
            // ù ���� ���, �����̸� "-" ǥ��, ����̸� �׳� ���
            if (coef < 0)
                fprintf(fp, "-%dx^%d", -coef, exp);
            else
                fprintf(fp, "%dx^%d", coef, exp);
            firstTerm = 0;
        }
        else {
            // �� ��° �׺��ʹ� " + " Ȥ�� " - " �߰�
            if (coef < 0)
                fprintf(fp, " - %dx^%d", -coef, exp);
            else
                fprintf(fp, " + %dx^%d", coef, exp);
        }
    }
    fprintf(fp, "\n");  // �� ���׽� ��� �� �ٹٲ�
}

//��� ���� �Լ�(����, ���)
polyNode* create_node(int coef, int exp) {//��� ���� �Լ�(���,���� �Է¹���)
    polyNode* node = (polyNode*)malloc(sizeof(polyNode));//����ü ����
    //��ȯ�� �ּҸ� polyNode*������ ĳ�����Ͽ� node�� ����.
    if (node == NULL) {
        printf("�޸� �Ҵ� ����\n");
        exit(1);
    }
    node->coef = coef;
    node->exp = exp;
    node->link = NULL;
    return node;
}
//��� ���� �Լ�
// (���� ��������, ������ ������ ���� �̹� �����ϸ� ������� �����ش�.)
void insert_term(polyNode** head, int coef, int exp) {
    if (coef == 0) return;  // ��� 0�� ����

    polyNode* new_node = create_node(coef, exp);//�� ��� ���� ����

    // 1. head�� ����ų�, �� ���� head���� ū ������ �� �� ����(�������� ����)
    if (*head == NULL || exp > (*head)->exp) {
        new_node->link = *head;
        *head = new_node;
        return;
    }

    //��ȸ �غ�
    polyNode* cur = *head;//���� ��� ������ ����
    polyNode* prev = NULL;//���� ��� ������ ����
    //���� �׺��� ������ �۰ų� ���� ���� ã�� ������ �̵�(�������� ����)
    while (cur != NULL && cur->exp > exp) {
        prev = cur;
        cur = cur->link;
    }
    if (cur != NULL && cur->exp == exp) {
        // ������ ������ ����� ���ϱ�
        cur->coef += coef;
        free(new_node);  // �� ���� �ʿ� ����
        if (cur->coef == 0) {
            // ����� 0�� �Ǹ� ��� ����
            if (prev) prev->link = cur->link;
            else *head = cur->link;
            free(cur);
        }
    }
    else {//������ �� �۰ų�, ������ ���� ���-> �߰� Ȥ�� ���� ����
        new_node->link = cur;
        if (prev) prev->link = new_node;
        else *head = new_node;
    }
}

//���� ���׽� ������� ����Ʈ ���� ����
// polyNode ��ũ�� ����Ʈ�� ����� ���׽��� ���Ͽ� ����ϴ� �Լ�
void write_poly_linked(FILE* fp, polyNode* head) {
    int first = 1;  // ù ���̸� ������ ���� ����ϵ��� ��

    while (head != NULL) {
        // ����� 0�̸� �ǳʶٱ� (�ʿ��ϸ� 0�׵� ����� �� ����)
        if (head->coef != 0) {
            if (first) {
                // ù ��: ����̸� �׳� ���, �����̸� '-' ó��
                if (head->coef < 0)
                    fprintf(fp, "-%dx^%d", -head->coef, head->exp);
                else
                    fprintf(fp, "%dx^%d", head->coef, head->exp);
                first = 0;
            }
            else {
                // ���� �׵�: ��ȣ�� ���� " + " �Ǵ� " - "�� ���
                if (head->coef < 0)
                    fprintf(fp, " - %dx^%d", -head->coef, head->exp);
                else
                    fprintf(fp, " + %dx^%d", head->coef, head->exp);
            }
        }
        head = head->link;
    }
    fprintf(fp, "\n");
}

//�޸� ��ȯ
void free_poly(polyNode* head) {
    polyNode* cur;
    while (head != NULL) {
        cur = head;
        head = head->link;
        free(cur);
    }
}
//�迭_�ʱ� ������� �������� �迭 ��ȯ
//�ð� ��� ���� �ʿ�
int* calculate_Array1() {
    FILE* input = fopen("input.txt", "r");//���� �б� ���� ����
    if (input == NULL) {//���� ���� ����ó��
        printf("���Ͽ��� ����\n");
        return NULL;
    }
    int n1, n2;//�� ���׽��� ������ �����ǹ�
    //([number_of_exponents]\t[number_of_exponents]\n)
    fscanf(input, "%d\t%d", &n1, &n2);

    int* A = make_array1(input, n1);
    int* B = make_array1(input, n2);
    fclose(input);//���� �ݱ� 

    int degA = A[0];  // A�� �ְ� ����
    int degB = B[0];  // B�� �ְ� ����
    int max_deg = MAX(degA, degB);

    int size = max_deg + 2; // [�ְ�����, ��� ...] �̹Ƿ� +2

    int* answer;//���� �Ϸ�� �迭 �����Ҵ�
    MALLOC(answer, size * sizeof(int));
    answer[0] = max_deg;

    // ��� 0���� �ʱ�ȭ
    for (int i = 1; i <= max_deg + 1; i++) {
        answer[i] = 0;
    }
    // A�� �׵� ����
    for (int i = 1; i <= degA + 1; i++) {
        int exp = degA - (i - 1);  // ���� ���
        int pos = max_deg - exp + 1;
        answer[pos] += A[i];
    }

    // B�� �׵� ���ϱ�
    for (int i = 1; i <= degB + 1; i++) {
        int exp = degB - (i - 1);  // ���� ���
        int pos = max_deg - exp + 1;
        answer[pos] += B[i];
    }
    //�ؽ�Ʈ ���Ϸ� ���
    FILE* out_fp = fopen("output.txt", "w");//�ؽ�Ʈ ���� ����
    if (out_fp == NULL) {
        perror("output.txt ���� ���� ����");
        exit(EXIT_FAILURE);
    }
    write_poly(out_fp, A);
    write_poly(out_fp, B);
    write_poly(out_fp, answer);

    fclose(out_fp);
    //�޸� ���� ���� 
    free(A);
    free(B);

    return answer;
}

//�迭_������ ������� �迭�� ����ϴ� �Լ� 
int calculate_Array2() {
    FILE* input = fopen("input.txt", "r");//���� �б� ���� ����
    if (input == NULL) {//���� ���� ����ó��
        printf("���Ͽ��� ����\n");
        return 1;
    }
    int n1, n2;//�� ���׽��� ������ �����ǹ�
    //([number_of_exponents]\t[number_of_exponents]\n)
    fscanf(input, "%d\t%d", &n1, &n2);

    //data ������ �ޱ����� ���� ����
    int* data = NULL;
    int** arr = make_array2(input, n1, n2, &data);
    fclose(input);//���� �ݱ�


   
    //���׽� ���� ����
    int out_rows;
    int** sum = add_array2(arr, n1, n2, &out_rows);

    //���� ��� ���� ���
    FILE* fp = fopen("output.txt", "a");
    if (fp == NULL) {
        perror("���� ���� ����");
        exit(EXIT_FAILURE);
    }
    write_poly_file(fp, arr, n1);  // arr�� ù n1���� ���� f1�� �׵�

    write_poly_file(fp, arr + n1, n2);  // arr+n1�� �ι�° ���׽� ����, n2���� �� ���

    write_poly_file(fp, sum, out_rows); // add_array2()�� ���� ���� ���� ���

    fclose(fp);

    //�޸� ���� 
    free(sum);
    free(data);
    free(arr);

    return 1;
}
// �� ���ĵ� ��ũ�� ����Ʈ(�������� ����)�� �����Ͽ� ���� ��� ��ũ�� ����Ʈ�� �����ϴ� �Լ�
polyNode* merge_poly(polyNode* A, polyNode* B) {
    // �ӽ� ���� ��带 �����Ͽ� ��� ����Ʈ�� ������ ���� ó��
    polyNode dummy;
    dummy.link = NULL;
    polyNode* tail = &dummy;

    while (A != NULL && B != NULL) {
        if (A->exp > B->exp) {
            // A�� ���� �� ū ���: ����� A�� ��带 �����ϰ� A�� �� ĭ �̵�
            tail->link = A;
            A = A->link;
            tail = tail->link;
        }
        else if (A->exp < B->exp) {
            // B�� ���� �� ū ���: ����� B�� ��带 �����ϰ� B�� �� ĭ �̵�
            tail->link = B;
            B = B->link;
            tail = tail->link;
        }
        else {
            // �� ���� ������ ������ ����� �ջ�
            int newCoef = A->coef + B->coef;
            if (newCoef != 0) {
                // �ջ��� ����� 0�� �ƴϸ�, �� ��带 �����Ͽ� ����� ����
                tail->link = create_node(newCoef, A->exp);
                tail = tail->link;
            }
            // �� ��带 ��� �Һ�
            A = A->link;
            B = B->link;
        }
    }
    // ���� ����Ʈ �� ���� ���� ����� ����
    if (A != NULL) {
        tail->link = A;
    }
    else if (B != NULL) {
        tail->link = B;
    }

    return dummy.link;
}

//Linkedlist_������� �迭�� ����ϴ� �Լ� 
int calculate_Linkedlist() {
    FILE* input = fopen("input.txt", "r"); // ���� �б� ���
    if (input == NULL) {
        printf("���Ͽ��� ����\n");
        return 1;
    }

    int n1, n2; // f��(x)�� f��(x)�� �� ����
    fscanf(input, "%d\t%d", &n1, &n2);

    int co, ex;
    polyNode* poly1 = NULL;
    polyNode* poly2 = NULL;

    // ù ��° ���׽��� n1���� �� �б�
    for (int i = 0; i < n1; i++) {
        fscanf(input, "%d\t%d", &co, &ex);
        insert_term(&poly1, co, ex);
    }
    // �� ��° ���׽��� n2���� �� �б� (���� ���� ����)
    for (int i = 0; i < n2; i++) {
        fscanf(input, "%d\t%d", &co, &ex);
        insert_term(&poly2, co, ex);
    }
    fclose(input);

    
    polyNode* sum = merge_poly(poly1, poly2);

    // output.txt�� ����� append ���� ���
    FILE* out_fp = fopen("output.txt", "a");
    if (out_fp == NULL) {
        perror("output.txt ���� ���� ����");
        exit(EXIT_FAILURE);
    }

    // ������ ���׽��� ��� (�� ���� ���׽ĸ� ���)
    write_poly_linked(out_fp, poly1);
    write_poly_linked(out_fp, poly2);
    write_poly_linked(out_fp, sum);

    fclose(out_fp);

    // merge_poly()�� �� ��带 ������ ���� new �޸𸮸� �Ҵ�
    // ���� ������ poly1�̳� poly2�� ��带 ����
    // ���� �� ����Ʈ�� ���յ� �� poly1�� poly2�� �� �̻� ��ȿ���� �����Ƿ�,
    // merge_poly() ��� sum ����Ʈ�� free_poly()�� ȣ���ؼ� ����
    free_poly(sum);

    return 0;
}


int main() {
    clock_t start, end;
    double time_array1, time_array2, time_linkedlist;

    //solution#1
    start = clock();
    int* result1 = calculate_Array1();
    end = clock();
    time_array1 = ((double)(end - start)) / CLOCKS_PER_SEC;
    //printf("calculate_Array1 ���� �ð�: %f ��\n", time_array1);
    free(result1);

    //solution#2
    start = clock();
    calculate_Array2(); // ��ȯ���� int ��(��: ���� ����)�̶� ����
    end = clock();
    time_array2 = ((double)(end - start)) / CLOCKS_PER_SEC;
    //printf("calculate_Array2 ���� �ð�: %f ��\n", time_array2);

    //solution#3
    start = clock();
    calculate_Linkedlist(); // ��ȯ���� int ��(��: ���� ����)�̶� ����
    end = clock();
    time_linkedlist = ((double)(end - start)) / CLOCKS_PER_SEC;
    //printf("calculate_Linkedlist ���� �ð�: %f ��\n", time_linkedlist);


    FILE* fp = fopen("output.txt", "a");
    fprintf(fp, "%f\t%f\t%f", time_array1, time_array2, time_linkedlist);
    fclose(fp);

    return 0;
}