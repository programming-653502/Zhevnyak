#include "stdafx.h"
#include <ctime>
#include <cstdio>
#include <iostream>
#include <conio.h>
#include <string>
#include <locale>
#include <windows.h>
#include <vector>

#define lint long long

using namespace std;

//////////////////////////////// S T R U C T U R E S //////////////////////////////////////

struct product {
	lint id;
	char name[80];
	lint clientId;
	double cost;
	double pledge;
	time_t delivered;
};

struct client {
	lint id;
	char name[80];
	lint passportSerialNum;
	time_t regestrationDate;
};


/////////////////////////////// F U N C T I O N S ////////////////////////////////////////////

void menu(vector<product> &products, vector<client> &clients);
void showProducts(vector<product> &products);
void showClients(vector<client> &clients);
void saveChanges(vector<product> &products, vector<client> &clients);
void loadInfo(vector<product> &products, vector<client> &clients);
void addProduct(vector<product> &products, int id = -1);
void deleteProduct(vector<product> &product, int id);
void addClient(vector<client> &clients, int id = -1);
void deleteClient(vector<client> &clients, int id);
void getRevenue(vector<product> &products);
void getTotalPriceOfProducts(vector<product> &products);

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	vector<product> productsVect;
	vector<client> clientsVect;
	int pSize, cSize;
	loadInfo(productsVect, clientsVect);

	menu(productsVect, clientsVect);
    return 0;
}

void menu(vector<product> &products, vector<client> &clients) {

	char choice;
	bool finished = false;

	while (!finished) {
		system("cls");
		cout << "\t\t\tÄîáðî ïîæàëîâàòü â Ëîìáàðä.èíê" << endl << endl;
		cout << "1. Ïðîñìîòð õðàíèìûõ òîâàðîâ" << endl;
		cout << "2. Ïðîñìîòð ñïèñêà êëèåíòîâ" << endl;
		cout << "3. Ñîõðàíèòü èçìåíåíèÿ" << endl;
		cout << "4. Âû÷èñëèòü ïðèáûëü ëîìáàðäà" << endl;
		cout << "5. Âû÷èñëèòü ñòîèìîñòü âñåõ òîâàðîâ ëîìáàðäà" << endl;
		cout << "6. Âûõîä èç ïðîãðàììû" << endl;

		choice = _getch();

		switch (choice) {
		case '1':
			showProducts(products);
			break;
		case '2':
			showClients(clients);
			break;
		case '3':
			saveChanges(products, clients);
			break;
		case '4':
			getRevenue(products);
			break;
		case '5':
			getTotalPriceOfProducts(products);
			break;
		case '6':
			saveChanges(products, clients);
			finished = true;
			break;
		}
	}
}

void loadInfo(vector<product> &products, vector<client> &clients) {
	FILE * pFile, * cFile;
	long pSize, cSize;

	pFile = fopen("products.bin", "rb");

	// obtain file size:
	fseek(pFile, 0, SEEK_END);
	pSize = ftell(pFile) / sizeof(product);
	rewind(pFile);

	// copy the file into the buffer:
	for (int i = 0; i < pSize; i++) {
		product* newProduct = new product;
		fread(newProduct, sizeof(product), 1, pFile);
		products.push_back(*newProduct);
	}
	
	fclose(pFile);

	cFile = fopen("clients.bin", "rb");

	fseek(cFile, 0, SEEK_END);
	cSize = ftell(cFile) / sizeof(client);
	rewind(cFile);

	for (int i = 0; i < cSize; i++) {
		client* newClient = new client;
		fread(newClient, sizeof(client), 1, cFile);
		clients.push_back(*newClient);
	}

	fclose(cFile);
}

void showProducts(vector<product> &products) {

	char choice;
	bool finished = false;

	while (!finished) {
		system("cls");
		cout << "\t1. Äîáàâèòü\t2. Ðåäàêòèðîâàòü\t3. Óäàëèòü\t4. Âåðíóòüñÿ" << endl << endl;

		cout << "id\tÒîâàð\t\tid Êëèåíòà\tÖåíà\tÇàëîã\tÄàòà ñäà÷è" << endl;
		cout << "----------------------------------------------------------------------" << endl;

		for (int i = 0; i < products.size(); i++) {
			cout << products[i].id << "\t" << products[i].name << "\t" << products[i].clientId << "\t\t" << products[i].cost << "\t" << products[i].pledge << "\t" << ctime(&products[i].delivered);
		}

		choice = _getch();

		int id;

		switch (choice) {
		case '1':
			addProduct(products);
			break;
		case '2':
			system("cls");
			cout << "Ââåäèòå id òîâàðà, êîòîðûé õîòèòå èçìåíèòü: ";
			cin >> id;
			cin.ignore(65536, '\n');
			cin.clear();
			addProduct(products, id);
			break;
		case '3' :
			system("cls");
			cout << "Ââåäèòå id òîâàðà, êîòîðûé õîòèòå óäàëèòü: ";
			cin >> id;
			cin.ignore(65536, '\n');
			cin.clear();
			deleteProduct(products, id);
			break;
		case '4':
			finished = true;
			break;
		}
	}
}

