#include <stdlib.h>
#include <iostream>
#include<fstream>
#include <cctype>
#include <string>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <format>
#include <sstream>

using namespace std;

string CurrentDate() {
	auto now = std::chrono::system_clock::now();

	std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

	struct tm localTime;

	localtime_s(&localTime, &currentTime); 


	std::ostringstream dateStream;
	dateStream << std::put_time(&localTime, "%Y-%m-%d");
	return dateStream.str();
}

void managerPanel(), login();

struct Bank
{
	int BankId;
	string BankName, Address;
};

struct BankBranch
{
	int BranchId;
	string BranchAddress;
	int BankId;

};

struct Account
{
	int AccId;
	int Balance, BranchId;
	string AccType;

};

struct Loan
{
	int LoanId;
	int Amount, BranchID;
	string LoanType;

};

struct Customer
{
	int CustId;
	string Name, Phone, Address;


};

struct Cust_ACC
{
	int CustId;
	int AccId;
	string date;

};

struct Cust_Loan
{
	int CustId;
	int LoanId;
	string date;

};

class BankClass {
public:

	void getAll() {


		ifstream ifile("E:\\c++\\Projects\\Bank\\files\\banks.txt");
		Bank banks[100], tempBank;

		string s;
		int t = 0;
		int i = 0;


		while (getline(ifile, s)) {

			string char_arr_str = s;

			if (s.find("id=") != string::npos) {
				tempBank.BankId = stoi(s.replace(0, 3, ""));
				t = 1;
			}
			if (s.find("name=") != string::npos) {
				tempBank.BankName = s.replace(0, 5, "");
				t = 2;
			}
			if (s.find("address=") != string::npos) {
				tempBank.Address = s.replace(0, 8, "");
				t = 3;
			}

			if (t == 3) {
				banks[i] = tempBank;
				t = 0;
				i++;
			}

		}

		ifile.close();

		cout << endl;
		cout << "     Id     |     Name     |     Address\n";
		for (int j = 0; j < i; j++)
		{
			Bank b = banks[j];
			cout << "------------------------------------------------------------------------------------------------------------------\n";
			cout << "     " << b.BankId << "     |     ";
			cout << b.BankName << "     |     ";
			cout << b.Address << endl;
		}


	}

	void add(string name, string address) {
		int id = 1;


		ifstream ifile("E:\\c++\\Projects\\Bank\\files\\banks.txt");


		string s;
		string readedFile = "";

		while (getline(ifile, s)) {
			readedFile.append(s);
			readedFile.append("\n");

			string char_arr_str = s;

			if (s.find("id=") != string::npos) {
				id = stoi(s.replace(0, 3, ""));
			}

		}
		id++;

		ifile.close();
		ofstream ofile;
		ofile.open("E:\\c++\\Projects\\Bank\\files\\banks.txt");


		ofile << readedFile;

		ofile << endl;
		ofile << "id=" << id;
		ofile << endl;
		ofile << "name=" << name;
		ofile << endl;
		ofile << "address=" << address;
		ofile << endl;
		ofile << ",";
		ofile << endl;

		ofile.close();


	}

	Bank searchByName(string searchedName) {
		Bank bank;
		bank.BankName = "";
		ifstream ifile("E:\\c++\\Projects\\Bank\\files\\banks.txt");


		string s;
		int temp = 0;


		while (getline(ifile, s)) {

			if (bank.BankName == "") {
				if (s.find("id=") != string::npos) {
					bank.BankId = stoi(s.replace(0, 3, ""));
				}
				if (s.find("name=") != string::npos) {
					string n = s.replace(0, 5, "");
					if (n.find(searchedName) != string::npos) {
						bank.BankName = n;
						temp = -1;
					}
				}
			}

			if (temp == -1) {
				if (s.find("address=") != string::npos) {
					bank.Address = s.replace(0, 8, "");
					temp = 0;
				}

			}

		}

		if (bank.BankName == "")
		{
			bank.Address = "";
			bank.BankId = -1;
		}

		ifile.close();
		return bank;
	}

	Bank searchById(int searchedId) {
		Bank bank;
		bank.BankId = -1;

		ifstream ifile("E:\\c++\\Projects\\Bank\\files\\banks.txt");
		string s;
		int temp = -1;

		while (getline(ifile, s)) {

			if (bank.BankId == -1 || temp == -1) {

				if (s.find("id=") != string::npos) {
					int n = stoi(s.replace(0, 3, ""));
					//cout << "searchedId " << searchedId << endl;
					//cout << "n " << n << endl;
					temp = 0;
					if (n == searchedId) {
						bank.BankId = n;
						temp = -1;
					}

				}

				if (s.find("name=") != string::npos) {
					bank.BankName = s.replace(0, 5, "");
				}
				if (s.find("address=") != string::npos) {
					bank.Address = s.replace(0, 8, "");
				}
			}
		}

		if (bank.BankId == -1)
		{
			bank.Address = "";
			bank.BankName = "";
		}
		ifile.close();

		return bank;
	}

	string deletef(Bank bank) {
		if (bank.BankId != -1) {

			ifstream ifile("E:\\c++\\Projects\\Bank\\files\\banks.txt");

			string s;
			string readedFile = "";

			while (getline(ifile, s)) {
				readedFile.append(s);
				readedFile.append("\n");
			}
			size_t indexa = 0;
			string a = "id=" + to_string(bank.BankId) + "\n" + "name=" + bank.BankName + "\n" + "address=" + bank.Address + "\n" + ",";

			while ((indexa = readedFile.find(a, indexa)) != string::npos) {
				readedFile.replace(indexa, a.length(), "");
			}

			ifile.close();
			ofstream ofile;
			ofile.open("E:\\c++\\Projects\\Bank\\files\\banks.txt");


			ofile << readedFile;
			ofile.close();
			return "bank deleted";
		}
		else {
			return "bank not found";
		}
	}

	string edit(int id, string name, string address) {
		Bank bank = searchById(id);
		if (bank.BankId != -1) {

			ifstream ifile("E:\\c++\\Projects\\Bank\\files\\banks.txt");

			string s;
			string readedFile = "";

			while (getline(ifile, s)) {
				readedFile.append(s);
				readedFile.append("\n");
			}
			size_t indexa = 0;
			string a = "id=" + to_string(bank.BankId) + "\n" + "name=" + bank.BankName + "\n" + "address=" + bank.Address + "\n" + ",";
			string b = "id=" + to_string(id) + "\n" + "name=" + name + "\n" + "address=" + address + "\n" + ",";

			while ((indexa = readedFile.find(a, indexa)) != string::npos) {
				readedFile.replace(indexa, a.length(), b);
			}

			ifile.close();
			ofstream ofile;
			ofile.open("E:\\c++\\Projects\\Bank\\files\\banks.txt");


			ofile << readedFile;
			ofile.close();
			return  "bank edited";
		}
		else {
			return "bank not found";
		}
	}


};

class BankBranchClass {
public:


	void getAll() {


		ifstream ifile("E:\\c++\\Projects\\Bank\\files\\BankBranchs.txt");

		BankBranch branches[100], tempBranch;

		string s;
		int t = 0;
		int i = 0;


		while (getline(ifile, s)) {

			string char_arr_str = s;

			if (s.find("id=") != string::npos) {
				tempBranch.BranchId = stoi(s.replace(0, 3, ""));
				t = 1;
			}
			if (s.find("BranchAddress=") != string::npos) {
				tempBranch.BranchAddress = s.replace(0, 14, "");
				t = 2;
			}
			if (s.find("BankID=") != string::npos) {
				tempBranch.BankId = stoi(s.replace(0, 7, ""));
				t = 3;
			}

			if (t == 3) {
				branches[i++] = tempBranch;
				t = 0;
			}

		}

		ifile.close();

		cout << endl;
		cout << "     Id     |     Address     |     BankId\n";
		for (int j = 0; j < i; j++)
		{
			BankBranch b = branches[j];
			cout << "------------------------------------------------------------------------------------------------------------------\n";
			cout << "     " << b.BranchId << "     |     ";
			cout << b.BranchAddress << "     |     ";
			cout << b.BankId << endl;
		}


	}

