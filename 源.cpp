#include <iostream>
#include <bitset>
using namespace std;


//�ַ���ת��Ϊ������
void CharToASCII(string& text, int** mingwen)
{
    string s;
    for (auto i : text)
    {
        bitset<8> bs(i);
        s += bs.to_string();
    }

    int a = 0;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 8; j++)
        {
            char d = s[a];
            mingwen[i][j] = d - '0';
            a++;
        }

}
// TODO ʵ��x^nfx�ĺ���
void x_de_n_fang_cheng_fx(int xfx[4], int a[4]) //* xfx�ǽ����a����һ���Ľ��
{
    //! ע��Ҫȡģ
    //! ��Լ����ʽ�� x^4 + x + 1
    //* �����Ĵγ˷���ϵ��
    if (a[0] == 0)
    {
        for (int i = 0; i < 3; i++)
            xfx[i] = a[i + 1];
    }
    else
    {
        //! ����������Ϊ1����Ҫ�� b1x^2+b0x �� x+1 �������
        xfx[1] = a[2];
        xfx[2] = a[3] == 1 ? 0 : 1;
        xfx[3] = 1;
    }
}
// TODO �˷�
int* chengfa(int a[4], int b[4])
{
    //* ��������ϵ��
    int* result = new int[4];
    for (int i = 0; i < 4; i++)
        result[i] = 0;

    //* ��¼��x^nfx
    int xfx[4] = { 0 };
    x_de_n_fang_cheng_fx(xfx, a);
    int x2fx[4] = { 0 };
    x_de_n_fang_cheng_fx(x2fx, xfx);
    int x3fx[4] = { 0 };
    x_de_n_fang_cheng_fx(x3fx, x2fx);

    //* ������Ҫ���ݶ���ʽa��b��ʼ���
    if (b[0] == 1)
        for (int i = 0; i < 4; i++)
            result[i] ^= x3fx[i];
    if (b[1] == 1)
        for (int i = 0; i < 4; i++)
            result[i] ^= x2fx[i];
    if (b[2] == 1)
        for (int i = 0; i < 4; i++)
            result[i] ^= xfx[i];
    if (b[3] == 1)
        for (int i = 0; i < 4; i++)
            result[i] ^= a[i];
    return result;
}

const int s[4][4] = {
    {9, 4, 10, 11},
    {13, 1, 8, 5},
    {6, 2, 0, 3},
    {12, 14, 15, 7} };

const int sni[4][4] = {
    {10, 5, 9, 11},
    {1, 7, 8, 15},
    {6, 0, 2, 3},
    {12, 4, 13, 14}
};

const int tihuanwei[16][4] = {
    {0, 0, 0, 0},
    {0, 0, 0, 1},
    {0, 0, 1, 0},
    {0, 0, 1, 1},
    {0, 1, 0, 0},
    {0, 1, 0, 1},
    {0, 1, 1, 0},
    {0, 1, 1, 1},
    {1, 0, 0, 0},
    {1, 0, 0, 1},
    {1, 0, 1, 0},
    {1, 0, 1, 1},
    {1, 1, 0, 0},
    {1, 1, 0, 1},
    {1, 1, 1, 0},
    {1, 1, 1, 1} };
// const int tihuanwei[4][4][4] = {
//     {{1, 0, 0, 1},{0, 1, 0, 0},{1, 0, 1, 0},{1, 0, 1, 1}},
//     {{1, 1, 0, 1},{0, 0, 0, 1},{1,0,0,0},{0,1,0,1}},
//     {{0,1,1,0},{0,0,1,0},{0,0,0,0},{0,0,1,1}},
//     {{1,1,0,0},{1,1,1,0},{1,1,1,1},{0,1,1,1}}};


//* �����ֳ���
int rcon1[8] = { 1, 0, 0, 0, 0, 0, 0, 0 };
int rcon2[8] = { 0, 0, 1, 1, 0, 0, 0, 0 };

int* yihuo8(int* a, int* b)//8λ�����
{
    int* t = new int[8];
    for (int i = 0; i < 8; i++)
        t[i] = a[i] ^ b[i];
    return t;
}

