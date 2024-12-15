#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
    double x, y;
} Point;

#define MAX 101 // Include (0,0)

Point points[MAX];
Point hull[MAX];

double cross(Point, Point, Point);
double distance(Point, Point);
int comparePoints(const void *, const void *);
void grahamScan(Point[], int, double *);

int main(void)
{

    int numCase;
    int numPoints;

    FILE *fp;
    fp = fopen("input.txt", "r");

    if (fp == NULL)
    {
        puts("input.txt could not be opened");
        exit(1);
    }

    fscanf(fp, "%d", &numCase);
    fgetc(fp);

    for (int i = 0; i < numCase; i++)
    {

        fscanf(fp, "%d", &numPoints);

        // Setting (0, 0) as the first point.
        points[0].x = 0.0;
        points[0].y = 0.0;

        for (int j = 1; j < numPoints + 1; j++)
        {
            // The first dimension is north/south and the second dimension is east/west
            fscanf(fp, "%lf %lf", &points[j].y, &points[j].x);
        }

        double len = 0;
        grahamScan(points, numPoints + 1, &len);

        printf("%.2lf\n", len + 2.0); // one extra meter at each end to tie it
        if (i < numCase - 1)
        {
            printf("\n");
            fgetc(fp);
        }
    }

    fclose(fp);
    return 0;
}

// Calculates the cross product of three points a, b, and c to check if point c is to the left of point b with respect to point a.
double cross(Point a, Point b, Point c)
{
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

// Calculates the distance using the Pythagorean theorem.
double distance(Point a, Point b)
{
    return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

// Measure the angle from the reference point in a counter-clockwise direction and pass it to qsort.
int comparePoints(const void *a, const void *b)
{
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    double angleA = atan2(p1->y - points[0].y, p1->x - points[0].x);
    double angleB = atan2(p2->y - points[0].y, p2->x - points[0].x);
    return (angleA < angleB) ? -1 : (angleA > angleB) ? 1
                                                      : 0;
}

// use the grahamScan
void grahamScan(Point points[], int n, double *length)
{
    int k = 0;
    int minY = 0;

    for (int i = 1; i < n; i++)
    {
        if (points[i].y < points[minY].y || (points[i].y == points[minY].y && points[i].x < points[minY].x))
        {
            minY = i;
        }
    }

    Point temp = points[1];
    points[1] = points[minY];
    points[minY] = temp;

    // sorting the points
    qsort(points + 2, n - 2, (sizeof(Point)), comparePoints);

    for (int i = 0; i < n; i++)
    {
        while (k >= 2 && cross(hull[k - 2], hull[k - 1], points[i]) <= 0)
        {
            k--;
        }
        hull[k++] = points[i];
    }

    *length = 0;
    for (int i = 0; i < k; i++)
    {
        *length += distance(hull[i], hull[(i + 1) % k]);
    }
}
