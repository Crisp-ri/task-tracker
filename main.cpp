#include <iostream>
#include <vector>
#include <string>

struct Task {
    std::string name;
    std::string description;
    std::string dateOfEnd;
    bool status = false;
};

class taskManager {
private:
    std::vector<Task> task;

public:
    void addTask(const std::string& name, const std::string& description, const std::string& dateOfEnd);
    void removeTask(int index);
    void markStatusCompleted(int index);
    void showTasks() const;
};

int main() {
    taskManager manager;
    bool isOpen = true;
    while (isOpen) {
        int numOfAction = 0;
        std::cout << "Choose action: \n1 - add a new task\n2 - remove task\n3 - make as completed\n4 - show all tasks\n5 - exit\n";
        std::cin >> numOfAction;

        std::string name;
        std::string description;
        std::string dateOfEnd;

        switch (numOfAction) {
            case 1:
		std::cout << "Write a name of task: \n";
                std::cin >> name;
		std::cout << "Write a desription: \n";
		std::cin.ignore();
		std::getline(std::cin, description);
		std::cout << "Write a deadline: \n";
		std::getline(std::cin, dateOfEnd);
		std::cout << std::endl;
                manager.addTask(name, description, dateOfEnd);
                break;
            case 2:
		{std::cout << "Which task you want to remove?\n";
		int num;
		std::cin >> num;
		manager.removeTask(num - 1);
                break;}
            case 3:
		{std::cout << "Whick task you want to make as completed?\n";
		int num;
		std::cin >> num;
		manager.markStatusCompleted(num - 1);
                break;}
            case 4:
                manager.showTasks();
                break;
	    case 5:
		std::cout << "Do you want to exit?\ny - yes, n - no\n";
		char exit;
		std::cin >> exit;
		if(exit == 'y')
			isOpen = false;
		else if(exit == 'n')
			isOpen = true;
		else
			std::cout << "Write a valid symbol!" << std::endl;
		break;
            default:
                std::cout << "Choose a valid number!" << std::endl;
        }
    }
    return 0;
}

void taskManager::addTask(const std::string& name, const std::string& description, const std::string& dateOfEnd) {
    task.push_back({name, description, dateOfEnd});
}

void taskManager::removeTask(int index) {
    if (index >= 0 && index < task.size()) {
        task.erase(task.begin() + index);
    } else {
        std::cout << "Choose the correct index!" << std::endl;
    }
}

void taskManager::markStatusCompleted(int index) {
    if (index >= 0 && index < task.size()) {
        task[index].status = true;
    } else {
        std::cout << "Choose the correct index!" << std::endl;
    }
}

void taskManager::showTasks() const {
    for (int i = 0; i < task.size(); i++) {
        std::cout << std::to_string(i + 1) << " " << task[i].name << std::endl;
        std::cout << task[i].description << std::endl;
        std::cout << "Date of finishing: " << task[i].dateOfEnd << std::endl;
        if (task[i].status == true)
            std::cout << "Task is completed!" << std::endl;
	std::cout << std::endl;
    }
}

