#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
using namespace std;

const int MAX_MENU_ITEM = 9; //Максимален брой опции в менюто.
const int MAX_DISCIPLINES = 5; //Максимален брой дисциплини.
const int MAX_STUDENTS = 30; //Максимален брой студенти.

//Дефинираме структурите преди да ги използваме.
struct Discipline
{
	string disciplineName; //Име на дисциплината.
	int grade; //Оценка по дисциплината.
};

struct Student
{
	string facultyNumber; //Факултетен номер на студента.
	string personalID; //ЕГН на студента.
	string sName; //Три имена на студента.
	Discipline disciplines[MAX_DISCIPLINES]; //Дисциплините на студента.
	char gender; //Полът на студента (Мъжки, Женски).
	int age; //Възрастта на студента.
	string status; //Статута на студента (Активен, Прекъснал, Завършил).
	float averageGrade; //Среден успех на студента.
};

//Дефинираме функциите преди да ги използваме.
int Menu();
void Dobavi_Student(Student students[], int &numStudents); //Използваме &numStudents, за да можем да променяме стойността на променливата numStudents.
void Izvedi_Student(Student students[], int numStudents);
void Tursi_Student(Student students[], int numStudents); 
void Sortiray_Student(Student students[], int numStudents); 
void Vunshen_Fayl(Student students[], int &numStudents); //Използваме &numStudents, за да можем да променяме стойността на променливата numStudents.
void Otdelqne_Studenti(Student students[], int numStudents);
void VavezhdaneAktualizaciq_Ocenki_SredenUspeh(Student students[], int numStudents);
void Smqna_Statut(Student students[], int numStudents);

int main()
{
	Student students[MAX_STUDENTS];
	int numStudents = 0;
	int menuItem = 0;
	ifstream inFile;
	inFile.open("Input_Output.txt");
	if (inFile.fail()) //Проверяваме дали файла е отворен успешно.
	{
		cout << "Faila ne moje da bude otvoren!\n";
		system("pause");
		system("cls");
	}
	else
	{
		while (numStudents < MAX_STUDENTS && getline(inFile, students[numStudents].sName, '\n'))
		{
			getline(inFile, students[numStudents].facultyNumber, '\n');
			getline(inFile, students[numStudents].personalID, '\n');
			inFile >> students[numStudents].gender;
			inFile >> students[numStudents].age;
			inFile.ignore();
			getline(inFile, students[numStudents].status, '\n');
			for (int j = 0; j < MAX_DISCIPLINES; j++)
			{
				getline(inFile, students[numStudents].disciplines[j].disciplineName, ',');
				inFile >> students[numStudents].disciplines[j].grade;
				inFile.ignore();
			}
			inFile.ignore();
			numStudents++;
		}
	}
	inFile.close();
	do
	{
		menuItem = Menu();
		system("cls");
		switch (menuItem)
		{
		case 1:
			Dobavi_Student(students, numStudents);
			break;
		case 2:
			Izvedi_Student(students, numStudents);
			break;
		case 3:
			Tursi_Student(students, numStudents);
			break;
		case 4:
			Sortiray_Student(students, numStudents);
			break;
		case 5:
			Vunshen_Fayl(students, numStudents);
			break;
		case 6:
			Otdelqne_Studenti(students, numStudents);
			break;
		case 7:
			VavezhdaneAktualizaciq_Ocenki_SredenUspeh(students, numStudents);
			break;
		case 8:
			Smqna_Statut(students, numStudents);
			break;
		case 9:
			ofstream outFile;
			outFile.open("Input_Output.txt");
			if (outFile.fail()) //Проверяваме дали файла е отворен успешно.
			{
				cout << "Faila ne moje da bude otvoren!\n";
				system("pause");
				system("cls");
			}
			else
			{
				for (int i = 0; i < numStudents; i++)
				{
					outFile << students[i].sName << "\n"
						<< students[i].facultyNumber << "\n"
						<< students[i].personalID << "\n"
						<< students[i].gender << "\n"
						<< students[i].age << "\n"
						<< students[i].status << "\n";
					for (int j = 0; j < MAX_DISCIPLINES; j++)
					{
						outFile << students[i].disciplines[j].disciplineName << ","
							<< students[i].disciplines[j].grade << "\n";
					}
					outFile << "\n";
				}
			}
			outFile.close();
			cout << "Krai na programata!\n";
			system("pause");
			system("cls");
			break;
		}
	} while (menuItem < MAX_MENU_ITEM);
	return 0;
}

