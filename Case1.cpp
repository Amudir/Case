
#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

struct Assignment {
    string name;         
    string deadline;     
    bool isCompleted;    
};


void showSchedule(const vector<Assignment>& assignments) {
    setlocale(LC_ALL, "RUS");
    cout << "Расписание домашних заданий:" << endl;
    for (const auto& assignment : assignments) {
        cout << assignment.name << " - Дедлайн: " << assignment.deadline;
        if (assignment.isCompleted) {
            cout << " (Выполнено)";
        }
        else {
            cout << " (Не выполнено)";
        }
        cout << endl;
    }
}

void addAssignment(vector<Assignment>& assignments) {
    setlocale(LC_ALL, "RUS"); 
    Assignment newAssignment;
    cout << "Введите название задания: ";
    cin.ignore(); 
    getline(cin, newAssignment.name);
    cout << "Введите дедлайн задания (формат: YYYY-MM-DD): ";
    cin >> newAssignment.deadline;
    newAssignment.isCompleted = false;
    assignments.push_back(newAssignment);
}


void markAsCompleted(vector<Assignment>& assignments) {
    setlocale(LC_ALL, "RUS"); 
    string assignmentName;
    cout << "Введите название задания, которое хотите отметить как выполненное: ";
    cin.ignore(); 
    getline(cin, assignmentName);

    bool found = false;
    for (auto& assignment : assignments) {
        if (assignment.name == assignmentName) {
            assignment.isCompleted = true;
            cout << "Задание \"" << assignment.name << "\" отмечено как выполненное." << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Задание не найдено!" << endl;
    }
}


void showStatistics(const vector<Assignment>& assignments) {
    int totalAssignments = assignments.size();
    int completedAssignments = 0;
    setlocale(LC_ALL, "RUS"); 

    for (const auto& assignment : assignments) {
        if (assignment.isCompleted) {
            completedAssignments++;
        }
    }

    cout << "Статистика успеваемости:" << endl;
    cout << "Всего заданий: " << totalAssignments << endl;
    cout << "Выполнено заданий: " << completedAssignments << endl;
    if (totalAssignments > 0) {
        double successRate = (double)completedAssignments / totalAssignments * 100;
        cout << "Процент выполненных заданий: " << successRate << "%" << endl;
    }
    else {
        cout << "Нет заданий в расписании." << endl;
    }
}


void remindAboutDeadlines(const vector<Assignment>& assignments) {
    time_t now = time(0);
    tm tstruct = {};
    setlocale(LC_ALL, "RUS"); 
  
    localtime_s(&tstruct, &now);

    
    char buf[11];
    strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);
    string currentDate(buf);

    cout << "\nНапоминания о ближайших дедлайнах:" << endl;
    for (const auto& assignment : assignments) {
        if (!assignment.isCompleted && assignment.deadline >= currentDate) {
            cout << "Задание \"" << assignment.name << "\" с дедлайном " << assignment.deadline << endl;
        }
    }
}

int main() {
    vector<Assignment> assignments;
    setlocale (LC_ALL, "RUS");
    int choice;

    while (true) {
        cout << "\nМеню:" << endl;
        cout << "1. Показать расписание" << endl;
        cout << "2. Добавить задание" << endl;
        cout << "3. Отметить задание как выполненное" << endl;
        cout << "4. Показать статистику успеваемости" << endl;
        cout << "5. Напомнить о дедлайнах" << endl;
        cout << "6. Выйти" << endl;
        cout << "Введите номер действия: ";
        cin >> choice;

        switch (choice) {
        case 1:
            showSchedule(assignments);
            break;
        case 2:
            addAssignment(assignments);
            break;
        case 3:
            markAsCompleted(assignments);
            break;
        case 4:
            showStatistics(assignments);
            break;
        case 5:
            remindAboutDeadlines(assignments);
            break;
        case 6:
            cout << "Выход из программы..." << endl;
            return 0;
        default:
            cout << "Неверный выбор, попробуйте снова." << endl;
        }
    }

    return 0;
}