	void add(string BranchAddress, int BankID) {
		int id = 1;


		ifstream ifile("E:\\c++\\Projects\\Bank\\files\\BankBranchs.txt");


		string s;
		string readedFile = "";

		while (getline(ifile, s)) {
			readedFile.append(s);
			readedFile.append("\n");
			cout << s << endl;;

			string char_arr_str = s;

			if (s.find("id=") != string::npos) {
				id = stoi(s.replace(0, 3, ""));
			}

		}
		id++;

		ifile.close();
		ofstream ofile;
		ofile.open("E:\\c++\\Projects\\Bank\\files\\BankBranchs.txt");


		ofile << readedFile;

		ofile << endl;
		ofile << "id=" << id;
		ofile << endl;
		ofile << "BranchAddress=" << BranchAddress;
		ofile << endl;
		ofile << "BankID=" << BankID;
		ofile << endl;
		ofile << ",";
		ofile << endl;

		ofile.close();


	}

	BankBranch searchByAddress(string searchedAddress) {
		BankBranch bankBranch;
		bankBranch.BranchAddress = "";
		ifstream ifile("E:\\c++\\Projects\\Bank\\files\\BankBranchs.txt");


		string s;
		int temp = 0;


		while (getline(ifile, s)) {
			if (bankBranch.BranchAddress == "") {
				if (s.find("id=") != string::npos) {
					bankBranch.BranchId = stoi(s.replace(0, 3, ""));
				}
				if (s.find("BranchAddress=") != string::npos) {
					string n = s.replace(0, 14, "");
					if (n.find(searchedAddress) != string::npos) {
						bankBranch.BranchAddress = n;
						temp = -1;
					}
				}
			}

			if (temp == -1) {
				if (s.find("BankID=") != string::npos) {
					bankBranch.BankId = stoi(s.replace(0, 7, ""));
					temp = 0;
				}

			}

		}

		if (bankBranch.BranchAddress == "")
		{
			bankBranch.BranchId = -1;
			bankBranch.BankId = -1;
		}

		ifile.close();
		return bankBranch;
	}

	BankBranch searchById(int searchedId) {
		BankBranch bankBranch;
		bankBranch.BranchAddress = "";
		ifstream ifile("E:\\c++\\Projects\\Bank\\files\\BankBranchs.txt");


		string s;
		int temp = 0;


		while (getline(ifile, s)) {
			if (bankBranch.BranchAddress == "") {
				if (s.find("id=") != string::npos) {
					int n = stoi(s.replace(0, 3, ""));
					if (n == searchedId) {
						bankBranch.BranchId = n;
						temp = -1;
					}
				}

			}

			if (temp == -1) {
				if (s.find("BranchAddress=") != string::npos) {
					bankBranch.BranchAddress = s.replace(0, 14, "");
				}
				if (s.find("BankID=") != string::npos) {
					bankBranch.BankId = stoi(s.replace(0, 7, ""));
					temp = 0;
				}
			}

		}

		if (bankBranch.BranchAddress == "")
		{
			bankBranch.BranchId = -1;
			bankBranch.BankId = -1;
		}

		ifile.close();
		return bankBranch;
	}

	string deletef(BankBranch bankBranch) {
		if (bankBranch.BranchId != -1) {

			ifstream ifile("E:\\c++\\Projects\\Bank\\files\\BankBranchs.txt");

			string s;
			string readedFile = "";

			while (getline(ifile, s)) {
				readedFile.append(s);
				readedFile.append("\n");
			}
			size_t indexa = 0;
			string a = "id=" + to_string(bankBranch.BranchId) + "\n" + "BranchAddress=" + bankBranch.BranchAddress + "\n" + "BankID=" + to_string(bankBranch.BankId) + "\n" + ",";

			while ((indexa = readedFile.find(a, indexa)) != string::npos) {
				readedFile.replace(indexa, a.length(), "");
			}

			ifile.close();
			ofstream ofile;
			ofile.open("E:\\c++\\Projects\\Bank\\files\\BankBranchs.txt");


			ofile << readedFile;
			ofile.close();
			return "Branch deleted";
		}
		else {
			return "Branch not found";
		}
	}

	string edit(int id, string BranchAddress, int BankID) {
		BankBranch bankBranch = searchById(id);
		if (bankBranch.BranchId != -1) {

			ifstream ifile("E:\\c++\\Projects\\Bank\\files\\BankBranchs.txt");

			string s;
			string readedFile = "";

			while (getline(ifile, s)) {
				readedFile.append(s);
				readedFile.append("\n");
			}
			size_t indexa = 0;
			string a = "id=" + to_string(bankBranch.BranchId) + "\n" + "BranchAddress=" + bankBranch.BranchAddress + "\n" + "BankID=" + to_string(bankBranch.BankId) + "\n" + ",";
			string b = "id=" + to_string(id) + "\n" + "BranchAddress=" + BranchAddress + "\n" + "BankID=" + to_string(BankID) + "\n" + ",";

			while ((indexa = readedFile.find(a, indexa)) != string::npos) {
				readedFile.replace(indexa, a.length(), b);
			}

			ifile.close();
			ofstream ofile;
			ofile.open("E:\\c++\\Projects\\Bank\\files\\BankBranchs.txt");


			ofile << readedFile;
			ofile.close();
			return  "branch edited";
		}
		else {
			return "branch not found";
		}
	}

};

class CustomerClass {
public:

	void getAll() {


		ifstream ifile("E:\\c++\\Projects\\Bank\\files\\Customers.txt");

		Customer customers[100], tempCustomer;


		string s;
		int t = 0;
		int i = 0;


		while (getline(ifile, s)) {

			string char_arr_str = s;

			if (s.find("id=") != string::npos) {
				tempCustomer.CustId = stoi(s.replace(0, 3, ""));
				t = 1;
			}
			if (s.find("name=") != string::npos) {
				tempCustomer.Name = s.replace(0, 5, "");
				t = 2;
			}
			if (s.find("phone=") != string::npos) {
				tempCustomer.Phone = s.replace(0, 6, "");
				t = 3;
			}
			if (s.find("address=") != string::npos) {
				tempCustomer.Address = s.replace(0, 8, "");
				t = 4;
			}

			if (t == 4) {
				customers[i] = tempCustomer;
				t = 0;
				i++;
			}

		}

		ifile.close();

		cout << endl;
		cout << "     Id     |     Name     |     Phone     |     Address\n";
		for (int j = 0; j < i; j++)
		{
			Customer c = customers[j];
			cout << "------------------------------------------------------------------------------------------------------------------\n";
			cout << "     " << c.CustId << "     |     ";
			cout << c.Name << "     |     ";
			cout << c.Phone << "     |     ";
			cout << c.Address << endl;
		}


	}

	void add(string name, string phone, string address) {
		int id = 1;


		ifstream ifile("E:\\c++\\Projects\\Bank\\files\\Customers.txt");


		string s;
		string readedFile = "";

		while (getline(ifile, s)) {
			readedFile.append(s);
			readedFile.append("\n");

			string char_arr_str = s;

			if (s.find("id=") != string::npos) {
				id = stoi(s.replace(0, 3, ""));
			}

		}
		id++;

		ifile.close();
		ofstream ofile;
		ofile.open("E:\\c++\\Projects\\Bank\\files\\Customers.txt");


		ofile << readedFile;

		ofile << endl;
		ofile << "id=" << id;
		ofile << endl;
		ofile << "name=" << name;
		ofile << endl;
		ofile << "phone=" << phone;
		ofile << endl;
		ofile << "address=" << address;
		ofile << endl;
		ofile << ",";
		ofile << endl;

		ofile.close();


	}

	Customer searchByName(string searchedName) {
		Customer customer;
		customer.Name = "";
		ifstream ifile("E:\\c++\\Projects\\Bank\\files\\Customers.txt");


		string s;
		int temp = 0;


		while (getline(ifile, s)) {

			if (customer.Name == "") {
				if (s.find("id=") != string::npos) {
					customer.CustId = stoi(s.replace(0, 3, ""));
				}
				if (s.find("name=") != string::npos) {
					string n = s.replace(0, 5, "");
					if (n.find(searchedName) != string::npos) {
						customer.Name = n;
						temp = -1;
					}
				}
			}

			if (temp == -1) {
				if (s.find("phone=") != string::npos) {
					customer.Phone = s.replace(0, 6, "");
				}
				if (s.find("address=") != string::npos) {
					customer.Address = s.replace(0, 8, "");
					temp = 0;
				}

			}

		}

		if (customer.Name == "")
		{
			customer.Address = "";
			customer.CustId = -1;
		}

		ifile.close();
		return customer;
	}