int Menu()
{
	int Selection = 0;
	cout << endl << "Menu";
	cout << endl << "1. Dobavqne na studenti.";
	cout << endl << "2. Izvezhdane na studenti.";
	cout << endl << "3. Tursene i izvezhdane na studenti.";
	cout << endl << "4. Sortirane i izvezhdane na stundenti.";
	cout << endl << "5. Rabota s vunshen fayl.";
	cout << endl << "6. Otdelqne na studenti.";
	cout << endl << "7. Vavezhdane, aktualizaciq na ocenki i sreden uspeh.";
	cout << endl << "8. Smqna na statut na student.";
	cout << endl << "9. Krai na programata.";
	do
	{
		cout << endl << "Izberete funkciq: ";
		cin >> Selection;
	} while (Selection < 1 || Selection > MAX_MENU_ITEM);
	return Selection;
}

void Dobavi_Student(Student students[], int &numStudents)
{
	int studentsToAdd; //Брой студенти, които искаме да добавим.
	do
	{
		cout << "Vavedete kolko studenta iskate da dobavite: ";
		cin >> studentsToAdd;
		if (studentsToAdd >= 1 && studentsToAdd <= MAX_STUDENTS - numStudents)
		{
			system("cls");
			break;
		}
		else if (studentsToAdd >= 1 && MAX_STUDENTS - numStudents == 0)
		{
			cout << "Nqma dostatuchno mqsto za novi studenti!\n";
			system("pause");
			system("cls");
			break;
		}
		else
		{
			cout << "Vavedete validen broi studenti!\n";
		}
	} while (true);
	/*Проверяваме дали има достатъчно място в масива за студенти.
	Използваме numStudents + studentsToAdd, за да не презаписваме старите студенти.*/ 
	for (int i = numStudents; i < numStudents + studentsToAdd && i < MAX_STUDENTS; i++)
	{
		do
		{
			cout << "Vavedete fakultetniq nomer na stundenta: ";
			cin >> students[i].facultyNumber;
			if (students[i].facultyNumber.length() == 8) //Проверяваме дали факултетния номер е с дължина 8.
			{
				bool isUnique = true;
				for (int j = 0; j < numStudents; j++)
				{
					if (students[i].facultyNumber == students[j].facultyNumber)
					{
						isUnique = false;
						break;
					}
				}
				if (isUnique)
				{
					system("cls");
					break;
				}
				else
				{
					cout << "Vavedete unikalen fakulteten nomer!\n";
				}
			}
			else
			{
				cout << "Vavedete validen fakulteten nomer!\n";
			}
		} while (true);
		do
		{
			cout << "Vavedete EGN na studenta: ";
			cin >> students[i].personalID;
			if (students[i].personalID.length() == 10) //Проверяваме дали ЕГН-то е с дължина 10.
			{
				bool isUnique = true;
				for (int j = 0; j < numStudents; j++)
				{
					if (students[i].personalID == students[j].personalID)
					{
						isUnique = false;
						break;
					}
				}
				if (isUnique)
				{
					system("cls");
					break;
				}
				else
				{
					cout << "Vavedete unikalno EGN!\n";
				}
			}
			else
			{
				cout << "Vavedete validno EGN!\n";
			}
		} while (true);
		cin.ignore(); //Използваме cin.ignore(), за да пропуснем символа за нов ред, който се запазва в буфера след използването на cin.
		cout << "Vavedete tri imena na studenta: ";
		getline(cin, students[i].sName);
		for (int j = 0; j < MAX_DISCIPLINES; j++)
		{
			cout << "Vavedete ime na " << j << ". Disiplina: ";
			cin >> students[i].disciplines[j].disciplineName;
			students[i].disciplines[j].grade = 0; //Инициализираме оценката на дисциплината с 0.
		}
		do
		{
			cout << "Vavedete pol na studenta (M ili F): ";
			cin >> students[i].gender;
			if (students[i].gender == 'M' || students[i].gender == 'F')
			{
				system("cls");
				break;
			}
			else
			{
				cout << "Vavedete validen simvol za pol! (M ili F)!\n";
			}
		} while (true);
		do
		{
			cout << "Vavedete vuzrastta na studenta: ";
			cin >> students[i].age;
			if (students[i].age >= 18 && students[i].age <= 100)
			{
				system("cls");
				break;
			}
			else
			{
				cout << "Vavedete validna vuzrast!\n";
			}
		} while (true);
		do
		{
			cout << "Vavedete statut na studenta (Aktiven, Prekusnal, Zavurshil): ";
			cin >> students[i].status;
			if (students[i].status == "Aktiven" || students[i].status == "Prekusnal" || students[i].status == "Zavurshil")
			{
				system("cls");
				break;
			}
			else
			{
				cout << "Vavedete validen statut! (Aktiven, Prekusnal, Zavurshil)!\n";
			}
		} while (true);
	}
	numStudents += studentsToAdd; //Увеличаваме броя студенти с броя студенти, които сме добавили.
}

