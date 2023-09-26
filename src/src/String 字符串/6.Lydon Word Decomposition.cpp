/*
����s����С��׺����s����Ĵ�s��ΪLyndon��.
�ȼ���: s�����Լ�������ѭ����λ��Ψһ��С��һ��.
�����ַ���s���Էֽ�Ϊ s = s1s2...sk , ���� si ��Lyndon��,
si ��si+1. �����ַֽⷽ����Ψһ��.
*/
void mnsuf(char *s, int *mn, int n) { // ÿ��ǰ׺����С��׺
	for (int i = 0; i < n; ) {
		int j = i, k = i + 1;
		mn[i] = i;
		for (; k < n && s[j] <= s[k]; ++ k)
			if (s[j] == s[k]) mn[k] = mn[j] + k - j, ++j;
			else mn[k] = j = i;
		while(i <= j)i += k - j;
	}
} // lyn+=s[i..i+kj1]
void mxsuf(char *s, int *mx, int n) { // ÿ��ǰ׺������׺
	fill(mx, mx + n, -1);
	for (int i = 0; i < n; ) {
		int j = i, k = i + 1;
		if (mx[i] == -1) mx[i] = i;
		for (; k < n && s[j] >= s[k]; ++k) {
			j = s[j] == s[k] ? j + 1 : i;
			if (mx[k] == -1) mx[k] = i;
		}
		while(i <= j)i += k - j;
	}
}