	Customer searchById(int searchedId) {
		Customer customer;
		customer.CustId = -1;

		ifstream ifile("E:\\c++\\Projects\\Bank\\files\\Customers.txt");
		string s;
		int temp = -1;

		while (getline(ifile, s)) {

			if (customer.CustId == -1 || temp == -1) {

				if (s.find("id=") != string::npos) {
					int n = stoi(s.replace(0, 3, ""));
					temp = 0;
					if (n == searchedId) {
						customer.CustId = n;
						temp = -1;
					}

				}

				if (s.find("name=") != string::npos) {
					customer.Name = s.replace(0, 5, "");
				}
				if (s.find("phone=") != string::npos) {
					customer.Phone = s.replace(0, 6, "");
				}
				if (s.find("address=") != string::npos) {
					customer.Address = s.replace(0, 8, "");
				}
			}
		}

		if (customer.CustId == -1)
		{
			customer.Address = "";
			customer.Name = "";
		}
		ifile.close();

		return customer;
	}

	string deletef(Customer customer) {
		if (customer.CustId != -1) {

			ifstream ifile("E:\\c++\\Projects\\Bank\\files\\Customers.txt");

			string s;
			string readedFile = "";

			while (getline(ifile, s)) {
				readedFile.append(s);
				readedFile.append("\n");
			}
			size_t indexa = 0;
			string a = "id=" + to_string(customer.CustId) + "\n" + "name=" + customer.Name + "\n" + "phone=" + customer.Phone + "\n" + "address=" + customer.Address + "\n" + ",";

			while ((indexa = readedFile.find(a, indexa)) != string::npos) {
				readedFile.replace(indexa, a.length(), "");
			}

			ifile.close();
			ofstream ofile;
			ofile.open("E:\\c++\\Projects\\Bank\\files\\Customers.txt");


			ofile << readedFile;
			ofile.close();
			return "customer deleted";
		}
		else {
			return "customer not found";
		}
	}

	string edit(int id, string name, string phone, string address) {
		Customer customer = searchById(id);
		if (customer.CustId != -1) {

			ifstream ifile("E:\\c++\\Projects\\Bank\\files\\Customers.txt");

			string s;
			string readedFile = "";

			while (getline(ifile, s)) {
				readedFile.append(s);
				readedFile.append("\n");
			}
			size_t indexa = 0;
			string a = "id=" + to_string(customer.CustId) + "\n" + "name=" + customer.Name + "\n" + "phone=" + customer.Phone + "\n" + "address=" + customer.Address + "\n" + ",";
			string b = "id=" + to_string(id) + "\n" + "name=" + name + "\n" + "phone=" + phone + "\n" + "address=" + address + "\n" + ",";

			while ((indexa = readedFile.find(a, indexa)) != string::npos) {
				readedFile.replace(indexa, a.length(), b);
			}

			ifile.close();
			ofstream ofile;
			ofile.open("E:\\c++\\Projects\\Bank\\files\\Customers.txt");


			ofile << readedFile;
			ofile.close();
			return  "Customer edited";
		}
		else {
			return "Customer not found";
		}
	}

};

class AccountClass {
public:

	void getAll() {


		ifstream ifile("E:\\c++\\Projects\\Bank\\files\\Accounts.txt");

		Account accounts[100], tempAccount;


		string s;
		int t = 0;
		int i = 0;


		while (getline(ifile, s)) {

			string char_arr_str = s;

			if (s.find("id=") != string::npos) {
				tempAccount.AccId = stoi(s.replace(0, 3, ""));
				t = 1;
			}
			if (s.find("type=") != string::npos) {
				tempAccount.AccType = s.replace(0, 5, "");
				t = 2;
			}
			if (s.find("balance=") != string::npos) {
				tempAccount.Balance = stoi(s.replace(0, 8, ""));
				t = 3;
			}
			if (s.find("branchId=") != string::npos) {
				tempAccount.BranchId = stoi(s.replace(0, 9, ""));
				t = 4;
			}

			if (t == 4) {
				accounts[i] = tempAccount;
				t = 0;
				i++;
			}

		}

		ifile.close();

		cout << endl;
		cout << "     Id     |     type     |     balance     |     branchId\n";
		for (int j = 0; j < i; j++)
		{
			Account c = accounts[j];
			cout << "------------------------------------------------------------------------------------------------------------------\n";
			cout << "     " << c.AccId << "     |     ";
			cout << c.AccType << "     |     ";
			cout << c.Balance << "     |     ";
			cout << c.BranchId << endl;
		}


	}

	int add(string type, int balance, int branchId) {
		int id = 1;


		ifstream ifile("E:\\c++\\Projects\\Bank\\files\\Accounts.txt");


		string s;
		string readedFile = "";

		while (getline(ifile, s)) {
			readedFile.append(s);
			readedFile.append("\n");

			string char_arr_str = s;

			if (s.find("id=") != string::npos) {
				id = stoi(s.replace(0, 3, ""));
			}

		}
		id++;

		ifile.close();
		ofstream ofile;
		ofile.open("E:\\c++\\Projects\\Bank\\files\\Accounts.txt");


		ofile << readedFile;

		ofile << endl;
		ofile << "id=" << id;
		ofile << endl;
		ofile << "type=" << type;
		ofile << endl;
		ofile << "balance=" << balance;
		ofile << endl;
		ofile << "branchId=" << branchId;
		ofile << endl;
		ofile << ",";
		ofile << endl;

		ofile.close();

		return id;


	}

	Account searchById(int searchedId) {
		Account account;
		account.AccId = -1;

		ifstream ifile("E:\\c++\\Projects\\Bank\\files\\Accounts.txt");
		string s;
		int temp = -1;

		while (getline(ifile, s)) {

			if (account.AccId == -1 || temp == -1) {

				if (s.find("id=") != string::npos) {
					int n = stoi(s.replace(0, 3, ""));
					temp = 0;
					if (n == searchedId) {
						account.AccId = n;
						temp = -1;
					}

				}

				if (s.find("type=") != string::npos) {
					account.AccType = s.replace(0, 5, "");
				}
				if (s.find("balance=") != string::npos) {
					account.Balance = stoi(s.replace(0, 6, ""));
				}
				if (s.find("branchId=") != string::npos) {
					account.BranchId = stoi(s.replace(0, 8, ""));
				}
			}
		}

		if (account.AccId == -1)
		{
			account.AccType = "";
			account.Balance = 0;
		}
		ifile.close();

		return account;
	}

	string deletef(Account account) {
		if (account.AccId != -1) {

			ifstream ifile("E:\\c++\\Projects\\Bank\\files\\Accounts.txt");

			string s;
			string readedFile = "";

			while (getline(ifile, s)) {
				readedFile.append(s);
				readedFile.append("\n");
			}
			size_t indexa = 0;
			string a = "id=" + to_string(account.AccId) + "\n" + "type=" + account.AccType + "\n" + "balance=" + to_string(account.Balance) + "\n" + "branchId=" + to_string(account.BranchId) + "\n" + ",";

			while ((indexa = readedFile.find(a, indexa)) != string::npos) {
				readedFile.replace(indexa, a.length(), "");
			}

			ifile.close();
			ofstream ofile;
			ofile.open("E:\\c++\\Projects\\Bank\\files\\Accounts.txt");


			ofile << readedFile;
			ofile.close();
			return "Account deleted";
		}
		else {
			return "Account not found";
		}
	}

	string edit(int id, string type, int balance, int branchId) {
		Account account = searchById(id);
		if (account.AccId != -1) {

			ifstream ifile("E:\\c++\\Projects\\Bank\\files\\Accounts.txt");

			string s;
			string readedFile = "";

			while (getline(ifile, s)) {
				readedFile.append(s);
				readedFile.append("\n");
			}
			size_t indexa = 0;
			string a = "id=" + to_string(account.AccId) + "\n" + "type=" + account.AccType + "\n" + "balance=" + to_string(account.Balance) + "\n" + "branchId=" + to_string(account.BranchId) + "\n" + ",";
			string b = "id=" + to_string(id) + "\n" + "type=" + type + "\n" + "balance=" + to_string(balance) + "\n" + "branchId=" + to_string(branchId) + "\n" + ",";

			while ((indexa = readedFile.find(a, indexa)) != string::npos) {
				readedFile.replace(indexa, a.length(), b);
			}

			ifile.close();
			ofstream ofile;
			ofile.open("E:\\c++\\Projects\\Bank\\files\\Accounts.txt");


			ofile << readedFile;
			ofile.close();
			return  "Account edited";
		}
		else {
			return "Account not found";
		}
	}

};