void Izvedi_Student(Student students[], int numStudents)
{
	//Използваме setw(), за да зададем широчината на колоните.
	cout << setw(30) << "Tri Imena"
		<< setw(30) << "Fakulteten Nomer"
		<< setw(20) << "EGN"
		<< setw(15) << "Pol"
		<< setw(10) << "Vuzrast"
		<< setw(15) << "Statut"
		<< endl;
	cout << endl << setfill('-') << setw(120) << " " << setfill(' ') << endl; //Използваме setfill(), за да запълним реда с тирета.
	for (int i = 0; i < numStudents; i++)
	{
		cout << endl << setw(30) << students[i].sName
			<< setw(30) << students[i].facultyNumber
			<< setw(20) << students[i].personalID
			<< setw(15) << students[i].gender
			<< setw(10) << students[i].age
			<< setw(15) << students[i].status
			<< endl;
	}
}

void Tursi_Student(Student students[], int numStudents)
{
	int Selection = 0;
	do
	{
		cout << endl << "Tursene i izvezhdane na studenti.";
		cout << endl << "1. Tursene na studenti s ocenka po BP v interval.";
		cout << endl << "2. Tursene na studenti s slaba ocenka.";
		cout << endl << "3. Nazad.";
		cout << endl << "Izberete funkciq: ";
		cin >> Selection;
		if (Selection == 1)
		{
			int min, max;
			cout << "Vavedete min: ";
			cin >> min;
			cout << "Vavedete max: ";
			cin >> max;
			system("cls");
			cout << setw(30) << "Tri Imena"
				<< setw(30) << "Fakulteten Nomer"
				<< setw(20) << "EGN"
				<< setw(25) << "Disiplina"
				<< setw(15) << "Ocenka"
				<< endl;
			cout << endl << setfill('-') << setw(120) << " " << setfill(' ') << endl;
			for (int i = 0; i < numStudents; i++)
			{
				for (int j = 0; j < MAX_DISCIPLINES; j++)
				{
					//Проверяваме дали имаме дисциплина с име "BP" и оценка в интервала [min, max].
					if (students[i].disciplines[j].disciplineName == "BP" && students[i].disciplines[j].grade >= min && students[i].disciplines[j].grade <= max)
					{
						cout << endl << setw(30) << students[i].sName
							<< setw(30) << students[i].facultyNumber
							<< setw(20) << students[i].personalID
							<< setw(25) << students[i].disciplines[j].disciplineName
							<< setw(15) << students[i].disciplines[j].grade
							<< endl;
					}
				}
			}

		}
		else if (Selection == 2)
		{
			system("cls");
			cout << setw(30) << "Tri Imena"
				<< setw(30) << "Fakulteten Nomer"
				<< setw(20) << "EGN"
				<< setw(25) << "Disiplina"
				<< setw(15) << "Ocenka"
				<< endl;
			cout << endl << setfill('-') << setw(120) << " " << setfill(' ') << endl;
			for (int i = 0; i < numStudents; i++)
			{
				for (int j = 0; j < MAX_DISCIPLINES; j++)
				{
					//Проверяваме дали имаме дисциплина с оценка 2.
					if (students[i].disciplines[j].grade == 2)
					{
						cout << endl << setw(30) << students[i].sName
							<< setw(30) << students[i].facultyNumber
							<< setw(20) << students[i].personalID
							<< setw(25) << students[i].disciplines[j].disciplineName
							<< setw(15) << students[i].disciplines[j].grade
							<< endl;
					}
				}
			}
		}
		else if (Selection == 3)
		{
			system("cls"); 
		}
		else
		{
			system("cls"); 
			cout << "Vavedete validen izbor!\n";
		}
	} while (Selection != 3); 
}

