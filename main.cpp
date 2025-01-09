#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

//Sturct with all information about tasks
struct Task {
    std::string name;
    std::string description;
    std::string dateOfEnd;
    bool status = false;
};

//class for managing of the task
class taskManager {
private:
    std::vector<Task> task;

public:
    //add new task
    void addTask(const std::string& name, const std::string& description, const std::string& dateOfEnd);
    //remove task
    void removeTask(int index);
    //making task as completed
    void markStatusCompleted(int index);
    //show the list of tasks
    void showTasks() const;
    //getting private variable
    const std::vector<Task>& getTasks() const;
};


void menu(taskManager& manager);

int main() {
    //create new object
	taskManager manager;
   
    //reading a file with tasks
	std::ifstream inFile("data.csv");
	if(inFile.is_open())
	{
		int index = 0;
        	std::string line;
		while(std::getline(inFile, line))
		{
        		std::istringstream ss(line);
			std::string name, description, dataOfEnd;
	        	bool status;
	        	std::getline(ss, name, ',');
	        	std::getline(ss, description, ',');
	        	std::getline(ss, dataOfEnd, ',');
	        	ss >> status;
	        	manager.addTask(name, description, dataOfEnd);
	        	if(status)
	        	{
			       	manager.markStatusCompleted(index);
	    		}
	    		index++;
    		}
		inFile.close();
    	}
        else
		std::cout << "File could not be opened!\n";
	
    //start ptogramm
	menu(manager);

    //writting all information in file
	std::ofstream outFile("data.csv");
	if(outFile.is_open())
	{
		for(const auto& task : manager.getTasks())
		{
			outFile << task.name << "," << task.description << "," << task.dateOfEnd << "," << task.status << '\n';
		}
		outFile.close();
	}
	else
        	std::cout << "File could not be opened!\n";
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


const std::vector<Task>& taskManager::getTasks() const {
    return task;
}

void menu(taskManager& manager)
{
	int numOfAction = 0;
        std::cout << "Choose action: \n1 - add a new task\n2 - remove task\n3 - make as completed\n4 - show all tasks\n5 - exit\n";
        std::cin >> numOfAction;
	std::cin.ignore();


        std::string name;
        std::string description;
        std::string dateOfEnd;

        switch (numOfAction) {
            case 1:
                std::cout << "Write a name of task: \n";
                std::getline(std::cin, name);

                std::cout << "Write a desription: \n";
                std::getline(std::cin, description);

                std::cout << "Write a deadline (format: 24-12-2024): \n";
                std::getline(std::cin, dateOfEnd);
                std::cout << std::endl;

                manager.addTask(name, description, dateOfEnd);
		
		menu(manager);

                break;
            case 2:
                {std::cout << "Which task you want to remove?\n";

                int num;
                std::cin >> num;

                manager.removeTask(num - 1);
		
		menu(manager);

                break;}
            case 3:
                {std::cout << "Whick task you want to make as completed?\n";

                int num;
                std::cin >> num;

                manager.markStatusCompleted(num - 1);
		
		menu(manager);

                break;}
            case 4:
                manager.showTasks();

		menu(manager);

                break;
            case 5:
                std::cout << "Do you want to exit?\ny - yes, n - no\n";
		
		char exit;
                std::cin >> exit;

                if(exit == 'y')
			std::cout << "Thank for using this programm!" << std::endl;
                else if(exit == 'n')
                        menu(manager);
                else
		{
                        std::cout << "Write a valid symbol!" << std::endl;
			menu(manager);
		}

                break;
            default:
                std::cout << "Choose a valid number!" << std::endl;
		menu(manager);
	}
}