int* yihuo4(int* a, int* b)//4λ�����
{
    int* t = new int[4];
    for (int i = 0; i < 4; i++)
        t[i] = a[i] ^ b[i];
    return t;
}

void s_he_tihuan(int* temp) //ʹ��s���滻�ĺ�����8λ��
{
    int t1 = 2 * temp[0] + temp[1];
    int t2 = 2 * temp[2] + temp[3];
    int t3 = 2 * temp[4] + temp[5];
    int t4 = 2 * temp[6] + temp[7];
    int tihuan1 = s[t1][t2]; //��¼�滻�������
    int tihuan2 = s[t3][t4];
    //* ��λ��λ�����滻
    for (int i = 0; i < 4; i++)
        temp[i] = tihuanwei[tihuan1][i];
    for (int i = 0; i < 4; i++)
        temp[i + 4] = tihuanwei[tihuan2][i];
}

void s_nihe_tihuan(int* temp) //ʹ��s���滻�ĺ�����8λ��
{
    int t1 = 2 * temp[0] + temp[1];
    int t2 = 2 * temp[2] + temp[3];
    int t3 = 2 * temp[4] + temp[5];
    int t4 = 2 * temp[6] + temp[7];
    int tihuan1 = sni[t1][t2]; //��¼�滻�������
    int tihuan2 = sni[t3][t4];
    //* ��λ��λ�����滻
    for (int i = 0; i < 4; i++)
        temp[i] = tihuanwei[tihuan1][i];
    for (int i = 0; i < 4; i++)
        temp[i + 4] = tihuanwei[tihuan2][i];
}

void zuoyi(int** temp) //ѭ������
{
    //! ����ӣ�������ע����ֽ����еķ�ʽ������Ӧ���ǵ�һ�ֽڵ��Ұ벿�ֺ͵ڶ��ֽڵ��Ұ벿�ֽ����滻
    for (int i = 4; i < 8; i++)
    {
        int t = temp[0][i];
        temp[0][i] = temp[1][i];
        temp[1][i] = t;
    }
}
int* g(int* temp, int* rcon) // temp��һ����λ������,rcon���ֳ���
{
    //! ע�����temp����Կ�����ܸĶ���Ҫ����һ���µĽ��м���
    int* t = new int[8];
    for (int i = 0; i < 8; i++)
        t[i] = temp[i];
    //* ѭ������
    for (int i = 0; i < 4; i++)
    {
        int tt = t[i + 4];
        t[i + 4] = t[i];
        t[i] = tt;
    }

    //* ����s���滻
    s_he_tihuan(t);

    //* �����ֳ������
    return yihuo8(t, rcon);
}

void liehunxiao(int** mingwen)//�л���
{
    int si_de2jinzhi[4] = { 0, 1, 0, 0 };
    int* m00 = new int[4];
    int* m10 = new int[4];
    int* m01 = new int[4];
    int* m11 = new int[4];
    for (int i = 0; i < 4; i++)
    {
        m00[i] = mingwen[0][i];
        m10[i] = mingwen[0][i + 4];
        m01[i] = mingwen[1][i];
        m11[i] = mingwen[1][i + 4];
    }
    int* n00 = new int[4];
    int* n10 = new int[4];
    int* n01 = new int[4];
    int* n11 = new int[4];
    n00 = yihuo4(m00, chengfa(si_de2jinzhi, m10));//�˷������1011
    n10 = yihuo4(chengfa(si_de2jinzhi, m00), m10);//0101
    n01 = yihuo4(m01, chengfa(si_de2jinzhi, m11));//0100
    n11 = yihuo4(chengfa(si_de2jinzhi, m01), m11);//0010
    for (int i = 0; i < 4; i++)
    {
        mingwen[0][i] = n00[i];
        mingwen[0][i + 4] = n10[i];
        mingwen[1][i] = n01[i];
        mingwen[1][i + 4] = n11[i];
    }
}