class LoanClass {
public:

	void getAll() {


		ifstream ifile("E:\\c++\\Projects\\Bank\\files\\Loans.txt");

		Loan loans[100], tempLoan;


		string s;
		int t = 0;
		int i = 0;


		while (getline(ifile, s)) {

			string char_arr_str = s;

			if (s.find("id=") != string::npos) {
				tempLoan.LoanId = stoi(s.replace(0, 3, ""));
				t = 1;
			}
			if (s.find("amount=") != string::npos) {
				tempLoan.Amount = stoi(s.replace(0, 7, ""));
				t = 2;
			}
			if (s.find("type=") != string::npos) {
				tempLoan.LoanType = s.replace(0, 5, "");
				t = 3;
			}
			if (s.find("branchId=") != string::npos) {
				tempLoan.BranchID = stoi(s.replace(0, 9, ""));
				t = 4;
			}

			if (t == 4) {
				loans[i] = tempLoan;
				t = 0;
				i++;
			}

		}

		ifile.close();

		cout << endl;
		cout << "     Id     |     amount     |     type     |     branchId\n";
		for (int j = 0; j < i; j++)
		{
			Loan c = loans[j];
			cout << "------------------------------------------------------------------------------------------------------------------\n";
			cout << "     " << c.LoanId << "     |     ";
			cout << c.Amount << "     |     ";
			cout << c.LoanType << "     |     ";
			cout << c.BranchID << endl;
		}


	}

	int add(string type, int amount, int branchId) {
		int id = 1;


		ifstream ifile("E:\\c++\\Projects\\Bank\\files\\Loans.txt");


		string s;
		string readedFile = "";

		while (getline(ifile, s)) {
			readedFile.append(s);
			readedFile.append("\n");

			string char_arr_str = s;

			if (s.find("id=") != string::npos) {
				id = stoi(s.replace(0, 3, ""));
			}

		}
		id++;

		ifile.close();
		ofstream ofile;
		ofile.open("E:\\c++\\Projects\\Bank\\files\\Loans.txt");


		ofile << readedFile;

		ofile << endl;
		ofile << "id=" << id;
		ofile << endl;
		ofile << "amount=" << amount;
		ofile << endl;
		ofile << "type=" << type;
		ofile << endl;
		ofile << "branchId=" << branchId;
		ofile << endl;
		ofile << ",";
		ofile << endl;

		ofile.close();

		return id;

	}

	Loan searchById(int searchedId) {
		Loan loan;
		loan.LoanId = -1;

		ifstream ifile("E:\\c++\\Projects\\Bank\\files\\Loans.txt");
		string s;
		int temp = -1;

		while (getline(ifile, s)) {

			if (loan.LoanId == -1 || temp == -1) {

				if (s.find("id=") != string::npos) {
					int n = stoi(s.replace(0, 3, ""));
					temp = 0;
					if (n == searchedId) {
						loan.LoanId = n;
						temp = -1;
					}

				}

				if (s.find("amount=") != string::npos) {
					loan.Amount = stoi(s.replace(0, 7, ""));
				}
				if (s.find("type=") != string::npos) {
					loan.LoanType = s.replace(0, 5, "");
				}
				if (s.find("branchId=") != string::npos) {
					loan.BranchID = stoi(s.replace(0, 9, ""));
				}
			}
		}

		if (loan.LoanId == -1)
		{
			loan.LoanType = "";
			loan.Amount = 0;
		}
		ifile.close();

		return loan;
	}

	Loan searchByBranchId(int searchedBranchId) {
		Loan loan;
		loan.BranchID = -1;
		ifstream ifile("E:\\c++\\Projects\\Bank\\files\\Customers.txt");


		string s;
		int temp = 0;


		while (getline(ifile, s)) {

			if (loan.BranchID == -1) {
				if (s.find("id=") != string::npos) {
					loan.LoanId = stoi(s.replace(0, 3, ""));
				}
				if (s.find("branchId=") != string::npos) {
					int n = stoi(s.replace(0, 9, ""));
					if (n == searchedBranchId) {
						loan.BranchID = n;
						temp = -1;
					}
				}
			}

			if (temp == -1) {
				if (s.find("amount=") != string::npos) {
					loan.Amount = stoi(s.replace(0, 7, ""));
				}
				if (s.find("type=") != string::npos) {
					loan.LoanType = s.replace(0, 5, "");
					temp = 0;
				}

			}

		}
		if (loan.BranchID == -1)
		{
			loan.LoanType = "";
			loan.Amount = 0;
			loan.LoanId = -1;
		}

		ifile.close();
		return loan;
	}

	string deletef(Loan loan) {
		if (loan.LoanId != -1) {

			ifstream ifile("E:\\c++\\Projects\\Bank\\files\\Loans.txt");

			string s;
			string readedFile = "";

			while (getline(ifile, s)) {
				readedFile.append(s);
				readedFile.append("\n");
			}
			size_t indexa = 0;
			string a = "id=" + to_string(loan.LoanId) + "\n" "amount=" + to_string(loan.Amount) + "\n" + "type=" + loan.LoanType + "\n" + "branchId=" + to_string(loan.BranchID) + "\n" + ",";

			while ((indexa = readedFile.find(a, indexa)) != string::npos) {
				readedFile.replace(indexa, a.length(), "");
			}

			ifile.close();
			ofstream ofile;
			ofile.open("E:\\c++\\Projects\\Bank\\files\\Loans.txt");


			ofile << readedFile;
			ofile.close();
			return "Loan deleted";
		}
		else {
			return "Loan not found";
		}
	}

	string edit(int id, string type, int amount, int branchId) {
		Loan loan = searchById(id);
		if (loan.LoanId != -1) {

			ifstream ifile("E:\\c++\\Projects\\Bank\\files\\Loans.txt");

			string s;
			string readedFile = "";

			while (getline(ifile, s)) {
				readedFile.append(s);
				readedFile.append("\n");
			}
			size_t indexa = 0;
			string a = "id=" + to_string(loan.LoanId) + "\n" "amount=" + to_string(loan.Amount) + "\n" + "type=" + loan.LoanType + "\n" + "branchId=" + to_string(loan.BranchID) + "\n" + ",";
			string b = "id=" + to_string(id) + "\n" + "amount=" + to_string(amount) + "\n" + "type=" + type + "\n" + "branchId=" + to_string(branchId) + "\n" + ",";

			while ((indexa = readedFile.find(a, indexa)) != string::npos) {
				readedFile.replace(indexa, a.length(), b);
			}

			ifile.close();
			ofstream ofile;
			ofile.open("E:\\c++\\Projects\\Bank\\files\\Loans.txt");


			ofile << readedFile;
			ofile.close();
			return  "Loan edited";
		}
		else {
			return "Loan not found";
		}
	}

};

class Cust_AccClass {
public:


	void add(string date, int cId, int aId) {


		ifstream ifile("E:\\c++\\Projects\\Bank\\files\\Cust_ACCs.txt");


		string s;
		string readedFile = "";

		while (getline(ifile, s)) {
			readedFile.append(s);
			readedFile.append("\n");
		}

		ifile.close();
		ofstream ofile;
		ofile.open("E:\\c++\\Projects\\Bank\\files\\Cust_ACCs.txt");


		ofile << readedFile;

		ofile << endl;
		ofile << "cId=" << cId;
		ofile << endl;
		ofile << "aId=" << aId;
		ofile << endl;
		ofile << "date=" << date;
		ofile << endl;
		ofile << ",";
		ofile << endl;

		ofile.close();


	}

	Cust_ACC searchBycId(int searchedcId) {
		Cust_ACC cust_acc;
		cust_acc.CustId = -1;

		ifstream ifile("E:\\c++\\Projects\\Bank\\files\\Cust_ACCs.txt");
		string s;
		int temp = -1;

		while (getline(ifile, s)) {

			if (cust_acc.CustId == -1 || temp == -1) {

				if (s.find("cId=") != string::npos) {
					int n = stoi(s.replace(0, 4, ""));
					temp = 0;
					if (n == searchedcId) {
						cust_acc.CustId = n;
						temp = -1;
					}

				}

				if (s.find("aId=") != string::npos) {
					cust_acc.AccId = stoi(s.replace(0, 4, ""));
				}
				if (s.find("date=") != string::npos) {
					cust_acc.date = s.replace(0, 5, "");
				}
			}
		}

		if (cust_acc.CustId == -1)
		{
			cust_acc.AccId = -1;
			cust_acc.date = "";
		}
		ifile.close();

		return cust_acc;
	}

