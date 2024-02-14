#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

double calc_length(double x0, double x1, double x2, double x3, double y0, double y1, double y2, double y3, double z0, double z1, double z2, double z3, double l, double r) {
    double step = 0.00000001;
    double length = 0;
    double prev_x = x0, prev_y = y0, prev_z = z0;
    for (double t = l; t < r; t += step) {
        double x = x0 + x1 * (t - l) + x2 * (t - l) * (t - l) + x3 * (t - l) * (t - l) * (t - l);
        double y = y0 + y1 * (t - l) + y2 * (t - l) * (t - l) + y3 * (t - l) * (t - l) * (t - l);
        double z = z0 + z1 * (t - l) + z2 * (t - l) * (t - l) + z3 * (t - l) * (t - l) * (t - l);
        double dx = x - prev_x, dy = y - prev_y, dz = z - prev_z;
        length += sqrt(dx * dx + dy * dy + dz * dz);
        prev_x = x, prev_y = y, prev_z = z;
    }
    return length;
}

int main() 
{
    FILE* in = fopen("input.txt", "r");
    FILE* out = fopen("output.txt", "w");
    int n;
    fscanf(in, "%d", &n);
    double length = 0;
    double prev_r = 0;
    for (int i = 0; i < n; i++) {
        double l, r, x0, x1, x2, x3, y0, y1, y2, y3, z0, z1, z2, z3;
        fscanf(in, "%lf %lf", &l, &r);
        fscanf(in, "%lf %lf %lf %lf", &x0, &x1, &x2, &x3);
        fscanf(in, "%lf %lf %lf %lf", &y0, &y1, &y2, &y3);
        fscanf(in, "%lf %lf %lf %lf", &z0, &z1, &z2, &z3);
        length += calc_length(x0, x1, x2, x3, y0, y1, y2, y3, z0, z1, z2, z3, prev_r, r);
        prev_r = r;
    }
    fprintf(out, "%.20lf\n", length);
    return 0;
}
