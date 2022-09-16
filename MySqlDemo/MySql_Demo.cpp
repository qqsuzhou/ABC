#include <stdio.h>
#include <mysql.h>		// mysql�ļ�
int main(void)
{
	MYSQL mysql;		//���ݿ���
	MYSQL_RES* res;		//��ѯ�����
	MYSQL_ROW row;		//��¼�ṹ��

	//��ʼ�����ݿ�
	mysql_init(&mysql);

	//�����ַ�����
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");

	//�������ݿ�
	if (mysql_real_connect(&mysql, "127.0.0.1", "root", "123456", "db1", 3306, NULL, 0) == NULL) {
		printf("����ԭ�� %s\n", mysql_error(&mysql));
		printf("����ʧ�ܣ�\n");
		exit(-1);
	}

	//��ѯ����
	int ret = mysql_query(&mysql, "select * from stu;");
	printf("ret: %d\n", ret);

	//��ȡ�����
	res = mysql_store_result(&mysql);

	//��ROW��ֵ���ж�ROW�Ƿ�Ϊ�գ���Ϊ�վʹ�ӡ���ݡ�
	while (row = mysql_fetch_row(res))
	{
		printf("%s  ", row[0]);  //��ӡID
		printf("%s  ", row[1]);  //��ӡ����
		printf("%s  ", row[2]);  //��ӡ�༶
		printf("%s  \n", row[3]);//��ӡ�Ա�
	}
	//�ͷŽ����
	mysql_free_result(res);

	//�ر����ݿ�
	mysql_close(&mysql);

	system("pause");
	return 0;
}
