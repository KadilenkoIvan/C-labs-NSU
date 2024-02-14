#pragma comment (linker, "/STACK:50000000 ")
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ssss {
	int vertex;
	long long ckoka;
	int nomer;
}sssss;

typedef struct trinochi {
	int vertec;
	int nomerrebra;
}trinochi;

typedef struct Graf {
	char color;
	long long path;
	sssss* arr;
	int n;
	int cap;
}Graf;

typedef struct kucha {
	int v;
	long long edge;
}kucha;

kucha* t;
int nomerkuchi = 0;
int sum = 0; int j = 0;
int* mas;

void SwiftUp(int q) {
	int w = (q-1)/2;
	while (t[q].edge < t[w].edge) {
		int y = t[w].v;
		long long h = t[w].edge;
		t[w].v = t[q].v;
		t[w].edge = t[q].edge;
		t[q].v = y;
		t[q].edge = h;
		q = w;
		w = (q-1)/2;
	}
}

void SwiftDown(int q) {
	int l, p, j;
	while ((2 * q + 1) < nomerkuchi) {
		l = 2 * q + 1;
		p = 2 * q + 2;
		j = l;
		if (p < nomerkuchi && t[p].edge < t[l].edge) {
			j = p;
		}
		if (t[q].edge <= t[j].edge) {
			break;
		}
		int y = t[j].v;
		long long h = t[j].edge;
		t[j].v = t[q].v;
		t[j].edge = t[q].edge;
		t[q].v = y;
		t[q].edge = h;
		q = j;
	}
}

void dobb(int v, long long edge) {
	t[nomerkuchi].v = v;
	t[nomerkuchi].edge = edge;
	SwiftUp(nomerkuchi);
	nomerkuchi++;
}

void deikstra(int v, Graf* graf, int n, trinochi* p) {
	if (graf[v].color == 'b') goto bbbb;
	graf[v].color = 'b';
	for (int i = 0; i < graf[v].n; i++) {
		if (graf[graf[v].arr[i].vertex].path >= (graf[v].path + graf[v].arr[i].ckoka) && graf[graf[v].arr[i].vertex].color == 'w') {
			dobb(graf[v].arr[i].vertex, (graf[v].path + graf[v].arr[i].ckoka));
			graf[graf[v].arr[i].vertex].path = graf[v].path + graf[v].arr[i].ckoka;
			p[graf[v].arr[i].vertex].nomerrebra = graf[v].arr[i].nomer;
			p[graf[v].arr[i].vertex].vertec = v;
		}
	}
bbbb:
	if (nomerkuchi != 0) {
		int y = t[0].v;
		t[0].v = t[nomerkuchi-1].v;
		t[0].edge = t[nomerkuchi-1].edge;
		nomerkuchi--;
		SwiftDown(0);
		deikstra(y, graf, n, p);
	}
	return;
}

int rec(trinochi* arrii, int v) {
	sum++;
	j = arrii[v].vertec;
	while (j != 0) {
		v = arrii[v].vertec;
		sum++;
		j = arrii[v].vertec;
	}
	return j;
}

int recc(trinochi* arrii, int v) {
	mas = (int*)realloc(mas, sizeof(int) * sum);
	int i = 0;
	j = arrii[v].vertec;
	while (j != 0) {
		mas[i] = arrii[v].nomerrebra;
		i++;
		v = arrii[v].vertec;
		j = arrii[v].vertec;
	}
	for (int i = sum - 2; i >= 0; i--) printf("%d ", mas[i]);
	return j;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n, m, k, otkuda, kuda, ckoka;
	int* arrn, * arrk;
	trinochi* p;
	sssss** arr;
	Graf* graf;
	scanf("%d %d %d", &n, &m, &k);
	graf = (Graf*)malloc(sizeof(Graf) * (n + 1));
	p = (trinochi*)malloc(sizeof(trinochi) * (n + 1));
	mas = (int*)malloc(sizeof(int) * (n + 1));
	t = (kucha*)malloc(sizeof(kucha) * (n + 10000));
	arrn = (int*)malloc(sizeof(int) * k);
	arrk = (int*)malloc(sizeof(int) * k);
	for (int i = 0; i < k; i++) scanf("%d %d", &arrn[i], &arrk[i]);
	for (int i = 0; i <= n; i++) {
		graf[i].arr = NULL;
		graf[i].path = 999999999;
		graf[i].color = 'w';
		graf[i].cap = 0;
		graf[i].n = 0;
		p[i].vertec = 0;
		p[i].nomerrebra = 0;
	}
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &otkuda, &kuda, &ckoka);
		if (otkuda == kuda) continue;
		if (graf[otkuda].cap == 0) {
			graf[otkuda].arr = realloc(graf[otkuda].arr, sizeof(sssss) * 2);
			graf[otkuda].cap = 2;
		}
		if (graf[otkuda].cap == graf[otkuda].n) {
			graf[otkuda].arr = realloc(graf[otkuda].arr, sizeof(sssss) * graf[otkuda].cap * 2);
			graf[otkuda].cap *= 2;
		}
		graf[otkuda].arr[graf[otkuda].n].ckoka = ckoka;
		graf[otkuda].arr[graf[otkuda].n].nomer = i + 1;
		graf[otkuda].arr[graf[otkuda].n].vertex = kuda;
		graf[otkuda].n++;
	}
	for (int i = 0; i < k; i++) {
		p[arrn[i]].vertec = 0;
		p[arrn[i]].nomerrebra = 0;
		graf[arrn[i]].path = 0;
		deikstra(arrn[i], graf, n, p);
		if (999999999 == graf[arrk[i]].path) printf("DOOMED\n");
		else {
			rec(p, arrk[i]);
			printf("quarantine  %lld %d  ", graf[arrk[i]].path, sum - 1);
			recc(p, arrk[i]);
			printf("\n");
		}
		for (int i = 1; i <= n; i++) {
			graf[i].path = 999999999;
			graf[i].color = 'w';
		}
		sum = 0;
		j = 0;
		nomerkuchi = 0;
	}
}