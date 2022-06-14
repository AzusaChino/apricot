#include <iostream>
#include <fcntl.h>

using namespace std;

int main(int argc, char **argv)
{
    FILE *f;
    if (argc != 2)
    {
        cout << "wrong usage, please provide only one filename" << endl;
        return -1;
    }

    f = fopen("foo.txt", O_RDONLY);
    if (!f)
    {
        cout << "failed to open file"
             << "foo.txt" << endl;
        return -1;
    }

    return 0;
}