	Cust_ACC searchByaId(int searchedaId) {
		Cust_ACC cust_acc;
		cust_acc.AccId = -1;

		ifstream ifile("E:\\c++\\Projects\\Bank\\files\\Cust_ACCs.txt");
		string s;
		int temp = -1;

		while (getline(ifile, s)) {

			if (cust_acc.AccId == -1 || temp == -1) {

				if (s.find("aId=") != string::npos) {
					int n = stoi(s.replace(0, 4, ""));
					temp = 0;
					if (n == searchedaId) {
						cust_acc.AccId = n;
						temp = -1;
					}

				}

				if (s.find("cId=") != string::npos) {
					cust_acc.CustId = stoi(s.replace(0, 4, ""));
				}
				if (s.find("date=") != string::npos) {
					cust_acc.date = s.replace(0, 5, "");
				}
			}
		}

		if (cust_acc.AccId == -1)
		{
			cust_acc.CustId = -1;
			cust_acc.date = "";
		}
		ifile.close();

		return cust_acc;
	}

	void deletef(Cust_ACC cust_acc) {
		if (cust_acc.AccId != -1) {

			ifstream ifile("E:\\c++\\Projects\\Bank\\files\\Cust_ACCs.txt");

			string s;
			string readedFile = "";

			while (getline(ifile, s)) {
				readedFile.append(s);
				readedFile.append("\n");
			}
			size_t indexa = 0;
			string a = "cId=" + to_string(cust_acc.CustId) + "\n" "aId=" + to_string(cust_acc.AccId) + "\n" + "date=" + cust_acc.date + "\n" + ",";

			while ((indexa = readedFile.find(a, indexa)) != string::npos) {
				readedFile.replace(indexa, a.length(), "");
			}

			ifile.close();
			ofstream ofile;
			ofile.open("E:\\c++\\Projects\\Bank\\files\\Cust_ACCs.txt");


			ofile << readedFile;
			ofile.close();
		}
	}

	void editaId(Cust_ACC cust_acc, int aId) {
		if (cust_acc.AccId != -1) {

			ifstream ifile("E:\\c++\\Projects\\Bank\\files\\Cust_ACCs.txt");

			string s;
			string readedFile = "";

			while (getline(ifile, s)) {
				readedFile.append(s);
				readedFile.append("\n");
			}
			size_t indexa = 0;
			string a = "cId=" + to_string(cust_acc.CustId) + "\n" "aId=" + to_string(cust_acc.AccId) + "\n" + "date=" + cust_acc.date + "\n" + ",";
			string b = "cId=" + to_string(cust_acc.CustId) + "\n" "aId=" + to_string(aId) + "\n" + "date=" + cust_acc.date + "\n" + ",";

			while ((indexa = readedFile.find(a, indexa)) != string::npos) {
				readedFile.replace(indexa, a.length(), b);
			}

			ifile.close();
			ofstream ofile;
			ofile.open("E:\\c++\\Projects\\Bank\\files\\Cust_ACCs.txt");


			ofile << readedFile;
			ofile.close();
		}
	}

	void editcId(Cust_ACC cust_acc, int cId) {
		if (cust_acc.CustId != -1) {

			ifstream ifile("E:\\c++\\Projects\\Bank\\files\\Cust_ACCs.txt");

			string s;
			string readedFile = "";

			while (getline(ifile, s)) {
				readedFile.append(s);
				readedFile.append("\n");
			}
			size_t indexa = 0;
			string a = "cId=" + to_string(cust_acc.CustId) + "\n" "aId=" + to_string(cust_acc.AccId) + "\n" + "date=" + cust_acc.date + "\n" + ",";
			string b = "cId=" + to_string(cId) + "\n" "aId=" + to_string(cust_acc.AccId) + "\n" + "date=" + cust_acc.date + "\n" + ",";

			while ((indexa = readedFile.find(a, indexa)) != string::npos) {
				readedFile.replace(indexa, a.length(), b);
			}

			ifile.close();
			ofstream ofile;
			ofile.open("E:\\c++\\Projects\\Bank\\files\\Cust_ACCs.txt");


			ofile << readedFile;
			ofile.close();
		}
	}

};

class Cust_LoansClass {
public:


	void add(string date, int cId, int lId) {


		ifstream ifile("E:\\c++\\Projects\\Bank\\files\\Cust_Loans.txt");


		string s;
		string readedFile = "";

		while (getline(ifile, s)) {
			readedFile.append(s);
			readedFile.append("\n");
		}

		ifile.close();
		ofstream ofile;
		ofile.open("E:\\c++\\Projects\\Bank\\files\\Cust_Loans.txt");


		ofile << readedFile;

		ofile << endl;
		ofile << "cId=" << cId;
		ofile << endl;
		ofile << "lId=" << lId;
		ofile << endl;
		ofile << "date=" << date;
		ofile << endl;
		ofile << ",";
		ofile << endl;

		ofile.close();


	}

	Cust_Loan searchBycId(int searchedcId) {
		Cust_Loan cust_loan;
		cust_loan.CustId = -1;

		ifstream ifile("E:\\c++\\Projects\\Bank\\files\\Cust_Loans.txt");
		string s;
		int temp = -1;

		while (getline(ifile, s)) {

			if (cust_loan.CustId == -1 || temp == -1) {

				if (s.find("cId=") != string::npos) {
					int n = stoi(s.replace(0, 4, ""));
					temp = 0;
					if (n == searchedcId) {
						cust_loan.CustId = n;
						temp = -1;
					}

				}

				if (s.find("lId=") != string::npos) {
					cust_loan.LoanId = stoi(s.replace(0, 4, ""));
				}
				if (s.find("date=") != string::npos) {
					cust_loan.date = s.replace(0, 5, "");
				}
			}
		}

		if (cust_loan.CustId == -1)
		{
			cust_loan.LoanId = -1;
			cust_loan.date = "";
		}
		ifile.close();

		return cust_loan;
	}

	Cust_Loan searchBylId(int searchedlId) {
		Cust_Loan cust_loan;
		cust_loan.LoanId = -1;

		ifstream ifile("E:\\c++\\Projects\\Bank\\files\\Cust_Loans.txt");
		string s;
		int temp = -1;

		while (getline(ifile, s)) {

			if (cust_loan.LoanId == -1 || temp == -1) {

				if (s.find("lId=") != string::npos) {
					int n = stoi(s.replace(0, 4, ""));
					temp = 0;
					if (n == searchedlId) {
						cust_loan.LoanId = n;
						temp = -1;
					}

				}

				if (s.find("cId=") != string::npos) {
					cust_loan.CustId = stoi(s.replace(0, 4, ""));
				}
				if (s.find("date=") != string::npos) {
					cust_loan.date = s.replace(0, 5, "");
				}
			}
		}

		if (cust_loan.LoanId == -1)
		{
			cust_loan.CustId = -1;
			cust_loan.date = "";
		}
		ifile.close();

		return cust_loan;
	}

	void deletef(Cust_Loan cust_loan) {
		if (cust_loan.LoanId != -1) {

			ifstream ifile("E:\\c++\\Projects\\Bank\\files\\Cust_Loans.txt");

			string s;
			string readedFile = "";

			while (getline(ifile, s)) {
				readedFile.append(s);
				readedFile.append("\n");
			}
			size_t indexa = 0;
			string a = "cId=" + to_string(cust_loan.CustId) + "\n" "lId=" + to_string(cust_loan.LoanId) + "\n" + "date=" + cust_loan.date + "\n" + ",";

			while ((indexa = readedFile.find(a, indexa)) != string::npos) {
				readedFile.replace(indexa, a.length(), "");
			}

			ifile.close();
			ofstream ofile;
			ofile.open("E:\\c++\\Projects\\Bank\\files\\Cust_Loans.txt");


			ofile << readedFile;
			ofile.close();
		}
	}