void Sortiray_Student(Student students[],int numStudents)
{
	bool isSorted = false;
	Student temp; //Използваме temp, за да разменяме стойностите на две променливи.
	for (int i = 0; i < numStudents - 1; i++)
	{
		isSorted = true; //Предполагаме, че масива е сортиран.
		for (int j = 0; j < numStudents - i - 1; j++) //Използваме numStudents - i - 1, за да не сортираме вече сортирани елементи.
		{
			if (students[j].sName > students[j + 1].sName)
			{
				temp = students[j];
				students[j] = students[j + 1];
				students[j + 1] = temp;
				isSorted = false; //Ако има размяна, значи масива не е сортиран.
			}
		}
		if (isSorted == true) //Ако масива е сортиран, излизаме от цикъла.
		{
			break;
		}
	}
	Izvedi_Student(students, numStudents);
}

void Vunshen_Fayl(Student students[], int &numStudents)
{
	int Selection = 0;
	do
	{
		cout << endl << "Rabota s vunshen fayl.";
		cout << endl << "1. Izvezhdane na masiva sus studenti v fayl.";
		cout << endl << "2. Vavezhdane na masiva ot fayl";
		cout << endl << "3. Nazad.";
		cout << endl << "Izberete funkciq: ";
		cin >> Selection;
		if (Selection == 1)
		{
			ofstream outFile;
			outFile.open("Input_Output.txt");
			if (outFile.fail()) //Проверяваме дали файла е отворен успешно.
			{
				cout << "Faila ne moje da bude otvoren!\n";
				system("pause");
				system("cls");
				break;
			}
			for (int i = 0; i < numStudents; i++)
			{
				outFile << students[i].sName << "\n"
					<< students[i].facultyNumber << "\n"
					<< students[i].personalID << "\n"
					<< students[i].gender << "\n"
					<< students[i].age << "\n"
					<< students[i].status << "\n";
				for (int j = 0; j < MAX_DISCIPLINES; j++)
				{
					outFile << students[i].disciplines[j].disciplineName << ","
						<< students[i].disciplines[j].grade << "\n";
				}
				outFile << "\n";
			}
			cout << "Izvezhdaneto e uspeshno!\n";
			system("pause");
			system("cls");
			outFile.close();
		}
		else if (Selection == 2)
		{
			ifstream inFile;
			inFile.open("Input_Output.txt");
			if (inFile.fail()) //Проверяваме дали файла е отворен успешно.
			{
				cout << "Faila ne moje da bude otvoren!\n";
				system("pause");
				system("cls");
				break;
			}
			while (numStudents < MAX_STUDENTS && getline(inFile, students[numStudents].sName, '\n'))
			{
				getline(inFile, students[numStudents].facultyNumber, '\n');
				getline(inFile, students[numStudents].personalID, '\n');
				inFile >> students[numStudents].gender;
				inFile >> students[numStudents].age;
				inFile.ignore();
				getline(inFile, students[numStudents].status, '\n');
				for (int j = 0; j < MAX_DISCIPLINES; j++)
				{
					getline(inFile, students[numStudents].disciplines[j].disciplineName, ',');
					inFile >> students[numStudents].disciplines[j].grade;
					inFile.ignore();
				}
				inFile.ignore();
				numStudents++;
			}
			if (MAX_STUDENTS - numStudents == 0)
			{
				cout << "Nqma dostatuchno mqsto za novi studenti!\n";
				system("pause");
				system("cls");
				break;
			}
			else
			{
				cout << "Vavezhdaneto e uspeshno!\n";
				system("pause");
				system("cls");
			}
			inFile.close();
		}
		else if  (Selection == 3)
		{
			system("cls");
		}
		else
		{
			system("cls");
			cout << "Vavedete validen izbor!\n";
		}
	} while (Selection != 3);
}