void niliehunxiao(int** mingwen)//���л���
{
    int si_de2jinzhi[4] = { 0, 0, 1, 0 };
    int si_de1jinzhi[4] = { 1, 0, 0, 1 };
    int* m00 = new int[4];
    int* m10 = new int[4];
    int* m01 = new int[4];
    int* m11 = new int[4];
    for (int i = 0; i < 4; i++)
    {
        m00[i] = mingwen[0][i];
        m10[i] = mingwen[0][i + 4];
        m01[i] = mingwen[1][i];
        m11[i] = mingwen[1][i + 4];
    }
    int* n00 = new int[4];
    int* n10 = new int[4];
    int* n01 = new int[4];
    int* n11 = new int[4];
    n00 = yihuo4(chengfa(si_de1jinzhi,m00), chengfa(si_de2jinzhi, m10));
    n10 = yihuo4(chengfa(si_de2jinzhi, m00), chengfa(si_de1jinzhi, m10));
    n01 = yihuo4(chengfa(si_de1jinzhi, m01), chengfa(si_de2jinzhi, m11));
    n11 = yihuo4(chengfa(si_de2jinzhi, m01), chengfa(si_de1jinzhi, m11));
    for (int i = 0; i < 4; i++)
    {
        mingwen[0][i] = n00[i];
        mingwen[0][i + 4] = n10[i];
        mingwen[1][i] = n01[i];
        mingwen[1][i + 4] = n11[i];
    }
}

void lunmiyaojia(int** mingwen, int** key)
{
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 8; j++)
            mingwen[i][j] ^= key[i][j];
}

//�������
void shuchu(int** a)
{
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 8; j++)
            cout << a[i][j] << ' ';
    cout << endl;
}

void makemi()//����
{
    //* �������ĺ���Կ
    int** mingwen = new int* [2];
    for (int i = 0; i < 2; i++) {
        mingwen[i] = new int[8];
    }
    int** key = new int* [2];
    for (int i = 0; i < 2; i++) {
        key[i] = new int[8];
    }
    cout << "����������" << endl;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 8; j++) {
            cin >> mingwen[i][j];
        }
    }
    //�ַ���ʽ����
    /*string mw;
    cin >> mw;
    CharToASCII(mw, mingwen);*/
    cout << "��������Կ" << endl;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 8; j++) {
            cin >> key[i][j];
        }
    }
    /*string my;
    cin >> my;
    CharToASCII(my, key);*/
    //* ��Կ��չ�㷨������ֻ�����ּ��ܣ���һ�ֻ�ֻʹ����ԭʼkey
    int** key1 = new int* [2];
    for (int i = 0; i < 2; i++)
        key1[i] = new int[8];
    int** key2 = new int* [2];
    for (int i = 0; i < 2; i++)
        key2[i] = new int[8];

    key1[0] = yihuo8(key[0], g(key[1], rcon1));
    key1[1] = yihuo8(key1[0], key[1]);
    key2[0] = yihuo8(key1[0], g(key1[1], rcon2));
    key2[1] = yihuo8(key2[0], key1[1]);

    //* ��0�ֵ�����Կ��
    lunmiyaojia(mingwen, key);

    //*��һ��
    //* ���İ��ֽڴ���
    s_he_tihuan(mingwen[0]);
    s_he_tihuan(mingwen[1]);
    //* ���ĵ�����λ
    zuoyi(mingwen);
    //* ���ĵ��л���
    liehunxiao(mingwen);
    //* ���ĵ�����Կ��
    lunmiyaojia(mingwen, key1);

    //*�ڶ���
    //* ���İ��ֽڴ���
    s_he_tihuan(mingwen[0]);
    s_he_tihuan(mingwen[1]);

    //* ���ĵ�����λ
    zuoyi(mingwen);
    //* ���ĵ�����Կ��
    lunmiyaojia(mingwen, key2);

    //* ���ڵ�������ʵ��������
    cout << "����Ϊ��" << endl;
    shuchu(mingwen);
}