	void editlId(Cust_Loan cust_loan, int lId) {
		if (cust_loan.LoanId != -1) {

			ifstream ifile("E:\\c++\\Projects\\Bank\\files\\Cust_Loans.txt");

			string s;
			string readedFile = "";

			while (getline(ifile, s)) {
				readedFile.append(s);
				readedFile.append("\n");
			}
			size_t indexa = 0;
			string a = "cId=" + to_string(cust_loan.CustId) + "\n" "lId=" + to_string(cust_loan.LoanId) + "\n" + "date=" + cust_loan.date + "\n" + ",";
			string b = "cId=" + to_string(cust_loan.CustId) + "\n" "lId=" + to_string(lId) + "\n" + "date=" + cust_loan.date + "\n" + ",";

			while ((indexa = readedFile.find(a, indexa)) != string::npos) {
				readedFile.replace(indexa, a.length(), b);
			}

			ifile.close();
			ofstream ofile;
			ofile.open("E:\\c++\\Projects\\Bank\\files\\Cust_Loans.txt");


			ofile << readedFile;
			ofile.close();
		}
	}

	void editcId(Cust_Loan cust_loan, int cId) {
		if (cust_loan.CustId != -1) {

			ifstream ifile("E:\\c++\\Projects\\Bank\\files\\Cust_Loans.txt");

			string s;
			string readedFile = "";

			while (getline(ifile, s)) {
				readedFile.append(s);
				readedFile.append("\n");
			}
			size_t indexa = 0;
			string a = "cId=" + to_string(cust_loan.CustId) + "\n" "lId=" + to_string(cust_loan.LoanId) + "\n" + "date=" + cust_loan.date + "\n" + ",";
			string b = "cId=" + to_string(cId) + "\n" "lId=" + to_string(cust_loan.LoanId) + "\n" + "date=" + cust_loan.date + "\n" + ",";

			while ((indexa = readedFile.find(a, indexa)) != string::npos) {
				readedFile.replace(indexa, a.length(), b);
			}

			ifile.close();
			ofstream ofile;
			ofile.open("E:\\c++\\Projects\\Bank\\files\\Cust_Loans.txt");


			ofile << readedFile;
			ofile.close();
		}
	}

};

void bankPanel() {
	BankClass bankClass;
	int selectedPos = 0;
	cout << endl;
	cout << "                                                      Bank Panel                                                       " << endl;
	cout << " ===================================================================================================================== " << endl;
	cout << "                |  Add  |  Delete  |  Edit  |  Read All  |  search by name  |  search by id  |  back  |                " << endl;
	cout << "                |   1   |    2     |    3   |     4      |        5         |       6        |    7   |                " << endl;
	cout << "                ---------------------------------------------------------------------------------------                " << endl;

	cout << " What do you want to work with?  ";
	cin >> selectedPos;

	int tempPos = 0;
	int tempId;
	string tempName, tempAddress, tempRes;
	Bank tempBank;

	switch (selectedPos) {
	case 1:
		cout << "Enter banks name:  ";
		cin >> tempName;
		cout << "Enter banks address:  ";
		cin >> tempAddress;
		bankClass.add(tempName, tempAddress);
		system("cls");
		cout << "Band added. \n";
		bankPanel();
		break;
	case 2:
		cout << "\n";
		cout << "Do you want to delete bank by name or id? \n";
		cout << "          |  by name  |  by id  |         " << endl;
		cout << "          |     1     |    2    |         " << endl;
		cout << "          -----------------------         " << endl;
		cin >> tempPos;
		switch (tempPos) {
		case 1:
			cout << "Enter the banks NAME tp delete:  ";
			cin >> tempName;
			tempBank = bankClass.searchByName(tempName);
			tempRes = bankClass.deletef(tempBank);
			system("cls");
			cout << tempRes + " \n";
			bankPanel();
			break;
		case 2:
			cout << "Enter the banks ID tp delete:  ";
			cin >> tempId;
			tempBank = bankClass.searchById(tempId);
			tempRes = bankClass.deletef(tempBank);
			system("cls");
			cout << tempRes + " \n";
			bankPanel();
			break;
		default:
			system("cls");
			cout << "Enter proper Commend. \n";
			bankPanel();
			break;
		}

		break;
	case 3:
		cout << "\n";
		cout << "Enter id of the bank yoi ant to edit:  ";
		cin >> tempId;

		cout << "Enter the new name : ";
		cin >> tempName;
		cout << "Enter the new address : ";
		cin >> tempAddress;

		tempRes = bankClass.edit(tempId, tempName, tempAddress);
		system("cls");
		cout << tempRes + " \n";
		bankPanel();


		break;
	case 4:
		system("cls");
		bankClass.getAll();

		cout << "Enter 1 to go back:  ";
		cin >> tempPos;

		if (tempPos == 1) {
			system("cls");
			bankPanel();
		}

		break;
	case 5:
		cout << "Enter the banks NAME for search:  ";
		cin >> tempName;
		tempBank = bankClass.searchByName(tempName);
		if (tempBank.BankId == -1) {
			cout << "\n";
			cout << "Bank not found";
			cout << "\n";
		}
		else {
			cout << "\n";
			cout << "Id = " << tempBank.BankId << "\n";
			cout << "name = " << tempBank.BankName << "\n";
			cout << "address = " << tempBank.Address << "\n";
			cout << "\n";
		}


		cout << "Enter 1 to go back:  ";
		cin >> tempPos;

		if (tempPos == 1) {
			system("cls");
			bankPanel();
		}
		break;
	case 6:
		cout << "Enter the banks Id for search:  ";
		cin >> tempId;
		tempBank = bankClass.searchById(tempId);
		if (tempBank.BankId == -1) {
			cout << "\n";
			cout << "Bank not found";
			cout << "\n";
		}
		else {
			cout << "\n";
			cout << "Id = " << tempBank.BankId << "\n";
			cout << "name = " << tempBank.BankName << "\n";
			cout << "address = " << tempBank.Address << "\n";
			cout << "\n";
		}


		cout << "Enter 1 to go back:  ";
		cin >> tempPos;

		if (tempPos == 1) {
			system("cls");
			bankPanel();
		}
		break;
	case 7:
		system("cls");
		managerPanel();
		break;
	default:
		break;
	}

}

void bankBranchPanel() {

	BankBranchClass bankBranchClass;
	BankClass bankClass;
	int selectedPos = 0;
	cout << endl;
	cout << "                                                    BankBranch Panel                                                   " << endl;
	cout << " ===================================================================================================================== " << endl;
	cout << "                         |  Add  |  Delete  |  Edit  |  Read All  |  search by id  |  back  |                          " << endl;
	cout << "                         |   1   |    2     |    3   |     4      |       5        |   6    |                          " << endl;
	cout << "                         --------------------------------------------------------------------                          " << endl;

	cout << " What do you want to work with?  ";
	cin >> selectedPos;


	int tempPos = 0;
	int tempId;
	int tempBankID;
	string tempBranchAddress, tempRes;
	BankBranch tempBankBranch;

	switch (selectedPos) {
	case 1:
		cout << "Enter branchs address:  ";
		cin >> tempBranchAddress;
		cout << "Enter branchs bankID:  ";
		cin >> tempBankID;

		while (bankClass.searchById(tempBankID).BankId == -1) {
			cout << "\nBank did not found. \n";
			cout << "\nEnter new branchs bankID:  ";
			cin >> tempBankID;
		}

		bankBranchClass.add(tempBranchAddress, tempBankID);
		system("cls");
		cout << "\nBranch added. \n";
		bankBranchPanel();
		break;

	case 2:
		cout << "Enter the branch ID tp delete:  ";
		cin >> tempId;
		tempBankBranch = bankBranchClass.searchById(tempId);
		tempRes = bankBranchClass.deletef(tempBankBranch);
		system("cls");
		cout << tempRes + " \n";
		bankBranchPanel();
		break;

	case 3:
		cout << "\n";
		cout << "Enter id of the branch you want to edit:  ";
		cin >> tempId;

		cout << "Enter the new address : ";
		cin >> tempBranchAddress;
		cout << "Enter the new bank id : ";
		cin >> tempBankID;

		while (bankClass.searchById(tempBankID).BankId == -1) {
			cout << "\nBank did not found. \n";
			cout << "\nEnter new bankID:  ";
			cin >> tempBankID;
		}

		tempRes = bankBranchClass.edit(tempId, tempBranchAddress, tempBankID);
		system("cls");
		cout << tempRes + " \n";
		bankBranchPanel();
		break;

	case 4:
		system("cls");
		bankBranchClass.getAll();

		cout << "Enter 1 to go back:  ";
		cin >> tempPos;

		if (tempPos == 1) {
			system("cls");
			bankBranchPanel();
		}
		break;

	case 5:
		cout << "Enter the branch Id for search:  ";
		cin >> tempId;
		tempBankBranch = bankBranchClass.searchById(tempId);
		if (tempBankBranch.BranchId == -1) {
			cout << "\n";
			cout << "Branch not found";
			cout << "\n";
		}
		else {
			cout << "\n";
			cout << "Id = " << tempBankBranch.BranchId << "\n";
			cout << "Address = " << tempBankBranch.BranchAddress << "\n";
			cout << "BankId = " << tempBankBranch.BankId << "\n";
			cout << "\n";
		}


		cout << "Enter 1 to go back:  ";
		cin >> tempPos;

		if (tempPos == 1) {
			system("cls");
			bankBranchPanel();
		}
		break;


	case 6:
		system("cls");
		managerPanel();
		break;
	default:

		break;
	}
}

