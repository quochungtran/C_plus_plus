// list of students
// sort the list based on two criterias:
// - student who have higher score 
// - student whose equal scores, priority the id
#include <iostream>


struct Student{
    int id;
    double score;
};

bool option(const& Student A, const& Student B)
{
    if (A.score > B.score || (A.score == B.score && A.id == B.id))
    {
        return true;
    }

    return false;
}

int main()
{
    vector<int> list_students;
    list_student.push_back({100, 8.5});
    list_student.push_back({101, 7.5});
    list_student.push_back({102, 8.5});
    list_student.push_back({103, 10});
    list_student.push_back({104, 4.5});

    sort(list_students.begin(), list_student.end(), option); // decreasing order
    for (auto& etu : list_students)
    {
        cout << etu.id << " " << etu.score << endl;
    }

    return 0; 
}