void addProduct(vector<product> &products, int id) {
	if (id <= 0) {
		id = products.size();
		lint newId = !id ? 1 : products[id - 1].id + 1; 
		product newProduct{ newId, "", 0, 0, 0, time(NULL)};
		products.push_back(newProduct);
	}
	else {
		bool changed = false;
		for (int i = 0; i < products.size(); i++) {
			if (products[i].id == id) {
				id = i;
				changed = true;
				break;
			}
		}
		if (!changed) {
			cout << "íåâåðíûé id";
			_getch();
			return;
		}
	}

	char buffer[80];

	cout << "Ââåäèòå íàçâàíèå òîâàðà: "; gets_s(products[id].name, 79);
	cout << "Ââåäèòå id êëèåíòà: "; cin >> products[id].clientId;
	cout << "Ââåäèòå öåíó òîâàðà: "; cin >> products[id].cost;
	cout << "Ââåäèòå çàëîã: "; cin >> products[id].pledge;

	cin.ignore(65536, '\n');
	cin.clear();

	cout << "\nÒîâàð äîáàâëåí.";
	_getch();
}


void saveChanges(vector<product> &products, vector<client> &clients) {
	FILE *pFile, *cFile;

	pFile = fopen("products.bin", "wb");
	for (int i = 0; i < products.size(); i++) {
		fwrite(&products[i], sizeof(product), 1, pFile);
	}
	fclose(pFile);

	cFile = fopen("clients.bin", "wb");
	for (int i = 0; i < clients.size(); i++) {
		fwrite(&clients[i], sizeof(client), 1, cFile);
	}
	fclose(cFile);
}

void deleteProduct(vector<product> &products, int id) {
	bool changed = false;
	for (int i = 0; i < products.size(); i++) {
		if (products[i].id == id) {
			products.erase(products.begin() + i);
			changed = true;
			break;
		}
	}
	if (!changed) cout << "Íåò òàêîãî ýëåìåíòà";
	else cout << "Óäàëåíî";
	_getch();
}

void showClients(vector<client> &clients) {
	char choice;
	bool finished = false;

	while (!finished) {
		system("cls");
		cout << "\t1. Äîáàâèòü\t2. Ðåäàêòèðîâàòü\t3. Óäàëèòü\t4. Âåðíóòüñÿ" << endl << endl;

		cout << "id\tÔÈÎ\t\t\tÍîìåð ïàñïîðòà\tÄàòà ðåãèñòðàöèè" << endl;
		cout << "----------------------------------------------------------------------" << endl;

		for (int i = 0; i < clients.size(); i++) {
			cout << clients[i].id << "\t" << clients[i].name << "\t" << clients[i].passportSerialNum << "\t\t" << ctime(&clients[i].regestrationDate);
		}

		choice = _getch();

		int id;

		switch (choice) {
		case '1':
			addClient(clients);
			break;
		case '2':
			system("cls");
			cout << "Ââåäèòå id êëèåíòà, êîòîðîãî õîòèòå èçìåíèòü: ";
			cin >> id;
			cin.ignore(65536, '\n');
			cin.clear();
			addClient(clients, id);
			break;
		case '3':
			system("cls");
			cout << "Ââåäèòå id êëèåíòà, êîòîðîãî õîòèòå óäàëèòü: ";
			cin >> id;
			cin.ignore(65536, '\n');
			cin.clear();
			deleteClient(clients, id);
			break;
		case '4':
			finished = true;
			break;
		}
	}
}

void addClient(vector<client> &clients, int id) {
	if (id <= 0) {
		id = clients.size();
		lint newId = !id ? 1 : clients[id - 1].id + 1;
		client newClient{ newId, "", 0, time(NULL) };
		clients.push_back(newClient);
	}
	else {
		bool changed = false;
		for (int i = 0; i < clients.size(); i++) {
			if (clients[i].id == id) {
				id = i;
				changed = true;
				break;
			}
		}
		if (!changed) {
			cout << "íåâåðíûé id";
			_getch();
			return;
		}
	}

	cout << "Ââåäèòå ÔÈÎ êëèåíòà: "; gets_s(clients[id].name, 79);
	cout << "Ââåäèòå íîìåð ïàñïîðòà êëèåíòà: "; cin >> clients[id].passportSerialNum;

	cin.ignore(65536, '\n');
	cin.clear();

	cout << "\nÊëèåíò äîáàâëåí.";
	_getch();
}


void deleteClient(vector<client> &clients, int id) {
	bool changed = false;
	for (int i = 0; i < clients.size(); i++) {
		if (clients[i].id == id) {
			clients.erase(clients.begin() + i);
			changed = true;
			break;
		}
	}
	if (!changed) cout << "Íåò òàêîãî ýëåìåíòà";
	else cout << "Óäàëåíî";
	_getch();
}

void getRevenue(vector<product> &products) {
	system("cls");

	int sum = 0;
	for (int i = 0; i < products.size(); i++) {
		sum += products[i].cost - products[i].pledge;
	}

	cout << "Ðàññ÷åòíàÿ ïðèáûëü ëîìáàðäà: " << sum;
	_getch();
}

void getTotalPriceOfProducts(vector<product> &products) {
	system("cls");

	int sum = 0;
	for (int i = 0; i < products.size(); i++) {
		sum += products[i].cost;
	}

	cout << "Îöåíî÷íàÿ ñòîèìîñòü âñåõ òîâàðîâ ëîìáàðäà: " << sum;
	_getch();
}