void CustomerPanel() {

	CustomerClass customerClass;
	int selectedPos = 0;
	cout << endl;
	cout << "                                                     Customer Panel                                                    " << endl;
	cout << " ===================================================================================================================== " << endl;
	cout << "                |  Add  |  Delete  |  Edit  |  Read All  |  search by name  |  search by id  |  back  |                " << endl;
	cout << "                |   1   |    2     |    3   |     4      |        5         |        6       |   7    |                " << endl;
	cout << "                ---------------------------------------------------------------------------------------                " << endl;

	cout << " What do you want to work with?  ";
	cin >> selectedPos;


	int tempPos = 0;
	int tempId;
	string tempName, tempPhone, tempAddress, tempRes;
	Customer tempCustomer;

	switch (selectedPos) {
	case 1:
		cout << "Enter customers name:  ";
		cin >> tempName;
		cout << "Enter customers phone:  ";
		cin >> tempPhone;
		cout << "Enter customers address:  ";
		cin >> tempAddress;


		customerClass.add(tempName, tempPhone, tempAddress);
		system("cls");
		cout << "\nCustomer added. \n";
		CustomerPanel();
		break;

	case 2:
		cout << "Enter the customer ID to delete:  ";
		cin >> tempId;
		tempCustomer = customerClass.searchById(tempId);
		tempRes = customerClass.deletef(tempCustomer);
		system("cls");
		cout << tempRes + " \n";
		CustomerPanel();
		break;

	case 3:
		cout << "\n";
		cout << "Enter id of the customer you want to edit:  ";
		cin >> tempId;

		cout << "Enter the new name : ";
		cin >> tempName;
		cout << "Enter the new phone : ";
		cin >> tempPhone;
		cout << "Enter the new address : ";
		cin >> tempAddress;

		tempRes = customerClass.edit(tempId, tempName, tempPhone, tempAddress);
		system("cls");
		cout << tempRes + " \n";
		CustomerPanel();
		break;

	case 4:
		system("cls");
		customerClass.getAll();

		cout << "Enter 1 to go back:  ";
		cin >> tempPos;

		if (tempPos == 1) {
			system("cls");
			CustomerPanel();
		}
		break;

	case 5:
		cout << "Enter the customer Name for search:  ";
		cin >> tempName;
		tempCustomer = customerClass.searchByName(tempName);
		if (tempCustomer.CustId == -1) {
			cout << "\n";
			cout << "customer not found";
			cout << "\n";
		}
		else {
			cout << "\n";
			cout << "Id = " << tempCustomer.CustId << "\n";
			cout << "Name = " << tempCustomer.Name << "\n";
			cout << "Phone = " << tempCustomer.Phone << "\n";
			cout << "Address = " << tempCustomer.Address << "\n";
			cout << "\n";
		}


		cout << "Enter 1 to go back:  ";
		cin >> tempPos;

		if (tempPos == 1) {
			system("cls");
			CustomerPanel();
		}
		break;
	case 6:
		cout << "Enter the customer Id for search:  ";
		cin >> tempId;
		tempCustomer = customerClass.searchById(tempId);
		if (tempCustomer.CustId == -1) {
			cout << "\n";
			cout << "customer not found";
			cout << "\n";
		}
		else {
			cout << "\n";
			cout << "Id = " << tempCustomer.CustId << "\n";
			cout << "Name = " << tempCustomer.Name << "\n";
			cout << "Phone = " << tempCustomer.Phone << "\n";
			cout << "Address = " << tempCustomer.Address << "\n";
			cout << "\n";
		}


		cout << "Enter 1 to go back:  ";
		cin >> tempPos;

		if (tempPos == 1) {
			system("cls");
			CustomerPanel();
		}
		break;


	case 7:
		system("cls");
		managerPanel();
		break;
	default:

		break;
	}
}

void AccountPanel() {

	AccountClass accountClasss;
	CustomerClass customerClass;
	BankBranchClass branchClass;
	Cust_AccClass cust_accClass;
	int selectedPos = 0;
	cout << endl;
	cout << "                                                     Account Panel                                                    " << endl;
	cout << " ===================================================================================================================== " << endl;
	cout << "                          |  Add  |  Delete  |  Edit  |  Read All  |  search by id  |  back  |                         " << endl;
	cout << "                          |   1   |    2     |    3   |     4      |       5        |   6    |                         " << endl;
	cout << "                          --------------------------------------------------------------------                         " << endl;

	cout << " What do you want to work with?  ";
	cin >> selectedPos;


	int tempPos = 0;
	int tempId, tempBalance, tempBranchId, tempCustomerId;
	string tempType, tempDate, tempRes;
	Account tempAccount;
	Cust_ACC cust_acc;
	ostringstream oss;


	switch (selectedPos) {
	case 1:
		cout << "Enter customers ID:  ";
		cin >> tempCustomerId;
		while (customerClass.searchById(tempCustomerId).CustId == -1) {
			cout << "\nCustomer did not found. \n";
			cout << "\nEnter customers ID:  ";
			cin >> tempCustomerId;
		}

		cout << "Enter accounts type:  ";
		cin >> tempType;
		cout << "Enter accounts balance:  ";
		cin >> tempBalance;

		while (tempBalance < 1000) {
			cout << "\nAccounts balance must be atleast 1000. \n";
			cout << "\nEnter accounts balance:  ";
			cin >> tempBalance;
		}

		cout << "Enter accounts branch ID:  ";
		cin >> tempBranchId;

		while (branchClass.searchById(tempBranchId).BranchId == -1) {
			cout << "\nBranch did not found. \n";
			cout << "\nEnter accounts branch ID:  ";
			cin >> tempBranchId;
		}

		tempId = accountClasss.add(tempType, tempBalance, tempBranchId);



		cust_accClass.add(CurrentDate(), tempCustomerId, tempId);

		system("cls");
		cout << "\nAccount added. \n";
		AccountPanel();
		break;

	case 2:
		cout << "Enter the account ID to delete:  ";
		cin >> tempId;
		tempAccount = accountClasss.searchById(tempId);
		tempRes = accountClasss.deletef(tempAccount);
		while (cust_accClass.searchByaId(tempId).AccId != -1) {
			cust_acc = cust_accClass.searchByaId(tempId);
			cust_accClass.deletef(cust_acc);
		}
		system("cls");
		cout << tempRes + " \n";
		AccountPanel();
		break;

	case 3:
		cout << "\n";
		cout << "Enter id of the Account you want to edit:  ";
		cin >> tempId;

		cout << "Enter new customers ID:  ";
		cin >> tempCustomerId;
		while (customerClass.searchById(tempCustomerId).CustId == -1) {
			cout << "\nCustomer did not found. \n";
			cout << "\nEnter new customers ID:  ";
			cin >> tempCustomerId;
		}

		cout << "Enter new accounts type:  ";
		cin >> tempType;
		cout << "Enter new accounts balance:  ";
		cin >> tempBalance;


		while (tempBalance < 1000) {
			cout << "\nAccounts balance must be atleast 1000. \n";
			cout << "\nEnter new accounts balance:  ";
			cin >> tempBalance;
		}

		cout << "Enter new accounts branch ID:  ";
		cin >> tempBranchId;

		while (branchClass.searchById(tempBranchId).BranchId == -1) {
			cout << "\nBranch did not found. \n";
			cout << "\nEnter new accounts branch ID:  ";
			cin >> tempBranchId;
		}

		tempRes = accountClasss.edit(tempId, tempType, tempBalance, tempBranchId);


		while (cust_accClass.searchByaId(tempId).AccId != -1) {
			cust_acc = cust_accClass.searchByaId(tempId);
			cust_accClass.editcId(cust_acc, tempCustomerId);
		}



		system("cls");
		cout << tempRes + " \n";
		AccountPanel();
		break;

	case 4:
		system("cls");
		accountClasss.getAll();

		cout << "Enter 1 to go back:  ";
		cin >> tempPos;

		if (tempPos == 1) {
			system("cls");
			AccountPanel();
		}
		break;

	case 5:
		cout << "Enter the customer Id for search:  ";
		cin >> tempId;
		tempAccount = accountClasss.searchById(tempId);
		if (tempAccount.AccId == -1) {
			cout << "\n";
			cout << "Account not found";
			cout << "\n";
		}
		else {
			cout << "\n";
			cout << "Id = " << tempAccount.AccId << "\n";
			cout << "Type = " << tempAccount.AccType << "\n";
			cout << "Balance = " << tempAccount.Balance << "\n";
			cout << "Branch id = " << tempAccount.BranchId << "\n";
			cout << "\n";
		}


		cout << "Enter 1 to go back:  ";
		cin >> tempPos;

		if (tempPos == 1) {
			system("cls");
			AccountPanel();
		}
		break;
	case 6:
		system("cls");
		managerPanel();
		break;
	default:

		break;
	}
}

