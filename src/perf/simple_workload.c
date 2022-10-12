void real_work(int *a, int *b)
{
    *b = (*a) * (*a);
    *b -= *a * 100;
    *b += (*a) * (*a) * (*a) / 100;
}

void workload1()
{
    int i, c = 0;
    for (i = 0; i < 10000000; i++)
    {
        real_work(&i, &c);
    }
}

void workload2()
{
    int i, c = 0;
    for (i = 0; i < 20000000; i++)
    {
        real_work(&i, &c);
    }
}


// 1. gcc sample.c -g -o sample (using -g to get function name for perf)
// 2. sudo perf record -g ./sample sleep 10
// 3. perf report -g
int main(int argc, char *argv[])
{
    workload1();
    workload2();
    return 0;
}