void makeming()//����
{
    //* �������ĺ���Կ
    int** miwen = new int* [2];
    for (int i = 0; i < 2; i++) {
        miwen[i] = new int[8];
    }
    int** key = new int* [2];
    for (int i = 0; i < 2; i++){
        key[i] = new int[8];
}
    cout << "����������" << endl;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 8; j++) {
            cin >> miwen[i][j];
        }
    }
    //�ַ���ʽ����
    /*string mw;
    cin >> mw;
    CharToASCII(mw, miwen);*/
    
    cout << "��������Կ" << endl;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 8; j++) {
            cin >> key[i][j];
        }
    }
    /*string my;
    cin >> my;
    CharToASCII(my, key);*/
    //* ��Կ��չ�㷨������ֻ�����ּ��ܣ���һ�ֻ�ֻʹ����ԭʼkey
    int** key1 = new int* [2];
    for (int i = 0; i < 2; i++)
        key1[i] = new int[8];
    int** key2 = new int* [2];
    for (int i = 0; i < 2; i++)
        key2[i] = new int[8];

    key1[0] = yihuo8(key[0], g(key[1], rcon1));
    key1[1] = yihuo8(key1[0], key[1]);
    key2[0] = yihuo8(key1[0], g(key1[1], rcon2));
    key2[1] = yihuo8(key2[0], key1[1]);

    //* ��0�ֵ�����Կ��
    lunmiyaojia(miwen, key2);

    //*��һ��
    //* ���ĵ�������λ
    zuoyi(miwen);
    //* ��������ֽڴ���
    s_nihe_tihuan(miwen[0]);
    s_nihe_tihuan(miwen[1]);
    //* ���ĵ�����Կ��
    lunmiyaojia(miwen, key1);
    //* ���ĵ����л���
    niliehunxiao(miwen);
    

    //*�ڶ���
    //* ���ĵ�������λ
    zuoyi(miwen);
    //* ��������ֽڴ���
    s_nihe_tihuan(miwen[0]);
    s_nihe_tihuan(miwen[1]);

    //* ���ĵ�����Կ��
    lunmiyaojia(miwen, key);

    //* ���ڵ�������ʵ��������
    cout << "����Ϊ��" << endl;
    shuchu(miwen);
}

void makemi2()
{
    //�������ĺ���Կ
    int** mingwen = new int* [2];
    for (int i = 0; i < 2; i++)
        mingwen[i] = new int[8];
    int** key = new int* [2];
    for (int i = 0; i < 2; i++)
        key[i] = new int[8];


    //˫�ؼ���
    int** k1ey = new int* [2];
    for (int i = 0; i < 2; i++)
        k1ey[i] = new int[8];

    //0.1�Ķ���������
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 8; j++)
            cin >> mingwen[i][j];
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 8; j++)
            cin >> key[i][j];


    //˫�ؼ���
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 8; j++)
            cin >> k1ey[i][j];



    //��Կ��չ�㷨������ֻ�����ּ��ܣ���һ�ֻ�ֻʹ����ԭʼkey
    int** key1 = new int* [2];
    for (int i = 0; i < 2; i++)
        key1[i] = new int[8];
    int** key2 = new int* [2];
    for (int i = 0; i < 2; i++)
        key2[i] = new int[8];


    //˫�ؼ���
    int** k1ey1 = new int* [2];
    for (int i = 0; i < 2; i++)
        k1ey1[i] = new int[8];
    int** k1ey2 = new int* [2];
    for (int i = 0; i < 2; i++)
        k1ey2[i] = new int[8];



    key1[0] = yihuo8(key[0], g(key[1], rcon1));
    key1[1] = yihuo8(key1[0], key[1]);
    key2[0] = yihuo8(key1[0], g(key1[1], rcon2));
    key2[1] = yihuo8(key2[0], key1[1]);


    //˫�ؼ���
    k1ey1[0] = yihuo8(k1ey[0], g(k1ey[1], rcon1));
    k1ey1[1] = yihuo8(k1ey1[0], k1ey[1]);
    k1ey2[0] = yihuo8(k1ey1[0], g(k1ey1[1], rcon2));
    k1ey2[1] = yihuo8(k1ey2[0], k1ey1[1]);



    //��0�ֵ�����Կ��
    lunmiyaojia(mingwen, key);

    //��һ��
    //���İ��ֽڴ���
    s_he_tihuan(mingwen[0]);
    s_he_tihuan(mingwen[1]);
    //���ĵ�����λ
    zuoyi(mingwen);
    //���ĵ��л���
    liehunxiao(mingwen);
    //���ĵ�����Կ��
    lunmiyaojia(mingwen, key1);

    //�ڶ���
    //���İ��ֽڴ���
    s_he_tihuan(mingwen[0]);
    s_he_tihuan(mingwen[1]);

    //���ĵ�����λ
    zuoyi(mingwen);
    //���ĵ�����Կ��
    lunmiyaojia(mingwen, key2);




    //˫�ؼ���
    lunmiyaojia(mingwen, k1ey);
    s_he_tihuan(mingwen[0]);
    s_he_tihuan(mingwen[1]);
    zuoyi(mingwen);
    liehunxiao(mingwen);
    lunmiyaojia(mingwen, k1ey1);
    s_he_tihuan(mingwen[0]);
    s_he_tihuan(mingwen[1]);
    zuoyi(mingwen);
    lunmiyaojia(mingwen, k1ey2);



    //�����ѱ�����
    shuchu(mingwen);
}

