#include <bits/stdc++.h>
using namespace std;

class Course
{
private:
    int max_degree;
    string instructor_name;
    string students[10];
    int no_of_enrolled_students;

public:
    Course()
    {
        max_degree = 100;
        instructor_name = "";
        no_of_enrolled_students = 0;
    }
    Course(int deg, string ins)
    {
        max_degree = deg;
        instructor_name = ins;
        no_of_enrolled_students = 0;
    }
    void set_max_degree(int degree)
    {
        max_degree = degree;
    }
    int get_max_degree()
    {
        return max_degree;
    }
    void add_student(string name)
    {
        students[no_of_enrolled_students] = name;
        no_of_enrolled_students++;
    }
};

int main(void)
{

    // // Dynamic Allocation for variables & Arrays

    // // In the Stack
    // int a = 15;

    // // In the Heap
    // int *p_a;
    // p_a = new int;
    // *p_a = 15;

    // cout << *p_a << "\n";

    // // Equivalent
    // delete p_a;
    // delete (p_a);
    // // ------------------------------------

    int *arr;
    arr = new int[sizeof(int) * 10000000];
    cout << arr[15];
    // [] for releasing memory of an Array
    delete[](arr);
    cout << "DONE";
    // ------------------------------------

    // // Pointer to Void
    // int x = 190;
    // void *p_v = &x;
    // cout << *((int *)p_v) << "\n";
    // // ------------------------------------

    // // Basics Of Classes
    // Course c1;
    // Course c2(150, "Usama");
    // c1.set_max_degree(150);
    // cout << c1.get_max_degree() << "\n";

    // // Dynamic Allocation With Classes
    // Course *c3;
    // Course *c4 = new Course();
    // c3 = new Course();
    // c3->set_max_degree(1400);

    // Course *p_c1 = &c1;
    // cout << p_c1->get_max_degree() << "\n";

    // // Arrow Operator
    // cout << c3->get_max_degree() << "\n";
    // cout << (*c3).get_max_degree() << "\n";
    // // // ------------------------------------

    // // Deleting an array of objects
    // Course *courses = new Course[sizeof(Course) * 30];

    // for (int i = 0; i < 30; i++)
    // {
    //     courses[i].set_max_degree(i * 13);
    //     cout << courses[i].get_max_degree() << "\n";
    // }
    // delete[] courses;

    // // Case 1: No Deletion:
    // // Lost + no Errors

    // // Case 2: delete:
    // // Lost + Error

    // // Case 3: delete[]:
    // // no loss + no Errors

    // Array Initialization

    // // Case1: Garbage
    // int arr[3];
    // for (int i = 0; i < 4; i++)
    // {
    //     cout << arr[i] << " ";
    // }
    // cout << "\n";

    // // Case2: Curly Braces zerofy!
    // int arr[3] = {1, 2};
    // for (int i = 0; i < 4; i++)
    // {
    //     cout << arr[i] << " ";
    // }
    // cout << "\n";

    // // Case3: int arr[3] outside the main(Global): first 3 are zeros
    // // int arr[3]
    // // int main (void){
    ////  blablabla
    // // }

    // // Case4: Segmentation fault (by far outside the limits)
    // int arr[3] = {1, 2};
    // for (int i = 0; i < 10000; i++)
    // {
    //     cout << arr[i] << " ";
    // }
    // cout << "\n";
}