void Otdelqne_Studenti(Student students[], int numStudents)
{
	int Selection = 0;
	do
	{
		cout << endl << "Otdelqne na Studenti";
		cout << endl << "1. Otedlqne na studenti s opredelen statut i sortirane po Fakulteten nomer.";
		cout << endl << "2. Otdelqne na studenti s uspeh v interval i sortirane po EGN.";
		cout << endl << "3. Nazad.";
		cout << endl << "Izberete funkciq: ";
		cin >> Selection;
		if (Selection == 1)
		{
			bool isSorted = true;
			Student temp;
			string separateStatus;
			do
			{
				cout << "Vavedete statut (Aktiven, Prekusnal, Zavurshil): ";
				cin >> separateStatus;
				if (separateStatus == "Aktiven")
				{
					break;
				}
				else if (separateStatus == "Prekusnal")
				{
					break;
				}
				else if (separateStatus == "Zavurshil")
				{
					break;
				}
				else
				{
					cout << "Vavedete validen statut! (Aktiven, Prekusnal, Zavurshil)!\n";
				}
			} while (true);
			
			for (int i = 0; i < numStudents - 1; i++)
			{
				isSorted = false;
				for (int j = 0; j < numStudents - i - 1; j++)
				{
					if (students[j].facultyNumber > students[j + 1].facultyNumber)
					{
						temp = students[j];
						students[j] = students[j + 1];
						students[j + 1] = temp;
						isSorted = true; 
					}
				}
				if (isSorted == false)
				{
					break;
				}
			}
			cout << setw(30) << "Tri Imena"
				<< setw(30) << "Fakulteten Nomer"
				<< setw(20) << "EGN"
				<< setw(15) << "Pol"
				<< setw(10) << "Vuzrast"
				<< setw(15) << "Statut"
				<< endl;
			cout << endl << setfill('-') << setw(120) << " " << setfill(' ') << endl;
			for (int i = 0; i < numStudents; i++)
			{
				if (students[i].status == separateStatus)
				{
					cout << endl << setw(30) << students[i].sName
						<< setw(30) << students[i].facultyNumber
						<< setw(20) << students[i].personalID
						<< setw(15) << students[i].gender
						<< setw(10) << students[i].age
						<< setw(15) << students[i].status
						<< endl;
					
				}
			}
		}
		else if (Selection == 2)
		{
			bool isSorted = true;
			Student temp;
			float min, max;
			cout << "Vavedete min: ";
			cin >> min;
			cout << "Vavedete max: ";
			cin >> max;
			system("cls");
			for (int i = 0; i < numStudents - 1; i++)
			{
				isSorted = false;
				for (int j = 0; j < numStudents - i - 1; j++)
				{
					if (students[j].personalID > students[j + 1].personalID)
					{
						temp = students[j];
						students[j] = students[j + 1];
						students[j + 1] = temp;
						isSorted = true;
					}
				}
				if (isSorted == false)
				{
					break;
				}
			}
			cout << setw(30) << "Tri Imena"
				<< setw(30) << "Fakulteten Nomer"
				<< setw(20) << "EGN"
				<< setw(25) << "Sreden Uspeh"
				<< endl;
			cout << endl << setfill('-') << setw(105) << " " << setfill(' ') << endl;
			for (int i = 0; i < numStudents; i++)
			{
				if (students[i].averageGrade >= min && students[i].averageGrade <= max)
				{
					cout << endl << setw(30) << students[i].sName
						<< setw(30) << students[i].facultyNumber
						<< setw(20) << students[i].personalID
						<< setw(25) << students[i].averageGrade
						<< endl;
				}
			}
		}
		else if (Selection == 3)
		{
			system("cls");
		}
		else
		{
			system("cls");
			cout << "Vavedete validen izbor!\n";
		}
	} while (Selection != 3);
}