void makemi3()
{
    //�������ĺ���Կ
    int** mingwen = new int* [2];
    for (int i = 0; i < 2; i++)
        mingwen[i] = new int[8];
    int** key = new int* [2];
    for (int i = 0; i < 2; i++)
        key[i] = new int[8];


    //˫�ؼ���
    int** k1ey = new int* [2];
    for (int i = 0; i < 2; i++)
        k1ey[i] = new int[8];

    //���ؼ���
    int** k2ey = new int* [2];
    for (int i = 0; i < 2; i++)
        k2ey[i] = new int[8];

    //0.1�Ķ���������
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 8; j++)
            cin >> mingwen[i][j];
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 8; j++)
            cin >> key[i][j];


    //˫�ؼ���
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 8; j++)
            cin >> k1ey[i][j];


    //���ؼ���
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 8; j++)
            cin >> k2ey[i][j];



    //��Կ��չ�㷨������ֻ�����ּ��ܣ���һ�ֻ�ֻʹ����ԭʼkey
    int** key1 = new int* [2];
    for (int i = 0; i < 2; i++)
        key1[i] = new int[8];
    int** key2 = new int* [2];
    for (int i = 0; i < 2; i++)
        key2[i] = new int[8];


    //˫�ؼ���
    int** k1ey1 = new int* [2];
    for (int i = 0; i < 2; i++)
        k1ey1[i] = new int[8];
    int** k1ey2 = new int* [2];
    for (int i = 0; i < 2; i++)
        k1ey2[i] = new int[8];

    //���ؼ���
    int** k2ey1 = new int* [2];
    for (int i = 0; i < 2; i++)
        k2ey1[i] = new int[8];
    int** k2ey2 = new int* [2];
    for (int i = 0; i < 2; i++)
        k2ey2[i] = new int[8];


    key1[0] = yihuo8(key[0], g(key[1], rcon1));
    key1[1] = yihuo8(key1[0], key[1]);
    key2[0] = yihuo8(key1[0], g(key1[1], rcon2));
    key2[1] = yihuo8(key2[0], key1[1]);


    //˫�ؼ���
    k1ey1[0] = yihuo8(k1ey[0], g(k1ey[1], rcon1));
    k1ey1[1] = yihuo8(k1ey1[0], k1ey[1]);
    k1ey2[0] = yihuo8(k1ey1[0], g(k1ey1[1], rcon2));
    k1ey2[1] = yihuo8(k1ey2[0], k1ey1[1]);


    //���ؼ���
    k2ey1[0] = yihuo8(k2ey[0], g(k2ey[1], rcon1));
    k2ey1[1] = yihuo8(k2ey1[0], k2ey[1]);
    k2ey2[0] = yihuo8(k2ey1[0], g(k2ey1[1], rcon2));
    k2ey2[1] = yihuo8(k2ey2[0], k2ey1[1]);


    //��0�ֵ�����Կ��
    lunmiyaojia(mingwen, key);

    //��һ��
    //���İ��ֽڴ���
    s_he_tihuan(mingwen[0]);
    s_he_tihuan(mingwen[1]);
    //���ĵ�����λ
    zuoyi(mingwen);
    //���ĵ��л���
    liehunxiao(mingwen);
    //���ĵ�����Կ��
    lunmiyaojia(mingwen, key1);

    //�ڶ���
    //���İ��ֽڴ���
    s_he_tihuan(mingwen[0]);
    s_he_tihuan(mingwen[1]);

    //���ĵ�����λ
    zuoyi(mingwen);
    //���ĵ�����Կ��
    lunmiyaojia(mingwen, key2);




    //˫�ؼ���
    lunmiyaojia(mingwen, k1ey);
    s_he_tihuan(mingwen[0]);
    s_he_tihuan(mingwen[1]);
    zuoyi(mingwen);
    liehunxiao(mingwen);
    lunmiyaojia(mingwen, k1ey1);
    s_he_tihuan(mingwen[0]);
    s_he_tihuan(mingwen[1]);
    zuoyi(mingwen);
    lunmiyaojia(mingwen, k1ey2);

    //���ؼ���
    lunmiyaojia(mingwen, k2ey);
    s_he_tihuan(mingwen[0]);
    s_he_tihuan(mingwen[1]);
    zuoyi(mingwen);
    liehunxiao(mingwen);
    lunmiyaojia(mingwen, k2ey1);
    s_he_tihuan(mingwen[0]);
    s_he_tihuan(mingwen[1]);
    zuoyi(mingwen);
    lunmiyaojia(mingwen, k2ey2);

    //�����ѱ�����
    shuchu(mingwen);
}