void LoanPanel() {

	LoanClass loanClass;
	CustomerClass customerClass;
	BankBranchClass branchClass;
	Cust_LoansClass cust_loanClass;
	int selectedPos = 0;
	cout << endl;
	cout << "                                                       Loan Panel                                                      " << endl;
	cout << " ===================================================================================================================== " << endl;
	cout << "                          |  Add  |  Delete  |  Edit  |  Read All  |  search by id  |  back  |                         " << endl;
	cout << "                          |   1   |    2     |    3   |     4      |       5        |   6    |                         " << endl;
	cout << "                          --------------------------------------------------------------------                         " << endl;

	cout << " What do you want to work with?  ";
	cin >> selectedPos;


	int tempPos = 0;
	int tempId, tempAmount, tempBranchId, tempCustomerId;
	string tempType, tempDate, tempRes;
	Loan tempLoan;
	Cust_Loan cust_loan;
	ostringstream oss;


	switch (selectedPos) {
	case 1:
		cout << "Enter customers ID:  ";
		cin >> tempCustomerId;
		while (customerClass.searchById(tempCustomerId).CustId == -1) {
			cout << "\nCustomer did not found. \n";
			cout << "\nEnter customers ID:  ";
			cin >> tempCustomerId;
		}

		cout << "Enter loans type:  ";
		cin >> tempType;
		cout << "Enter loans amount:  ";
		cin >> tempAmount;


		cout << "Enter loans branch ID:  ";
		cin >> tempBranchId;

		while (branchClass.searchById(tempBranchId).BranchId == -1) {
			cout << "\nBranch did not found. \n";
			cout << "\nEnter loans branch ID:  ";
			cin >> tempBranchId;
		} 

		while (loanClass.searchByBranchId(tempBranchId).LoanId != -1) {
			cout << "\nThis customer already has a loan in this branch . \n";
			cout << "\nEnter another branch ID:  ";
			cin >> tempBranchId;
		}


		tempId = loanClass.add(tempType, tempAmount, tempBranchId);



		cust_loanClass.add(CurrentDate(), tempCustomerId, tempId);

		system("cls");
		cout << "\nLoan added. \n";
		LoanPanel();
		break;

	case 2:
		cout << "Enter the loan ID to delete:  ";
		cin >> tempId;
		tempLoan = loanClass.searchById(tempId);
		tempRes = loanClass.deletef(tempLoan);
		while (cust_loanClass.searchBylId(tempId).CustId != -1) {
			cust_loan = cust_loanClass.searchBylId(tempId);
			cust_loanClass.deletef(cust_loan);
		}
		system("cls");
		cout << tempRes + " \n";
		LoanPanel();
		break;

	case 3:
		cout << "\n";
		cout << "Enter id of the loan you want to edit:  ";
		cin >> tempId;

		cout << "Enter new customers ID:  ";
		cin >> tempCustomerId;
		while (customerClass.searchById(tempCustomerId).CustId == -1) {
			cout << "\nCustomer did not found. \n";
			cout << "\nEnter new customers ID:  ";
			cin >> tempCustomerId;
		}

		cout << "Enter new loans type:  ";
		cin >> tempType;
		cout << "Enter new loans amount:  ";
		cin >> tempAmount;


		cout << "Enter new loans branch ID:  ";
		cin >> tempBranchId;

		while (branchClass.searchById(tempBranchId).BranchId == -1) {
			cout << "\nBranch did not found. \n";
			cout << "\nEnter new loans branch ID:  ";
			cin >> tempBranchId;
		}


		while (loanClass.searchByBranchId(tempBranchId).LoanId != -1) {
			cout << "\nThis customer already has a loan in this branch . \n";
			cout << "\nEnter another branch ID:  ";
			cin >> tempBranchId;
		}

		tempRes = loanClass.edit(tempId, tempType, tempAmount, tempBranchId);


		while (cust_loanClass.searchBylId(tempId).LoanId != -1) {
			cust_loan = cust_loanClass.searchBylId(tempId);
			cust_loanClass.editcId(cust_loan, tempCustomerId);
		}



		system("cls");
		cout << tempRes + " \n";
		LoanPanel();
		break;

	case 4:
		system("cls");
		loanClass.getAll();

		cout << "Enter 1 to go back:  ";
		cin >> tempPos;

		if (tempPos == 1) {
			system("cls");
			LoanPanel();
		}
		break;

	case 5:
		cout << "Enter the loans Id for search:  ";
		cin >> tempId;
		tempLoan = loanClass.searchById(tempId);
		if (tempLoan.LoanId == -1) {
			cout << "\n";
			cout << "Loan not found";
			cout << "\n";
		}
		else {
			cout << "\n";
			cout << "Id = " << tempLoan.LoanId << "\n";
			cout << "Type = " << tempLoan.LoanType << "\n";
			cout << "Amount = " << tempLoan.Amount << "\n";
			cout << "Branch id = " << tempLoan.BranchID << "\n";
			cout << "\n";
		}


		cout << "Enter 1 to go back:  ";
		cin >> tempPos;

		if (tempPos == 1) {
			system("cls");
			LoanPanel();
		}
		break;
	case 6:
		system("cls");
		managerPanel();
		break;
	default:

		break;
	}
}

void managerPanel() {
	int selectedPos = 0;
	cout << endl;
	cout << "                                                     Manager Panel                                                     " << endl;
	cout << " ===================================================================================================================== " << endl;
	cout << "                            |  Bank  |  Branch  |  Customer  |  Account  |  Loan  |  back  |                           " << endl;
	cout << "                            |   1    |    2     |      3     |     4     |   5    |    6   |                           " << endl;
	cout << "                            ----------------------------------------------------------------                           " << endl;
	cout << " What do you want to work with?  ";
	cin >> selectedPos;
	switch (selectedPos) {
	case 1:
		system("cls");
		bankPanel();
		break;
	case 2:
		system("cls");
		bankBranchPanel();
		break;
	case 3:
		system("cls");
		CustomerPanel();
		break;
	case 4:
		system("cls");
		AccountPanel();
		break;
	case 5:
		system("cls");
		LoanPanel();
		break;
	case 6:
		break;
	default:
		break;
	}
}

void userPanel() {
	cout << "user panel";
}

void login() {

	string username, password;
	cout << "                                                        Login                                                          " << endl;
	cout << " ===================================================================================================================== " << endl;
	cout << "Enter your username: ";
	cin >> username;

	cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "Enter your password: ";
	cin >> password;

	system("cls");

	if (username == "Admin" && password == "12345") {
		system("cls");
		managerPanel();

	}
	else if (username == "User" && password == "54321") {
		system("cls");
		userPanel();
	}
	else {
		cout << "Login info is incurrect.";
	}
}

void main() {

	login();
}

