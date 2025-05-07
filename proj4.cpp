#include <iostream>
using namespace std;
typedef long long ll;

class Client {
    ll phone;
    string name;

    bool isEmpty() {
        return phone == 0;
    }

    public:
    Client() {
        phone = 0;
        name = "----";
    }

    Client(string name, ll phone) {
        this->name = name;
        this->phone = phone;
    }

    void printDetails() {
        cout.width(20);
        cout << name << " ";
        cout.width(20);
        cout << phone << endl;
    }

    friend class HashTable;
};

class HashTable {
    int tablesize;
    Client *clients;

    int hashFunction(string clientname) {
        int sum = 0;
        for(int ch : clientname) {
            sum += (int)ch;
        }
        return sum % tablesize;
    }

    bool isOriginal(int index) {
        return hashFunction(clients[index].name) == index; 
    }

    public:
    
    HashTable(int size) {
        tablesize = size;
        clients = new Client[tablesize];
    }

    //Initialize the whole clients array with default name and phone number (---- and 0)
    void createTable() {
        for(int i=0; i<tablesize; i++) {
            clients[i] = Client();      //imp, not new Client()
        }
    }

    void insertClientWORepl(Client newClient) {
        int index = hashFunction(newClient.name);
        
        //if empty, insert directly
        if(clients[index].isEmpty()) {
            clients[index] = newClient;
            return;
        }
        else {
            int currIndex = index;
            while(!clients[currIndex].isEmpty()) {
                currIndex = (currIndex + 1) % tablesize;
            }
            //insert into empty location
            clients[currIndex] = newClient;
        }
    }

    void insertClientWRepl(Client newClient) {
        int index = hashFunction(newClient.name);

        if(clients[index].isEmpty()) {
            clients[index] = newClient;
        }
        else {
            //Not empty
            int currIndex = index;

            //Check if element actually belongs on that index
            if(isOriginal(index)) {
               currIndex = index;
               while(!clients[currIndex].isEmpty()) {
                    currIndex = (currIndex + 1) % tablesize;
                } 
                clients[currIndex] = newClient;
            }
            else {
                //if not then store the existing client and put the newClient on its place. Linear probe for the next client.
                Client existingClient = clients[index];
                clients[index] = newClient;
                while(!clients[currIndex].isEmpty()) {
                    currIndex = (currIndex + 1) % tablesize;
                }
                clients[currIndex] = existingClient;
            }
        }

    }

    bool search(string clientname) {
        int index = hashFunction(clientname);
        //check if client exists on the index location
        if(clients[index].name == clientname) {
            cout << "Client exists";
            return true;
        }

        //check for next locations (might be there because of probing)
        int currIndex = index;
        int pass = 0;

        while(clients[currIndex].name != clientname && pass < tablesize) {
            currIndex = (currIndex + 1) % tablesize;
            pass++;
        }
        
        if(pass == tablesize) {
            cout << "Client not found" << endl;
            return false;
        }
        else {
            cout << "Client exists" << endl;
            return true;
        }
    }

    void displayHT() {
        cout.width(10);
        cout << "Client Name  ";
        cout.width(10);
        cout << "Telephone  " << endl;

        for(int i=0; i< this->tablesize; i++) {
            clients[i].printDetails();
        }
    }



};

int main() {
    HashTable table(10);
    table.createTable();
    
    table.insertClientWORepl(Client("abcd", 10002));
    table.insertClientWORepl(Client("zdfg", 10003));
    table.insertClientWORepl(Client("asdf", 10004));
    table.insertClientWORepl(Client("dbca", 10005));
    table.insertClientWORepl(Client("qwer", 10006));
    table.insertClientWORepl(Client("rtyu", 10006));
    table.insertClientWORepl(Client("ergh", 10006));
    table.insertClientWORepl(Client("fghj", 10006));
    table.insertClientWORepl(Client("zasd", 10006));
    table.insertClientWORepl(Client("dfgh", 10006));
    table.displayHT();

    table.search("abcd");
    table.search("zdfg");
    table.search("asdf");
    table.search("dbca");
    table.search("qwer");
    table.search("rtyu");
    table.search("ergh");
    table.search("fghj");
    table.search("zasd");
    table.search("dfgh");

    HashTable table1(10);
    table1.createTable();

    table1.insertClientWRepl(Client("abcd", 10002));
    table1.insertClientWRepl(Client("zdfg", 10003));
    table1.insertClientWRepl(Client("asdf", 10004));
    table1.insertClientWRepl(Client("dbca", 10005));
    table1.insertClientWRepl(Client("qwer", 10006));
    table1.insertClientWRepl(Client("rtyu", 10006));
    table1.insertClientWRepl(Client("ergh", 10006));
    table1.insertClientWRepl(Client("fghj", 10006));
    table1.insertClientWRepl(Client("zasd", 10006));
    table1.insertClientWRepl(Client("dfgh", 10006));
    table1.displayHT();

    table1.search("abcd");
    table1.search("zdfg");
    table1.search("asdf");
    table1.search("dbca");
    table1.search("qwer");
    table1.search("rtyu");
    table1.search("ergh");
    table1.search("fghj");
    table1.search("zasd");
    table1.search("dfgh");
    return 0;
}