void jiami(int** mingwen, int** key)
{
    //�������ĺ���Կ


      //��Կ��չ�㷨������ֻ�����ּ��ܣ���һ�ֻ�ֻʹ����ԭʼkey
    int** key1 = new int* [2];
    for (int i = 0; i < 2; i++)
        key1[i] = new int[8];
    int** key2 = new int* [2];
    for (int i = 0; i < 2; i++)
        key2[i] = new int[8];



    key1[0] = yihuo8(key[0], g(key[1], rcon1));
    key1[1] = yihuo8(key1[0], key[1]);
    key2[0] = yihuo8(key1[0], g(key1[1], rcon2));
    key2[1] = yihuo8(key2[0], key1[1]);






    //��0�ֵ�����Կ��
    lunmiyaojia(mingwen, key);

    //��һ��
    //���İ��ֽڴ���
    s_he_tihuan(mingwen[0]);
    s_he_tihuan(mingwen[1]);
    //���ĵ�����λ
    zuoyi(mingwen);
    //���ĵ��л���
    liehunxiao(mingwen);
    //���ĵ�����Կ��
    lunmiyaojia(mingwen, key1);

    //�ڶ���
    //���İ��ֽڴ���
    s_he_tihuan(mingwen[0]);
    s_he_tihuan(mingwen[1]);

    //���ĵ�����λ
    zuoyi(mingwen);
    //���ĵ�����Կ��
    lunmiyaojia(mingwen, key2);

}

void decimalToBinary(int decimal, int** key)
{
    for (int i = 0; i < 2; i++)
        for (int j = 7; j >= 0; j--)
        {
            key[i][j] = decimal % 2;
            decimal /= 2;
        }
}

void pojie()
{
    int** mingwen = new int* [2];
    for (int i = 0; i < 2; i++)
        mingwen[i] = new int[8];

    int** miwen = new int* [2];
    for (int i = 0; i < 2; i++)
        miwen[i] = new int[8];






    //0.1�Ķ���������
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 8; j++)
            cin >> mingwen[i][j];
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 8; j++)
            cin >> miwen[i][j];


    for (int a = 0; a <= 65536; a++)
    {
        int** linshi = new int* [2];
        for (int i = 0; i < 2; i++)
            linshi[i] = new int[8];

        linshi = mingwen;

        int** key = new int* [2];
        for (int i = 0; i < 2; i++)
            key[i] = new int[8];

        decimalToBinary(a, key);
        jiami(linshi, key);
        int t = 0;
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 8; j++)
            {
                if (linshi[i][j] == miwen[i][j])
                    t++;
            }

        if (t == 16)
        {
            shuchu(key);
            break;
        }
    }
}

int main()
{
    int t;
    while (1)
    {
        cout << "��ѡ��1.���� 2.���� 3.���ؼ��� 4.���ؼ��� �����˳�" << endl;
        cin >> t;
        if (t == 1)
        {
            makemi();
        }
        else if (t == 2)
        {
            makeming();
        }
        else if (t == 3)
        {
            makemi2();
        }
        else if (t == 4)
        {
            makemi3();
        }
        else
        {
            break;
        }
    }
    return 0;
}