void VavezhdaneAktualizaciq_Ocenki_SredenUspeh(Student students[], int numStudents)
{
	string facultyNumberToSearch, disciplineName;
	bool isFound = false;
	do
	{
		cout << "Vavedete fakultetniq nomer na stundenta: ";
		cin >> facultyNumberToSearch;;
		if (facultyNumberToSearch.length() == 8) //Проверяваме дали факултетния номер е с дължина 8.
		{
			system("cls");
			break;
		}
		else
		{
			cout << "Vavedete validen fakulteten nomer!\n";
		}
	} while (true);
	for (int i = 0; i < numStudents; i++)
	{
		if (facultyNumberToSearch == students[i].facultyNumber && students[i].status == "Aktiven")
		{
			isFound = true;
			cout << setw(10) << "Disiplina"<< setw(20) << "Ocenka" << endl;
			cout << endl << setfill('-') << setw(35) << " " << setfill(' ') << endl;
			for (int j = 0; j < MAX_DISCIPLINES; j++)
			{
				
					cout << setw(10) << students[i].disciplines[j].disciplineName
					<< setw(20) << students[i].disciplines[j].grade << endl;
				
			}
			cout << endl;
			cout << "Vavedete ime na disiplina: ";
			cin >> disciplineName;
			for (int j = 0; j < MAX_DISCIPLINES; j++)
			{
				if (disciplineName == students[i].disciplines[j].disciplineName && students[i].disciplines[j].grade == 0)
				{
					int noGrade = 0;
					do
					{
						cout << "Vavedete ocenka: ";
						cin >> students[i].disciplines[j].grade;
						if (students[i].disciplines[j].grade == 0)
						{
							break;
						}
						else if (students[i].disciplines[j].grade >= 2 && students[i].disciplines[j].grade <= 6)
						{
							break;
						}
						else
						{
							cout << "Vavedete validna ocenka!\n";
						}
					} while (true);
					float sum = 0;
					for (int k = 0; k < MAX_DISCIPLINES; k++)
					{
						if (students[i].disciplines[k].grade == 0)
						{
							noGrade++;
						}
						sum += students[i].disciplines[k].grade;
					}
					students[i].averageGrade = sum / (MAX_DISCIPLINES - noGrade);
					//Използваме fixed и setprecision(), за да зададем, точността на средния успех.
					cout << "Sreden uspeh: " << fixed << setprecision(2) << students[i].averageGrade << endl;
					system("pause");
					system("cls");
					break;
				}
				else if (disciplineName == students[i].disciplines[j].disciplineName)
				{
					string choice;
					do
					{
						cout << "Sigurni li ste che iskate da promenite ocenkata na studenta? (Da ili Ne): ";
						cin >> choice;
						if (choice != "Da" && choice != "Ne")
						{
							cout << "Vavedete (Da ili Ne)!\n";
						}
						else
						{
							system("cls");
							break;
						}
					} while (true);
					if (choice == "Da")
					{
						int noGrade = 0;
						do
						{
							cout << "Vavedete nova ocenka: ";
							cin >> students[i].disciplines[j].grade;
							if (students[i].disciplines[j].grade == 0)
							{
								break;
							}
							else if (students[i].disciplines[j].grade >= 2 && students[i].disciplines[j].grade <= 6)
							{
								break;
							}
							else
							{
								cout << "Vavedete validna ocenka!\n";
							}
						} while (true);
						float sum = 0;
						for (int k = 0; k < MAX_DISCIPLINES; k++)
						{
							if (students[i].disciplines[k].grade == 0)
							{
								noGrade++;
							}
							sum += students[i].disciplines[k].grade;
						}
						students[i].averageGrade = sum / (MAX_DISCIPLINES - noGrade);
						////Използваме fixed и setprecision(), за да зададем точността на средния успех.
						cout << "Sreden uspeh: " << fixed << setprecision(2) << students[i].averageGrade << endl;
						system("pause");
						system("cls");
						break;
					}
					else
					{
						system("cls");
						break;
					}
				}
				else if (j == MAX_DISCIPLINES - 1) //Проверявамe дали сме стигнали до последната дисциплина.
				{
					cout << "Takava disiplina ne sushtestvuva!\n";
					system("pause");
					system("cls");
					break;
				}
			}
		}
		else if (facultyNumberToSearch == students[i].facultyNumber)
		{
			cout << "Ne se dopuska promqna na dannite na tozi student!\n";
			system("pause");
			system("cls");
			break;
		}
		else if (i == numStudents - 1 && isFound != true)
		{
			cout << "Nqma student s takuv fakulteten nomer!\n";
			system("pause");
			system("cls");
		}
	}
}

void Smqna_Statut(Student students[], int numStudents)
{
	string facultyNumberToSearch;
	do
	{
		cout << "Vavedete fakultetniq nomer na stundenta: ";
		cin >> facultyNumberToSearch;;
		if (facultyNumberToSearch.length() == 8) //Проверяваме дали факултетния номер е с дължина 8.
		{
			system("cls");
			break;
		}
		else
		{
			cout << "Vavedete validen fakulteten nomer!\n";
		}
	} while (true);
	for (int i = 0; i < numStudents; i++)
	{
		if (facultyNumberToSearch == students[i].facultyNumber)
		{
			if (students[i].status == "Aktiven" || students[i].status == "Prekusnal")
			{
				do
				{
					cout << "Vavedete noviq statut na studenta: ";
					cin >> students[i].status;
					if (students[i].status == "Aktiven" || students[i].status == "Prekusnal" || students[i].status == "Zavurshil")
					{
						break;
					}
					else
					{
						cout << "Vavedete validen statut! (Aktiven, Prekusnal, Zavurshil)!\n";
					}
				} while (true);
				system("cls");
				break;
			}
			else
			{
				cout << "Ne se dopuska promqna na dannite na tozi student!\n";
				system("pause");
				system("cls");
				break;
			}
		}
		else if (i == numStudents - 1)
		{
			cout << "Nqma student s takuv fakulteten nomer!\n";
			system("pause");
			system("cls");
			break;
		}
	}
}